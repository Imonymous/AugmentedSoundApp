/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
    audioEngine = new AudioEngine();
    String filePath = File::getSpecialLocation(File::userDocumentsDirectory).getFullPathName() + "/Mind if I Cut In.mp3";
    audioEngine->loadAudioFile(filePath);
    
    addAndMakeVisible (audioToggleButton = new TextButton ("audioToggleButton"));
    audioToggleButton->setButtonText (TRANS("Audio Toggle"));
    audioToggleButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    audioToggleButton->setColour (TextButton::buttonColourId, Colour (0xff3b3b3b));
    audioToggleButton->setColour (TextButton::buttonOnColourId, Colour (0xff797979));
    audioToggleButton->setClickingTogglesState(true);
    audioToggleButton->addListener(this);
    
    addAndMakeVisible (audioFileToggleButton = new TextButton ("audioFileToggleButton"));
    audioFileToggleButton->setButtonText (TRANS("File Toggle"));
    audioFileToggleButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    audioFileToggleButton->setColour (TextButton::buttonColourId, Colour (0xff3b3b3b));
    audioFileToggleButton->setColour (TextButton::buttonOnColourId, Colour (0xff797979));
    audioFileToggleButton->setClickingTogglesState(true);
    audioFileToggleButton->addListener(this);
    
    addAndMakeVisible(playBackRate = new Slider("playBackRate"));
    playBackRate->setRange(1.0, 2.0);
    playBackRate->setValue(1.0, sendNotification);
    playBackRate->setColour (Slider::thumbColourId, Colours::red);
    playBackRate->addListener(this);
    
    setSize (getParentHeight(), getParentWidth());
}

MainContentComponent::~MainContentComponent()
{
    audioEngine             = nullptr;
    audioToggleButton       = nullptr;
    audioFileToggleButton   = nullptr;
    playBackRate            = nullptr;
    
    // This never hurts
    deleteAllChildren();
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
    audioToggleButton->setBounds(getWidth()/2 - 60, getHeight()/2 - 60, 120, 40);
    audioFileToggleButton->setBounds(getWidth()/2 - 60, getHeight()/2 + 60, 120, 40);
    playBackRate->setBounds(getWidth()/2 - 60, getHeight()/2 - 120, 120, 40);
}

void MainContentComponent::buttonClicked(Button *buttonThatWasClicked)
{
    if (buttonThatWasClicked == audioToggleButton)
    {
        if (audioToggleButton->getToggleState())
        {
            audioEngine->startLiveStreaming();
        }
        
        else
        {
            audioEngine->stopLiveStreaming();
        }        
    }
    
    
    if (buttonThatWasClicked == audioFileToggleButton)
    {
        if (audioFileToggleButton->getToggleState())
        {
            audioEngine->startAudioPlayback();
        }
        
        else
        {
            audioEngine->stopAudioPlayback();
        }
    }
}

void MainContentComponent::sliderValueChanged(Slider* slider)
{
    if (playBackRate == slider) {
        audioEngine->setPlayBackRate(playBackRate->getValue());
    }
}