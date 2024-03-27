/*  
This example code is in the public domain.
https://randomnerdtutorials.com/raspberry-pi-pico-dht11-dht22-arduino/
*/
#include <DHT.h>
//define pin data
#define DHTPIN 22                             
// any other DI pin (GPIO22 on Pi PICO), or almost any other I/O pin
#define DHTTYPE DHT22                         
// DHT 22 (AM2302)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.print("Testing DHT sensor");
  dht.begin();
}

void loop() {
 // Wait a few seconds between measurements.
  delay(2000);
  // starts with a 2000 ms (2 seconds) delay, because the DHT22 maximum sampling period is 2 seconds. So, we can only get readings every two seconds.
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature()+1.0;
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true)+1.8;
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  /*
  Heat Index is 
  "The temperature that a person's body feels depends on the relationship between temperature and humidity, 
  that is, the temperature that a person experiences whether the weather is hot or cold at that time."
  */
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}
