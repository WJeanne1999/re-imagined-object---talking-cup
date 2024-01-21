#include <SoftwareSerial.h>

int ThermistorPin = A0; 
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

int buttonPin = 2;      
int REC_LED = 13;        
int isRecording = false; 

SoftwareSerial mySerial(10, 11); 

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(REC_LED, OUTPUT);

  mySerial.begin(9600);
}

void loop() {
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  T = T - 273.15;
  T = (T * 9.0) / 5.0 + 32.0;

  Serial.print("Temperature: ");
  Serial.print(T);
  Serial.println(" F");

  if (T > 44.65 && !isRecording) {
    
    digitalWrite(REC_LED, HIGH); 
    playRecordingOnISD1820();
  }

  int buttonState = digitalRead(buttonPin);



  delay(1000); 
}

void playRecordingOnISD1820() {
  mySerial.write(0x31); 
  delay(3000);          
  digitalWrite(REC_LED, LOW); 
}
