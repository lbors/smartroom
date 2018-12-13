//Contagem de Tempo
long previousMillis = 0;
long interval = 10000;

//PIR
int pirPin = A5;   //Analogico A5 para o sensor
int val_pir = 0;

// LDR e Led
int ledPin = 5;
int ldrPin = A3;
int valorLDR = 0;
float luminosidade = 0;

// DHT e Motor DC
#include <DHT.h>
#define DHTPin A1
#define DHTTYPE DHT11
DHT dht(DHTPin, DHTTYPE);
int motorPin = 3;
int rotacao = 0;

// Servo e IR
#include <Servo.h>
Servo s; //cria o objeto servo para controle do servo
int pos = 20;
int pos_def = 0; // variavel de posição do servo
boolean ida = true;
boolean volta, controle = false;

//int ir_sensor = 8;
int objeto = 0;
int buttonPin = 12;
//int buttonState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);

  Serial.println("DHTxx test!");
  dht.begin();
  pinMode(motorPin, OUTPUT);

  s.attach(6); //atribui o pino 6 ao servo
  
//  pinMode(ir_sensor, INPUT); //Pino ligado ao coletor do fototransistor

  pinMode(buttonPin, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  val_pir = analogRead(pirPin); 
  
  if(val_pir > 100){
    previousMillis = currentMillis;
    Serial.println("PIR DETECTOU");
    liga();
  }else{
    if(currentMillis - previousMillis > interval){
      previousMillis = currentMillis;
      liga();
    }else{
    desliga();
    Serial.println("PIR NÂO DETECTOU, sistema desligou");
    }
  }
  delay(1000);
}

void liga(){
  intensidade_led();
  temp();
  motor();
  Serial.println("---------------------------");
}

void desliga(){
  analogWrite(ledPin, LOW);
  digitalWrite(motorPin, LOW);
}

void intensidade_led() {
  valorLDR = analogRead(ldrPin);
  luminosidade = map(valorLDR, 600, 1023, 0, 255); // Converte valor lido do LDR para ajustar a luminosidade do led
  Serial.print("Valor lido do LDR: ");
  Serial.print(valorLDR);
  Serial.print(" = Luminosidade: ");
  Serial.println(luminosidade);

  if (luminosidade < 30.00)
    analogWrite(ledPin, LOW);
  else
    analogWrite(ledPin, luminosidade);
}

void temp() {
  float t = dht.readTemperature();
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" *C");
  
  rotacao = map(t, 16, 35, 0, 255);
  digitalWrite(motorPin, rotacao);
  Serial.print("Motor com rotacao: ");
  Serial.println(rotacao);
}
//*
void sensor_ir() {
//  objeto = digitalRead(ir_sensor); // realiza a leitura do sensor
  objeto = digitalRead(buttonPin);
  if (objeto == HIGH) {
    controle = true;
    Serial.println("IR Detectado");
  }
  else
    controle = false;
}

void motor() {
  if (ida == true) {
    for (pos = pos_def; pos < 100; pos++) {
      s.write(pos);
      sensor_ir();
      if (controle == true) {
        pos_def = pos;
        Serial.println("Vai parar, foi detectado na ida");
        break;
      }
      if (pos == 99 && controle == false) {
        ida = false;
        volta = true;
        Serial.println("Nada detectado na ida");
        pos_def = pos;
      }
      delay(60);
    }
  }

  if (volta == true) {
    for (pos = pos_def; pos >= 5; pos--) {
      s.write(pos);
      sensor_ir();
      if (controle == true) {
        pos_def = pos;
        Serial.println("Vai parar, foi detectado na volta");
        break;
      }
      if (pos == 5 && controle == false) {
        volta = false;
        ida = true;
        Serial.println("Nada detectado na volta");
        pos_def = pos;
      }
      delay(60);
    }
  }
}
//*/
