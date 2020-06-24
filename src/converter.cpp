//  converter.cpp
//  Hows-The-Weather-Sounding

#include "converter.h"

//--------------------------------------------------------------
void Converter::weatherToAudio()
{
    //getting new weather values
    Weather::weatherData();
    
    //storing the weather values to new variables as we don't wont to effect the orginal values
    
     humidToSines =  humidityValue;
    // cout << humidityConvert << endl;
    
    tempToFreq = temperatureValue;
    // cout << temperatureConvert << endl;
    
    minTempToAttack = minTemperatureValue;
    // cout << minTemperatureConvert << endl;
    
    maxTempToDecay = maxTemperatureValue;
    // cout << maxTemperatureConvert << endl;
    
    windToModSpeed = windSpeedValue;
    // cout << windConvert << endl;
    
    windDirToModFreq = windDirValue;
    // cout << windDirConvert << endl;
    
    precipToRelease = precipitationValue;
    // cout << precipitationConvert << endl;
    
    cloudsResult = cloudsValue;
    
}

//--------------------------------------------------------------
//convertinon function that scale numbers up and return the result
int Converter::humidityToNumofSines(double input, double minInput, double maxInput, double minOutput, double maxOutput)

{
    
    humidResult = (maxOutput - minOutput) / (maxInput - minInput) * (input - maxInput) + maxOutput;
    return humidResult;

    
}

//--------------------------------------------------------------
double Converter::temperatureToFrequency(double input, double minInput, double maxInput, double minOutput, double maxOutput)
{
    
    tempResult = (maxOutput - minOutput) / (maxInput - minInput) * (input - maxInput) + maxOutput;
    return tempResult;
    
    
}

//--------------------------------------------------------------
double Converter::minTemperatureToAttack(double input, double minInput, double maxInput, double minOutput, double maxOutput)
{
   
    minTempResult = (maxOutput - minOutput) / (maxInput - minInput) * (input - maxInput) + maxOutput;
   return minTempResult;
    
}

//--------------------------------------------------------------
double Converter::maxTemperatureToDecay(double input, double minInput, double maxInput, double minOutput, double maxOutput)
{
    
    maxTempResult = (maxOutput - minOutput) / (maxInput - minInput) * (input - maxInput) + maxOutput;
    return maxTempResult;
    
}

//--------------------------------------------------------------
double Converter::precipitationToRelease(double input, double minInput, double maxInput, double minOutput, double maxOutput)
{
    
    precipResult = (maxOutput - minOutput) / (maxInput - minInput) * (input - maxInput) + maxOutput;
    return precipResult;
    
}

//--------------------------------------------------------------
double Converter::windspeedToModSpeed(double input, double minInput, double maxInput, double minOutput, double maxOutput)
{
    
    windResult = (maxOutput - minOutput) / (maxInput - minInput) * (input - maxInput) + maxOutput;
    return windResult;
    
}

//--------------------------------------------------------------
double Converter::windDirectionToModFreq(double input, double minInput, double maxInput, double minOutput, double maxOutput)
{
    
    windDirResult = (maxOutput - minOutput) / (maxInput - minInput) * (input - maxInput) + maxOutput;
    return windDirResult;
    
}

//--------------------------------------------------------------
double Converter::cloudinessToModIndex()
{
    
    return cloudsResult;
    
}





