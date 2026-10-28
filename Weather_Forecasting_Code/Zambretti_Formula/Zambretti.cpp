#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

double rawToSeaLevelPressure(double p, double temperature, double altitude)
{
    double pO;
    double step1 = (1 - ((0.0065 * altitude)/((altitude * 0.0065) + 273.15 + temperature)));
    pO = p * pow(step1, -5.257);
    return pO;
}

double changeInPressure() {
    // 1. Open the text file created by Python
    ifstream infile("pressure_log.txt");
    string line;
    vector<double> pressures; // Dynamic list to store all pressure values

    // 2. Read the file line by line until the end
    while (getline(infile, line)) {
        if (!line.empty()) {
            // Convert the text string into a decimal number (float) and store it
            pressures.push_back(stod(line));
        }
        else
        {
            cout<<"Waiting for the next line...";
        }
    }
    infile.close(); // Always close the file when finished reading

    // 3. Safety check: make sure we have at least 2 readings to compare
    if (pressures.size() < 2) {
        cout << "Waiting for more data points..." << endl;
        return 0.0;
    }

    // 4. Grab the very first reading (initial) and the latest reading (final)
    double initialPressure = pressures.front(); // First item in the list
    double finalPressure = pressures.back();   // Last item in the list
    
    // 5. Calculate Delta P
    double deltaPressure = finalPressure - initialPressure;

    cout << "Initial Pressure: " << initialPressure << " hPa" << endl;
    cout << "Final Pressure: " << finalPressure << " hPa" << endl;
    cout << "Calculated Delta P: " << deltaPressure << " hPa" << endl;

    return deltaPressure;
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

bool isEasternleyWind(double windDirection)
{
    return (windDirection >= 67.5) && (windDirection <= 112.5);
}

bool isSouthernleyWind(double windDirection)
{
    return (windDirection >= 157.5) && (windDirection <= 200.5);
}

bool isNorthernleyWind(double windDirection)
{
    return (windDirection >= 22.5) && (windDirection >= 337.5);
}

bool isWesternleyWind(double windDirection)
{
    return (windDirection >= 247.5) && (windDirection <= 292.5);
}

string zambrettiWeather(int zambrettiIndex, double deltaPressure, double windDirection)
{
    if(isEasternleyWind(windDirection) || isWesternleyWind(windDirection))
    {
        zambrettiIndex += 1;
    }
    else if(isSouthernleyWind(windDirection))
    {
        zambrettiIndex += 2;
    }
    else if(isNorthernleyWind(windDirection))
    {
        zambrettiIndex -= 1;
    }

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
    //The wind direction measured by our cansat, for the moment it is set to the dummy value 180, later we will properly measure this value
    double windDirection = 180;
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
    deltaPressure =  changeInPressure();
    //Zambretti Index gives us what sort of weather we have
    int zambrettiIndex = (int)index(pO, deltaPressure);

    cout<<zambrettiWeather(zambrettiIndex, deltaPressure, windDirection)<<endl;
    

}