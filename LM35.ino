#include <WiFi.h>
#include <WebServer.h>
#include "esp_adc_cal.h"
#include "html.h"

WebServer server(80);

#define LM35_SENSOR_PIN 33

// Function prototype for reading and calibrating the ADC value
uint32_t readAndCalibrateADC(int rawADCValue);

// Variables to store raw ADC value, voltage in millivolts, and temperatures in Celsius and Fahrenheit
int rawADCValue = 0;
float voltageInMilliVolts = 0.0;
float temperatureInCelsius = 0.0;
float temperatureInFahrenheit = 0.0;

// Replace these with your WiFi network settings
const char* ssid = "123";
const char* password = "03011995";

void MainPage() {
  String _html_page = html_page;             /*Read The HTML Page*/
  server.send(200, "text/html", _html_page); /*Send the code to the web server*/
}

void Temp() {
  // Prepare a JSON string that includes both Celsius and Fahrenheit temperatures
  String json = "{";
  json += "\"celsius\": " + String(temperatureInCelsius, 2) + ",";
  json += "\"fahrenheit\": " + String(temperatureInFahrenheit, 2);
  json += "}";
  server.send(200, "application/json", json);  //Send updated temperature values to the web server
}


void setup(void) {
  Serial.begin(115200); /*Set the baudrate to 115200*/
  WiFi.mode(WIFI_STA);  /*Set the WiFi in STA Mode*/
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  delay(1000); /*Wait for 1000mS*/
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.print(".");
  }
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("Your Local IP address is: ");
  Serial.println(WiFi.localIP()); /*Print the Local IP*/

  server.on("/", MainPage);     /*Display the Web/HTML Page*/
  server.on("/readTemp", Temp); /*Display the updated Temperature and Humidity value*/
  server.begin();               /*Start Server*/
  delay(1000);                  /*Wait for 1000mS*/
}

void loop(void) {
  // Read the raw ADC value from the LM35 sensor
  rawADCValue = analogRead(LM35_SENSOR_PIN);

  // Calibrate the raw ADC value and convert it to voltage in millivolts
  voltageInMilliVolts = readAndCalibrateADC(rawADCValue);

  // Calculate the temperature in Celsius. The LM35 outputs 10mV per degree Celsius.
  temperatureInCelsius = voltageInMilliVolts / 10;

  // Convert the temperature to Fahrenheit
  temperatureInFahrenheit = (temperatureInCelsius * 1.8) + 32;

  server.handleClient();

  // Print the temperature readings in both Celsius and Fahrenheit
  Serial.print("Temperature = ");
  Serial.print(temperatureInCelsius);
  Serial.print(" °C, ");
  Serial.print("Temperature = ");
  Serial.print(temperatureInFahrenheit);
  Serial.println(" °F");

  // Delay for a short period before reading the temperature again
  delay(1000);  // Delay of 1 second
}

// Function to read and calibrate the raw ADC value to voltage in millivolts
uint32_t readAndCalibrateADC(int rawADCValue) {
  // ADC calibration characteristics
  esp_adc_cal_characteristics_t adcCharacteristics;

  // Characterize the ADC at attenuation of 11dB and width of 12 bits
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adcCharacteristics);

  // Convert the raw ADC value to calibrated voltage in millivolts
  return esp_adc_cal_raw_to_voltage(rawADCValue, &adcCharacteristics);
}