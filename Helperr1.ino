
#include <Wire.h>

int btnPin1 = 9;

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int precBtn1 = HIGH;

void setup(){
  pinMode(btnPin1, INPUT_PULLUP);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); 
  Wire.write(0);     
  Wire.endTransmission(true);
  Serial.begin(38400);
}
void loop(){
  int resultBtn1 = digitalRead(btnPin1);
  if (precBtn1 == HIGH && resultBtn1 == LOW)
  {
    startBatch();
  }
  if (resultBtn1==LOW)
  {
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B); 
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr,14,true);      
      AcX=Wire.read()<<8|Wire.read();    
      AcY=Wire.read()<<8|Wire.read(); 
      AcZ=Wire.read()<<8|Wire.read(); 
      Tmp=Wire.read()<<8|Wire.read(); 
    GyX=Wire.read()<<8|Wire.read();  
    GyY=Wire.read()<<8|Wire.read(); 
    GyZ=Wire.read()<<8|Wire.read(); 

    Serial.print("START");
    Serial.print(" "); Serial.print(AcX);
    Serial.print(" "); Serial.print(AcY);
    Serial.print(" "); Serial.print(AcZ);
    Serial.print(" "); Serial.print(GyX);
    Serial.print(" "); Serial.print(GyY);
    Serial.print(" "); Serial.print(GyZ);
    Serial.println(" END");
  }

    if (precBtn1 == LOW && resultBtn1 == HIGH)
  {
    closeBatch();
  }

   precBtn1 = resultBtn1;
}

void startBatch()
{
  Serial.println("STARTING BATCH");
}

void closeBatch()
{
  Serial.println("CLOSING BATCH");
}

