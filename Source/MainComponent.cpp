/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "Macros.h"


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
    
    addAndMakeVisible (recordButton = new TextButton ("recordButton"));
    recordButton->setButtonText (TRANS("Audio Record"));
    recordButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    recordButton->setColour (TextButton::buttonColourId, Colour (0xff3b3b3b));
    recordButton->setColour (TextButton::buttonOnColourId, Colour (0xff797979));
    recordButton->setClickingTogglesState(true);
    recordButton->addListener(this);
    
    addAndMakeVisible (playTimeStretchButton = new TextButton ("playTimeStretchButton"));
    playTimeStretchButton->setButtonText (TRANS("Play Stretch"));
    playTimeStretchButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    playTimeStretchButton->setColour (TextButton::buttonColourId, Colour (0xff3b3b3b));
    playTimeStretchButton->setColour (TextButton::buttonOnColourId, Colour (0xff797979));
    playTimeStretchButton->setClickingTogglesState(true);
    playTimeStretchButton->addListener(this);
    
    addAndMakeVisible (delayToggleButton = new TextButton ("delayToggleButton"));
    delayToggleButton->setButtonText (TRANS("Delay"));
    delayToggleButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    delayToggleButton->setColour (TextButton::buttonColourId, Colour (0xff3b3b3b));
    delayToggleButton->setColour (TextButton::buttonOnColourId, Colour (0xff797979));
    delayToggleButton->setClickingTogglesState(true);
    delayToggleButton->addListener(this);
    
    addAndMakeVisible (robotToggleButton = new TextButton ("robotToggleButton"));
    robotToggleButton->setButtonText (TRANS("Robot"));
    robotToggleButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    robotToggleButton->setColour (TextButton::buttonColourId, Colour (0xff3b3b3b));
    robotToggleButton->setColour (TextButton::buttonOnColourId, Colour (0xff797979));
    robotToggleButton->setClickingTogglesState(true);
    robotToggleButton->addListener(this);
    
    
    addAndMakeVisible(playBackRate = new Slider("playBackRate"));
    playBackRate->setRange(0.7, 1.3);
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
    audioToggleButton->setBounds(getWidth()/2 - 90, getHeight()/2 - 100, 60, 40);
    audioFileToggleButton->setBounds(getWidth()/2 + 30, getHeight()/2 - 100, 60, 40);
    
    delayToggleButton->setBounds(getWidth()/2 - 90, getHeight()/2 , 60, 40);
    robotToggleButton->setBounds(getWidth()/2 + 30, getHeight()/2, 60, 40);
    
    recordButton->setBounds(getWidth()/2 - 90, getHeight()/2 + 100, 60, 40);
    playTimeStretchButton->setBounds(getWidth()/2 + 30, getHeight()/2 + 100, 60, 40);
    
    
    playBackRate->setBounds(getWidth()/2 - 120, getHeight()/2 - 150, 240, 40);
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
    
    
    if (buttonThatWasClicked == delayToggleButton)
    {
        audioEngine->toggleEffect(kDelay);
    }
    
    if (buttonThatWasClicked == robotToggleButton)
    {
        audioEngine->toggleEffect(kRobot);
    }
    
    if (buttonThatWasClicked == recordButton)
    {
        audioEngine->toggleRecord();
    }
    
    if (buttonThatWasClicked == playTimeStretchButton)
    {
        
        if (playTimeStretchButton->getToggleState())
        {
            audioEngine->startStretchedFile();
        }
        else
        {
            audioEngine->stopStretchedFile();
        }
        
    }
    
    
}

void MainContentComponent::sliderValueChanged(Slider* slider)
{
    if (playBackRate == slider) {
        audioEngine->setPlayBackRate(playBackRate->getValue());
    }
}