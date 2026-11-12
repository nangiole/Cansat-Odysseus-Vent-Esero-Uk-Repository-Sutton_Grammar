#include <iostream>
#include <string>
#include <cmath>

double dewPointCalculator(double relativeHumidity, double temperature)
{
    //an intermediate maths value that treats the temperature and relative humidity
    double dewpointFactor = (((17.27 * temperature)/(237.7 * temperature)) + log(relativeHumidity/100));
    double dewPoint = ((237.7 * dewpointFactor)/(17.27 - dewpointFactor));
    return dewPoint;
}

//double readValueTemperature()
//double readValueAltitude()
//double readValueRelativeHumidity()

double deltaTemperature()
{
    //TODO!
}

double deltaAltitude()
{
    //TODO!
}

double lapseRate()
{
    return deltaTemperature()/deltaAltitude();
}

double cloudBaseLevel(double temperature, double dewPoint)
{
    return (temperature - dewPoint) * lapseRate();
}

int main()
{
    double altitude;
    //altitude = readValueAltitude():
    double relativeHumidity;
    //readValueRelativeHumidity();
    double temperature;
    //readValueTemperature();
    double dewPoint = dewPointCalculator(relativeHumidity, temperature);


}