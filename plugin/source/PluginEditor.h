#pragma once

#include "PluginProcessor.h"

//==============================================================================
class OotbAudioProcessorEditor final :
        public juce::AudioProcessorEditor,
        public juce::Button::Listener
{
public:
    explicit OotbAudioProcessorEditor (OotbAudioProcessor&);
    ~OotbAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button *button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    OotbAudioProcessor& processorRef;

    juce::TextButton invokeSysExButton;
    juce::Label messageStatusLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OotbAudioProcessorEditor)
};