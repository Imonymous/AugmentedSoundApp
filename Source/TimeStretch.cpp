/*
 ==============================================================================
 
 TimeStretch.cpp
 Created: 26 Apr 2014 3:14:37pm
 Author:  MusicUser
 
 ==============================================================================
 */

#include "TimeStretch.h"

CTimeStretch::CTimeStretch():
m_iAnalysisStep(0),
m_iSynthesisStep(0),
m_iTimeStretchRatio(1),
m_iWindowLength(0),
m_fOmega(0),
m_fGrain(0)
{
    
}

CTimeStretch::~CTimeStretch()
{
    delete [] m_fGrain;
}


Error_t CTimeStretch::createInstance (CTimeStretch*& pCTimeStretch)
{
    pCTimeStretch = new CTimeStretch ();
    
    if (!pCTimeStretch)
        return kUnknownError;
    
    
    return kNoError;
}

Error_t CTimeStretch::destroyInstance (CTimeStretch*& pCTimeStretch)
{
    if (!pCTimeStretch)
        return kUnknownError;
    
    //    pCTimeStretch->resetInstance ();
    
    delete pCTimeStretch;
    pCTimeStretch = 0;
    
    return kNoError;
}

Error_t CTimeStretch::initInstance(int iWindowLength, int iAnalysisStep, int iSynthesisStep)
{
    m_iAnalysisStep = iAnalysisStep;
    m_iSynthesisStep = iSynthesisStep;
    
    m_iWindowLength = iWindowLength;
    
    m_fGrain = new float[iWindowLength];
    CUtil::setZero(m_fGrain, iWindowLength);
    
    return kNoError;
}

Error_t CTimeStretch::process(float *pfInputBuffer, float *pfOutputBuffer, int iLengthOfFile)
{
    overLapAndAdd(pfInputBuffer, pfOutputBuffer, iLengthOfFile);
    
    return kNoError;
}

Error_t CTimeStretch::overLapAndAdd(float *pfInputBuffer, float *pfOutputBuffer, int iLengthOfFile)
{
    int pin = 0;
    int pout = 0;
    int pend = iLengthOfFile - m_iWindowLength;
    
    while (pin < pend) {
        
        for (int i = 0; i < m_iWindowLength; i++) {
            m_fGrain[i] = pfInputBuffer[pin+i];
        }
        
        for (int i = 0; i < m_iWindowLength; i++) {
            pfOutputBuffer[pout+i] = pfOutputBuffer[pout+i] + m_fGrain[i];
        }
        
        pin = pin + m_iAnalysisStep;
        pout = pout + m_iSynthesisStep;
    }
    
    return kNoError;
}

Error_t CTimeStretch::phaseVocode()
{
    
    return kNoError;
}