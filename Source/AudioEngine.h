/*
  ==============================================================================

    AudioEngine.h
    Created: 23 Apr 2014 3:04:55am
    Author:  MusicUser

  ==============================================================================
*/

#ifndef AUDIOENGINE_H_INCLUDED
#define AUDIOENGINE_H_INCLUDED

#include "JuceHeader.h"
#include "Macros.h"
#include "AudioStream.h"
#include "AudioFileStream.h"

class AudioEngine
{
    
public:
    
    AudioEngine();
    ~AudioEngine();
    
    void startLiveStreaming();
    void stopLiveStreaming();
    
    void startAudioPlayback();
    void stopAudioPlayback();
    
    void loadAudioFile(String filePath);
    void setPlayBackRate(double ratio);
    
private:
    
    ScopedPointer<AudioDeviceManager>   deviceManager;
    ScopedPointer<AudioStream>          audioStream;
    ScopedPointer<AudioFileStream>      fileStream;

};



#endif  // AUDIOENGINE_H_INCLUDED
