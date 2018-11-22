
//Sensor LDR
int ldrPin = A3;
float valorLDR = 0;

//Sensor IR
int irPin = 8;
int objeto = 0;
float luminosidade = 0;

//Sensor Temperatura
#include <DHT.h>
#define DHTPin A1
#define DHTTYPE DHT11
DHT dht(DHTPin, DHTTYPE);
float t = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ldrPin, INPUT);
  pinMode(irPin, INPUT);
  dht.begin();
}

void loop() {
  sensor_ldr();
  delay(1500);
  sensor_ir();
  delay(1500);
  sensor_temp();
  delay(1500);
}


void sensor_ldr(){ 
  valorLDR = analogRead(ldrPin);
  luminosidade = map(valorLDR, 0, 1023, 0, 255);
  //Serial.print("Valor lido do LDR: ");
  //Serial.println(valorLDR);
  Serial.print("Luminosidade: ");
  Serial.println(luminosidade);
}

void sensor_ir(){
  objeto = digitalRead(irPin);
  Serial.print("Sensor de Infravermelho ");
  if (objeto == HIGH){
    Serial.println("não encontrou nada");
  }
  else{
    Serial.println("encontrou um objeto próximo");
  }
}

void sensor_temp(){
  t = dht.readTemperature();
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" *C");
  Serial.println("---------------------------");
}
