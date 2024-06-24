#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 7   
#define DHTTYPE DHT22
#define Duty_pin 13

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(Duty_pin, OUTPUT);

  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
}

void loop()
{
  delay(3000);

  float h = dht.readHumidity();

  float t = dht.readTemperature();

  float f = dht.readTemperature(true);


  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

 //int dutyCycle = map(t, 25, 35, 110, 255);
  float dutyCycle = ((255-110)/(35-25))*(t-25) + 110;
  if (dutyCycle > 255)
  {
    dutyCycle = 255;
  }
  if (dutyCycle < 128)
  {
    dutyCycle = 128;
  }
  
  //dutyCycle=100;
  analogWrite(Duty_pin, dutyCycle);
  //analogWrite(Duty_pin, 100);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C  or  "));
  Serial.print(f);
  Serial.print(F("°F   "));
  Serial.print("dutyCycle: ");
  Serial.print(dutyCycle);
  Serial.print(" & ");
  Serial.print((dutyCycle/255.0)*100.0);
  Serial.println("%");

  lcd.setCursor(0,0);
  lcd.print("Humi: ");
  lcd.print(h);
  lcd.print(" %");
  lcd.setCursor(0,1);
  lcd.print("T: ");
  lcd.print(t);
  lcd.print(" D: ");
  lcd.print((dutyCycle/255.0)*100.0);
  lcd.print("%");
}