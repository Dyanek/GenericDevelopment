#include <iostream>
#include <fstream>
#include <fstream>
#include "Image2DWriter.hpp"
#include "Image2DReader.hpp"

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


    //Parcourt chaque pixel et inverse le rouge et le bleu
    for(Iterator it = img.begin(), itE = img.end(); it != itE; ++it)
    {
        Color c = *it;
        *it = Color(c.blue, c.green, c.red);
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