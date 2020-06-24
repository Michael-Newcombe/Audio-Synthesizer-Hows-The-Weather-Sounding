#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
   
    //setting app window position to top left
    ofSetWindowPosition(0, 0);
    
    //loading font
    font.load("Azonix.otf", 32);
    //loading play button image
    playButton.load("images/play-button2.png");
    //setting play button background colour
    playButtonCol = 72;

    //setting buffer size
    bufferSize = 512;
    //setting sample rate
    sampleRate = 44100;
    
    //creating ofsoundStreamsetting object to set up audio so we can work with the computers sound card
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
    
    //setting up maximilian settings for maximilian libary
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    //setting function which makes request to api to false
    c.hitApi(false);
    //creating 3 new synthesizer objects and settings the synthesizer values to a default sound *the synthesizer must be given inital values otherwise will break*
    synth = new Synthesizer();
    currentFreq = 440;
    synth->settings(12, currentFreq ,1000.0, 500.0, 2000.0, 24.0, 1.0, 50.0);
    synth2 = new Synthesizer();
    synth2->settings(12, currentFreq ,1000.0, 500.0, 2000.0, 24.0, 1.0, 50.0);
    synth3 = new Synthesizer();
    synth3->settings(12, currentFreq ,1000.0, 500.0, 2000.0, 24.0, 1.0, 50.0);
    
    cout << "temperature (frequency) " << c.tempResult << endl;
    cout << "humidity ( num of sines) " << c.humidResult << endl;
    cout << "min temperature (attack) " << c.minTempResult << endl;
    cout << "max temperature (decay) " << c.maxTempResult << endl;
    cout << "precipitation (release) " << c.precipResult << endl;
    cout << "wind speed (mod speed) " << c.windResult << endl;
    cout << "wind direction (mod freq) " << c.windDirResult << endl;
    cout << "cloud percentage (mod index) " << c.cloudsResult << endl;
    
    //setting oscilloscope to be no bigger than the width of the screen
    for (int i = 0; i < ofGetWidth(); ++i) {
        
        waveform[i] = 0;
        
    }
    //setting the oscilloscope index to 0
    waveIndex = 0;
    
    //creating a ofxDatGui text box
    searchBox = new ofxDatGuiTextInput("Enter a city", "City");
    //calling the functinon for retrieving user input
    searchBox->getText();
    //calling text input event function
    searchBox->onTextInputEvent(this, &ofApp::onTextInputEvent);
    //setting postion
    searchBox->setPosition(555, 135);
    //setting stripe colour
    searchBox->setStripeColor(ofColor(0,255,0,200));
    
    //vector of city names that will display on the drop down menu
    vector<string> options = {"London", "Paris", "Moscow", "Barcelona","Sydney", "Los Angeles","Dubai","Tokyo","Bangkok","Toronto"};

    //creating a ofxDatGui dropdown menu
    dropDown = new ofxDatGuiDropdown("SELECT A CITY",options);
    //setting the postion
    dropDown->setPosition(275, 135);
    //calling drop down event function
    dropDown->onDropdownEvent(this, &ofApp::onDropdownEvent);
    //setting inital strip colour
    dropDown->setStripeColor(ofColor(0,255,0,200));
    //setting stripe colour for every option on the drop down
    for (int i=0; i<dropDown->size(); i++) dropDown->getChildAt(i)->setStripeColor(ofColor(0,255,0,150));
    
    //creating a ofxDatGui toggle button
    editSynth = new ofxDatGuiToggle("edit sound",false);
    //calling the toggle event function
    editSynth->onToggleEvent(this, &ofApp::onToggleEvent);
    //setting the stripe colour
    editSynth->setStripeColor(ofColor(0,255,0,200));
    //setting postion
    editSynth->setPosition(555, 175);
    //calling the that toggles the button
    editSynth->toggle();
    //setting if the toggle has been cliked to intial false
    editSynth->setChecked(false);
    //calling the function which checks if the toggle has been pressed
    editSynth->getChecked();
    //intially setting the toggle to not be visable as it can only be used once the synth uses the weather data
    editSynth->setVisible(false);
    
    //creating a ofDatGuiSlider
    oscSlider = new ofxDatGuiSlider("oscillators", 3, 20, 3);
    //setting the postion
    oscSlider->setPosition(555, 200);
    //setting the stripe colour
    oscSlider->setStripeColor(ofColor(0,255,0,200));
    //calling the slider event function
    oscSlider->onSliderEvent(this, &ofApp::onSliderEvent);
     //intially setting the slider to not be visable as it can only be used once the user presses the toggle button
    oscSlider->setVisible(false);
    
    //same method as above
    freqSlider = new ofxDatGuiSlider("Freq", 200.0, 1000.0, 200.0);
    freqSlider->setPosition(555, 225);
    freqSlider->setStripeColor(ofColor(0,255,0,200));
    freqSlider->onSliderEvent(this, &ofApp::onSliderEvent);
    freqSlider->setVisible(false);
    
    attSlider = new ofxDatGuiSlider("attack", 20.0, 50000.0, 20.0);
    attSlider->setPosition(555, 250);
    attSlider->setStripeColor(ofColor(0,255,0,200));
    attSlider->onSliderEvent(this, &ofApp::onSliderEvent);
    attSlider->setVisible(false);

    decaySlider = new ofxDatGuiSlider("decay", 50.0, 1000.0, 50.0);
    decaySlider->setPosition(555, 275);
    decaySlider->setStripeColor(ofColor(0,255,0,200));
    decaySlider->onSliderEvent(this, &ofApp::onSliderEvent);
    decaySlider->setVisible(false);

    releaseSlider = new ofxDatGuiSlider("release", 2000.0,10000.0, 2000.0);
    releaseSlider->setPosition(555, 300);
    releaseSlider->setStripeColor(ofColor(0,255,0,200));
    releaseSlider->onSliderEvent(this, &ofApp::onSliderEvent);
    releaseSlider->setVisible(false);

    ampModSlider = new ofxDatGuiSlider("amp mod", 4.0, 24.0, 4.0);
    ampModSlider->setPosition(555, 325);
    ampModSlider->setStripeColor(ofColor(0,255,0,200));
    ampModSlider->onSliderEvent(this, &ofApp::onSliderEvent);
    ampModSlider->setVisible(false);

    //usnig floating point parameter instead of int
    freqModSlider = new ofxDatGuiSlider(ofParamFloat.set("freq mod",0.01f, 0.01f, 1.0f));
    freqModSlider->setPosition(555, 350);
    freqModSlider->setStripeColor(ofColor(0,255,0,200));
    freqModSlider->onSliderEvent(this, &ofApp::onSliderEvent);
    freqModSlider->setVisible(false);

    indexModSlider = new ofxDatGuiSlider("index mod", 0.1, 100, 0.1);
    indexModSlider->setPosition(555, 375);
    indexModSlider->setStripeColor(ofColor(0,255,0,200));
    indexModSlider->onSliderEvent(this, &ofApp::onSliderEvent);
    indexModSlider->setVisible(false);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //calling update on all the ofxDatGui objects
    searchBox->update();
    
    dropDown->update();
    
    oscSlider->update();
    
    freqSlider->update();
    
    attSlider->update();
    
    decaySlider->update();
    
    releaseSlider->update();
    
    ampModSlider->update();
    
    freqModSlider->update();
    
    indexModSlider->update();
    
    editSynth->update();
    
    
    //calling the converter function which stores the updated weather values so they can passed into the convertion functions
    c.weatherToAudio();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(0, 255, 0);
    
    ofSetColor(0,255,0,200);
    
    ofSetBackgroundColor(52, 52, 52);

    //setting the title
    font.drawString("HOW'S THE WEATHER SOUNDING", 100,60);
    //project description
    ofDrawBitmapString("How’s the weather sounding is an additive synthesis application that uses current weather data to generate \nsound. Please select a city from the drop down menu below or type a city into the search bar. Use the play \nbutton to play a singal sound, press the 1,2,3 keys to play a pattern and press the edit sound button to \nedit the synth.", 93, 80);
    
    //calling draw on the ofxDatGui objects
    searchBox->draw();

    dropDown->draw();
    
    oscSlider->draw();
    
    freqSlider->draw();
    
    attSlider->draw();
    
    decaySlider->draw();
    
    releaseSlider->draw();
    
    ampModSlider->draw();
    
    freqModSlider->draw();
    
    indexModSlider->draw();
    
    editSynth->draw();
    
    //user feedback message if the user has entered a invalid city into the search box then this message will display
    if(invalidCity == true){
        ofDrawBitmapString(invalidEntry, ofGetWidth()/3, 350);
    }
    
    //drawing the weather values
    c.draw();
    
    //play button
    ofSetColor(playButtonCol, playButtonCol, playButtonCol);
    ofDrawEllipse(913, 285,105,105);
    playButton.draw(850, 225,125,125);
    
    ofSetColor(0, 255, 0, 150);
    
    ofSetColor(0,255,0, 150);
    
    //drawing the oscilloscope
    ofTranslate(0, ofGetHeight()/1.25);
    ofFill();
    int oldX = 0;
    int oldY = 0;
    for(int i = 0; i < ofGetWidth(); ++i) {
        ofDrawLine(oldX, oldY, i, waveform[i] * ofGetHeight()/2);
        oldX = i;
        oldY = waveform[i] * ofGetHeight()/2;
    }
 }


