/*
  ==============================================================================

    AudioFileStream.cpp
    Created: 23 Apr 2014 3:21:28am
    Author:  MusicUser

  ==============================================================================
*/

#include "AudioFileStream.h"


AudioFileStream::AudioFileStream(AudioDeviceManager& deviceManager)
                                :   m_cDeviceManager(deviceManager),
                                    thread ("audio file playback")
{
    currentAudioFileSource = 0;
    
    formatManager.registerBasicFormats();
    
    resamplingAudioSource   = new ResamplingAudioSource(&transportSource, true);
    
    mixerSource.addInputSource (resamplingAudioSource, false);
	
	masterResamplingSource = new ResamplingAudioSource(&mixerSource, true); //now resample the mixer output
	
	// ..and connect the mixer to our source player.
	audioSourcePlayer.setSource (masterResamplingSource);
    
    m_cDeviceManager.addAudioCallback (&audioSourcePlayer);
    
    thread.startThread (5);
}


AudioFileStream::~AudioFileStream()
{
    m_cDeviceManager.removeAudioCallback(&audioSourcePlayer);
    
    transportSource.setSource (nullptr);
    audioSourcePlayer.setSource (nullptr);
}

void AudioFileStream::startPlaying()
{
    transportSource.setPosition (0);
    transportSource.start();
}


void AudioFileStream::stopPlaying()
{
    transportSource.stop();
}



void AudioFileStream::loadFileIntoTransport(String filePath)
{
    File audioFile(filePath);
    
    transportSource.stop();
    transportSource.setSource (nullptr);
    currentAudioFileSource = nullptr;
    
    AudioFormatReader* reader = formatManager.createReaderFor (audioFile);
    
    if (reader != nullptr)
    {
        currentAudioFileSource  = new AudioFormatReaderSource (reader, true);
        
        // ..and plug it into our transport source
        transportSource.setSource (currentAudioFileSource,
                                   32768,                   // tells it to buffer this many samples ahead
                                   &thread,                 // this is the background thread to use for reading-ahead
                                   reader->sampleRate);     // allows for sample rate correction
        
        transportSource.setGain(0.5);
        currentAudioFileSource->setLooping(true);
    }
}

void AudioFileStream::setPlayBackRate(double ratio)
{
    resamplingAudioSource->setResamplingRatio(ratio);
}
