#include "MidiParameters.h"

#include <juce_core/juce_core.h>
#include <juce_data_structures/juce_data_structures.h>
#include <unordered_map>

using namespace juce;

MidiParameters::MidiParameters(const char *definitionFile) {
    // Load XML file
    std::unique_ptr<XmlElement> xml(XmlDocument::parse(File(definitionFile)));

//    juce::String xmlString = R"(
//<parameters>
//    <parameter name="parameter1" description="Common Parameter" address="0x00,0x00,0x00,0x01" type="Number" rangeMin="0" rangeMax="127" stepRate="1" value="64"/>
//    <parameter name="parameter2" description="Patch Parameter" address="0x00,0x00,0x00,0x02" type="Text" value="Hello"/>
//</parameters>
//)";
//
//    std::unique_ptr<juce::XmlElement> xml(XmlDocument::parse(xmlString));

    // Convert XML to ValueTree
    ValueTree synthParameters = ValueTree::fromXml(*xml);

    // Create lookup table by address
    std::unordered_map<String, ValueTree> lookupByAddress;
    for (int i = 0; i < synthParameters.getNumChildren(); ++i) {
        ValueTree child = synthParameters.getChild(i);
        String address = child.getProperty("address");
        lookupByAddress[address] = child;
    }

    // Now you can look up parameters by address and modify them directly
    // For example:
    ValueTree& parameterByAddress = lookupByAddress["0x00,0x00,0x00,0x01"];
    std::cout << "Parameter with address 0x00,0x00,0x00,0x01: " << parameterByAddress.getProperty("name").toString() << std::endl;

    // Modify it directly
    parameterByAddress.setProperty("name", "modifiedParameter1", nullptr);
    std::cout << "Modified parameter name: " << parameterByAddress.getProperty("name").toString() << std::endl;

    ValueTree modifiedParameter = lookupByAddress["0x00,0x00,0x00,0x01"];
    std::cout << "new valuetree get Modified parameter name: " << parameterByAddress.getProperty("name").toString() << std::endl;

    std::unique_ptr<juce::XmlElement> xmlElement = synthParameters.createXml();
    std::cout << xmlElement->toString() << std::endl;
}