#include <DHT.h>;
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x3F,16,2);

#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino


int celsius = 0;
int fahrenheit = 0;
int Ena=7;
int h;  //Stores humidity value
int t; //Stores temperature value

void setup()
{
  Serial.begin(9600);
      Serial.println("Temperature and Humidity Sensor Test");
    dht.begin();
    lcd.init(); //initialize the lcd
    lcd.backlight(); //open the backlight
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  analogWrite(Ena,255);
}

void loop()
{
  h = dht.readHumidity();
  t = dht.readTemperature();
  celsius = map(((analogRead(A0))), 0, 1023, 30, 70);
  fahrenheit = ((celsius * 9) / 5 + 32);
  Serial.print(celsius);
  Serial.print(" C, ");
  Serial.print(fahrenheit);
  Serial.println(" F");

  lcd.setCursor(0, 0);
    lcd.println(" Now Temperature ");
    
    lcd.setCursor(0, 1);
    lcd.print("T:");
    lcd.print(t);
    lcd.print("C");

    lcd.setCursor(6, 1);
    lcd.println("2021 ");
     
    lcd.setCursor(11, 1);
    lcd.print("H:");
    lcd.print(h);
    lcd.print("%");
  
   if (t < 35) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(8, LOW);
    digitalWrite(13, LOW);
   
  }
  
  if (t >= 35)
  {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(13,LOW);
    digitalWrite(8, HIGH);
    
  }
  
  delay(10); 
}