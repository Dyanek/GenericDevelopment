#include <cmath>
#include <iostream>
#include <fstream>
#include "Image2DReader.hpp"
#include "Image2DWriter.hpp"
#include "Accessor.hpp"

int main( int argc, char** argv )
{
    typedef Image2D<Color> ColorImage2D;
    typedef Image2DReader<Color> ColorImage2DReader;
    typedef ColorImage2D::Iterator ColorIterator;

    if ( argc < 3 ) 
    { 
        std::cerr << "Usage: save-green-channel <input.ppm> <output.pgm>" << std::endl;
        return 0;
    }

    ColorImage2D img;

    std::ifstream input( argv[1] ); // récupère le 1er argument.
    bool ok = ColorImage2DReader::read( img, input );
    if ( !ok )
    {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();

    typedef Image2D<unsigned char> GrayLevelImage2D;
    typedef Image2DWriter<unsigned char> GrayLevelImage2DWriter;
    typedef GrayLevelImage2D::Iterator GrayLevelIterator;

    GrayLevelImage2D img2( img.w(), img.h() );
    
    //-----------------------------------------------------------------------------
    // vvvvvvvvv Toute la transformation couleur -> canal vert est ici vvvvvvvvvvvv
    //

    // Servira à parcourir la composante verte de l'image couleur.
    typedef ColorImage2D::GenericIterator< ColorGreenAccessor > ColorGreenConstIterator;

    // Notez comment on appelle la méthode \b générique `begin` de `Image2D`.
    ColorGreenConstIterator itGreen = img.begin< ColorGreenAccessor >();

    // On écrit la composante verte dans l'image en niveaux de gris.
    for ( GrayLevelIterator it = img2.begin(), itE = img2.end(); it != itE; ++it )
    {
        *it = *itGreen;
        ++itGreen;
        // NB: si on veut faire *itGreen++, il faut redéfinir GenericConstIterator<T>::operator++(int).
    }

    //-----------------------------------------------------------------------------
    std::ofstream output( argv[2] ); // récupère le 2eme argument.
    bool ok2 = GrayLevelImage2DWriter::write( img2, output, false );
    if ( !ok2 )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();

    return 0;
}