//  synthesizer.cpp
//  Hows-The-Weather-Sounding
#include "synthesizer.h"

//--------------------------------------------------------------
//function for setting up our synth values
void Synthesizer::settings(int sines,double fund,double att, double dec, double rel, double modS, double modF, double modI)
{
    sound = 0.0;
    trigger = 0;
    numOfsines = sines;
    fundamental = fund;
    
    attack = att;
    decay = dec;
    release = rel;
        
    env.setAttack(attack);
    env.setDecay(decay);
    env.setSustain(1.0);
    env.setRelease(release);
    
    ampModSpeed = modS;
    modFreq = modF;
    modIndex = modI;
    
    //for loop which creates a multiple oscillators
    for(int i =0; i < numOfsines; i++){

        double detuneValue = ofRandom(-1.0, 1.0);
        detune.push_back(ofRandom(detuneValue));

        ampModOscs.push_back(new maxiOsc());
        
        oscillators.push_back(new maxiOsc());
    }
    
}

//--------------------------------------------------------------
//update functions for updating the synth values when the user uses the slider or presses the pattern keys
void Synthesizer::updateSines(double _updateSines)
{
    numOfsines = _updateSines;
}

//--------------------------------------------------------------
void Synthesizer::updateFreq(double _updateFreq)
{
    
   fundamental = _updateFreq;
}

//--------------------------------------------------------------
void Synthesizer::updateAttack(double _updateAttack)
{
    attack = _updateAttack;
    env.setAttack(attack);
}

//--------------------------------------------------------------
void Synthesizer::updateDecay(double _updateDecay)
{
    
    decay = _updateDecay;
    env.setDecay(decay);
}

//--------------------------------------------------------------
void Synthesizer::updateRelease(double _updateRelease)
{
    
    env.setRelease(release);
    release = _updateRelease;
}

//--------------------------------------------------------------
void Synthesizer::updateAmpMod(double _updateAmpMod)
{
    
   ampModSpeed = _updateAmpMod;
}

//--------------------------------------------------------------
void Synthesizer::updateFreqMod(double _updateFreqMod)
{
    
    modFreq = _updateFreqMod;
}

//--------------------------------------------------------------
void Synthesizer::updateModIndex(double _updateModIndex)
{
    
    modIndex = _updateModIndex;
}

//--------------------------------------------------------------
void Synthesizer::toggleSynthesizer(int _trigger)
{
    trigger = _trigger;
}

//--------------------------------------------------------------
double Synthesizer::playAudio()
{
 
    //here we doing addtive synthesis as well as amp and freq modulation the sound is being passed though an envelope
    for (int j =0; j < numOfsines; j++)
    {
        sound += env.adsr(oscillators[j]->sinewave(fundamental + (j * fundamental) + detune[j] + (freqModOsc.sinewave(modFreq) * modIndex)) * (ampModOscs[j]->sinewave(ampModSpeed)+1/2), trigger);
    }
    
    //passing the sound through a low pass filter
   filterResult += lowpassFilter.lopass(sound, 0.25);
    
    //dividing by the number of sine waves to prevent distortion
    return  filterResult /= numOfsines;
    
}

//--------------------------------------------------------------
Synthesizer::~Synthesizer()
{
    for (maxiOsc *o : oscillators){

        delete o;
    }

    for (maxiOsc *a : ampModOscs){

        delete a;
    }
    
}
