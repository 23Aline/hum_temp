#include "DHT.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  

float DHTPIN = 23;

#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE);

int led1 = 26; //azul - ar condicionado desligado
int led2 = 34; //vermelho - ar condicionado ligado
int Relay = 19;
const int ledPino = 4;
const int pirPino = 15;

int LedState = 0; 

void setup() {
  Serial.begin(115200);
  Serial.println("Teste de modulo - Temperatura e Umidade: ");

  dht.begin();

  lcd.init();  
 
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Temperatura...");
  lcd.setCursor(0, 1);
  lcd.print("Umidade...");
  delay(2000);
  lcd.clear();

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(Relay, OUTPUT);
  
  pinMode(ledPino, OUTPUT);
  pinMode(pirPino, INPUT);

}
void loop() {

  delay(500);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Erro de leitura!");
    return;
  }
  lcd.setCursor(0, 0);
  lcd.print("Temp : ");
  lcd.print(t);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Umi : ");
  lcd.print(h);
  lcd.print(" %");
  if (t >= 27) {
    
    digitalWrite(led1, LOW);
    LedState = ! LedState;
    digitalWrite(led2, LedState);
    digitalWrite(Relay, HIGH);
  } if (t < 27) {
    digitalWrite(led2, LOW);
    digitalWrite(led1, HIGH);
    digitalWrite(Relay, LOW);
  }
  
  const int IP = digitalRead(pirPino);
  Serial.println(IP);
  delay(1000);
  if(IP == 1){
    digitalWrite(ledPino, HIGH);
    Serial.println("Acendeu!");
    delay(1000);
  }
  else{
    digitalWrite(ledPino, LOW);
    Serial.println("Apagado!");
    delay(1000);
  }

}