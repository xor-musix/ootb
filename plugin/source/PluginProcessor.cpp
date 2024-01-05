#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
OotbAudioProcessor::OotbAudioProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
{
}

OotbAudioProcessor::~OotbAudioProcessor()
{
}

//==============================================================================
const juce::String OotbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool OotbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool OotbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool OotbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double OotbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int OotbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int OotbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void OotbAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String OotbAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void OotbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void OotbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused (sampleRate, samplesPerBlock);
}

void OotbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool OotbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}

void OotbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                       juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        juce::ignoreUnused (channelData);
        // ..do something to the data...
    }

    if (midiMessages.data.size() > 0)
    {
        std::cout << "midi messages IN size: " << midiMessages.data.size() << std::endl;
    }

    // Iterate over incoming MIDI messages
    juce::MidiBuffer processedMidi;
    for (const auto metadata : midiMessages)
    {
        auto message = metadata.getMessage();
        if (message.isSysEx())
        {
            // Handle SysEx message
            handleIncomingMidiMessage(message);
        }
        else
        {
            // Pass non-SysEx messages through
            processedMidi.addEvent(message, metadata.samplePosition);
            std::cout << "pass non-sysex message through: " << message.getDescription() << std::endl;
        }
    }

    // Swap MIDI buffers
    midiMessages.clear();
    midiMessages.swapWith(processedMidi);

    this->swapWithMidiMessageFromEditor(midiMessages);

    if (midiMessages.data.size() > 0)
    {
        std::cout << "midi messages OUT size: " << midiMessages.data.size() << std::endl;
    }
}

//==============================================================================
bool OotbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* OotbAudioProcessor::createEditor()
{
    return new OotbAudioProcessorEditor (*this);
}

//==============================================================================
void OotbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused (destData);
}

void OotbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}

void OotbAudioProcessor::handleIncomingMidiMessage(juce::MidiMessage message) {
    std::cout << "handle incoming midi message: " << message.getDescription() << std::endl;
}

void OotbAudioProcessor::addMidiMessage(const juce::MidiMessage &message) {
    std::cout << "add midi message: " << message.getDescription() << std::endl;

    juce::ScopedLock lock (midiBufferCriticalSection);
    midiMessageFromEditor.addEvent (message, 0);
}

void OotbAudioProcessor::swapWithMidiMessageFromEditor(juce::MidiBuffer &midiBuffer) {
    if (midiMessageFromEditor.data.size() > 0)
    {
        std::cout << "prepare midi message: " << midiMessageFromEditor.data.size() << std::endl;

        juce::ScopedLock lock (midiBufferCriticalSection);
        midiBuffer.swapWith (midiMessageFromEditor);
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new OotbAudioProcessor();
}