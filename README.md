# IoT Air Quality Monitoring System

## Wowki link
https://wokwi.com/projects/469523852356216833

## Overview

This project monitors air quality using an ESP32 and an MQ2 Gas Sensor. The measured air quality value is displayed on an OLED display and published to an MQTT broker for remote monitoring.

> Note: Wokwi does not provide PM2.5 or CO₂ sensors. Therefore, the MQ2 Gas Sensor is used to simulate air quality monitoring. In a real-world implementation, sensors such as PMS5003 or MH-Z19B can replace the MQ2 without changing the system architecture.

## Components Used

- ESP32
- MQ2 Gas Sensor
- SSD1306 OLED Display
- MQTT (HiveMQ)
- Wokwi Simulator

## Features

- Air quality monitoring
- OLED display output
- MQTT data publishing
- Wi-Fi connectivity
- Real-time updates

## MQTT Details

Broker:
broker.hivemq.com

Topic:
airquality/data

## Working

1. ESP32 connects to Wi-Fi.
2. Reads the MQ2 sensor value.
3. Classifies air quality as GOOD, MODERATE, or POOR.
4. Displays the reading on the OLED.
5. Publishes the data to the MQTT broker.

## Future Scope

- Replace MQ2 with PM2.5 or CO₂ sensors.
- Store historical air quality data.
- Create a mobile/web dashboard.
- Send email or SMS alerts.
