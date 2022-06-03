#include<Wire.h>
 
#define MPU 0x68
  const  int FLEX_PIN = A0; //27

  int flexADC_min = 1023;
  int flexADC_max = 0;
  int maxGy = 512;
  int minGy = -512;
int16_t ivmeX,ivmeY,ivmeZ,IsI,GyX,GyY,GyZ;
int GyYY;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0); 
  Wire.endTransmission(true);
   // put your setup code here, to run once:
  pinMode(FLEX_PIN, INPUT);
}

void loop() {
  verileriOku(); // put your main code here, to run repeatedly:
  int flexADC = analogRead(FLEX_PIN);
  flexADC = 1023 - flexADC;
  if (flexADC > flexADC_max) flexADC_max = flexADC;
  if (flexADC < flexADC_min) flexADC_min = flexADC; 
  flexADC = map(flexADC, flexADC_min, flexADC_max, 0, 1023);
  //Serial.println(flexADC);
  Serial.println( String(flexADC)+ "*" + String(GyYY));

  
  delay(20);
}
void verileriOku(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // mpu6050 nin ilk sensör verisinin adresi.
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true); //0X3B den başlayan 14 bitlik veri istendi. İçinde tüm değerlerimiz var.
  GyX=Wire.read()<<8|Wire.read(); 
  GyY=Wire.read()<<8|Wire.read();  
  GyY=Wire.read()<<8|Wire.read(); 
  if (GyY > maxGy) maxGy = GyY ;
  if ( GyY < minGy) minGy = GyY ;
  GyYY=map(GyY,minGy,maxGy,-512,512);  
 
 
   
}
