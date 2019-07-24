#include <iostream>
#include <fstream>
#include <fstream>
#include "Image2DWriter.hpp"
#include "Image2DReader.hpp"
#include "Accessor.hpp"
#include "Histogramme.hpp"

using namespace std;

int main( int argc, char** argv )
{
    typedef Image2D<Color> ColorImage2D;
    typedef ColorImage2D::Iterator ColorIterator;
    typedef Image2D<unsigned char> GrayLevelImage2D;
    typedef Image2DWriter<unsigned char> GrayLevelImage2DWriter;
    typedef GrayLevelImage2D::Iterator GLIterator;
    
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



    //Crée une image en GrayLevel qui stockera la valeur V du HSV de chaque pixel
    GrayLevelImage2D valueImage( img.w(), img.h() );

    typedef ColorImage2D::GenericIterator< ColorValueAccessor > ColorValueIterator;

    //Permet de parcourir l'itérateur de l'image couleur
    ColorIterator itVal = img.begin();

    for(GLIterator it = valueImage.begin(), itE = valueImage.end(); it != itE; ++it)
    {
        Color c = *itVal;

        int h;
        float s, v;

        c.getHSV(h,s,v);

        //v est entre 0 et 1
        *it = v * 255;

        ++itVal;
    }


    /*Une fois l'image en GrayScale remplie, nous pouvons calculer son histogramme
    en la traitant en tant qu'image en GrayScale */
    Histogramme hist;
    hist.init( valueImage.begin(), valueImage.end() ); 


    std::ofstream output( argv[2] ); // récupère le 2eme argument.
    bool ok3 = GrayLevelImage2DWriter::write( valueImage, output, false );
    if ( !ok3 )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();

    return 0;
}