//--------------------------------------------------------------
//this function stores both our convertions functions and synth objects so that we can reuse the synth objects that contain the weather values anywhere in the code without having to repeat our convertion functions and snyth objects.
void ofApp::weatherSynth()
{
    //calling our converter functions
    c.humidityToNumofSines(c.humidToSines, 20, 95, 3, 20);
    c.temperatureToFrequency(c.tempToFreq, -10.0, 50.0, 200.0, 1000.0);
    c.minTemperatureToAttack(c.minTempToAttack, -20.0, 50.0, 20.0, 50000.0);
    c.maxTemperatureToDecay(c.maxTempToDecay, -20.0, 50.0, 50.0, 1000.0);
    c.precipitationToRelease(c.precipToRelease,0.0,50.0,2000.0,10000.0);
    c.windspeedToModSpeed(c.windToModSpeed, 1.0, 50.0, 4.0, 24.0);
    c.windDirectionToModFreq(c.windDirToModFreq, 0.0, 360.0, 0.01, 1.0);
    c.cloudinessToModIndex();
    //here we are calling the synth setting again but this time we are passing the converted weather values
    synth->settings(c.humidResult,c.tempResult,c.minTempResult,c.maxTempResult,c.precipResult,c.windResult,c.windDirResult,c.cloudsResult);
    synth2->settings(c.humidResult,c.tempResult,c.minTempResult,c.maxTempResult,c.precipResult,c.windResult,c.windDirResult,c.cloudsResult);
    synth3->settings(c.humidResult,c.tempResult,c.minTempResult,c.maxTempResult,c.precipResult,c.windResult,c.windDirResult,c.cloudsResult);

    //these variables are used to store the current synth values by storing the current convertion result
    currentNumSines= c.humidResult;
    currentFreq = c.tempResult;
    currentAtt = c.minTempResult;
    currentDecay = c.maxTempResult;
    currentRelease = c.precipResult;
    currentAmpMod = c.windResult;
    currentFreqMod = c.windDirResult;
    currentModIndex = c.cloudsResult;
    
}

