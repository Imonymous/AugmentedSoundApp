/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
    deviceManager   =   new AudioDeviceManager;
    deviceManager->initialise(2, 2, NULL, false);
    
    
    addAndMakeVisible (audioToggleButton = new TextButton ("audioToggleButton"));
    audioToggleButton->setButtonText (TRANS("Audio Toggle"));
    audioToggleButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    audioToggleButton->setColour (TextButton::buttonColourId, Colour (0xff3b3b3b));
    audioToggleButton->setColour (TextButton::buttonOnColourId, Colour (0xff797979));
    audioToggleButton->setClickingTogglesState(true);
    audioToggleButton->addListener(this);
    
    liveAudioStream =   new AudioStream();
    
    setSize (getParentHeight(), getParentWidth());
}

MainContentComponent::~MainContentComponent()
{
    deviceManager = nullptr;
    liveAudioStream =   nullptr;
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xffffffff));
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    audioToggleButton->setBounds(getWidth()/2 - 60, getHeight()/2 - 20, 120, 40);
}

void MainContentComponent::buttonClicked(Button *buttonThatWasClicked)
{
    if (buttonThatWasClicked == audioToggleButton)
    {
        if (audioToggleButton->getToggleState())
        {
            deviceManager->addAudioCallback(liveAudioStream);
        }
        
        else
        {
            deviceManager->removeAudioCallback(liveAudioStream);
        }        
    }
}