#include <DHT.h>

#define DHTPin A1
#define DHTTYPE DHT11
DHT dht(DHTPin, DHTTYPE);

int motorPin = 3;
int rotacao = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
  pinMode(motorPin, OUTPUT);
}

void loop(){
  temp();
}

void temp(){
  float t = dht.readTemperature();
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" *C");
  Serial.println("---------------------------");

  rotacao = map(t, 16, 35, 0,255);
  digitalWrite(motorPin, rotacao);
//  digitalWrite(motorPin, HIGH);
/*
  if(t>=28){
    digitalWrite(motorPin, HIGH);
    Serial.println("Entrou");
  }
  else{
    digitalWrite(motorPin, LOW);
    Serial.println("Não entrou");
  }*/
  delay(1000);
}
