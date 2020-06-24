#pragma once
#include "ofMain.h"
#include "synthesizer.h"
#include "weather.h"
#include "converter.h"
#include "ofxDatGui.h"

using namespace std;

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    //destructor
    ~ofApp();
    
    //openframeworks audio set up
    //audio out function
    void audioOut(ofSoundBuffer & buffer);
    //openframeworks sound object
    ofSoundStream soundStream;
    //buffer size
    int bufferSize;
    //sample rate
    int sampleRate;
    //maximilian mixer object
    maxiMix mix;
    //number of output channels
    double outputs[2];
    
    //oscilloscope variables
    float waveform[8096];
    int waveIndex;
    
    //synth objects
    Synthesizer* synth;
    Synthesizer* synth2;
    Synthesizer* synth3;
    //synth using weather values
    void weatherSynth();

    //weather class
    Weather weatherClass;
    
    //converter class
    Converter c;

    //drop down menu
    ofxDatGuiDropdown* dropDown;
    //drop down event function
    void onDropdownEvent(ofxDatGuiDropdownEvent e);
    
    //search bar
    ofxDatGuiTextInput* searchBox;
    //text box event function
    void onTextInputEvent(ofxDatGuiTextInputEvent e);
    //user feeback message
    string invalidEntry;
    //check user input
    bool invalidCity;
    
    //oscillators slider
    ofxDatGuiSlider* oscSlider;
    //slider event function
    void onSliderEvent(ofxDatGuiSliderEvent e);
    //variable for storing current number of sines waves value for slider
    int currentNumSines;
    
    //frequecny slider
    ofxDatGuiSlider* freqSlider;
    //variable for storing current frequecny value for slider
    int currentFreq;
    
    //attack slider
    ofxDatGuiSlider* attSlider;
    //variable for storing current attack value for slider
    int currentAtt;
    
    //decay slider
    ofxDatGuiSlider* decaySlider;
    //variable for storing current decay value for slider
    int currentDecay;
    
    //release slider
    ofxDatGuiSlider* releaseSlider;
    //variable for storing current release value for slider
    int currentRelease;
    
    //amp mod slider
    ofxDatGuiSlider* ampModSlider;
    //variable for storing current amp mod value for slider
    int currentAmpMod;
    
    //freq mod slider
    ofxDatGuiSlider* freqModSlider;
    //floating point paramter for freq mod slider
    ofParameter<float> ofParamFloat;
    //variable for storing current feq mod value for slider
    float currentFreqMod;
    
    //index mod slider
    ofxDatGuiSlider* indexModSlider;
    //variable for storing current feq mod index value for slider
    int currentModIndex;
    
    //enable sliders button
    ofxDatGuiToggle* editSynth;
    //on button event function
    void onToggleEvent(ofxDatGuiToggleEvent e);
    
    //play button
    ofImage playButton;
    //play button background colour
    int playButtonCol;
    
    //app title
    ofTrueTypeFont font;
    
};

