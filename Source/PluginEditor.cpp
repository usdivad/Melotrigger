/*
  ==============================================================================

    Melotrigger

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MelotriggerAudioProcessorEditor::MelotriggerAudioProcessorEditor (MelotriggerAudioProcessor& p)
    : AudioProcessorEditor (&p), _processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    // MIDI info display properties
    Font midiInfoDisplayFont("Arial", 15.0f, Font::plain);
    _midiInfoDisplay.setAlpha(0.75);
    _midiInfoDisplay.setColour(Colours::white);
    _midiInfoDisplay.setFont(midiInfoDisplayFont, true);
    _midiInfoDisplay.setText("No MIDI input detected");
    
    // MIDI note out
    _midiNoteOutSelector.setSliderStyle(Slider::LinearBarVertical);
    _midiNoteOutSelector.setRange(0.0, 127.0);
    _midiNoteOutSelector.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    _midiNoteOutSelector.setTextValueSuffix(" Note Out");
    _midiNoteOutSelector.setPopupDisplayEnabled(true, this);
    _midiNoteOutSelector.setValue(1.0);
    _midiNoteOutSelector.addListener(this);
    
    // Add UI elements to editor
    addAndMakeVisible(&_midiInfoDisplay);
    addAndMakeVisible(&_midiNoteOutSelector);
}

MelotriggerAudioProcessorEditor::~MelotriggerAudioProcessorEditor()
{
}

//==============================================================================
void MelotriggerAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);

    g.setColour (Colours::white);
    g.setFont (15.0f);
    
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
    g.drawFittedText("Melotrigger", 0, 0, getWidth(), 30, Justification::centred, 1);
}

void MelotriggerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    _midiNoteOutSelector.setBounds(40, 30, 20, getHeight()-60);
}

void MelotriggerAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    _processor._noteOnNum = _midiNoteOutSelector.getValue();
}

