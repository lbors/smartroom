#include <Servo.h>

Servo s; //cria o objeto servo para controle do servo
int pos, pos_def = 0; // variavel de posição do servo
boolean ida = true;
boolean volta, controle = false;

int ir_sensor = 8;
int objeto = 0;
   
void setup()  
{
  s.attach(6); //atribui o pino 6 ao servo
  pinMode(8, INPUT); //Pino ligado ao coletor do fototransistor
  pinMode(4, OUTPUT);
  Serial.begin(9600);  
}  
   
void loop()  
{  
  motor();
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
  switch (controle){
    case false:
      for(pos=0; pos<180; pos++){
        s.write(pos);
        sensor_ir();
        if (controle==true){
          digitalWrite(led,HIGH);
          break;
        }
        else
          digitalWrite(led,LOW);
        delay(30);
        }
      delay (30void motor(){
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
