# Acoustic-Based Rail Defect Detection System

This project is designed to collect and process sensor data using the ESP32-WROOM-32 microcontroller, storing data on an SD card and sending it to the cloud via Wi-Fi. The system reads sensor values, smooths the data using a moving average filter, and logs the results. The data is sent to the cloud at regular intervals, and the SD card is cleared after successful transmission.
![Screenshot (308)](https://github.com/user-attachments/assets/8dfd0a15-0a3d-4604-8ff6-2253457e174e)

## Features
- **Wi-Fi Integration**: Connects to a Wi-Fi network for data transmission.
- **SD Card Storage**: Logs sensor data to an SD card.
- **Moving Average Filter**: Smooths sensor readings for more stable data.
- **Cloud Communication**: Sends processed data to the cloud at specified intervals.
- **Automatic Data Clearing**: Clears SD card data after successful transmission.

## Components
- **ESP32-WROOM-32**: Main microcontroller for processing and communication.
- **SD Card Module**: Stores sensor data locally.
- **Wi-Fi**: Enables cloud communication.

## How It Works
1. **Initialize Components**: Wi-Fi and SD card are initialized in the setup.
2. **Sensor Data Collection**: The system reads analog sensor data, applies a moving average filter, and prints the smoothed value.
3. **Data Logging**: Smoothed data is logged to an SD card.
4. **Cloud Data Transmission**: Data is sent to the cloud every 10 seconds, and the SD card is cleared upon successful transmission.
5. **Error Handling**: The system checks for Wi-Fi connectivity and SD card availability.

## Usage
1. **Setup Wi-Fi Credentials**: Modify the `ssid` and `password` in the code.
2. **Deploy on ESP32**: Upload the code to the ESP32 microcontroller.
3. **Monitor Serial Output**: View real-time sensor data and logs via Serial Monitor.
4. **Check SD Card Logs**: Access logged data on the SD card.

This system is ideal for applications requiring reliable sensor data logging and transmission, such as monitoring rail infrastructure for defects.
