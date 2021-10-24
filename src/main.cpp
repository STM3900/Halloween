#include <Arduino.h>

// Constants
#define DELAY 500 // Delay between two measurements in ms

/* Broches */
const byte redPinLeft = 9;
const byte greenPinLeft = 10;
const byte bluePinLeft = 11;

const byte redPinRight = 3;
const byte greenPinRight = 5;
const byte bluePinRight = 6;

// Parameters
const int sensorPin = A0; // Pin connected to sensor

//Variables
int sensorVal; // Analog value from the sensor
int lux;       //Lux value

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
}

void setup()
{
  pinMode(redPinLeft, OUTPUT);
  pinMode(greenPinLeft, OUTPUT);
  pinMode(bluePinLeft, OUTPUT);

  pinMode(redPinRight, OUTPUT);
  pinMode(greenPinRight, OUTPUT);
  pinMode(bluePinRight, OUTPUT);

  displayColor(0, 0, 0);
  Serial.begin(9600);
}

void loop()
{
  sensorVal = analogRead(sensorPin);
  Serial.print(F("Raw value from sensor = "));
  Serial.println(sensorVal); // the analog reading

  sensorVal < 200 ? displayColor(255, 0, 0) : displayColor(0, 0, 0);

  delay(DELAY);

  /*
  displayColor(255, 0, 0);
  delay(1000);

  displayColor(0, 255, 0);
  delay(1000);

  displayColor(0, 0, 255);
  delay(1000);

  displayColor(255, 0, 255);
  delay(1000);

  displayColor(0, 255, 255);
  delay(1000);

  displayColor(255, 255, 0);
  delay(1000);

  displayColor(255, 255, 255);
  delay(1000);

  displayColor(0, 0, 0);
  delay(1000);
  */
}
