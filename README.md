# TestUcusKanatPerformansTakibi-OlcmeProje
## My first labwiev project which using with serial communication

## Projenin Amacı
Üretilen kanatların farklı ivme ve eksen konumlarında esneklik performansını incelemek için esneklik ve gyro sensörlerini Labwiev üzerinde görselleştirmek.


## Sensörler ##
**Sensör Listesi**  | **Alınan veri**
------------- | -------------
Flex Sensor  | Büküm
MPU6050  | Gyro



## Sensör Bağlantıları ##
**MPU6050**

<img src="https://user-images.githubusercontent.com/74202445/171967108-e6ca7722-4119-4477-9d81-35fcf6ed378d.png" width="350" height="300" >

**Flex Sensor**

![flex-connection](https://user-images.githubusercontent.com/74202445/171967242-dd7e37de-004f-4456-9938-6adcc92e30a6.png)


## Ardunio Kodu ##
**sensörler için ekstra kütüphanelere başvurulmamıştır**
```ruby
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
```
## Labwiev Görselleri ##
**Labview Front Paneli**
https://drive.google.com/file/d/1J91extLnc7UoXQ86piGZU80naYX26jYJ/view?usp=sharing

**Labview Blok Diyagramı**
(https://drive.google.com/file/d/1O4bfz09QpJNrd5YybHd7UZc4xHhiODJh/view?usp=sharing)

** İncelediğiniz için teşekkürler, diğer repository içeriklerini profilimden inceleyebilirsiniz :zap: **
