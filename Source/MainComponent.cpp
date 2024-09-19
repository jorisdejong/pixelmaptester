#include "MainComponent.h"
#include "RandomWords.h"

//==============================================================================
MainComponent::MainComponent()
{

	wordsArray = StringArray::fromTokens( words, false );


	setSize( 600, 400 );
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint( juce::Graphics& g )
{
	for ( auto pmButton : pmButtons )
		pmButton->paint( g, pmButtons.indexOf( pmButton ) / ( float )pmButtons.size(), { 0, 0 }, 300, 500 );
}

void MainComponent::resized()
{
	pmButtons.clear();
	
	Array<Rectangle<int>> rectangles;
	subdivideRectangle( 0, 0, getWidth(), getHeight(), rectangles );

	for ( auto& rect : rectangles )
	{
		Slice s;
		int numWords = 2;
		for ( int i = 0; i < numWords; i++ )
		{
			int index = rand() % wordsArray.size();
			s.name += wordsArray[ index ];
			if ( i != numWords - 1 )
				s.name += " ";
		}

		Path p;

		p.addRectangle( rect );
		s.inputRect = p;
		pmButtons.add( new PixelMapButton( s, true ) );
	}
}

void MainComponent::mouseDown( const MouseEvent& e )
{
	startDraggingComponent( getParentComponent(), e );
	
}

void MainComponent::mouseDrag( const MouseEvent& e )
{
	dragComponent( getParentComponent(), e, nullptr );
}

void MainComponent::mouseUp( const MouseEvent& e )
{
	if ( !e.mouseWasDraggedSinceMouseDown() )
	{
		resized();
		repaint();
	}
}

void MainComponent::subdivideRectangle( int x, int y, int width, int height, Array<Rectangle<int>>& rectangles )
{
	// Check if we need to stop subdividing
	int max = 256;
	int min = 64;
	if ( width < ( rand() % max ) + min || height < ( rand() % max ) + min )
	{
		rectangles.add( { x, y, width, height } );
		return;
	}

	// Randomly decide to split horizontally or vertically
	bool splitHorizontally = rand() % 2 == 0;

	if ( splitHorizontally ) 
	{
		int splitY = rand() % ( height - 1  ) + 1; // Random split point for height
		// Create two new rectangles
		subdivideRectangle( x, y, width, splitY, rectangles ); // Top rectangle
		subdivideRectangle( x, y + splitY, width, height - splitY, rectangles ); // Bottom rectangle
	}
	else 
	{
		int splitX = rand() % ( width - 1 ) + 1; // Random split point for width
		// Create two new rectangles
		subdivideRectangle( x, y, splitX, height, rectangles ); // Left rectangle
		subdivideRectangle( x + splitX, y, width - splitX, height, rectangles ); // Right rectangle
	}
}

