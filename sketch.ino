#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT
const char* mqtt_server = "broker.hivemq.com";
const char* topic = "airquality/data";

WiFiClient espClient;
PubSubClient client(espClient);

// MQ2 Sensor
const int mq2Pin = 34;

void setupWiFi() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void reconnect() {
  while (!client.connected()) {
    String clientId = "ESP32-AirQuality-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("MQTT Connected");
    } else {
      delay(1000);
    }
  }
}

void setup() {

  Serial.begin(115200);

  setupWiFi();

  client.setServer(mqtt_server, 1883);

  Wire.begin(21,22);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.display();
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  int airValue = analogRead(mq2Pin);

  String status;

  if (airValue < 1000)
    status = "GOOD";
  else if (airValue < 2500)
    status = "MODERATE";
  else
    status = "POOR";

  // OLED Display
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0,0);
  display.println("Air Quality");

  display.setCursor(0,20);
  display.print("Value: ");
  display.println(airValue);

  display.setCursor(0,40);
  display.print("Status:");
  display.println(status);

  display.display();

  // MQTT Publish
  String message =
      "AQ Value: " + String(airValue) +
      " | Status: " + status;

  client.publish(topic, message.c_str());

  Serial.println(message);

  delay(2000);
}
