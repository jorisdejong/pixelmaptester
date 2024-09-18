#pragma once

#include <JuceHeader.h>
#include "../chaser/Source/utility/PixelMapButton.h"
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component,
    public ComponentDragger
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    OwnedArray<PixelMapButton> pmButtons;

    void mouseDown( const MouseEvent& ) override;
    void mouseDrag( const MouseEvent& ) override;
    void mouseUp( const MouseEvent& ) override;

    void subdivideRectangle( int x, int y, int width, int height, Array<Rectangle<int>>& rectangles );

    StringArray wordsArray;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
