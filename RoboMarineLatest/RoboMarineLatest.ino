#include <Servo.h>
#include "vec3.h"



#define MOT1PIN 2       // FWD LEFT
#define MOT2PIN 3       // FWD RIGHT
#define MOT3PIN 4       // BACK RIGHT
#define MOT4PIN 5       // BACK LEFT
#define MOT5PIN 6       // LEFT CENTRE
#define MOT6PIN 7       // RIGHT CENTRE

#define CH1PIN 8
#define CH2PIN 9
#define CH3PIN 10
#define CH4PIN 11
#define CH5PIN 12
#define CH6PIN 13

#define USECH1 false
#define USECH2 false
#define USECH3 true
#define USECH4 true
#define USECH5 false
#define USECH6 true

#define MOT1DZ 87
#define MOT2DZ 88
#define MOT3DZ 88
#define MOT4DZ 87
#define MOT5DZ 88
#define MOT6DZ 88

#define PULSEWEIGHT 10

Servo mot1;
Servo mot2;
Servo mot3;
Servo mot4;
Servo mot5;
Servo mot6;

int pulseCh1;
int pulseCh2;
int pulseCh3;
int pulseCh4;
int pulseCh5;
int pulseCh6;

int rawPulseCh1;
int rawPulseCh2;
int rawPulseCh3;
int rawPulseCh4;
int rawPulseCh5;
int rawPulseCh6;

void setup() {
  Serial.begin(9600);
  mot1.attach(MOT1PIN, 1000, 2000);
  mot2.attach(MOT2PIN, 1000, 2000);
  mot3.attach(MOT3PIN, 1000, 2000);
  mot4.attach(MOT4PIN, 1000, 2000);
  mot5.attach(MOT5PIN, 1000, 2000);
  mot6.attach(MOT6PIN, 1000, 2000);
  mot1.write(MOT1DZ);
  mot2.write(MOT2DZ);
  mot3.write(MOT3DZ);
  mot4.write(MOT4DZ);
  // mot5.write(MOT5DZ);
  mot5.write(0);
  // mot6.write(MOT6DZ);
  mot6.write(0);
  if (USECH1) { pinMode(CH1PIN, INPUT); }
  if (USECH2) { pinMode(CH2PIN, INPUT); }
  if (USECH3) { pinMode(CH3PIN, INPUT); }
  if (USECH4) { pinMode(CH4PIN, INPUT); }
  if (USECH5) { pinMode(CH5PIN, INPUT); }
  if (USECH6) { pinMode(CH6PIN, INPUT); }
}

void loop() {
  if (USECH1) {
    rawPulseCh1 = pulseIn(CH1PIN, HIGH);
    pulseCh1 = ((PULSEWEIGHT-1)*pulseCh1 + rawPulseCh1)/PULSEWEIGHT;
  }
  if (USECH2) {
    rawPulseCh2 = pulseIn(CH2PIN, HIGH);
    pulseCh2 = ((PULSEWEIGHT-1)*pulseCh2 + rawPulseCh2)/PULSEWEIGHT;
  }
  if (USECH3) {
    rawPulseCh3 = pulseIn(CH3PIN, HIGH);
    pulseCh3 = ((PULSEWEIGHT-1)*pulseCh3 + rawPulseCh3)/PULSEWEIGHT;
  }
  if (USECH4) {
    rawPulseCh4 = pulseIn(CH4PIN, HIGH);
    pulseCh4 = ((PULSEWEIGHT-1)*pulseCh4 + rawPulseCh4)/PULSEWEIGHT;
  }
  if (USECH5) {
    rawPulseCh5 = pulseIn(CH5PIN, HIGH);
    pulseCh5 = ((PULSEWEIGHT-1)*pulseCh5 + rawPulseCh5)/PULSEWEIGHT;
  }
  if (USECH6) {
    rawPulseCh6 = pulseIn(CH6PIN, HIGH);
    pulseCh6 = ((PULSEWEIGHT-1)*pulseCh6 + rawPulseCh6)/PULSEWEIGHT;
  }
  if (rawPulseCh6<800) { kill(); return; }
  runUpDownMots();
  runFBLRMots();
}

void runUpDownMots()
{
  // int degMot5 = map(pulseCh6, 900, 2000, 0, 1.1*MOT5DZ);
  // int degMot6 = map(pulseCh6, 900, 2000, 0, 1.1*MOT6DZ);
  int degMot5 = map(pulseCh6, 1100, 1900, 0, 170);
  int degMot6 = map(pulseCh6, 1100, 1900, 0, 170);
  mot5.write(degMot5);
  mot6.write(degMot6);
}

void runFBLRMots()
{
  float fb = (pulseCh3-1500)/(float)500; // (Value - Midpoint) / Avg diff;
  float lr = (pulseCh4-1500)/(float)500; // (Value - Midpoint) / Avg diff;
  Serial.println(abs(fb));
  if (abs(fb)>0.5)
  {
    if (fb>0)
    {
      Serial.println("F");
      mot1.write(20);
      mot2.write(160);
      mot3.write(20);
      mot4.write(160);
    }
    if (fb<0)
    {
      Serial.println("B");
      mot1.write(160);
      mot2.write(20);
      mot3.write(160);
      mot4.write(20);
    }    
  }
  else if (abs(lr)>0.5)
  {
    if (lr<0)
    {
      Serial.println("L");
      mot1.write(160);
      mot2.write(160);
      mot3.write(160);
      mot4.write(160);
    }
    if (lr>0)
    {
      Serial.println("R");
      mot1.write(20);
      mot2.write(20);
      mot3.write(20);
      mot4.write(20);
    }    
  }
  else
  {
    Serial.println("0");
    mot1.write(MOT1DZ);
    mot2.write(MOT2DZ);
    mot3.write(MOT3DZ);
    mot4.write(MOT4DZ);
  }
}

void kill()
{
  mot1.write(MOT1DZ);
  mot2.write(MOT2DZ);
  mot3.write(MOT3DZ);
  mot4.write(MOT4DZ);
  // mot5.write(MOT5DZ);
  mot5.write(0);
  // mot6.write(MOT6DZ);
  mot6.write(0);
}
