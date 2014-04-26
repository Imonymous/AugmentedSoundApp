/*
  ==============================================================================

    AudioFileStream.h
    Created: 23 Apr 2014 3:21:28am
    Author:  MusicUser

  ==============================================================================
*/

#ifndef AUDIOFILESTREAM_H_INCLUDED
#define AUDIOFILESTREAM_H_INCLUDED

#include "JuceHeader.h"

class AudioFileStream
{
    
public:
    
    AudioFileStream(AudioDeviceManager& deviceManager);
    ~AudioFileStream();
    
    void startPlaying();
    void stopPlaying();
    
    void loadFileIntoTransport(String filePath);
    void setPlayBackRate(double ratio);
    
private:
    
    String m_sCurrentFilePath;
    
    AudioDeviceManager&   m_cDeviceManager;
    
    AudioFormatManager formatManager;
    TimeSliceThread thread;
    
    AudioSourcePlayer audioSourcePlayer;
    AudioTransportSource transportSource;
    MixerAudioSource mixerSource;
    ScopedPointer<ResamplingAudioSource> resamplingAudioSource;
    ScopedPointer<ResamplingAudioSource> masterResamplingSource;
    ScopedPointer<AudioFormatReaderSource> currentAudioFileSource;
    
};


#endif  // AUDIOFILESTREAM_H_INCLUDED
