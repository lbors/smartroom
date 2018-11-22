// LDR e Led
int ledPin = 11;
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
int pos, pos_def = 0; // variavel de posição do servo
boolean ida = true;
boolean volta, controle = false;

int ir_sensor = 8;
int objeto = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);

  Serial.println("DHTxx test!");
  dht.begin();
  pinMode(motorPin, OUTPUT);

  s.attach(6); //atribui o pino 6 ao servo
  pinMode(8, INPUT); //Pino ligado ao coletor do fototransistor
  pinMode(4, OUTPUT);
}

void loop() {
  intensidade_led();
  temp();
  motor();
  delay(1000);
}

void intensidade_led(){
  valorLDR = analogRead(ldrPin);
  luminosidade = map(valorLDR, 600, 1023, 0, 255); // Converte valor lido do LDR para ajustar a luminosidade do led
  Serial.print("Valor lido do LDR: ");
  Serial.print(valorLDR);
  Serial.print(" = Luminosidade: ");
  Serial.println(luminosidade);

  if(luminosidade<30.00)
    analogWrite(ledPin, LOW);
  else
    analogWrite(ledPin, luminosidade);
}

void temp(){
  float t = dht.readTemperature();
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" *C");
  Serial.println("---------------------------");

  rotacao = map(t, 16, 35, 0,255);
  digitalWrite(motorPin, rotacao);
  Serial.print("Rotacao: ");
  Serial.println(rotacao);
  Serial.println("---------------------------");
}

void sensor_ir(){
  objeto = digitalRead(ir_sensor); // realiza a leitura do sensor
  if (objeto == LOW){
    controle = true;
    Serial.println("Detectado");
  }
  else
    controle = false;
}

void motor(){
  if(ida == true){
    for(pos = pos_def; pos < 180; pos++){
      s.write(pos);
      sensor_ir();
      if(controle == true){
        pos_def = pos;
        Serial.println("Vai parar, foi detectado na ida");
        break;
      }
      if(pos == 179 && controle == false){
        ida = false;
        volta = true;
        Serial.println("Nada detectado na ida");
        pos_def = pos;
      }
      delay(30);
    }
  }
  
  if(volta == true){
    for(pos = pos_def; pos >= 0; pos--){
      s.write(pos);
      sensor_ir();
      if(controle == true){
        pos_def = pos;
        Serial.println("Vai parar, foi detectado na volta");
        break;
      }
      if(pos == 0 && controle == false){
        volta = false;
        ida = true;
        Serial.println("Nada detectado na volta");
        pos_def = pos;
      }
      delay(30);
    }
  }
}
