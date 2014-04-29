/*
  ==============================================================================

    Robot.cpp
    Created: 29 Apr 2014 4:54:55pm
    Author:  MusicUser

  ==============================================================================
*/

#include "Robot.h"
#include <math.h>

static const char*  kCDelayBuildDate             = __DATE__;

CRobot::CRobot():
    m_fPhase(0),
    m_fFreq(0)
{
    
}

CRobot::~CRobot()
{
    
}

const int  CRobot::getVersion (const Version_t eVersionIdx)
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
const char*  CRobot::getBuildDate ()
{
    return kCDelayBuildDate;
}

Error_t CRobot::createInstance (CRobot*& pCRobot)
{
    pCRobot = new CRobot ();
    
    if (!pCRobot)
        return kUnknownError;
    
    return kNoError;
}

Error_t CRobot::destroyInstance (CRobot*& pCRobot)
{
    if (!pCRobot)
        return kUnknownError;
    
    pCRobot->resetInstance ();
    
    delete pCRobot;
    pCRobot = 0;
    
    return kNoError;
    
}

Error_t CRobot::initInstance(int iNumChannels, float fSampleRate, float fFreq, float fPhase)
{
    if (m_fFreq < 0 || m_fPhase < 0) {
        return kFunctionInvalidArgsError;
    }
    
    m_iNumChannels = iNumChannels;
    m_fSampleRate = fSampleRate;
    m_fFreq = fFreq;
    m_fPhase = fPhase;
    
    return kNoError;
}

Error_t CRobot::resetInstance()
{
    m_fFreq = 0;
    m_fPhase = 0;
    
    return kNoError;
}

Error_t CRobot::roboticize(const float **ppfInputBuffer, float **ppfOutputBuffer, int iNumSamples)
{
    for (int channel = 0; channel < m_iNumChannels; channel++)
    {
        for (int sample = 0; sample < iNumSamples; sample++)
        {
            float theta = m_fPhase * ( 2 * M_PI );
            
            ppfOutputBuffer[channel][sample] = (sin(theta))*(ppfInputBuffer[channel][sample]);
            
            m_fPhase += 1.0*m_fFreq/m_fSampleRate;
            if (m_fPhase > 1.0) {
                m_fPhase -= 1.0;
            }
        }
    }
    
    return kNoError;
}