#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (1000, 400);
    TC.setText ("00:00:00:00", juce::dontSendNotification);
    // Set font justified center
    TC.setJustificationType (juce::Justification::centred);
    TC.setFont(juce::Font (juce::FontOptions ("Courier New", 80.0f, juce::Font::plain)));
    addAndMakeVisible (TC);
    Cue.setText ("Next Cue: : ", juce::dontSendNotification);
    Cue.setJustificationType (juce::Justification::centred);
    Cue.setFont(juce::Font (juce::FontOptions ("Courier New", 80.0f, juce::Font::plain)));
    Cue.setColour (juce::Label::textColourId, juce::Colours::red);
    addAndMakeVisible (Cue);
    // configure the OSCReceiver
    connect(9000);
    addListener(this, "/tc");
    addListener(this, "/cue");
    startTimer (16);
}

MainComponent::~MainComponent()
{
}

void MainComponent::oscMessageReceived (const juce::OSCMessage& message)
{
    // handle incoming OSC messages
    auto addr = message.getAddressPattern().toString();
    if (addr == "/tc") {
        if (message.size() == 4) {
            h = message[0].getInt32();
            m = message[1].getInt32();
            s = message[2].getInt32();
            f = message[3].getInt32();
           // TC.setText (juce::String::formatted ("%02d:%02d:%02d:%02d", h, m, s, f), juce::dontSendNotification);
        }
    }
    
    if (addr == "/cue") {
        if (message.size() == 2) {
            auto cueCount = message[0].getInt32();
            auto cueName = message[1].getString();
            Cue.setText (juce::String::formatted ("Next Cue: %d: ", cueCount) + cueName, juce::dontSendNotification);
        }
    }
    
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);

    g.setFont (juce::FontOptions (16.0f));
    g.setColour (juce::Colours::white);
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds();
    
    auto TCBounds = bounds.removeFromTop (getHeight() / 2);
    
    TC.setBounds (TCBounds.reduced(20));
    Cue.setBounds (bounds.reduced(20));
    
    TC.setFont(juce::Font (juce::FontOptions ("Courier New", getWidth() / 8, juce::Font::plain)));
    Cue.setFont(juce::Font (juce::FontOptions ("Courier New", getWidth() / 11, juce::Font::plain)));
    
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainComponent::timerCallback()
{
    TC.setText (juce::String::formatted ("%02d:%02d:%02d:%02d", h, m, s, f), juce::dontSendNotification);
    
}
