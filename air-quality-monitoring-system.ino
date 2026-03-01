#define BLYNK_TEMPLATE_ID "TMPL3-wo0q0bb"
#define BLYNK_TEMPLATE_NAME "Air quality monitoring system"
#define BLYNK_AUTH_TOKEN "drMuwybCtxHhbK93tcTe3cW3pSlFN7t2"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// WiFi
char ssid[] = "SAKEC-LOCAL";
char pass[] = "SAKEC@123";

// MQ135
#define MQ135_PIN 34

// DHT11
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// LEDs
#define GREEN_LED  25
#define YELLOW_LED 26
#define RED_LED    27

BlynkTimer timer;

// -------- Send Data Function --------
void sendSensorData() {

  // Raw MQ135
  int rawValue = analogRead(MQ135_PIN);

  // Convert to AQI (0–500)
  int aqi = map(rawValue, 400, 2500, 0, 500);
  aqi = constrain(aqi, 0, 500);

  // Read DHT11
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  // Check DHT Valid
  if (isnan(temp) || isnan(hum)) {
    Serial.println("DHT11 Error!");
    return;
  }

  // Air Status + LEDs
  String status;

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);

  if (aqi < 100) {
    status = "GOOD";
    digitalWrite(GREEN_LED, HIGH);
  }
  else if (aqi < 200) {
    status = "MODERATE";
    digitalWrite(YELLOW_LED, HIGH);
  }
  else {
    status = "BAD";
    digitalWrite(RED_LED, HIGH);
  }

  // Serial Output
  Serial.println("------ DATA ------");
  Serial.print("Raw MQ135: "); Serial.println(rawValue);
  Serial.print("AQI Value: "); Serial.println(aqi);
  Serial.print("Temp: "); Serial.print(temp); Serial.println(" C");
  Serial.print("Humidity: "); Serial.print(hum); Serial.println(" %");
  Serial.print("Status: "); Serial.println(status);

  // Send to Blynk
  Blynk.virtualWrite(V0, aqi);       // Gauge AQI
  Blynk.virtualWrite(V1, temp);      // Temperature
  Blynk.virtualWrite(V2, hum);       // Humidity
  Blynk.virtualWrite(V3, status);    // Status text
  Blynk.virtualWrite(V4, rawValue);  // Raw MQ135 value
}

void setup() {
  Serial.begin(9600);

  dht.begin();

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}