//--------------------------------------------------------------
//toggle event function where we pass ofxDatGuiToggleEvent object called  as e
void ofApp::onToggleEvent(ofxDatGuiToggleEvent e)
{
    //e.target refers to the toggle but object which is editSynth in our case
    //e.checked refers to if the toggle has been pressed if equal to 1 then the toggle has been pressed
    if(e.target == editSynth && e.checked == 1){
        
        //if the editSynth toggle has been pressed then each slider gets set to the current synth values and each slider to made visable
        oscSlider->setValue(currentNumSines);
        oscSlider->setVisible(true);

        freqSlider->setValue(currentFreq);
        freqSlider->setVisible(true);

        attSlider->setValue(currentAtt);
        attSlider->setVisible(true);

        decaySlider->setValue(currentDecay);
        decaySlider->setVisible(true);

        releaseSlider->setValue(currentRelease);
        releaseSlider->setVisible(true);

        ampModSlider->setValue(currentAmpMod);
        ampModSlider->setVisible(true);

        freqModSlider->setValue(currentFreqMod);
        freqModSlider->setVisible(true);

        indexModSlider->setValue(currentModIndex);
        indexModSlider->setVisible(true);
     
    }
}

//--------------------------------------------------------------
//toggle event function where we pass a ofxDatGuiSliderEvent object as e
void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
    //e.target refers to the slider object that is being used
    //each slider is liked to the current synthesizer value variables so that the slider can dynamically change the values on the synth
    if (e.target == oscSlider) {
        oscSlider->bind(currentNumSines);
        synth->updateSines(currentNumSines);
    }

    else if (e.target == freqSlider) {
        freqSlider->bind(currentFreq);
        synth->updateFreq(currentFreq);
    }
  
    else if (e.target == attSlider) {
        attSlider->bind(currentAtt);
        synth->updateAttack(currentAtt);
    }

    else if (e.target == decaySlider) {
        decaySlider->bind(currentDecay);
        synth->updateDecay(currentDecay);
    }

    else if (e.target == releaseSlider) {
        releaseSlider->bind(currentRelease);
        synth->updateRelease(currentRelease);
    }

    else if (e.target == ampModSlider) {
        ampModSlider->bind(currentAmpMod);
        synth->updateAmpMod(currentAmpMod);
    }

    else if (e.target == freqModSlider) {
        freqModSlider->bind(currentFreqMod);
        synth->updateFreqMod(currentFreqMod);
    }

    else if (e.target == indexModSlider) {
        indexModSlider->bind(currentModIndex);
        synth->updateModIndex(currentModIndex);
    }
}
//--------------------------------------------------------------
//text input function where we pass a ofxDatGuiSliderEvent object as e
void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
    //assigning the user input to the city that goes inside the api link
    c.changeCity = e.text;
    
    //calling the search box mouse/pressed/released member functions so a request is only made to the api on a uni input
    searchBox->ofxDatGuiComponent::onMousePress(ofPoint(ofGetMouseX(),ofGetMouseY()));
    {c.hitApi(true);c.weatherToAudio();}

    searchBox->ofxDatGuiComponent::onMouseRelease(ofPoint(ofGetMouseX(),ofGetMouseY()));
    {c.hitApi(false);c.weatherToAudio();}
    
    //if a valid city has been entered we call the synth function otherwise we don't
    if(c.invalidCity() == "200"){
        invalidCity = false;
        cout << "SUCCSESS!" << endl;
        cout << c.invalidCity() << endl;
        
        weatherSynth();
    }
    else {
        invalidCity = true;
        cout << "INVALID CITY!" << endl;
        cout << c.invalidCity() << endl;
        invalidEntry = "Please Enter A Valid City";
    }
    
    cout << "temperature (frequency) " << c.tempResult << endl;
    cout << "humidity ( num of sines) " << c.humidResult << endl;
    cout << "min temperature (attack) " << c.minTempResult << endl;
    cout << "max temperature (decay) " << c.maxTempResult << endl;
    cout << "precipitation (release) " << c.precipResult << endl;
    cout << "wind speed (mod speed) " << c.windResult << endl;
    cout << "wind direction (mod freq) " << c.windDirResult << endl;
    cout << "cloud percentage (mod index) " << c.cloudsResult << endl;
    
    editSynth->setVisible(true);

    //cout << "the input field changed to: " << e.text << endl;
    
}

