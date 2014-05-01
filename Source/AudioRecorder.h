/*
  ==============================================================================

    AudioRecorder.h
    Created: 29 Apr 2014 7:02:08pm
    Author:  MusicUser

  ==============================================================================
*/

#ifndef AUDIORECORDER_H_INCLUDED
#define AUDIORECORDER_H_INCLUDED

#include "JuceHeader.h"

class AudioRecorder  :   public AudioIODeviceCallback
{
    
public:
    
    AudioRecorder(AudioDeviceManager& sharedDeviceManager);
    ~AudioRecorder();
    
    void startRecording(String filePath, bool internalCallback);
    void stopRecording();
    
    
    void audioDeviceAboutToStart (AudioIODevice* device) override;
    void audioDeviceStopped() override;
    void audioDeviceIOCallback (const float** inputChannelData, int numInputChannels,
                                float** outputChannelData, int numOutputChannels,
                                int numSamples) override;
    
    void writeBuffer(float** buffer, int blockSize);
    
    bool isRecording();
    
    double  sampleRate;
    
    
private:
    
    AudioDeviceManager& deviceManager;
    TimeSliceThread backgroundThread;
    
    String m_sCurrentFilePath;
    
    ScopedPointer<AudioFormatWriter::ThreadedWriter> threadedWriter;
    int64 nextSampleNum;
    
    CriticalSection writerLock;
    AudioFormatWriter::ThreadedWriter* volatile activeWriter;
};


#endif  // AUDIORECORDER_H_INCLUDED
