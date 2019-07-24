#include <iostream>
#include <fstream>
#include <fstream>
#include <algorithm> 
#include "Image2DWriter.hpp"
#include "Image2DReader.hpp"

using namespace std;

int main( int argc, char** argv )
{
    
    typedef Image2D<unsigned char> ColorImage2D;
    typedef ColorImage2D::Iterator Iterator;
        
    ColorImage2D img;
        
    ifstream input( argv[1] );
    try 
    {
        Image2DReader<unsigned char>::read( img, input );
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

    Image2D<Color> imgColor(img.w(), img.h());

    img.sepiaFilter(imgColor);


    ofstream output( argv[2] );
    bool ok2 = Image2DWriter<Color>::write( imgColor, output, false );
    if ( !ok2 ) 
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();

    return 0;
}