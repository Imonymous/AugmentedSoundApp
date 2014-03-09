/*
  ==============================================================================

    AudioStream.cpp
    Created: 9 Mar 2014 1:35:56am
    Author:  MusicUser

  ==============================================================================
*/

#include "AudioStream.h"


AudioStream::AudioStream()
{
    
}

AudioStream::~AudioStream()
{
    
}

void AudioStream::audioDeviceAboutToStart (AudioIODevice* device)
{
    CDelay::createInstance (m_pCDelay);
    m_pCDelay->initInstance(2, device->getCurrentSampleRate(), 0.5, 0.5);
}

void AudioStream::audioDeviceStopped()
{
    CDelay::destroyInstance(m_pCDelay);
}

void AudioStream::audioDeviceIOCallback (const float** inputChannelData, int numInputChannels,
                                         float** outputChannelData, int numOutputChannels,
                                         int numSamples)
{
    
    //for (int channel = 0; channel < numInputChannels; channel++) {
      //  for (int sample = 0; sample < numSamples; sample++) {
            m_pCDelay->iircomb(inputChannelData, outputChannelData, numSamples);
        //}
    //}
    
}
