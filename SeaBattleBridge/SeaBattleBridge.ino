#include <Wire.h>

#define SERIAL_BOUD_RATE 9600
#define I2C_BOUD_RATE 10E5
#define I2C_ADDR 8
#define BUFFER_SIZE 7

uint8_t buffer[BUFFER_SIZE];

void setup() {
  Serial.begin(SERIAL_BOUD_RATE);
  Wire.setClock(I2C_BOUD_RATE);
  Wire.begin();

  for(uint8_t index = 0; index < BUFFER_SIZE; ++index){
    buffer[index] = 0;
  }
}

void loop() {
  if(Serial.available()) {
    Serial.readBytes(buffer, BUFFER_SIZE);
    
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(buffer, BUFFER_SIZE);
    Wire.endTransmission();
    
    Wire.requestFrom(I2C_ADDR, BUFFER_SIZE);
    uint32_t index = 0;
    while(Wire.available())    // slave may send less than requested
    {
      buffer[index++] = Wire.read();
    }
    
    Serial.write(buffer, BUFFER_SIZE);
  }
}
