#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Image2DWriter.hpp"
#include "Image2DReader.hpp"

using namespace std;

int main( int argc, char** argv )
{
    typedef unsigned char GrayLevel;
    typedef Image2D<GrayLevel> GrayLevelImage2D;
    typedef GrayLevelImage2D::Iterator Iterator;

    
    GrayLevelImage2D img;
        
    ifstream input( argv[1] );
    try 
    {
        Image2DReader<GrayLevel>::read( img, input );
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

    for ( Iterator it = img.begin(), itE = img.end(); it != itE; ++it )
        *it = (2 * ((int)(*it))) % 256;
        
    ofstream output( argv[2] );
    bool ok2 = Image2DWriter<GrayLevel>::write( img, output, false );
    if ( !ok2 ) 
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();
    
    return 0;
}