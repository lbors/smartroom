#include <Servo.h>

//Servo
Servo s; //cria o objeto servo para controle do servo 
int pos, pos_ant = 0; // variavel de posição do servo


//Sensor ir
int ir_sensor = 8;
int objeto = 0;  

int led = 4;
   
void setup()  
{
  s.attach(6); //atribui o pino 9 ao servo
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
    digitalWrite(led, HIGH);
    controle = true;
  }
  else
    controle = false;
}

void motor_while(){
  
  do
    sensor_ir();
  while(pos<180 && controle == false){
    s.write(pos);
    sensor_ir();
    pos++;
    delay(30);
  }
  delay(30);
  while(pos>=0 && controle == false){
    s.write(pos);
    sensor_ir();
    pos--;
    delay(30);
  }
}

/*
void motor_for(){
  for(pos = 0; pos < 180; pos++)
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
  }
}
*/
