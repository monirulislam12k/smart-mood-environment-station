#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// OLED Display Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DHT11 Sensor Configuration
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Peripheral Hardware Pins
const int RELAY_PIN = 3;
const int BUZZER_PIN = 4;

// Temperature Thresholds for Alerts
const float TEMP_HIGH_THRESHOLD = 32.0;
const float TEMP_LOW_THRESHOLD  = 18.0; 
void setup() {
  Serial.begin(9600);
  
  // Pin modes definition
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Set default status (Relay OFF, Buzzer OFF)
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // Initialize DHT Sensor
  dht.begin();

  // Initialize OLED Display (I2C Address: 0x3C)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("OLED hardware allocation failed"));
    for(;;); // System halt if display not found
  }
  
  // Initial Welcome Screen
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  display.println("Smart Mood Station");
  display.setCursor(30, 40);
  display.println("Initializing...");
  display.display();
  delay(2000);
}

void loop() {
  // Read environment parameters
  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature();

  // Check if readings failed
  if (isnan(humidity) || isnan(tempC)) {
    Serial.println(F("Failed to read data from DHT sensor!"));
    display.clearDisplay();
    display.setCursor(0, 20);
    display.println("Sensor Error!");
    display.display();
    return;
  }

  display.clearDisplay();
  
  // Display Temperature and Humidity Info
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(tempC, 1);
  display.print(" C");

  display.setCursor(0, 16);
  display.print("Humidity: ");
  display.print(humidity, 0);
  display.print(" %");

  // Environmental Logic, Relay Controls & Mood Display
  display.setCursor(0, 40);
  display.print("Mood: ");
  
  if (tempC >= TEMP_HIGH_THRESHOLD) {
    //  HOT MOOD: Activate Relay (AC/Fan) & Sound Alert
    digitalWrite(RELAY_PIN, HIGH); // Turn ON cooling device
    digitalWrite(BUZZER_PIN, HIGH); // Sound warning beep
    
    display.setTextSize(2);
    display.print("HOT !! ");
    display.setTextSize(1);
    display.setCursor(0, 55);
    display.print("Relay: ON | Alert!");
    
  } else if (tempC <= TEMP_LOW_THRESHOLD) {
    //  COLD MOOD: Turn off cooling, show freeze warning
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    
    display.setTextSize(2);
    display.print("COLD ");
    display.setTextSize(1);
    display.setCursor(0, 55);
    display.print("Relay: OFF");
    
  } else {
    //  COMFORTABLE MOOD: Ideal conditions
    digitalWrite(RELAY_PIN, LOW);  // Keep device off
    digitalWrite(BUZZER_PIN, LOW); // Silent buzzer
    
    display.setTextSize(2);
    display.print("GOOD ");
    display.setTextSize(1);
    display.setCursor(0, 55);
    display.print("Relay: OFF | Safe");
  }

  // Render buffer to OLED hardware screen
  display.display();
  
  // Debug output via Serial Monitor
  Serial.print("T: "); Serial.print(tempC);
  Serial.print(" | H: "); Serial.print(humidity);
  Serial.println(digitalRead(RELAY_PIN) ? " | Relay: ON" : " | Relay: OFF");

  delay(2000); // Sampling loop delay (2 seconds)
}
