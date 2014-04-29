/*
  ==============================================================================

    AudioEngine.cpp
    Created: 23 Apr 2014 3:04:55am
    Author:  MusicUser

  ==============================================================================
*/

#include "AudioEngine.h"


AudioEngine::AudioEngine()
{
    deviceManager   = new AudioDeviceManager();
    deviceManager->initialiseWithDefaultDevices(NUM_INPUT_CHANNELS, NUM_OUTPUT_CHANNELS);
    
    audioStream     = new AudioStream();
    
    fileStream      = new AudioFileStream(*deviceManager);
}


AudioEngine::~AudioEngine()
{
    audioStream     =   nullptr;
    fileStream      =   nullptr;
    deviceManager   =   nullptr;
}

void AudioEngine::startLiveStreaming()
{
    deviceManager->addAudioCallback(audioStream);
}

void AudioEngine::stopLiveStreaming()
{
    deviceManager->removeAudioCallback(audioStream);
}

void AudioEngine::startAudioPlayback()
{
    fileStream->startPlaying();
}

void AudioEngine::stopAudioPlayback()
{
    fileStream->stopPlaying();
}

void AudioEngine::loadAudioFile(String filePath)
{
    fileStream->loadFileIntoTransport(filePath);
}

void AudioEngine::setPlayBackRate(double ratio)
{
    fileStream->setPlayBackRate(ratio);
}

void AudioEngine::toggleEffect(int iEffect)
{
    audioStream->toggleEffect(iEffect);
}