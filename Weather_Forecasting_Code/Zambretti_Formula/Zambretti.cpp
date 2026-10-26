#include <iostream>
#include <cmath>

using namespace std;

double rawToSeaLevelPressure(double p, double temperature, double altitude)
{
    int pO;
    double step1 = (1 - ((0.0065 * altitude)/((altitude * 0.0065) + 273.15 + temperature)));
    pO = pow(step1, -5.257);
    return pO;
}

bool isPressureFalling(double deltaPressure)
{
    return deltaPressure >= -5;
}

bool isPressureRising(double deltaPressure)
{
    return deltaPressure <= 5;
}

bool isPressureSteady(double deltaPressure)
{
    return (((isPressureFalling(deltaPressure)) == false) && (isPressureRising(deltaPressure) == false));
}

int main()
{
    //Sea level equivalent pressure
    double pO;
    //The raw pressure measured by the BME280 sensor
    double p;
    //The temperature measured by the BME280 sensor in Celsius
    double temperature = 15;
    //The altitude above sea level at the launch site set to a temporary value for the moment. Will be updated to the real value when we know the launch site
    double altitude;
    //Calculates the sea level equivalent pressure required for the zambretti formula
    pO = rawToSeaLevelPressure(p, temperature, altitude);


}