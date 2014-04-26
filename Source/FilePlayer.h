/*
  ==============================================================================

    FilePlayer.h
    Created: 10 Mar 2014 12:31:00pm
    Author:  MusicUser

  ==============================================================================
*/

#include "JuceHeader.h"

#ifndef FILEPLAYER_H_INCLUDED
#define FILEPLAYER_H_INCLUDED

class FilePlayer   :    public AudioSource,
                        public ChangeListener
{
    
public:
    
    FilePlayer();
    ~FilePlayer();
    
    enum TransportState {
        Stopped,
        Starting,
        Playing,
        Pausing,
        Paused,
        Stopping
    };
    void changeState (TransportState newState);
    void changeListenerCallback (ChangeBroadcaster* source);
    void chooseFile(FilePlayer& filePlayer);
    
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void releaseResources();
    void getNextAudioBlock (const AudioSourceChannelInfo &bufferToFill);
    
    
private:
    AudioFormatManager formatManager;
    ScopedPointer<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    TransportState state;
    AudioSourcePlayer audioSourcePlayer;
};


#endif  // FILEPLAYER_H_INCLUDED
