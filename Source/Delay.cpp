/*
  ==============================================================================

    Delay.cpp
    Created: 9 Mar 2014 3:47:20am
    Author:  MusicUser

  ==============================================================================
*/

#include "Delay.h"

static const char*  kCDelayBuildDate             = __DATE__;

CDelay::CDelay ()
{
    // this never hurts
    this->resetInstance (false);
}

CDelay::~CDelay ()
{
    this->resetInstance (false);
}

const int  CDelay::getVersion (const Version_t eVersionIdx)
{
    int iVersion = 0;
    
    switch (eVersionIdx)
    {
        case kMajor:
            iVersion    = 1;
            break;
        case kMinor:
            iVersion    = 0;
            break;
        case kPatch:
            iVersion    = 0;
            break;
        case kNumVersionInts:
            iVersion    = -1;
            break;
    }
    
    return iVersion;
}
const char*  CDelay::getBuildDate ()
{
    return kCDelayBuildDate;
}

Error_t CDelay::createInstance (CDelay*& pCDelay)
{
    pCDelay = new CDelay ();
    
    if (!pCDelay)
        return kUnknownError;
    
    return kNoError;
}

Error_t CDelay::destroyInstance (CDelay*& pCDelay)
{
    if (!pCDelay)
        return kUnknownError;
    
    pCDelay->resetInstance (true);
    
    delete pCDelay;
    pCDelay = 0;
    
    return kNoError;
    
}

Error_t CDelay::initInstance(int numChannels, float sampleRate, float gain, float delay)
{
    // initialize variables and buffers
    
    iNumChannels = numChannels;
    fSampleRate = sampleRate;
    fGain = gain;
    fDelay = delay;
    
    // allocate memory for Ring Buffers
    
    m_pCRingBuffer = new CRingBuffer<float>* [iNumChannels];
    
    for (int i = 0; i < iNumChannels; i++)
    {
        m_pCRingBuffer[i]  = new CRingBuffer<float> (fSampleRate);
        m_pCRingBuffer[i]->setReadIdx(0);
        m_pCRingBuffer[i]->setWriteIdx((int)(fDelay*fSampleRate));
    }
    
    return kNoError;
}

Error_t CDelay::resetInstance (bool flag)
{
    // reset buffers and variables to default values
    
    if (m_pCRingBuffer) {
        for (int i = 0; i < iNumChannels; i++)
            m_pCRingBuffer[i]->resetInstance();
        
        // Using a flag to flush Ring Buffers
        if (flag)
        {
            for (int i = 0; i < iNumChannels; i++)
                delete m_pCRingBuffer[i];
            delete [] m_pCRingBuffer;
            m_pCRingBuffer = 0;
        }
    }
    
    iNumChannels    = 2;
    fSampleRate     = 44100;
    fGain           = 1.0;
    fDelay          = 0.0;
    
    return kNoError;
}

// The FIR Comb filter process
Error_t CDelay::fircomb(const float **ppfInputBuffer, float **ppfOutputBuffer, int iNumFrames)
{
    for (int i = 0; i < iNumFrames; i++)
    {
        for (int c = 0; c < iNumChannels; c++)
        {
            m_pCRingBuffer[c]->putPostInc(ppfInputBuffer[c][i]);
            ppfOutputBuffer[c][i] = ppfInputBuffer[c][i] + fGain * m_pCRingBuffer[c]->getPostInc();
        }
    }
    
    return kNoError;
}

// The IIR Comb filter process
Error_t CDelay::iircomb(const float **ppfInputBuffer, float **ppfOutputBuffer, int iNumFrames)
{
    for (int i = 0; i < iNumFrames; i++)
    {
        for (int c = 0; c < iNumChannels; c++)
        {
            ppfOutputBuffer[c][i] = ppfInputBuffer[c][i] + fGain * m_pCRingBuffer[c]->getPostInc();
            m_pCRingBuffer[c]->putPostInc(ppfInputBuffer[c][i]);
        }
    }
    
    return kNoError;
}