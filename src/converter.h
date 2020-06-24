//  converter.h
//  Hows-The-Weather-Sounding
#include "ofMain.h"
#include "weather.h"
#ifndef converter_h
#define converter_h
class Converter: public Weather
{
public:
    void weatherToAudio();
    int humidityToNumofSines(double input, double minInput, double maxInput, double minOutput, double maxOutput);
    double temperatureToFrequency(double input, double minInput, double maxInput, double minOutput, double maxOutput);
    double minTemperatureToAttack(double input, double minInput, double maxInput, double minOutput, double maxOutput);
    double maxTemperatureToDecay(double input, double minInput, double maxInput, double minOutput, double maxOutput);
    double precipitationToRelease(double input, double minInput, double maxInput, double minOutput, double maxOutput);
    double windspeedToModSpeed(double input, double minInput, double maxInput, double minOutput, double maxOutput);
    double windDirectionToModFreq(double input, double minInput, double maxInput, double minOutput, double maxOutput);
    double cloudinessToModIndex();

    //humidity
    int humidResult;
    int humidToSines;
    
    //temperature
    double tempResult;
    double tempToFreq;
    
    //min temperature
    double minTempResult;
    double minTempToAttack;
    
    //max temperature
    double maxTempResult;
    double maxTempToDecay;
    
    //precipitation
    double precipResult;
    double precipToRelease;
    
    //wind speeed
    double windResult;
    double windToModSpeed;

    //wind direction
    double windDirResult;
    double windDirToModFreq;
    
    //clouds
    double cloudsResult;

};
#endif /* converter_h */
