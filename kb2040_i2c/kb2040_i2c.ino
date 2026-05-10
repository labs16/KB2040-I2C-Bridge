#include <Wire.h>
#include <Adafruit_NeoPixel.h>
//#include "src/Adafruit_NeoPixel/Adafruit_NeoPixel.h"
// ---------- NEOPIXEL ----------
#define PIXEL_PIN   PIN_NEOPIXEL
#define PIXEL_COUNT 1

Adafruit_NeoPixel pixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

// ---------- I2C Serial Variables ----------
uint8_t dataLen;
uint8_t blockMode;
uint32_t i2cSpeed = 100000;  // default 100 kHz



void setup() {

// Setup Serial Port
  Serial.begin(115200);
  while (!Serial) delay(10);

// I2C Setup
  Wire.begin();
  Wire.setClock(i2cSpeed);

// Set-up NeoPixel
  pixel.begin();
  pixel.clear();
  pixel.show();
}

void loop() {

// Check if anything on Serial Port
  if (!Serial.available()) return;

// Start Processing the Serial Information
  uint8_t cmd = Serial.read();

// ================= I2C SPEED CONFIG =================
  if (cmd == 's') {
    while (!Serial.available());
    uint8_t sel = Serial.read();

    setI2CSpeed(sel);

    if (i2cSpeed != 0) {
      Serial.write((uint8_t)0x00);
      ledGreen();
    } else {
      Serial.write((uint8_t)0xFF);
      ledRed(); 
    }
    return;
  }

// ---------- BYTE 0: MODE / LENGTH ----------
  uint8_t hdr = cmd;
  blockMode = hdr & 0xF0;
  dataLen   = hdr & 0x0F;

  if (dataLen == 0 || dataLen > 4) {
    Serial.write((uint8_t)0xFF);
    ledRed();
    return;
  }

// ---------- BYTE 1: READ / WRITE ----------
  while (!Serial.available());
  uint8_t op = Serial.read();   // 'r' or 'w'

// ---------- BYTE 2: DEVICE ----------
  while (!Serial.available());
  uint8_t dev = Serial.read();  // 7-bit address

// ---------- BYTE 3: REGISTER ADDRESSS ----------
  while (!Serial.available());
  uint8_t reg = Serial.read();

// ================= PROCESS IF WRITE =================
  if (op == 'w') {

// RECEIVE Remainder of Serial Information
    while (Serial.available() < dataLen);

// START I2C WIRE TX
    Wire.beginTransmission(dev);
    Wire.write(reg);

// PROCESS IF BLOCK WRITE
// SET BLOCK BYTE SIZE
// UPDATE OLED to Dislplay Block Size
    if (blockMode == 0xB0) {
      uint8_t data_send = Serial.read();
      Wire.write(data_send);
    }

// PROCESS DATA FOR WRITE ON SERIAL/WIRE
    for (uint8_t i = 0; i < dataLen; i++) {
      Wire.write(Serial.read());
    }

// END I2C WIRE TX    
    uint8_t err = Wire.endTransmission();

// LED DISPLAY IF Serial/Wire was processed success or failure
    Serial.write(err == 0 ? (uint8_t)0x00 : (uint8_t)0xFF);
    (err == 0) ? ledGreen() : ledRed();
  }

  // ================= PROCESS IF READ =================
  else if (op == 'r') {

// START I2C WIRE RX     
    Wire.beginTransmission(dev);
    Wire.write(reg);

// LED DISPLAY IF Serial/Wire failure
    if (Wire.endTransmission(false) != 0) {
      Serial.write((uint8_t)0xFF);
      ledRed();
      return;
    }

// PROCESS SETUP IF BLOCK READ
    if (blockMode == 0xB0) {
      dataLen = dataLen+1;
    }

// DOES DATA RX'd Match Expected Size
    uint8_t rx = Wire.requestFrom(dev, dataLen);
    if (rx != dataLen) {
      Serial.write((uint8_t)0xFF);
      ledRed();
      return;
    }

// PROCESS IF BLOCK READ
// RX BLOCK BYTE SIZE
// UPDATE OLED to Dislplay Block Size
    if (blockMode == 0xB0) {
      uint8_t data_read = Wire.read(); // Read the Block Size, if applicable
      Serial.write(data_read);
      dataLen = dataLen-1;
    }

// PROCESS DATA FOR READ ON SERIAL/WIRE CAPTURE DATA FOR OLED Update
    for (uint8_t i = 0; i < dataLen; i++) {
      uint8_t data_read = Wire.read();
      Serial.write(data_read);
    }
 
// LED DISPLAY IF Serial/Wire was processed success or failure
      Serial.write((uint8_t)0x00);
      ledGreen();
      return;
  }
 // ================= INVALID =================
  else {
    Serial.write((uint8_t)0xFF);
    ledRed();
    return;
  
  }
}

// ---------- LED HELPERS ----------
void ledGreen() {
  pixel.setPixelColor(0, pixel.Color(0, 125, 0));
  pixel.show();
}

void ledRed() {
  pixel.setPixelColor(0, pixel.Color(125, 0, 0));
  pixel.show();
}

void setI2CSpeed(uint8_t sel) {
  switch (sel) {
    case 0x00: i2cSpeed = 100000; break;
    case 0x01: i2cSpeed = 400000; break;
    case 0x02: i2cSpeed = 1000000; break;
    default:   i2cSpeed = 0; break;
  }

  if (i2cSpeed != 0) {
    Wire.setClock(i2cSpeed);
  }
}


