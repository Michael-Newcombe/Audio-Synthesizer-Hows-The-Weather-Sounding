//  weather.cpp
//  Hows-The-Weather-Sounding
#include "weather.h"

//--------------------------------------------------------------
void Weather::hitApi(bool _hit)
{
    usingGui = _hit;
}

//--------------------------------------------------------------
void Weather::weatherData()
{
//if the user is using the any gui elements then make a request otherwise don't
if(usingGui == true){
    
    //api link
    url = "http://api.openweathermap.org/data/2.5/weather?q="+changeCity+"&appid=c91a69107ac437c98e8f6d821ba8bd3c";
    
    parsingSuccessful = result.open(url);
    
    if (parsingSuccessful)
    {
        ofLogNotice("weather::setup") << result.getRawString();
    }
    else
    {
        ofLogNotice("weather::setup") << "Failed to parse JSON" << endl;
    }
    
    //accessing and storing the JSON values
    
    //cod code
    Json::Value& cod = result["cod"];
    codCode = cod.asString();
          
    if(codCode == "200"){
    
    //city
    Json::Value& city = result["name"];
    cityName = city.asString();
    
    //temperaturer
    Json::Value& temperature = result["main"]["temp"];
    temperatureValue = temperature.asDouble();
    temperatureValue -= 273.15;
    temperatureText = to_string(lround(temperatureValue));
    
    //min temperaturer
    Json::Value& minTemperature = result["main"]["temp_min"];
    minTemperatureValue = minTemperature.asDouble();
    minTemperatureValue -= 273.15;
    minTemperatureText = to_string(lround(minTemperatureValue));
    
    //max temperaturer
    Json::Value& maxTemperature = result["main"]["temp_max"];
    maxTemperatureValue = maxTemperature.asDouble();
    maxTemperatureValue -= 273.15;
    maxTemperatureText = to_string(lround(maxTemperatureValue));
    
    //humidity
    Json::Value& humidity = result["main"]["humidity"];
    humidityValue = humidity.asInt();
    humidityText = to_string(humidityValue);
    
    //precipitation
    Json::Value& precipitation = result["rain"]["3h"];
    precipitationValue = precipitation.asDouble();
    precipitationText = to_string(lround(precipitationValue));
    
    //wind speed
    Json::Value& wind = result["wind"]["speed"];
    windSpeedValue = wind.asDouble();
    windSpeedValue *= 2.2369;
    windSpeedText = to_string(lround(windSpeedValue));
    
    //wind direction
    Json::Value& windDir = result["wind"]["deg"];
    windDirValue = windDir.asDouble();
    windDirText = to_string(lround(windDirValue));
    
    //cloud Percentage
    Json::Value& cloudPercentage = result["clouds"]["all"];
    cloudsValue = cloudPercentage.asDouble();
    cloudsText = to_string(lround(cloudsValue));
        
    celsius = "C";
    mph = "MPH";
    degrees = "DEG";
    percent = "%";
    millimeters = "MM";

    }
          
    else{
        
        cityName = "N/A";
        temperatureText = "N/A";
        minTemperatureText = "N/A";
        maxTemperatureText = "N/A";
        humidityText = "N/A";
        precipitationText = "N/A";
        windSpeedText = "N/A";
        windDirText = "N/A";
        
        celsius = "";
        mph = "";
        degrees = "";
        percent = "";
        millimeters = "";

    }
  }
}
//--------------------------------------------------------------
void Weather::draw() {
    
    //drawing the weather valus to the screen
    ofDrawBitmapString("City:", 20, 144);
    ofDrawBitmapString(cityName, 172, 144);

    ofDrawBitmapString("Temperature:", 20, 182);
    ofDrawBitmapString(temperatureText+" "+celsius, 172, 182);
    
    ofDrawBitmapString("Min Temperature:", 20, 222);
    ofDrawBitmapString(minTemperatureText+" "+celsius, 172, 222);
    
    ofDrawBitmapString("Max Temperature:", 20, 262);
    ofDrawBitmapString(maxTemperatureText+" "+celsius, 172, 262);
    
    ofDrawBitmapString("Humidity:", 20, 302);
    ofDrawBitmapString(humidityText+" "+percent, 172, 302);
    
    ofDrawBitmapString("Precipitation:", 20, 342);
    ofDrawBitmapString(precipitationText+" "+millimeters, 172, 342);

    ofDrawBitmapString("Wind Speed:", 20, 382);
    ofDrawBitmapString(windSpeedText+" "+mph, 172, 382);
    
    ofDrawBitmapString("Wind Direction:", 20, 422);
    ofDrawBitmapString(windDirText+" "+degrees, 172, 422);
    
    ofDrawBitmapString("Cloud Percentage:", 20, 462);
    ofDrawBitmapString(cloudsText+" "+percent, 172, 462);
    
}

//--------------------------------------------------------------
string Weather::invalidCity(){
    
    return codCode;
}


