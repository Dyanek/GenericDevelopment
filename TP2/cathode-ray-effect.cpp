#include <iostream>
#include <fstream>
#include <fstream>
#include "Image2D.hpp"
#include "Color.hpp"
#include "Image2DWriter.hpp"
#include "Image2DReader.hpp"
#include "Accessor.hpp"

using namespace std;

int main( int argc, char** argv )
{
    typedef Image2D<Color> ColorImage2D;
    typedef ColorImage2D::Iterator Iterator;
        
    ColorImage2D img;
        
    ifstream input( argv[1] );
    try 
    {
        Image2DReader<Color>::read( img, input );
    }
    catch ( char const * msg ) 
    {
        std::cerr << "Exception: " << msg << std::endl;
    }
    catch (...) 
    {
        std::cerr << "Exception." << std::endl;
    }
    input.close();


    typedef ColorImage2D::GenericIterator< ColorRedAccessor >   ColorRedConstIterator;
    typedef ColorImage2D::GenericIterator< ColorGreenAccessor > ColorGreenConstIterator;
    typedef ColorImage2D::GenericIterator< ColorBlueAccessor >  ColorBlueConstIterator;

    ColorRedConstIterator   itRed   = img.begin< ColorRedAccessor >();
    ColorGreenConstIterator itGreen = img.begin< ColorGreenAccessor >();
    ColorBlueConstIterator  itBlue  = img.begin< ColorBlueAccessor >();

    int x = 0;
    for ( Iterator it = img.begin(), itE = img.end(); it != itE; ++it )
    {
        switch ( x % 3 ) 
        {
            case 0: 
                *itGreen = *itBlue  = 0; 
                break;
            case 1: 
                *itRed   = *itBlue  = 0; 
                break;
            case 2: 
                *itRed   = *itGreen = 0; 
                break;
        }

        ++itRed; 
        ++itGreen; 
        ++itBlue;
            
        x = ( x+1 ) % img.w();
    }


    ofstream output( argv[2] );
    bool ok2 = Image2DWriter<Color>::write( img, output, false );
    if ( !ok2 ) 
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();

    return 0;
}