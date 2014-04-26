/*
  ==============================================================================

    Mixer.h
    Created: 10 Mar 2014 5:11:31pm
    Author:  MusicUser

  ==============================================================================
*/

#ifndef MIXER_H_INCLUDED
#define MIXER_H_INCLUDED

#include "JuceHeader.h"

class Mixer     :       public AudioIODeviceCallback
{
    
public:
    
    Mixer();
    ~Mixer();
    
    void audioDeviceAboutToStart (AudioIODevice* device) override;
    void audioDeviceStopped() override;
    void audioDeviceIOCallback (const float** inputChannelData, int numInputChannels,
                                float** outputChannelData, int numOutputChannels,
                                int numSamples) override;
    
private:
    
    MixerAudioSource mixer;
    
    AudioSourcePlayer sourcePlayer;
    
};

#endif  // MIXER_H_INCLUDED
