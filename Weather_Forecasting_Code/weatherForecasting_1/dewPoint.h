#ifndef DESCENT_ANALYSIS_H
#define DESCENT_ANALYSIS_H

#include <iostream>
#include <cmath>

inline double dewPointCalculator(double relativeHumidity, double temperature)
{
    //an intermediate maths value that treats the temperature and relative humidity
    double dewpointFactor = (((17.27 * temperature)/(237.7 * temperature)) + log(relativeHumidity/100));
    double dewPoint = ((237.7 * dewpointFactor)/(17.27 - dewpointFactor));
    return dewPoint;
}

//double readCurrentTemperature(){}
//double readCurrentAltitude(){}
//double readCurrentRelativeHumidity(){}

inline double deltaTemperature()
{
    //For the moment we are just setting random values, later on we will read values from the graphs produced by app.py
    double initialTemperature = 1000;
    double finalTemperature = 1034;
    double deltaPressure = initialTemperature - finalTemperature;
    return deltaPressure;
    //TODO!
}

inline double deltaAltitude()
{
    //For the moment we are just setting random values, later on we will read values from the graphs produced by app.py
    double initialTemperature = 1000;
    double finalTemperature = 1034;
    double deltaPressure = initialTemperature - finalTemperature;
    return deltaPressure;
    //TODO!
}

inline double environmentalLapseRate(double dPressure, double dAltitude)
{
    double lapseRatePerMetre = -(dPressure/dAltitude);
    return 1000 * lapseRatePerMetre;
}


inline double cloudBaseLevel(double temperature, double dewPoint, double dPressure, double dAltitude)
{
    return (temperature - dewPoint) * environmentalLapseRate(dPressure, dAltitude);
}

inline int calculateStabilityIndex(double ELR) {
    const double MALR = 6.0; // Moist adiabatic benchmark (°C/km)
    const double DALR = 9.8; // Dry adiabatic benchmark (°C/km)
    
    // Percentage position between moist and dry limits
    double decimalStabilityIndex = ((ELR - MALR) / (DALR - MALR)) * 100.0;
    if(decimalStabilityIndex < 0)
    {
        return 1;
    }
    else if((decimalStabilityIndex >= 0) && (decimalStabilityIndex < 50))
    {
        return 2;
    }
    else if(decimalStabilityIndex == 50)
    {
        return 3;
    }
    else if((decimalStabilityIndex > 50) && (decimalStabilityIndex < 100))
    {
        return 4;
    }
    else if(decimalStabilityIndex = 100)
    {
        return 5;
    }
    else if(decimalStabilityIndex > 100)
    {
        return 6;
    }

}

#endif