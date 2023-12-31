#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
OotbAudioProcessorEditor::OotbAudioProcessorEditor (OotbAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);

    addAndMakeVisible(invokeSysExButton);
    invokeSysExButton.setButtonText("Send SysEx Messages");
    invokeSysExButton.addListener(this);

    addAndMakeVisible (messageStatusLabel);
    messageStatusLabel.setColour (juce::Label::backgroundColourId, juce::Colours::black);
    messageStatusLabel.setColour (juce::Label::textColourId, juce::Colours::white);
    messageStatusLabel.setJustificationType (juce::Justification::centred);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

OotbAudioProcessorEditor::~OotbAudioProcessorEditor()
{
    invokeSysExButton.removeListener(this);
}

//==============================================================================
void OotbAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("The OOTB MIDI Platform!", getLocalBounds(), juce::Justification::centred, 1);
}

void OotbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor.
    invokeSysExButton.setBounds (10, 10, getWidth() - 20, 40);
    messageStatusLabel.setBounds (10, 60, getWidth() - 20, 40);
}

void OotbAudioProcessorEditor::buttonClicked(juce::Button *button) {
    if (button == &invokeSysExButton)
    {
        auto currentTime = juce::Time::getCurrentTime();

        auto includeDate = true;
        auto includeTime = true;
        auto currentTimeString = currentTime.toString (includeDate, includeTime);

        messageStatusLabel.setText (currentTimeString, juce::dontSendNotification);
    }
}