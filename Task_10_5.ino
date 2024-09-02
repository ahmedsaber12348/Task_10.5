#include <Wire.h>

int16_t ax, ay, az;
int16_t gx, gy, gz;
float yaw;
const int MPU_ADDR = 0x68;  // I2C address of the MPU6050


void setup() {
  Serial.begin(9600);

  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);  
  Wire.write(0);     
  Wire.endTransmission(true);


  yaw = 0;
}

void loop() {


  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);  
  
  ax = Wire.read() << 8 | Wire.read();
  ay = Wire.read() << 8 | Wire.read();
  az = Wire.read() << 8 | Wire.read();
  
  Wire.read();
  Wire.read();
  
  gx = Wire.read() << 8 | Wire.read();
  gy = Wire.read() << 8 | Wire.read();
  gz = Wire.read() << 8 | Wire.read();


  float gyroZrate = gz / 131.0;  
  yaw += gyroZrate * 0.01;          
  Serial.print("Yaw: ");
  Serial.println(yaw);
  delay(10);  
}
