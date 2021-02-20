#define Rpin 11
#define Gpin 10
#define Bpin 9
#define Mpin 6
#define delayLEDS 1
#define sensorPin A0
#define top 15
#define bottom 0
float r = 0, g = 0, b = 0;
float mid = top - bottom;
float midmid = top - mid;

float sensorValue = 0, filteredSignal = 0;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    MainFunction();
}

void MainFunction()
{
    sensorValue = (float)analogRead(sensorPin) * (5.0 / 1024) - 2.5;
    FilterSignal(sensorValue);
    Serial.println(filteredSignal);
    CompareSignalFiltered(filteredSignal);
}

void FilterSignal(float sensorSignal)
{
    filteredSignal = (8 * sensorSignal);
}

void CompareSignalFiltered(float filteredSignal)
{
    r = map(filteredSignal, mid, top, 0, 255);
    g = map(filteredSignal, top - midmid, bottom + midmid, 0, 255);
    b = map(filteredSignal, mid, bottom, 0, 255);

    // Sets RGB LED lights
    RGBColor(r, g, b);

    // Activate Vibration Motor
    RunMotor(filteredSignal);
}

void RunMotor(int filteredSignal)
{
    int strength = map(filteredSignal, bottom, top, 0, 255);
    analogWrite(Mpin, strength);
}

void RGBColor(int Rcolor, int Gcolor, int Bcolor)
{
    analogWrite(Rpin, Rcolor);
    analogWrite(Gpin, Gcolor);
    analogWrite(Bpin, Bcolor);
    delay(delayLEDS);
}
