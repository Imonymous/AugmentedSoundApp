/*
  ==============================================================================

    FilePlayer.cpp
    Created: 10 Mar 2014 12:31:00pm
    Author:  MusicUser

  ==============================================================================
*/

#include "FilePlayer.h"

//
//FilePlayer::FilePlayer()
//{
//    formatManager.registerBasicFormats();
//    
//    audioSourcePlayer.setSource (&transportSource);
//
//    transportSource.addChangeListener (this);
//    state = Stopped;
//}
//
//FilePlayer::~FilePlayer()
//{
//    
//}
//
//void FilePlayer::chooseFile(FilePlayer& filePlayer)
//{
//    FileChooser chooser ("Select a Wave file to play...", File::nonexistent, "*.wav");
//    
//    if (chooser.browseForFileToOpen())
//    {
//        File file (chooser.getResult());
//        readerSource = new AudioFormatReaderSource(formatManager.createReaderFor (file), true);
//        transportSource.setSource (readerSource);
//    }
//}
//
//void prepareToPlay(int samplesPerBlockExpected, double sampleRate)
//{
//    
//}
//
//void releaseResources()
//{
//    
//}
//
//void getNextAudioBlock (const AudioSourceChannelInfo &bufferToFill)
//{
//    
//}
