/*
 ==============================================================================
 
 TimeStretch.h
 Created: 26 Apr 2014 3:14:37pm
 Author:  MusicUser
 
 ==============================================================================
 */

#ifndef TIMESTRETCH_H_INCLUDED
#define TIMESTRETCH_H_INCLUDED

#include "RingBuffer.h"
#include "ErrorDef.h"
#include "Fft.h"

class CTimeStretch
{
public:
    
    CTimeStretch();
    virtual ~CTimeStretch();
    
    Error_t process(float *pfInputBuffer, float *pfOutputBuffer, int iLengthOfFile);
    Error_t overLapAndAdd(float *pfInputBuffer, float *pfOutputBuffer, int iLengthOfFile);
    Error_t phaseVocode();
    
    static Error_t createInstance (CTimeStretch*& pCTimeStretch);
    static Error_t destroyInstance (CTimeStretch*& pCTimeStretch);
    
    Error_t initInstance(int iWindowLength, int iAnalysisStep, int iSynthesisStep);
    
private:
    
    int m_iAnalysisStep;
    int m_iSynthesisStep;
    int m_iTimeStretchRatio;
    
    int m_iWindowLength;
    float *m_fOmega;
    float *m_fGrain;
};



#endif  // TIMESTRETCH_H_INCLUDED