//--------------------------------------------------------------
//text input function where we pass a ofxDatGuiDropdownEvent object as e
void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    
    invalidCity = false;
    //e.child refers to what option has been selected
    switch (e.child) {
        case 0:
            c.changeCity = "London";
            break;
        case 1:
            c.changeCity = "Paris";
            break;
        case 2:
            c.changeCity ="Moscow";
            break;
        case 3:
            c.changeCity = "Barcelona";
            break;
        case 4:
            c.changeCity = "Sydney";
            break;
        case 5:
            c.changeCity = "Los Angeles";
            break;
        case 6:
            c.changeCity = "Dubai";
            break;
        case 7:
            c.changeCity = "Tokyo";
            break;
        case 8:
            c.changeCity = "Bangkok";
            break;
        case 9:
            c.changeCity = "Toronto";
    }
    
    dropDown->ofxDatGuiComponent::onMousePress(ofPoint(ofGetMouseX(),ofGetMouseY()));
    {c.hitApi(true);c.weatherToAudio();}

    dropDown->ofxDatGuiComponent::onMouseRelease(ofPoint(ofGetMouseX(),ofGetMouseY()));
    {c.hitApi(false);c.weatherToAudio();
    }
        
    weatherSynth();
   
    cout << "temperature (frequency) " << c.tempResult << endl;
    cout << "humidity ( num of sines) " << c.humidResult << endl;
    cout << "min temperature (attack) " << c.minTempResult << endl;
    cout << "max temperature (decay) " << c.maxTempResult << endl;
    cout << "precipitation (release) " << c.precipResult << endl;
    cout << "wind speed (mod speed) " << c.windResult << endl;
    cout << "wind direction (mod freq) " << c.windDirResult << endl;
    cout << "cloud percentage (mod index) " << c.cloudsResult << endl;
    
    editSynth->setVisible(true);
    
    // cout << "the option at index # " << e.child << " was selected " << endl;
    
}

