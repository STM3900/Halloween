#include <Arduino.h>

/* Déclaration des pins */
const byte redPinLeft = 9;
const byte greenPinLeft = 10;
const byte bluePinLeft = 11;

const byte redPinRight = 3;
const byte greenPinRight = 5;
const byte bluePinRight = 6;

// sert à stocker la valeur de la couleur des LEDS
byte oldRedPinRight;
byte oldGreenPinRight;
byte oldBluePinRight;

const int buzPin = 2;     // Buzzer
const int sensorPin = A0; //Capteur de luminosité

//Variables
int sensorVal; // Analog value from the sensor

/** Affiche une couleur */
void displayColor(byte r, byte g, byte b)
{
  // Assigne l'état des broches
  analogWrite(redPinLeft, r);
  analogWrite(greenPinLeft, g);
  analogWrite(bluePinLeft, b);

  analogWrite(redPinRight, r);
  analogWrite(greenPinRight, g);
  analogWrite(bluePinRight, b);

  oldRedPinRight = r;
  oldGreenPinRight = g;
  oldBluePinRight = b;
}

/* Buzzer */
void buzTV(int duration)
{
  tone(buzPin, random(70, 666), duration);
  //delay(duration);
}

void buzChaos(int duration)
{
  int delay1 = random(0, duration + 1);
  int delay2 = random(0, duration + 1 - delay1);
  int delay3 = random(0, duration + 1 - delay1 - delay2);
  int delay4 = random(0, duration + 1 - delay1 - delay2 - delay3);

  tone(buzPin, random(666, 999), delay2);
  delay(delay2);
  tone(buzPin, random(666, 999), delay1);
  delay(delay1);
  tone(buzPin, random(666, 999), delay4);
  delay(delay4);
  tone(buzPin, random(666, 999), delay2);
  delay(delay2);
}

void transitionRedLight(byte rValue, int delayTime)
{
  if (rValue > oldRedPinRight)
  {
    for (int i = 0; i < rValue + 1; i++)
    {
      displayColor(i, 0, 0);
      if (delayTime > 0)
      {
        delay(delayTime / rValue);
      }
    }
  }
  else
  {
    int delayDiv = oldRedPinRight;
    for (int i = delayDiv; i >= rValue; i--)
    {
      displayColor(i, 0, 0);
      if (delayTime > 0)
      {
        delay(delayTime / delayDiv);
      }
    }
  }
}

void blinkRedLight(byte r, int delayTime)
{
  transitionRedLight(10, delayTime);
  buzTV(delayTime);
  transitionRedLight(r * 0.75, delayTime * 4);
  buzTV(delayTime * 4);
  transitionRedLight(10, delayTime);
  buzTV(delayTime);
  transitionRedLight(r * 0.75, delayTime);
  buzTV(delayTime);
  transitionRedLight(r, delayTime * 4);
}

void blackout(int duration)
{
  int currentColor = oldRedPinRight;
  transitionRedLight(0, 0);
  tone(buzPin, random(70, 90), duration);
  delay(duration);
  transitionRedLight(currentColor, 0);
}

void whiteWoke(int duration)
{
  displayColor(255, 255, 255);
  buzChaos(duration);
  displayColor(0, 0, 0);
}

void ledAnimation()
{
  delay(10000);
  transitionRedLight(100, 4000);
  delay(5000);
  blinkRedLight(200, 50);
  transitionRedLight(100, 1000);
  delay(4500);
  blinkRedLight(200, 40);
  blinkRedLight(200, 100);
  delay(3000);
  blinkRedLight(200, 30);
  blinkRedLight(200, 100);
  blinkRedLight(200, 50);
  blinkRedLight(200, 20);
  transitionRedLight(100, 1000);
  delay(4000);
  blackout(2000);
  delay(5000);
  blinkRedLight(200, 30);
  blinkRedLight(200, 100);
  blinkRedLight(200, 50);
  blinkRedLight(200, 40);
  blinkRedLight(200, 20);
  blinkRedLight(200, 10);
  blackout(300);
  delay(50);
  blackout(100);
  delay(100);
  blackout(200);
  whiteWoke(1000);
  delay(1000);
  transitionRedLight(100, 4000);
}

void setup()
{
  pinMode(redPinLeft, OUTPUT);
  pinMode(greenPinLeft, OUTPUT);
  pinMode(bluePinLeft, OUTPUT);

  pinMode(redPinRight, OUTPUT);
  pinMode(greenPinRight, OUTPUT);
  pinMode(bluePinRight, OUTPUT);

  Serial.begin(9600);

  displayColor(0, 0, 0);
}

void loop()
{
  sensorVal = analogRead(sensorPin);

  sensorVal < 125
      ? ledAnimation()
      : displayColor(0, 0, 0);

  delay(500);
}
