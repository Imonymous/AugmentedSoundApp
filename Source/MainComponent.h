/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioEngine.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component,
                                public ButtonListener,
                                public SliderListener
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&);
    void resized();
    
    void buttonClicked(Button* buttonThatWasClicked) override;
    
    void sliderValueChanged(Slider* slider) override;

private:
    //==============================================================================
    
    ScopedPointer<TextButton>   audioToggleButton;
    ScopedPointer<TextButton>   audioFileToggleButton;
    ScopedPointer<TextButton>   recordButton;
    ScopedPointer<TextButton>   playTimeStretchButton;
    ScopedPointer<TextButton>   delayToggleButton;
    ScopedPointer<TextButton>   robotToggleButton;
    
    ScopedPointer<Slider>       playBackRate;
    
    ScopedPointer<AudioEngine>  audioEngine;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
