#include <juce_audio_devices/juce_audio_devices.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MidiStructure.h"

//==============================================================================
OotbAudioProcessorEditor::OotbAudioProcessorEditor(OotbAudioProcessor &p)
        : AudioProcessorEditor(&p), processorRef(p) {
    juce::ignoreUnused(processorRef);

    addAndMakeVisible(invokeSysExButton);
    invokeSysExButton.setButtonText("Send SysEx Messages");
    invokeSysExButton.addListener(this);

    addAndMakeVisible(messageStatusLabel);
    messageStatusLabel.setColour(juce::Label::backgroundColourId, juce::Colours::black);
    messageStatusLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    messageStatusLabel.setJustificationType(juce::Justification::centred);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(400, 300);
}

OotbAudioProcessorEditor::~OotbAudioProcessorEditor() {
    invokeSysExButton.removeListener(this);
}

//==============================================================================
void OotbAudioProcessorEditor::paint(juce::Graphics &g) {
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("The OOTB MIDI Platform!", getLocalBounds(), juce::Justification::centred, 1);
}

void OotbAudioProcessorEditor::resized() {
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor.
    invokeSysExButton.setBounds(10, 10, getWidth() - 20, 40);
    messageStatusLabel.setBounds(10, 60, getWidth() - 20, 40);
}

void OotbAudioProcessorEditor::buttonClicked(juce::Button *button) {
    if (button == &invokeSysExButton) {
        auto currentTime = juce::Time::getCurrentTime();

        SysExData sysexData;
        DataParametersType1 dataParametersType1;
        sysexData.data = &dataParametersType1;
        uint8_t checksum = sysexData.calculateChecksum();
        std::cout << "sending sysex midi message with checksum of '0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(checksum) << "'" << std::endl;

        std::vector<uint8_t> sysexDataVector;
        std::vector<uint8_t> dataVector = sysexData.data->toVector();
        sysexDataVector = {sysexData.manufacturerId, sysexData.deviceId, sysexData.modelId, sysexData.commandId};
        sysexDataVector.insert(sysexDataVector.end(), std::begin(sysexData.address), std::end(sysexData.address));
        sysexDataVector.insert(sysexDataVector.end(), std::begin(dataVector), std::end(dataVector));
        sysexDataVector.push_back(checksum);

        juce::MidiMessage message;
        message = juce::MidiMessage::createSysExMessage(sysexDataVector.data(), sysexDataVector.size());

        // Get the first available MIDI output device
//        juce::Array<juce::MidiDeviceInfo> availableDevices;
//        availableDevices = juce::MidiOutput::getAvailableDevices();
//
//        for (auto& device : availableDevices) {
//            std::cout << device.name + ":" + device.identifier << std::endl;
//        }

        std::string deviceName = "24-0";
        std::unique_ptr<juce::MidiOutput> midiOut;
        midiOut = juce::MidiOutput::openDevice(deviceName);

        if (midiOut)
        {
            // Add the message to a MidiBuffer
            this->processorRef.addMidiMessage(message);
        }

        auto includeDate = true;
        auto includeTime = true;
        auto currentTimeString = currentTime.toString(includeDate, includeTime);

        messageStatusLabel.setText(currentTimeString, juce::dontSendNotification);
    }
}