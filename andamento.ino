int ledPin = 13;
int pos, pos_def = 0;
boolean teste_sinal = false;
boolean ida, volta = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  
}

void print(){
  Serial.print("Esta na posicao ");
  Serial.println(pos_def);
  }

void sinal(){
  if (Serial.available()){
    switch(Serial.read()){
      case '1':
        teste_sinal == true;
      break;
      case '0':
        teste_sinal == false;
      break;
    }
  }
  }

void contagem(){
  if(ida = true){
    for(pos = pos_def; pos < 180; pos++){
      ida == true;
      print();
      if(teste_sinal == true){
        digitalWrite(ledPin, HIGH);
        break;
        }
      }
    }
   if
}
