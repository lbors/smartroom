#include <Servo.h>

//Servo
Servo s; //cria o objeto servo para controle do servo 
int pos = 0; // variavel de posição do servo

//Sensor ir
int ir_sensor = 8;
int objeto = 0;  

int led = 4;
int teste=13;
boolean controle =false;
   
void setup()  
{
  s.attach(6); //atribui o pino 9 ao servo
  pinMode(8, INPUT); //Pino ligado ao coletor do fototransistor
  pinMode(4, OUTPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);  
}  
   
void loop()  
{  
  motor();
} 

void sensor_ir(){
  objeto = digitalRead(ir_sensor); // realiza a leitura do sensor
  if (objeto == LOW){
    controle=true;
    digitalWrite(led,HIGH);
    }
/*    while(objeto==LOW){
      digitalWrite(led, HIGH);
      //s.write(pos);
      objeto=digitalRead(ir_sensor);
    }
  }*/
  else{
    digitalWrite(led, LOW);
    controle=false;
    }
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
      delay (30);
      for(pos=180; pos>=0; pos--){
        s.write(pos);
        sensor_ir();
        if(controle==true){
           digitalWrite(led,HIGH);
           break;
        }
        else
          digitalWrite(led,LOW);
        delay(30);
      }
    case true:
      s.write(pos);
      break;
  }
/*  for(pos = 0; pos < 180; pos++)
  {
    s.write(pos);
    sensor_ir();
  delay(30);
  }
delay(30);
  for(pos = 180; pos >= 0; pos--)
  {
    s.write(pos);
    sensor_ir();
    delay(30);
  }*/
}
