/*
  ==============================================================================

    AudioStream.h
    Created: 9 Mar 2014 1:38:03am
    Author:  MusicUser

  ==============================================================================
*/

#ifndef AUDIOSTREAM_H_INCLUDED
#define AUDIOSTREAM_H_INCLUDED

#include "JuceHeader.h"
#include "Delay.h"

class AudioStream   :   public AudioIODeviceCallback
{
    
public:
    
    AudioStream();
    ~AudioStream();
    
    CDelay *m_pCDelay;
    
    void audioDeviceAboutToStart (AudioIODevice* device) override;
    void audioDeviceStopped() override;
    void audioDeviceIOCallback (const float** inputChannelData, int numInputChannels,
                                float** outputChannelData, int numOutputChannels,
                                int numSamples) override;
    
private:
    
};




#endif  // AUDIOSTREAM_H_INCLUDED
