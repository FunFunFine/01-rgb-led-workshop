#include <Arduino.h>
#include <MD_TCS230.h>

#define  S0_OUT  2
#define  S1_OUT  3
#define  S2_OUT  4
#define  S3_OUT  5
MD_TCS230 ColorSensor(S2_OUT, S3_OUT, S0_OUT, S1_OUT);

#define R_OUT 6
#define G_OUT 7
#define B_OUT 8

void setup()
{
    Serial.begin(115200);
    Serial.println("Started!");

    sensorData whiteCalibration;
    whiteCalibration.value[TCS230_RGB_R] = 111060;
    whiteCalibration.value[TCS230_RGB_G] = 105240;
    whiteCalibration.value[TCS230_RGB_B] = 130580;

    sensorData blackCalibration;
    blackCalibration.value[TCS230_RGB_R] = 9540;
    blackCalibration.value[TCS230_RGB_G] = 9190;
    blackCalibration.value[TCS230_RGB_B] = 11870;

    ColorSensor.begin();
    ColorSensor.setDarkCal(&blackCalibration);
    ColorSensor.setWhiteCal(&whiteCalibration);

    pinMode(R_OUT, OUTPUT);
    pinMode(G_OUT, OUTPUT);
    pinMode(B_OUT, OUTPUT);
}

void loop() 
{
    colorData rgb;
    ColorSensor.read();
    while (!ColorSensor.available())
        ;
    ColorSensor.getRGB(&rgb);
    print_rgb(rgb);
    delay(1000);
}

void print_rgb(colorData rgb)
{
	Serial.print(rgb.value[TCS230_RGB_R]);
	Serial.print(" ");
	Serial.print(rgb.value[TCS230_RGB_G]);
	Serial.print(" ");
	Serial.print(rgb.value[TCS230_RGB_B]);
	Serial.println();
}
