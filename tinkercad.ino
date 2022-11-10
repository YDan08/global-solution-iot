// C++ code
//
#include <LiquidCrystal.h>

LiquidCrystal lcd(5, 4, A2, A3, A4, A5);

float distancia1,distancia2, duracao;
int livres, ocupadas;

byte pinoTransmissor1=13; 
byte pinoReceptor1=12;

byte pinoTransmissor2=7; 
byte pinoReceptor2=6;

const byte ledVermelho1 = 11;
const byte ledVerde1 = 10;

const byte ledVermelho2 = 9;
const byte ledVerde2 = 8;
void setup()
{
  pinMode(ledVermelho1, OUTPUT);
  pinMode(ledVerde1, OUTPUT);
  pinMode(pinoTransmissor1, OUTPUT);
  pinMode(pinoReceptor1, INPUT);
  pinMode(ledVermelho2, OUTPUT);
  pinMode(ledVerde2, OUTPUT);
  pinMode(pinoTransmissor2, OUTPUT);
  pinMode(pinoReceptor2, INPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop()
{
 	distancia1 = calcularDistancia(pinoTransmissor1,pinoReceptor1);
	distancia2 = calcularDistancia(pinoTransmissor2,pinoReceptor2);
 	trocarLed(distancia1,ledVerde1,ledVermelho1);
  	trocarLed(distancia2,ledVerde2,ledVermelho2);
  	calcularVagas(distancia1,distancia2);
   	lcd.clear();
  	lcd.setCursor(0, 0);
  	lcd.print("Vagas livres ");
  	lcd.setCursor(15, 0);
  	lcd.print(livres);
  	lcd.setCursor(0, 1);
  	lcd.print("Vagas ocupadas");
  	lcd.setCursor(15, 1);
  	lcd.print(ocupadas);
  	delay(500);
}

float calcularDistancia(int transmissor,int receptor)
{  
  digitalWrite(transmissor, LOW);
  delayMicroseconds(5); 
  digitalWrite(transmissor, HIGH); 
  delayMicroseconds(10);
  digitalWrite(transmissor, LOW);
  duracao = pulseIn(receptor, HIGH);
  float calcDistancia= (duracao/2) * 0.0343;
  if (calcDistancia>=331){
      calcDistancia=0;
  }
  return calcDistancia;  
}

void trocarLed(float valorDistancia, int ledVerde, int ledVermelho)
{
  if(valorDistancia <200){
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledVerde, LOW);
  }
  else{
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledVerde, HIGH);
  }
}

void calcularVagas(float valor1, float valor2){
  if(valor1< 200 && valor2 <200){
    livres = 0;
    ocupadas = 2;
  } else if (valor1< 200 || valor2 <200){
    livres = 1;
    ocupadas = 1;
  }else{
  	livres = 2;
    ocupadas = 0;
  }
}