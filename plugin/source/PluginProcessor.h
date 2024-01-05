#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

//==============================================================================
class OotbAudioProcessor final : public juce::AudioProcessor
{
public:
    //==============================================================================
    OotbAudioProcessor();
    ~OotbAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void addMidiMessage (const juce::MidiMessage& message)
    {
        std::cout << "add midi message: " << message.getDescription() << std::endl;

        juce::ScopedLock lock (midiBufferCriticalSection);
        midiMessageFromEditor.addEvent (message, 0);
    }

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OotbAudioProcessor)

    juce::CriticalSection midiBufferCriticalSection;
    juce::MidiBuffer midiMessageFromEditor;

    void swapWithMidiMessageFromEditor (juce::MidiBuffer& midiBuffer)
    {
        if (midiMessageFromEditor.data.size() > 0)
        {
            std::cout << "prepare midi message: " << midiMessageFromEditor.data.size() << std::endl;

            juce::ScopedLock lock (midiBufferCriticalSection);
            midiBuffer.swapWith (midiMessageFromEditor);
        }
    }

    static void handleIncomingMidiMessage(juce::MidiMessage message);
};