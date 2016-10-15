/*
  ==============================================================================

    Melotrigger

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MelotriggerAudioProcessor::MelotriggerAudioProcessor()
{
}

MelotriggerAudioProcessor::~MelotriggerAudioProcessor()
{
}

//==============================================================================
const String MelotriggerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MelotriggerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MelotriggerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double MelotriggerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MelotriggerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MelotriggerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MelotriggerAudioProcessor::setCurrentProgram (int index)
{
}

const String MelotriggerAudioProcessor::getProgramName (int index)
{
    return String();
}

void MelotriggerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MelotriggerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MelotriggerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MelotriggerAudioProcessor::setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet)
{
    // Reject any bus arrangements that are not compatible with your plugin

    const int numChannels = preferredSet.size();

   #if JucePlugin_IsMidiEffect
    if (numChannels != 0)
        return false;
   #elif JucePlugin_IsSynth
    if (isInput || (numChannels != 1 && numChannels != 2))
        return false;
   #else
    if (numChannels != 1 && numChannels != 2)
        return false;

    if (! AudioProcessor::setPreferredBusArrangement (! isInput, bus, preferredSet))
        return false;
   #endif

    return AudioProcessor::setPreferredBusArrangement (isInput, bus, preferredSet);
}
#endif

void MelotriggerAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // JUCE boilerplate
    /*
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
    */
    
    // MIDI processing
    buffer.clear();
    MidiBuffer processedMidi;
    int time;
    MidiMessage m;
    
    for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);)
    {
        if (m.isNoteOn())
        {
            uint8 newNoteNum = (uint8)_noteOnNum;
            m = MidiMessage::noteOn(m.getChannel(), newNoteNum, m.getVelocity());
        }
        else if (m.isNoteOff())
        {}
        else if (m.isAftertouch())
        {}
        else if (m.isPitchWheel())
        {}
        
        processedMidi.addEvent(m, time);
        printf("adding event at time %d\n", time);
    }
    
    midiMessages.swapWith(processedMidi);
}

//==============================================================================
bool MelotriggerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MelotriggerAudioProcessor::createEditor()
{
    return new MelotriggerAudioProcessorEditor (*this);
}

//==============================================================================
void MelotriggerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MelotriggerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MelotriggerAudioProcessor();
}
