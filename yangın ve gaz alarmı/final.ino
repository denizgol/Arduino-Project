#include <LiquidCrystal.h>

// SENSÖR YERLERİ
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

const int FIRE_SENSOR_PIN = 2;
const int GAS_SENSOR_PIN = 3;
const int BUZZER_PIN = 7;
const int LED_PIN = 6;

void setup() {
  pinMode(FIRE_SENSOR_PIN, INPUT); // Yangın Sensörü INPUT
  pinMode(GAS_SENSOR_PIN, INPUT); // Gaz Sensörü INPUT
  pinMode(BUZZER_PIN, OUTPUT);  // BUZZER ÇIKIŞ
  pinMode(LED_PIN, OUTPUT);  // LEDLER ÇIKIŞ

  lcd.begin(20, 4); // LCD EKRAN
  lcd.setCursor(0, 0); // İmleç konumunu ayarla
  lcd.print("  EV GUVENLIK SISTEMI   ");
  lcd.setCursor(0, 1);
  lcd.print("  YANGIN VE GAZ ALARMI   ");
}

void loop() {
  int Fire_Sensor_Degeri = digitalRead(FIRE_SENSOR_PIN);  // Yangın Sensöründen OKU
  int Gas_Sensor_Degeri = digitalRead(GAS_SENSOR_PIN);    // Gaz Sensöründen OKU
  
  lcd.setCursor(0, 3);
  lcd.print("                    ");  
  lcd.setCursor(0, 3);  

  if (Fire_Sensor_Degeri == HIGH && Gas_Sensor_Degeri == HIGH) // Yangın ve gaz algılama
  {
    tone(BUZZER_PIN, 2000); // İki sensör de algılandı
    digitalWrite(LED_PIN, LOW);
    lcd.print("     TEHLIKE     ");
  }
  else if (Fire_Sensor_Degeri == HIGH) // Yangın algılama
  {
    tone(BUZZER_PIN, 1000); 
    digitalWrite(LED_PIN, LOW);
    lcd.print("    Yangin Var    ");
  } 
  else if (Gas_Sensor_Degeri == HIGH) // Gaz algılama 
  {
    tone(BUZZER_PIN, 500); // Gaz sesi
    digitalWrite(LED_PIN, LOW);
    lcd.print("    Gaz Kacagi Var    ");
  } 
  else 
  {
    lcd.print("    Guvenli    ");
    noTone(BUZZER_PIN); // Buzzer'ı kapat
    digitalWrite(LED_PIN, HIGH);
  }
}
