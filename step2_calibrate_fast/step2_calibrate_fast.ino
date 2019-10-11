#include <MD_TCS230.h>
#include <FreqCount.h>

#define  S0_OUT  2
#define  S1_OUT  3
#define  S2_OUT  4
#define  S3_OUT  5

MD_TCS230	CS(S2_OUT, S3_OUT, S0_OUT, S1_OUT);

void setup() 
{
  Serial.begin(115200);
  Serial.println("Press enter to start calibration");
  blockingRead();

  CS.begin();
}

void loop() 
{
    calibrate();
}

String blockingRead()
{
    while (!Serial.available())
        ;
    String command = Serial.readStringUntil('\n');
    return command;
}

void calibrate()
{
    sensorData blackCalibration, whiteCalibration;

    readRaw(blackCalibration, "BLACK");
    CS.setDarkCal(&blackCalibration);

    readRaw(whiteCalibration, "WHITE");
    CS.setWhiteCal(&whiteCalibration);

    Serial.println("Calibration values:");
    Serial.println();
    printCalibration("whiteCalibration", whiteCalibration);
    printCalibration("blackCalibration", blackCalibration);

    Serial.println("Press enter to read RGB value. Send 'retry' to calibrate again");
    while (true)
    {
        String command = blockingRead();
        if (command == "retry")
        {
            return;
        }

        colorData rgb;
        readRgb(rgb);
    }
}

void readRaw(sensorData& sd, const char* cardColor)
{
    Serial.print("Put ");
    Serial.print(cardColor);
    Serial.println(" card on the sensor and press enter");
    blockingRead();

    CS.read();
    while (!CS.available())
        ;
    CS.getRaw(&sd);

    Serial.print(cardColor);
    Serial.println(" calibration finished");
}

void readRgb(colorData& cd)
{
    Serial.println("Reading RGB...");
    
    CS.read();
    while (!CS.available())
        ;
    CS.getRGB(&cd);

    Serial.print(cd.value[TCS230_RGB_R]);
    Serial.print(' ');
    Serial.print(cd.value[TCS230_RGB_G]);
    Serial.print(' ');
    Serial.print(cd.value[TCS230_RGB_B]);
    Serial.println();
}

void printCalibration(const char* variableName, const sensorData& sd)
{
    Serial.print("sensorData "); Serial.print(variableName); Serial.println(";");
    printAssignment(variableName, "R", sd.value[TCS230_RGB_R]);
    printAssignment(variableName, "G", sd.value[TCS230_RGB_G]);
    printAssignment(variableName, "B", sd.value[TCS230_RGB_B]);
}

void printAssignment(const char* variableName, const char* color, int32_t value)
{
    Serial.print(variableName);
    Serial.print(".value[TCS230_RGB_");
    Serial.print(color);
    Serial.print("] = ");
    Serial.print(value);
    Serial.println(";");
}