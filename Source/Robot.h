/*
  ==============================================================================

    Robot.h
    Created: 29 Apr 2014 4:54:55pm
    Author:  MusicUser

  ==============================================================================
*/

#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include "Robot.h"
#include "ErrorDef.h"

class CRobot
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
    
    int     m_iNumChannels;
    float   m_fSampleRate;
    float   m_fPhase;
    float   m_fFreq;
    
    static const int  getVersion (const Version_t eVersionIdx);
    static const char* getBuildDate ();
    
    static Error_t createInstance (CRobot*& pCRobot);
    static Error_t destroyInstance (CRobot*& pCRobot);
    
    Error_t initInstance(int iNumChannels, float fSampleRate, float fFreq, float fPhase);
    Error_t resetInstance();
    
    Error_t roboticize(const float **ppfInputBuffer, float **ppfOutputBuffer, int iNumSamples);
    
private:
    
    CRobot();
    virtual ~CRobot();
    
};




#endif  // ROBOT_H_INCLUDED
