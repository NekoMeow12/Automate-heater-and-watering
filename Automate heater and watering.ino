// github : NekoMeow12
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define WATER_LEVEL_SENSOR_PIN A2   
#define LED_PIN_1 8               
#define LED_PIN_2 9               
#define TEMPERATURE_LED_PIN 10     

// LCD dituy
#define LCD_ADDRESS 0x27          
#define LCD_COLS 16         
#define LCD_ROWS 2              

// jay water lvl tuy
#define WATER_LEVEL_OFF_THRESHOLD 90
#define WATER_LEVEL_ON_THRESHOLD_LOW 5 

// Temperature tuy
#define TEMPERATURE_THRESHOLD 27  

// pang lcd
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS); 

// madiyu paki bibyangan atuy nga part ta nalipatakon
OneWire oneWire(A1);
DallasTemperature sensors(&oneWire);

void setup() {
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(TEMPERATURE_LED_PIN, OUTPUT);

  // jay start up nga ibag bagana
  // mabalin yu edit kabil yu naganyu
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Grade 12 Project");
  Serial.begin(9600);
  sensors.begin();
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Setup Complete");
  delay(2000);
}

void loop() {
  sensors.requestTemperatures(); 
  float waterTemp = sensors.getTempCByIndex(0);
  // madyu palya palya jay board ti ph sensor
  // ngem ag balin latta met, paki baga langtun iti range na
  float pHValue = analogRead(A0);
  pHValue = (pHValue / 1024) * 14; 


  int waterLevel = analogRead(WATER_LEVEL_SENSOR_PIN);
  int waterLevelPercent = map(waterLevel, 0, 1023, 0, 100); 

  // baliktad jay relay, nu LOW ag ON tas nu HIGH ag off hahahahah
  if (waterLevelPercent >= WATER_LEVEL_OFF_THRESHOLD) {
    digitalWrite(LED_PIN_1, LOW); // Turn off LED 1
    digitalWrite(LED_PIN_2, LOW); // Turn off LED 2
  } else if (waterLevelPercent >= WATER_LEVEL_ON_THRESHOLD_LOW) {
    digitalWrite(LED_PIN_1, HIGH); // Turn on LED 1
    digitalWrite(LED_PIN_2, LOW); // Turn off LED 2
  } else {
    digitalWrite(LED_PIN_1, LOW); // Turn off LED 1
    digitalWrite(LED_PIN_2, LOW); // Turn off LED 2
  }
  if (waterTemp < TEMPERATURE_THRESHOLD) {
    digitalWrite(TEMPERATURE_LED_PIN, LOW ); 
  } else {
    digitalWrite(TEMPERATURE_LED_PIN, HIGH); 
  }

  // dagiyay i display yanti LCD
  // han umanay jay water lvl ta kurang jay lcd haha
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(waterTemp);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("pH: ");
  lcd.print(pHValue);
  Serial.print("Water Temperature: ");
  Serial.print(waterTemp);
  Serial.println(" °C");
  Serial.print("pH Value: ");
  Serial.println(pHValue);
  Serial.print("Water Level (%): ");
  Serial.println(waterLevelPercent);

  delay(1000);
}
  // nalpasen, na check and testing amin bago i pack with video
    // nu nagka problema, contact dak lang, nalakalang i edit tuy code ko
      // dagiyay kayat na agpa aramid met, adda kami tuy, thank you!
