// Projeto Brilho LED PWM e LDR
 
int ledPin = 11;
int ldrPin = A3;
int valorLDR = 0;
float luminosidade = 0;
//float sinVal;
//int ledVal;
 
void setup() 
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
}
 
void loop() 
{
  intensidade_led();
}

void intensidade_led(){
  
  valorLDR = analogRead(ldrPin);
  luminosidade = map(valorLDR, 0, 1023, 0, 255); // Converte valor lido do LDR para ajustar a luminosidade do led
  Serial.print("Valor lido do LDR: ");
  Serial.print(valorLDR);
  Serial.print(" = Luminosidade: ");
  Serial.println(luminosidade);

  if(luminosidade<83.00)
    analogWrite(ledPin, LOW);
  else
    analogWrite(ledPin, luminosidade);
  delay(500);
 
  }
