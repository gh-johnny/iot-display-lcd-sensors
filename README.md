# LCD Display + sensors 💡💧🔆
 
## Integrantes 👋
<ul>
    <li>Gabriel Barros Cisoto (RM556309)</li>
    <li>Pedro Henrique Bizzo de Santana (RM557263)</li>
    <li>Pedro Henrique Mendes dos Santos (RM555332)</li>
    <li>João Marcelo Furtado Romero (RM555199)</li>
    <li>Kayky Silva Stiliano (RM555148)</li>
</ul>
 
<img src="https://raw.githubusercontent.com/gh-johnny/iot-display-lcd-sensors/main/docs/assets/project-printscreen.png" alt="print do circuito Arduino/printscreen Arduino circuit"/>
 
Link da simulação no <a href="https://wokwi.com/projects/396863714056398849">Wokwi</a>
<br />
<br />
## Explicação do Projeto 📖
Um programa que mede:
 
 O nível de luminosidade através de um LDR 🔆
<ul>
<li>
    Baixa luminosidade: LED verde  + mensagem no LCD
</li>
<li>
    Média luminosidade: LED amarelo + mensagem no LCD
 
</li>
<li>
    Alta luminosidade: LED vermelho + beep + mensagem no LCD
</li>
</ul>
<br>
 O nível de umidade através do DHT 💦
<ul>
<li>
  Baixa umidade: LED vermelho + mensagem no LCD + beep
</li>
<li>
  Umidade ideal: LED verde + mensagem no LCD
</li>
<li>
  Alta umidade: LED vermelho + mensagem no LCD + beep
</li>
</ul>
<br>
 E temperatura (em °C), também através do DHT 🌡
<ul>
<li>
  Baixa temperatura: LED amarelo + mensagem no LCD + beep
</li>
<li>
  temperatura ideal: LED verde + mensagem no LCD
</li>
<li>
  Alta temperatura: LED amarelo + mensagem no LCD + beep
</li>
</ul>
 
## Componentes 🛠️
<ul>
    <li>1x Placa Arduino Uno</li>
    <li>1x Breadboard</li>
    <li>1x Potenciômetro</li>
    <li>1x DHT11</li>
    <li>1x Buzzer</li>
    <li>1x Display LCD</li>
    <li>1x Sensor de fotorrresistência</li>
    <li>3x LEDs</li>
    <li>6x Resistores</li>
</ul>
 
<br>
 
## Dependências 📦
<ul>
    <li>LiquidCrystal</li>
    <li>DHT Sensor library</li>
</ul>
 
<br>
 
## Explicando o <a href="https://github.com/gh-johnny/iot-display-lcd-sensors/blob/main/arduino.c">Código</a> 🧑‍💻
 
Precisamos incluir as bibliotecas para podermos ter acesso a métodos dos quais vamos precisar para interagir com o DHT.
 
Assim como também é preciso declarar, iniciando tais valores para podermos usá-los depois na aplicação.
 
```c
#include <LiquidCrystal.h>
#include <DHT.h>
 
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
#define DHTPIN A0
#define DHTTYPE DHT22
 
DHT dht(DHTPIN, DHTTYPE);
 
int valor_ldr;
```
<hr>
 
A função `testaLuminozidade()` que retorna void, ou seja, não retorna nada, é declarada.
 
Fazemos a leitura analógica do nosso LDR, coloamos dentro da função map, para que possamos controlar os valores de forma relativa.
 
Logo, precisamos da lógica, na qual se o valor se encontra abaixo ou igual a 33
o led verde é aceso e então escrevemos no display que o ambiente está escuro
 
se está com uma quantidade média de luminosidade (33 < valor analógico do ldr <= 66) o led amarelo é aceso e o beep (piezo/campainha) é tocado além de mostrar no display que o ambiente se encontra em meia luz
 
caso não entre en nenhum desses casos, significa que a luminosidade está alta, então o led vermelho se acende assim como continua a tocar o beep e escreve no display ambiente muito claro
 
```c
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
```
<hr>
 
A função `montaTelaHumidade()` que retorna void irá ler valores analógicos do DHT, em específico, a humidade
   
Verifica o valor da umidade lida e executa diferentes ações com base em intervalos de valor. Se a umidade for inferior a 50%, será exibida uma mensagem indicando que a umidade está baixa. Se estiver entre 50% e 70%, será exibida uma mensagem indicando que a umidade está ok. Se for superior a 70%, será exibida uma mensagem indicando que a umidade está alta.
 
Atualiza o display LCD com a mensagem correspondente ao nível de umidade detectado.
 
Controla os LEDs conectados aos pinos 13, 12 e 11, e um buzzer conectado ao pino 8, para indicar visual e auditivamente o nível de umidade. Os LEDs e o buzzer são acionados de acordo com as condições de umidade detectadas.
 
 
```c
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
```
<hr>
 
A função `montaTelaTemp()` que retorna void irá ler valores analógicos do DHT, em específico, a temperatura

Verifica o valor da temperatura lida e executa diferentes ações com base em intervalos de valor. Se a temperatura for inferior a 10°C, será exibida uma mensagem indicando que a temperatura está baixa. Se estiver entre 10°C e 15°C, será exibida uma mensagem indicando que a temperatura está ok. Se for superior a 15°C, será exibida uma mensagem indicando que a temperatura está alta.
 
Controla os LEDs conectados aos pinos 13, 12 e 11, e um buzzer conectado ao pino 8, para indicar visual e auditivamente o nível de temperatura. Os LEDs e o buzzer são acionados de acordo com as condições de temperatura detectadas.
 
```c
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
 
```
<hr>
 
A função `montaTelaBlank()` que retorna void, servirá como uma "helper" funciton para que possamos causar delays entre as diferentes funções, limpando o display e silenciando o beep
 
```c
void montaTelaBlank() {
  delay(4000);
  noTone(8);
  delay(1000);
  lcd.clear();
}
```
<hr>
 
A função `setup()` que retorna void, no Arduíno serve para fazermos o setup da nosso projeto, dizendo para o programa quais pinos utilizaremos e em qual modo, iniciar o DHT e o display LCD, o código extra com diferentes passos para já escrever no display serve para melhorar a experiência de usuário indicando-o que o programa está sendo inicializado
 
```c
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
```
<hr>
 
A função <span style="font-style: italic;">loop</span> que retorna void, no Arduíno, servirá como o ciclo de vida inteiro do projeto, é uma função que por padrão roda infinitamente até algo dentro ou fora do códgio pará-lo.
 Aqui, vamos chamar nossas funções principais já declaradas para termos uma melhor leitura e manutenção do código, assim como chamar também a função
<span style="font-style: italic;">montaTelaBlank</span> entre essas funções para termos um "reset" entre os passos da nossa aplicação
 
```c
void loop() {
  testaLuminozidade();
  montaTelaBlank();
 
  montaTelaHumidade();
  montaTelaBlank();
 
  montaTelaTemp();
  montaTelaBlank();
}
```
 
<center><img width="120px" src="https://raw.githubusercontent.com/gh-johnny/iot-display-lcd-sensors/main/docs/assets/arudino-icon.png" alt="Placa Arduino/Arduino board"></center>
 
<hr>
 
<center>Este projeto encontra sob a <a href="https://github.com/gh-johnny/iot-display-lcd-sensors/blob/main/LICENSE">MIT License.</a></center>
