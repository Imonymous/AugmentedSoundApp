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
    CDelay::createInstance (m_pCDelay);
}

AudioStream::~AudioStream()
{
    CDelay::destroyInstance(m_pCDelay);
}

void AudioStream::audioDeviceAboutToStart (AudioIODevice* device)
{
    m_pCDelay->initInstance(2, device->getCurrentSampleRate(), 0.5, 0.5);
}

void AudioStream::audioDeviceStopped()
{
    m_pCDelay->resetInstance(true);
}

void AudioStream::audioDeviceIOCallback (const float** inputChannelData, int numInputChannels,
                                         float** outputChannelData, int numOutputChannels,
                                         int numSamples)
{
    
    m_pCDelay->iircomb(inputChannelData, outputChannelData, numSamples);
    
    
    for (int channel = 0; channel < numOutputChannels; channel++)
    {
        for (int sample = 0; sample < numSamples; sample++)
        {
            outputChannelData[channel][sample] *= 0.5;
        }
    }
}
