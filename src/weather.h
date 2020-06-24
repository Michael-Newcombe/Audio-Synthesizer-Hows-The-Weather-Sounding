//  weather.h
//  Hows-The-Weather-Sounding
#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxDatGui.h"

#ifndef weather_h
#define weather_h

class Weather
{
public:
    virtual void weatherData();
    string changeCity;
    string invalidCity();
    void hitApi(bool _hit);
    void draw();
    
protected:
    string codCode;
    string url;
    string cityName;
    bool usingGui;
    bool parsingSuccessful;
    int humidityValue;
    double temperatureValue;
    double maxTemperatureValue;
    double minTemperatureValue;
    double windSpeedValue;
    double windDirValue;
    double precipitationValue;
    double cloudsValue;
    ofxJSONElement result;
    
    string temperatureText;
    string maxTemperatureText;
    string minTemperatureText;
    string celsius;
    string windSpeedText;
    string mph;
    string windDirText;
    string degrees;
    string precipitationText;
    string millimeters;
    string humidityText;
    string cloudsText;
    string percent;

};

#endif /* weather_h */
