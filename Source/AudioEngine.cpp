/*
  ==============================================================================

    AudioEngine.cpp
    Created: 23 Apr 2014 3:04:55am
    Author:  MusicUser

  ==============================================================================
*/

#include "AudioEngine.h"
#include "TimeStretch.h"
#include "AudioRecorder.h"

AudioEngine::AudioEngine()
{
    deviceManager       = new AudioDeviceManager();
    deviceManager->initialiseWithDefaultDevices(NUM_INPUT_CHANNELS, NUM_OUTPUT_CHANNELS);
    
    audioStream         = new AudioStream();
    
    fileStream          = new AudioFileStream(*deviceManager);
    
    stretchFileStream   = new AudioFileStream(*deviceManager);
    
    recorder            = new AudioRecorder(*deviceManager);
    
    stretcher           = new AudioRecorder(*deviceManager);
    
    inputRecordingFilepath = File::getSpecialLocation (File::userDocumentsDirectory).getFullPathName() + "/TimeStretchThis.wav";
    
    outputRecordingFilepath = File::getSpecialLocation (File::userDocumentsDirectory).getFullPathName() + "/TimeStretchDone.wav";
    
    CTimeStretch::createInstance(m_pcTimeStretch);
    
    formatManager.registerBasicFormats();
}


AudioEngine::~AudioEngine()
{
    CTimeStretch::destroyInstance(m_pcTimeStretch);
    recorder            =   nullptr;
    audioStream         =   nullptr;
    fileStream          =   nullptr;
    stretchFileStream   =   nullptr;
    deviceManager       =   nullptr;
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

void AudioEngine::toggleRecord()
{
    if (recorder->isRecording())
    {
        recorder->stopRecording();
        
        doneRecording();
        
    }
    else
    {
        recorder->startRecording (inputRecordingFilepath, true);
    }
}


void AudioEngine::startStretchedFile()
{
    stretchFileStream->loadFileIntoTransport(outputRecordingFilepath);
    
    std::cout << outputRecordingFilepath << std::endl;
    
    stretchFileStream->startPlaying();
}

void AudioEngine::stopStretchedFile()
{
    stretchFileStream->stopPlaying();
}


void AudioEngine::doneRecording()
{
    
    // Audio Format Reader
    File audioFile(inputRecordingFilepath);
    AudioFormatReader* reader = formatManager.createReaderFor (audioFile);
    
    // Start the stretcher's instance of FileWriter
    stretcher->sampleRate = reader->sampleRate;
    stretcher->startRecording(outputRecordingFilepath, false);
    
    int iFileLength = (reader->sampleRate)/4; //Selecting only quarter of the sample rate wide length for timestretching
    
    int iNumChannnels = reader->numChannels;
    
    float                   *pInputData;
    float                   *pOutputData;
    
    float                   **outputBuffer  = 0;
    AudioSampleBuffer*      inputBuffer     = new AudioSampleBuffer(iNumChannnels, iFileLength);

    reader->read(inputBuffer, 0, iFileLength, 0, true, true);
    
    m_pcTimeStretch->initInstance(2048, 200, 400);
    
    pInputData = new float[iFileLength];
    pOutputData = new float[(iFileLength*2)];
    
    for(int i = 0; i < iFileLength; i++)
    {
        for(int j = 0; j < iNumChannnels; j++)
        {
            pInputData[i] += (inputBuffer->getArrayOfReadPointers())[j][i];
        }
        pInputData[i] = static_cast<float>(pInputData[i]/iNumChannnels);
    }
    
    m_pcTimeStretch->process(pInputData, pOutputData, iFileLength);
    
    outputBuffer            = new float* [iNumChannnels];
    for (int i = 0; i < iNumChannnels; i++)
    {
        outputBuffer[i] = new float [(iFileLength*2)];
        CUtil::setZero(outputBuffer[i], (iFileLength*2));
    }
    
    for (int i = 0; i < iNumChannnels; i++)
    {
        CUtil::copyBuff(outputBuffer[i], pOutputData, (iFileLength*2));
    }
    
    stretcher->writeBuffer(outputBuffer, (iFileLength));
    
    stretcher->stopRecording();

    /////////////////////////////////////////////////
    // free memory
    
    for (int i = 0; i < iNumChannnels; i++)
        delete [] outputBuffer[i];
    delete [] outputBuffer;
    outputBuffer = 0;
    
    delete [] pInputData;
    pInputData = 0;
    
    delete [] pOutputData;
    pOutputData = 0;
    
    //inputBuffer->~AudioSampleBuffer();

    /////////////////////////////////////////////////
    
}


