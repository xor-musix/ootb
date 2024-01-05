#ifndef SYSEX_MIDI_INPUT_CALLBACK_H
#define SYSEX_MIDI_INPUT_CALLBACK_H

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/midi_io/juce_MidiDevices.h>

class SysexMidiInputCallback : public juce::MidiInputCallback
{
public:
    void handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message) override;
    void handlePartialSysexMessage(juce::MidiInput* source, const juce::uint8* messageData, int numBytesSoFar, double timestamp) override;
};

#endif // SYSEX_MIDI_INPUT_CALLBACK_H