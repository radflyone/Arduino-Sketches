
#include <LiquidCrystal.h>
int tempPin = A0; //Pin for thermistor input
//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
void setup()
{
  lcd.begin(16, 2);
  // initialize the serial port for MCP9700
  Serial.begin(9600);
}
void loop()
{
  int tempReading = analogRead(tempPin);
  // This is OK
  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
  float tempC = tempK - 273.15;            // Convert Kelvin to Celcius
  float tempF = (tempC * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  /*  replaced
    float tempVolts = tempReading * 5.0 / 1024.0;
    float tempC = (tempVolts - 0.5) * 10.0;
    float tempF = tempC * 9.0 / 5.0 + 32.0;
  */
  // Display Temperature in C
  lcd.setCursor(0, 0);
  //lcd.print("Temp         C  ");
  // Display Temperature in F
  lcd.print("Temp         F  ");
  lcd.setCursor(6, 0);
  // Display Temperature in C
  //lcd.print(tempC);
  // Display Temperature in F
  lcd.print(tempF+8.5);
  delay(500);
  
  //Code for MCP9700 to serial output
    float temperature = 0.0;   // stores the calculated temperature
    int sample;                // counts through ADC samples
    float ten_samples = 0.0;   // stores sum of 10 samples
  
    // take 10 samples from the MCP9700
    for (sample = 0; sample < 10; sample++) {
        // convert A0 value to temperature
        temperature = ((float)analogRead(A3) * 5.0 / 1024.0) - 0.5;
        temperature = temperature / 0.01;
        // sample every 0.1 seconds
        delay(100);
        // sum of all samples
        ten_samples = ten_samples + temperature;
    }
    // get the average value of 10 temperatures
    temperature = (((ten_samples / 10.0) * 9) / 5) + 32;
    // send temperature out of serial port
    Serial.print(temperature);
    Serial.println(" deg. F");
    ten_samples = 0.0;
}
