#include <Servo.h>


int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741;
Servo myservo;


void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(0);
}

void loop() {
  int numberOfValues = 60;
  float totalTemperature = 0.0;

   

  for (int i = 0; i < numberOfValues; i++) {
    Vo = analogRead(ThermistorPin);
    R2 = R1 * (1024.0 / (float)Vo - 1.0);
    logR2 = log(R2);
    T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
    T = T - 273.15;
    T = (T * 9.0) / 5.0 + 32.0;

    totalTemperature += T;
    delay(10);
  }

  float average = totalTemperature / numberOfValues;
  Serial.print("Average Temperature: ");
  Serial.println(average);
  totalTemperature = 0; 
  


  if(average >= 80){
    Serial.print("Servo rotate");
    myservo.write(270);
    myservo.write(270);
    delay(3000);
    myservo.write(-270);
    myservo.write(-270);
  }
  
  delay(5000);
}