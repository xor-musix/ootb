#include "SysexMidiInputCallback.h"

void SysexMidiInputCallback::handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message)
{
    // Handle the incoming MIDI message here
    std::cout << "Handle the incoming MIDI message...";
}

void SysexMidiInputCallback::handlePartialSysexMessage(juce::MidiInput* source, const juce::uint8* messageData, int numBytesSoFar, double timestamp)
{
    // Handle the incoming SysEx message here
    std::cout << "Handle the incoming SysEx message...";
}