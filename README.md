# Smart Mood & Environment Station 🌡️🤖

An Arduino-based smart environmental monitoring system that tracks ambient temperature and humidity, dynamically displays status moods on an OLED screen, triggers physical relay actions for device control, and raises audio alerts via a buzzer during critical thresholds.

---

## 🚀 Features

- **Real-Time Environment Tracking:** Monitors accurate temperature and humidity using the DHT11 sensor.
- **Dynamic Mood Engine:** Visualizes environment status on a 0.96" I2C OLED display with clear emotional markers (`GOOD 😊`, `HOT 🥵`, `COLD 🥶`).
- **Automated Relay Control:** Automatically triggers a 5V relay to turn on a fan or cooling system when the room temperature crosses the critical high threshold (≥ 32°C).
- **Safety Audio Alarm:** Emits a continuous warning beep using a buzzer under high-temperature alerts.
- **Serial Debugging:** Broadcasts active live data streams to the Arduino IDE Serial Monitor at 9600 baud rate.

---

## 🔌 Hardware Configuration & Pin Mapping

Connect your hardware components to the Arduino board according to the specific layout configuration defined below:

| Component | Component Pin | Arduino Pin | Description |
| :--- | :--- | :--- | :--- |
| **DHT11 Sensor** | VCC | 5V | Power Supply |
| | GND | GND | Ground Reference |
| | DATA | Digital Pin 2 | Environment Data Input |
| **I2C OLED (SSD1306)** | VCC | 5V / 3.3V | Power Supply |
| | GND | GND | Ground Reference |
| | SDA | A4 (SDA) | I2C Data Line |
| | SCL | A5 (SCL) | I2C Clock Line |
| **5V Relay Module** | VCC | 5V | Power Supply |
| | GND | GND | Ground Reference |
| | IN (Signal) | Digital Pin 3 | Relay Toggle Output |
| **Buzzer** | Positive (+) | Digital Pin 4 | Alarm Signal Output |
| | Negative (-) | GND | Ground Reference |

---

## 🛠️ Software Dependencies

Before compiling the main codebase, ensure that you have downloaded and installed the following official library modules inside your **Arduino IDE**:

1. `Adafruit SSD1306` (OLED screen driver framework)
2. `Adafruit GFX Library` (Core graphics core engine)
3. `DHT Sensor Library` by Adafruit (DHT11 API controller)

---

## 📈 System Operation Logic

- **Condition 1 (Safe/Comfortable):** If the measured ambient temperature stays balanced between **18°C and 32°C**, the station flags a `GOOD 😊` state. The relay remains inactive (OFF) and the safety alarm stays quiet.
- **Condition 2 (Overheating Alert):** When temperature data moves to **32°C or above**, the system goes into an automated protection cycle: the OLED displays `HOT !! 🥵`, the relay switches ON to run structural cooling appliances, and the buzzer turns ON.
- **Condition 3 (Freezing Alert):** If parameters fall beneath **18°C**, the monitor triggers a `COLD 🥶` alert on-screen, cutting off active ventilation systems (Relay OFF).
