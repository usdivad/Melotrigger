/*
  ==============================================================================

    Melotrigger

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class MelotriggerAudioProcessorEditor  : public AudioProcessorEditor,
                                         private Slider::Listener
{
public:
    MelotriggerAudioProcessorEditor (MelotriggerAudioProcessor&);
    ~MelotriggerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    void sliderValueChanged(Slider* slider) override;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MelotriggerAudioProcessor& _processor;
    
    // Melotrigger members
    DrawableText _midiInfoDisplay;
    Slider _midiNoteOutSelector;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MelotriggerAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
