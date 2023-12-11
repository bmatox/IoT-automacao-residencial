#include "DHT.h"
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "brisa-2413710"; 
const char* password = "pzggcm8t"; 
const char* mqttServer = "broker.hivemq.com"; 
const int mqttPort = 1883; 
const char* mqttUser = ""; 
const char* mqttPassword = ""; 

int pinoDHT = 33;
int pinoVent = 32;
int pinoPIR = 34;

float temp, umid;
int tempoDHT = 0;
int movimento;
bool modoManual = false;

String estadoVent = "off";
String estadoAnterior = "off"; // variável para guardar o estado anterior do ventilador

DHT dht(pinoDHT, DHT11);
WiFiClient espClient; 
PubSubClient clientMqtt(espClient); 

void setup() {
    pinMode(pinoVent, OUTPUT);
    pinMode(pinoPIR, INPUT); 
    Serial.begin(9600);
    dht.begin(); 
    WiFi.begin(ssid, password);     
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print("Tentando se conectar na rede: ");
        Serial.println(ssid);
    }
    Serial.println("Conectado na Rede WiFi.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    clientMqtt.setServer(mqttServer, mqttPort);
    clientMqtt.setCallback(callback);
    while (!clientMqtt.connected()) {
        Serial.println("Conectando ao Broker MQTT...");
        String clientId = "ESP32Client_" + String(random(0xffff), HEX);
        Serial.println("clientId = " + clientId);
        if (clientMqtt.connect(clientId.c_str(), mqttUser, mqttPassword )) { 
            Serial.println("O cliente " + clientId + " foi conectado com sucesso");
            clientMqtt.subscribe("unifor/cps/vent");
        } else {
            int clientState = clientMqtt.state();
            Serial.print("Falha ao se conectar. ");
            Serial.println("Estado do cliente: " + (String) clientState);
            delay(2000);
        }
    }
}

void callback(char* topic, unsigned char* payload, unsigned int length) {
    String strTopic = String(topic);
    String strPayload = "";
    for (int i = 0; i < length; i++) {
        strPayload += (char)payload[i];
    }
    Serial.print("Uma mensagem chegou no tópico: ");
    Serial.println(strTopic);
    Serial.print("Payload: ");
    Serial.println(strPayload); 
    if( strTopic == "unifor/cps/vent") {
        if(strPayload == "on") {
            digitalWrite(pinoVent, HIGH);
            Serial.println("Ventilador ligado!");
            modoManual = true; 
            estadoVent = "on";   
        } else if(strPayload == "off") {
            digitalWrite(pinoVent, LOW);
            Serial.println("Ventilador desligado!");
            modoManual = false; 
            estadoVent = "off";
            delay(10000);
        }
    }
}

void loop() { 
    clientMqtt.loop();
    int tempoAtual = millis();
    if(tempoAtual - tempoDHT >= 2000) {
        temp = dht.readTemperature();
        umid = dht.readHumidity(); 
        tempoDHT = tempoAtual;
    }
    if(isnan(temp) || isnan(umid)) {
        Serial.println("Falha na Leitura do sensor");
    } else {
        Serial.print(temp);
        Serial.print(" C - ");
        Serial.print(umid);
        Serial.println("% UR");
    }
    String payload = (String) temp;
    clientMqtt.publish("unifor/cps/temp", payload.c_str());
    payload = (String) umid;
    clientMqtt.publish("unifor/cps/umid", payload.c_str());  
    movimento = digitalRead(pinoPIR);
    payload = String(movimento); 
    clientMqtt.publish("unifor/cps/pir", payload.c_str()); 
    if(!modoManual) {
        if(temp > 25 && umid < 80 && movimento == HIGH) {
            digitalWrite(pinoVent, HIGH);
            Serial.println("Ventilador ligado!");
            estadoVent = "on";
        } else {
            digitalWrite(pinoVent, LOW);
            Serial.println("Ventilador desligado!");
            estadoVent = "off";
        }
    } else {
        estadoVent = estadoAnterior; // mantém o estado do ventilador igual ao anterior
    }
    if(estadoVent != estadoAnterior) { // só publica o estado do ventilador se ele mudou
        clientMqtt.publish("unifor/cps/vent", estadoVent.c_str());
        estadoAnterior = estadoVent;
    }
    delay(750); 
}