//--------------------------------------------------------------
//audio out function for outputting sound to the speakers
void ofApp::audioOut(ofSoundBuffer & output)
{
    size_t nChannels = output.getNumChannels();
    
    for(int i = 0; i < bufferSize; i++){
        
        double sample = 0.0;
        
        sample += synth->playAudio() + synth2->playAudio() + synth3->playAudio();
        
        mix.stereo(sample, outputs, 0.5);
        
        double volLeft = outputs[0] * 0.25;
        double volRight = outputs[0] * 0.25;
        
        double maxVolLeft = ofClamp(volLeft, -1, 1);
        double maxVolRight = ofClamp(volRight, -1, 1);
        
        output[i *nChannels] = maxVolLeft;
        output[i *nChannels +1] = maxVolRight;
        
        waveform[waveIndex] =  output[i * nChannels];
        ++waveIndex;
        if (waveIndex > (ofGetWidth() - 1)) waveIndex = 0;
        
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    //here the user is able to play pattern of the same sound but at a different freq
   if (key == '2') {
        synth->toggleSynthesizer(1);
    }
    
   else if (key == '1') {
       synth2->updateFreq(currentFreq-100);
       synth2->toggleSynthesizer(1);
     }
    
    else if (key == '3') {
        synth3->updateFreq(currentFreq+100);
        synth3->toggleSynthesizer(1);
    }
    
    cout << "You pressed " << key << endl;

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    synth->toggleSynthesizer(0);
    synth2->toggleSynthesizer(0);
    synth3->toggleSynthesizer(0);

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    float dist = ofDist(x, y, 913, 285);
    
    if (dist < 52.5 && invalidCity ==! true){
        
        synth->toggleSynthesizer(1);
        playButtonCol = 52;
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    synth->toggleSynthesizer(0);
    playButtonCol = 72;

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
 

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

//--------------------------------------------------------------
ofApp::~ofApp()
{
    delete dropDown;
    delete searchBox;
    delete oscSlider;
    delete freqSlider;
    delete attSlider;
    delete decaySlider;
    delete releaseSlider;
    delete ampModSlider;
    delete freqModSlider;
    delete indexModSlider;
    delete editSynth;
    
    delete synth;
    delete synth2;
    delete synth3;
}
