#include <iostream>
#include <cmath>

using namespace std;

double rawToSeaLevelPressure(double p, double temperature, double altitude)
{
    double pO;
    double step1 = (1 - ((0.0065 * altitude)/((altitude * 0.0065) + 273.15 + temperature)));
    pO = p * pow(step1, -5.257);
    return pO;
}

double changeInPressure(double pO)
{
    //calculate the amount of pressure change over a 3 hour window at the ground station before launching the cansat. Flask will make a graph
    return pO; //TODO!
}

bool isPressureFalling(double deltaPressure)
{
    return deltaPressure > -1.6;
}

bool isPressureRising(double deltaPressure)
{
    return deltaPressure < 1.6;
}

bool isPressureSteady(double deltaPressure)
{
    return (((isPressureFalling(deltaPressure)) == false) && (isPressureRising(deltaPressure) == false));
}

double index(double pO, double deltaPressure)
{
    if(isPressureFalling(deltaPressure) == true)
    {
        return 127 - (0.12 * pO);
    }
    else if(isPressureRising(deltaPressure) == true)
    {
        return 144 - (0.13 * pO);

    }
    else
    {
        return 185 - (0.16 * pO);
    }
}

string zambrettiWeather(int zambrettiIndex, double deltaPressure)
{
    //if(isEasternleyWind(double windDirection) || isWesternlyWind(double windDirection))
    //{
        //zambrettiIndex += 1;
    //}
    //else if(isSouthernleyWind(double windDirection))
    //{
        //zambrettiIndex += 2;
    //}
    //else if(isNorthenlyWind(double windDirection))
    //{
        //zambrettiIndex -= 1;
    //}

    if(isPressureFalling(deltaPressure))
    {
        switch(zambrettiIndex)
        {
            case 1:
                return "Settled Fine";
            case 2:
                return "Fine Weather";
            case 3:
                return "Fine, Becoming Less Settled";
            case 4:
                return "Fairly Fine, Showery Later";
            case 5:
                return "Showery, Becoming More Unsettled";
            case 6:
                return "Unsettled, Rain Later";
            case 7:
                return "Rain at Times, Worse Later";
            case 8:
                return "Rain at Times, Becoming Very Unsettled";
            case 9:
                return "Very Unsettled, Rain";
            default:
                return "Unknown Falling State";
        }
    }
    else if(isPressureSteady(deltaPressure))
    {
        switch(zambrettiIndex)
        {
            case 10:
                return "Settled Fine";
            case 11:
                return "Fine Weather";
            case 12:
                return "Fine, Possibly Showers";
            case 13:
                return "Fairly Fine, Showers Likely";
            case 14:
                return "Showery, Bright Intervals";
            case 15:
                return "Changeable, Some Rain";
            case 16:
                return "Unsettled, Rain at Times";
            case 17:
                return "Rain at Frequent Intervals";
            case 18:
                return "Very Unsettled, Rain";
            case 19:
                return "Stormy, Much Rain";
            default:
                return "Unknown Steady State";
        }
    }
    else if(isPressureRising(deltaPressure))
    {
        switch(zambrettiIndex)
        {
            case 20:
                return "Settled Fine";
            case 21:
                return "Fine Weather";
            case 22:
                return "Becoming Fine";
            case 23:
                return "Fairly Fine, Improving";
            case 24:
                return "Fairly Fine, Possibly Showers Early";
            case 25:
                return "Showery Early, Improving";
            case 26:
                return "Changeable, Mending";
            case 27:
                return "Rather Unsettled, Clearing Later";
            case 28:
                return "Unsettled, Probably Improving";
            case 29:
                return "Unsettled, Short Fine Intervals";
            case 30:
                return "Very Unsettled, Finer at Times";
            case 31:
                return "Stormy, Possibly Improving";
            case 32:
                return "Stormy, Much Rain";
            default:
                return "Unknown Rising State";
        }
    }
    else
    {
        return "Unknown Weather Conditions - error";
    }
}

int main()
{
    //Sea level equivalent pressure in hectopascals
    double pO;
    //The raw pressure measured by the BME280 sensor in hectopascals
    double p;
    //The temperature measured by the BME280 sensor in Degrees Celsius
    double temperature = 15;
    //The altitude above sea level (in meters) at the launch site set to a temporary value for the moment. Will be updated to the real value when we know the launch site
    double altitude = 40;
    //Calculates the sea level equivalent pressure required for the zambretti formula
    pO = rawToSeaLevelPressure(p, temperature, altitude);
    double deltaPressure;
    //Calculates change in pressure
    deltaPressure =  changeInPressure(pO);
    //Zambretti Index gives us what sort of weather we have
    int zambrettiIndex = (int)index(pO, deltaPressure);

    cout<<zambrettiWeather(zambrettiIndex, deltaPressure)<<endl;
    

}