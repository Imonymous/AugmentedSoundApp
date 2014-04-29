/*
  ==============================================================================

    AudioStream.cpp
    Created: 9 Mar 2014 1:35:56am
    Author:  MusicUser

  ==============================================================================
*/

#include "AudioStream.h"
#include "Macros.h"


AudioStream::AudioStream()
{
    CDelay::createInstance (m_pCDelay);
    CRobot::createInstance (m_pCRobot);
}

AudioStream::~AudioStream()
{
    CDelay::destroyInstance(m_pCDelay);
    CRobot::destroyInstance(m_pCRobot);
}

void AudioStream::audioDeviceAboutToStart (AudioIODevice* device)
{
    m_pCDelay->initInstance(2, device->getCurrentSampleRate(), 0.5, 0.5);
    m_pCRobot->initInstance(2, device->getCurrentSampleRate(), 30.0, 0);
    isDelayOn = false;
    isRobotOn = false;
}

void AudioStream::audioDeviceStopped()
{
    m_pCDelay->resetInstance(true);
    m_pCRobot->resetInstance();
}

void AudioStream::audioDeviceIOCallback (const float** inputChannelData, int numInputChannels,
                                         float** outputChannelData, int numOutputChannels,
                                         int numSamples)
{
    for (int i = 0; i < kTotalEffects; i++) {
        switch (i) {
            case kDelay:
                if (isDelayOn)
                {
                    m_pCDelay->iircomb(inputChannelData, const_cast<float**>(inputChannelData), numSamples);
                }
                break;
            case kRobot:
                if (isRobotOn)
                {
                    m_pCRobot->roboticize(inputChannelData, const_cast<float**>(inputChannelData), numSamples);
                }
                break;
            default:
                break;
        }
    }
    
    for (int channel = 0; channel < numOutputChannels; channel++)
    {
        for (int sample = 0; sample < numSamples; sample++)
        {
            outputChannelData[channel][sample] = 0.5*inputChannelData[channel][sample];
        }
    }
    
}

void AudioStream::toggleEffect(int iEffect)
{
    switch (iEffect) {
        case kDelay:
            isDelayOn = !isDelayOn;
            break;
        case kRobot:
            isRobotOn = !isRobotOn;
            break;
        default:
            break;
    }
}
