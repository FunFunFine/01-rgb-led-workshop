#include <Arduino.h>
#include <MD_TCS230.h>

#define R_OUT 6
#define G_OUT 7
#define B_OUT 8

void setup()
{
    pinMode(R_OUT, OUTPUT);
    pinMode(G_OUT, OUTPUT);
    pinMode(B_OUT, OUTPUT);
}

void loop() 
{
    set_rgb_led(255, 0, 0);
    delay(250);
    set_rgb_led(0, 255, 0);
    delay(250);
    set_rgb_led(0, 0, 255);
    delay(250);
}

void set_rgb_led(int r, int g, int b)
{
    analogWrite(R_OUT, 255 - r);
    analogWrite(G_OUT, 255 - g);
    analogWrite(B_OUT, 255 - b);
}
