#include <WiFi.h>
#include <SD.h>
#include <SPI.h>

// WiFi credentials
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// SD card configuration
const int chipSelect = 5;
File dataFile;

// Filter settings
#define NUM_SAMPLES 10
int readings[NUM_SAMPLES]; // Array to store readings for averaging
int readIndex = 0;         // Index of current reading
int total = 0;             // Total of all readings
int average = 0;           // Moving average value

// Time settings
unsigned long lastSendTime = 0;
const unsigned long sendInterval = 10000;  // Send data every 10 seconds

void setup() {
  Serial.begin(115200);

  // Initialize the SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card initialized.");

  // Initialize WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n...Connected to Wi-Fi");

  // Initialize filter array
  for (int i = 0; i < NUM_SAMPLES; i++) {
    readings[i] = 0;
  }
}

void loop() {
  // Read the potentiometer value (or sensor value)
  int sensorValue = analogRead(33);

  // Subtract the last reading from the total
  total = total - readings[readIndex];
  
  // Store the new reading in the array
  readings[readIndex] = sensorValue;
  
  // Add the new reading to the total
  total = total + readings[readIndex];
  
  // Advance to the next position in the array
  readIndex = readIndex + 1;
  
  // Wrap around to the beginning of the array if necessary
  if (readIndex >= NUM_SAMPLES) {
    readIndex = 0;
  }

  // Calculate the moving average
  average = total / NUM_SAMPLES;

  // Print the smoothed value
  Serial.print("Smoothed Sensor Value: ");
  Serial.println(average);

  // Save data to SD card
  dataFile = SD.open("/data.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print("Smoothed Value: ");
    dataFile.println(average);
    dataFile.close();
    Serial.println("Data written to SD card.");
  } else {
    Serial.println("Error opening file on SD card.");
  }

  // Check if it's time to send data
  if (millis() - lastSendTime >= sendInterval) {
    // Send data to cloud
    sendDataToCloud();

    // Clear SD card data after sending
    if (SD.remove("/data.txt")) {
      Serial.println("Data sent and cleared from SD card.");
    } else {
      Serial.println("Failed to clear SD card data.");
    }

    // Update the last send time
    lastSendTime = millis();
  }

  delay(1000);  // Adjust the delay as needed
}

void sendDataToCloud() {
  if (WiFi.status() == WL_CONNECTED) {
    // Simulate sending data to the cloud
    Serial.println("Sending data to cloud...");

    // Simulate a delay for sending data
    delay(2000);

    Serial.println("Data sent successfully.");
  } else {
    Serial.println("WiFi not connected. Cannot send data.");
  }
}
