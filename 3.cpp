#include <LiquidCrystal.h>

//* How to use the DHT-22 sensor with Arduino
//   Temperature and humidity sensor and
//   I2C LCD1602
 //  SDA --> A4
 //  SCL --> A5
 //DHT 22 out-->D7

//Libraries
#include <DHT.h>;
//I2C LCD:
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display,Pls check your lcd.
  
//Constants
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

//Variables
//int chk;
int h;  //Stores humidity value
int t; //Stores temperature value

void setup()
{
    Serial.begin(9600);
    Serial.println("Temperature and Humidity Sensor Test");
    dht.begin();
    lcd.init(); //initialize the lcd
    lcd.backlight(); //open the backlight
}

void loop()
{
    //Read data and store it to variables h (humidity) and t (temperature)
    // Reading temperature or humidity takes about 250 milliseconds!
    h = dht.readHumidity();
    t = dht.readTemperature();
    
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %, Temp: ");
    Serial.print(t);
    Serial.println(" ° Celsius");
        
// set the cursor to (0,0):
// print from 0 to 9:

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
   
  if (t < 34) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(8, LOW);
    digitalWrite(13, LOW);
   
  }
  
  if (t > 34)
  {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(13,LOW);
    digitalWrite(8, HIGH);
    
  }
  
  delay(10);
}