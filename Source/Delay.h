/*
  ==============================================================================

    Delay.h
    Created: 9 Mar 2014 3:47:33am
    Author:  MusicUser

  ==============================================================================
*/

#ifndef DELAY_H_INCLUDED
#define DELAY_H_INCLUDED

#include "RingBuffer.h"

enum Error_t
{
    kNoError,
    
    kFileOpenError,
    kFileAccessError,
    
    kFunctionInvalidArgsError,
    
    kNotInitializedError,
    
    kMemError,
    
    kUnknownError,
    
    kNumErrors
};

class CDelay
{
public:
    /*! version number */
    enum Version_t
    {
        kMajor,                         //!< major version number
        kMinor,                         //!< minor version number
        kPatch,                         //!< patch version number
        
        kNumVersionInts
    };
    
    int     iNumChannels;
    float   fSampleRate;
    float   fGain;
    float   fDelay;
    
    CRingBuffer<float> **m_pCRingBuffer;
    
    static const int  getVersion (const Version_t eVersionIdx);
    static const char* getBuildDate ();
    
    static Error_t createInstance (CDelay*& pCKortIf);
    static Error_t destroyInstance (CDelay*& pCKortIf);
    
    Error_t initInstance (int numChannels, float sampleRate, float gain, float delay);
    Error_t resetInstance (bool flag);
    
    Error_t fircomb(const float **ppfInputBuffer, float **ppfOutputBuffer, int iNumFrames);
    Error_t iircomb(const float **ppfInputBuffer, float **ppfOutputBuffer, int iNumFrames);
    
protected:
    CDelay ();
    virtual ~CDelay ();
};





#endif  // DELAY_H_INCLUDED
