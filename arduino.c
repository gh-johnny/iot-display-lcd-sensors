#include <LiquidCrystal.h>
#include <DHT.h>

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define DHTPIN A0
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
 
int valor_ldr;

void testaLuminozidade() {
  lcd.clear();
  valor_ldr = map(analogRead(A1), 8, 1016, 100, 0);
 
  if(valor_ldr<= 33){
    noTone(8);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, HIGH);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ambiente esta");
    lcd.setCursor(0, 1);
    lcd.print("escuro");
  }
  else if((valor_ldr > 33)&&(valor_ldr <= 66)){
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ambiente a meia");
    lcd.setCursor(0, 1);
    lcd.print("luz");
  }
  else {
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    for (int i = 0; i < 5; i++){
      tone(8, 500);
      
    }
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ambiente muito");
    lcd.setCursor(0, 1);
    lcd.print("claro");
  }
}
 
void montaTelaHumidade() {
  String string1 = "Humidade: ";
  float humidade = dht.readHumidity();
  String string2 = "%";
  String exibirHum = string1 + humidade + string2;

  if (humidade < 50){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humidade BAIXA");
    lcd.setCursor(0,1);
    lcd.print(exibirHum);

    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    tone(8, 500);
  }
  else if ((humidade >= 50)&&(humidade < 70)){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humidade OK");
    lcd.setCursor(0,1);
    lcd.print(exibirHum);

    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, HIGH);
    noTone(8);
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humidade ALTA");
    lcd.setCursor(0,1);
    lcd.print(exibirHum);

    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    tone(8, 500);
  }

}
 
void montaTelaTemp(){
  String string1 = "Temp: ";
  float temperatura = dht.readTemperature();
  String string2 = "C";
  String exibeTemp = string1 + temperatura + string2;

  if (temperatura < 10){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp. BAIXA");
    lcd.setCursor(0, 1);
    lcd.print(exibeTemp);

    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);
    tone(8, 500);
  }
  else if ((temperatura >= 10)&&(temperatura < 15)){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperatura OK");
    lcd.setCursor(0, 1);
    lcd.print(exibeTemp);

    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, HIGH);
    noTone(8);
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp. ALTA");
    lcd.setCursor(0, 1);
    lcd.print(exibeTemp);

    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);
    tone(8, 500);
  }
}
 
void montaTelaBlank() {
  delay(4000);
  noTone(8);
  delay(1000);
  lcd.clear();
}

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(A1, INPUT);

  dht.begin();
 
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Initializing");
  delay (1000);
  lcd.setCursor(8, 1);
  lcd.print("SETUP...");
  delay (2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("CP2 - Edge");
  delay (1000);
  lcd.setCursor(0, 1);
  lcd.print("Computing");
  delay (2000);
  lcd.clear();

  for (int i = 0; i <= 15; i++) {
    lcd.setCursor(0, 0);
    lcd.print("Carregando...");
    lcd.setCursor(i, 1);
    lcd.print("*");
    delay (200);
    lcd.clear();
  }
}

void loop() {
  testaLuminozidade();
  montaTelaBlank();
 
  montaTelaHumidade();
  montaTelaBlank();

  montaTelaTemp();
  montaTelaBlank();
}
