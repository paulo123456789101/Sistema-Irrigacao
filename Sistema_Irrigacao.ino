#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Endereço I2C do LCD 
LiquidCrystal_I2C lcd(0x20, 16, 2);

// Pinos dos sensores e bomba
const int sensorUmidade = A0;
const int sensorNivelAgua = A1;
const int bomba = 7;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(bomba, OUTPUT);
  digitalWrite(bomba, LOW);
}

void loop() {
  int leituraUmidade = analogRead(sensorUmidade);
  int leituraNivelAgua = analogRead(sensorNivelAgua);

  float umidadePercentual = map(leituraUmidade, 1023, 0, 0, 100);
  float nivelPercentual = map(leituraNivelAgua, 0, 1023, 0, 100);

  Serial.print("Umidade do Solo: ");
  Serial.print(umidadePercentual);
  Serial.println(" %");

  Serial.print("Nivel do Poco: ");
  Serial.print(nivelPercentual);
  Serial.println(" %");

  // Mostrar leitura na 1ª linha
  lcd.setCursor(0, 0);
  lcd.print("Solo:");
  lcd.setCursor(6, 0);
  lcd.print("    "); // Limpa os números anteriores
  lcd.setCursor(6, 0);
  lcd.print((int)umidadePercentual);
  lcd.print("%");

  // Mostrar leitura na 2ª linha
  lcd.setCursor(0, 1);
  lcd.print("Nivel:");
  lcd.setCursor(7, 1);
  lcd.print("    "); // Limpa os números anteriores
  lcd.setCursor(7, 1);
  lcd.print((int)nivelPercentual);
  lcd.print("%");

  if (umidadePercentual <= 30 && nivelPercentual > 20) {
    Serial.println("Irrigando...");
    lcd.setCursor(13, 1);
    lcd.print(" ON"); // Bomba ligada
    digitalWrite(bomba, HIGH);
    delay(5000); // Tempo de irrigação
    digitalWrite(bomba, LOW);
  } else {
    Serial.println("Sem irrigacao.");
    lcd.setCursor(13, 1);
    lcd.print("OFF"); // Bomba desligada
  }

  Serial.println("---------------");
  delay(3000);
}
