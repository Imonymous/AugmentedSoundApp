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
#include "AudioRecorder.h"
#include "TimeStretch.h"

class AudioEngine
{
    
public:
    
    CTimeStretch                        *m_pcTimeStretch;
    
    AudioEngine();
    virtual ~AudioEngine();
    
    void startLiveStreaming();
    void stopLiveStreaming();
    
    void startAudioPlayback();
    void stopAudioPlayback();
    
    void loadAudioFile(String filePath);
    void setPlayBackRate(double ratio);
    
    void toggleEffect(int iEffect);
    void toggleRecord();
    void startStretchedFile();
    void stopStretchedFile();
    
private:
    
    void doneRecording();
    
    ScopedPointer<AudioDeviceManager>   deviceManager;
    ScopedPointer<AudioStream>          audioStream;
    ScopedPointer<AudioFileStream>      fileStream;
    ScopedPointer<AudioFileStream>      stretchFileStream;
    ScopedPointer<AudioRecorder>        recorder;
    ScopedPointer<AudioRecorder>        stretcher;
    
    AudioFormatManager                  formatManager;
    
    String                              inputRecordingFilepath;
    String                              outputRecordingFilepath;

};



#endif  // AUDIOENGINE_H_INCLUDED
