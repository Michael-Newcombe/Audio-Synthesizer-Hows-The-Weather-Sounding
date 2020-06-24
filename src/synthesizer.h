//  synthesizer.h
//  Hows-The-Weather-Sounding
#include "ofMain.h"
#include "ofxMaxim.h"

#ifndef synthesizer_h
#define synthesizer_h

class Synthesizer
{
public:
    //Synthesizer functions
    void settings(int sines,double fund,double att, double dec, double rel, double modS, double modF, double modI);
    void toggleSynthesizer(int _trigger);
    void updateSines(double _updateSines);
    void updateFreq(double _updateFreq);
    void updateAttack(double _updateAttack);
    void updateDecay(double _updateDecay);
    void updateRelease(double _updateRelease);
    void updateAmpMod(double _updateAmpMod);
    void updateFreqMod(double _updateFreqMod);
    void updateModIndex(double _updateModIndex);
    double playAudio();
    ~Synthesizer();


private:
    //Synthesizer variables
    int numOfsines;
    double fundamental;
    int trigger;
    double sound;
    double soundEnv;
    double attack;
    double decay;
    double sustain;
    double release;
    double soundFilter;
    vector <maxiOsc*> oscillators;
    maxiEnv env;
    maxiFilter lowpassFilter;
    double filterResult;
    vector <maxiOsc*> ampModOscs;
    double ampModSpeed;
    vector <double> detune;
    maxiOsc freqModOsc;
    double modFreq;
    double modIndex;
    
};

#endif /* synthesizer_h */
