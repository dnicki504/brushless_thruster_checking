#include "ESC.h"
#include <GyverJoy.h>

#define LED_PIN (13)                      // Pin for the LED
#define SPEED_MIN (1400)                   // Set the Minimum Speed in microseconds
#define SPEED_MAX (1600)                  // Set the Minimum Speed in microseconds
ESC myESC(3, SPEED_MIN, SPEED_MAX, 1500); // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)

#define JOY1_X_PIN A1
GyverJoy joy1X(JOY1_X_PIN);

#define JOY1_B_PIN A2

void resetTrusters();

void setup()
{
    Serial.begin(9600);
    Serial.println("starting..");
    pinMode(LED_PIN, OUTPUT); // LED Visual Output

    resetTrusters();

    joy1X.invert(true);
    joy1X.calibrate();        // калибровка нуля при запуске
    joy1X.deadzone(30);       // мёртвая зона
    joy1X.exponent(GJ_CUBIC); // экспонента для плавности
}

void resetTrusters()
{
    Serial.println("resetting...");
    digitalWrite(LED_PIN, LOW);
    myESC.arm();
    delay(3000);
    digitalWrite(LED_PIN, HIGH); // LED High Once Armed
}

void loop()
{
    int z10 = analogRead(JOY1_B_PIN);
    Serial.println(z10);
    if (z10 > 1000)
    {
        resetTrusters();
    }

    Serial.print("now ");
    int v = analogRead(1);
    if (joy1X.tick())
    {
        v = joy1X.value();
    }

    Serial.print(v);
    Serial.print(" / ");
    int val = map(v, -255, 255, SPEED_MIN, SPEED_MAX);
    Serial.println(val);
    myESC.speed(val);
    // delay(100);
}
