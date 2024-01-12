#ifndef OOTB_MIDIPARAMETERS_H
#define OOTB_MIDIPARAMETERS_H

#include <juce_data_structures/juce_data_structures.h>

class MidiParameters final {
public:
    MidiParameters(const char *definitionFile);
    ~MidiParameters() = default;

    void traverseValueTree(const juce::ValueTree& tree);

};


#endif //OOTB_MIDIPARAMETERS_H