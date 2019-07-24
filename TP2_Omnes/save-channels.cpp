#include <cmath>
#include <iostream>
#include <fstream>
#include "Image2D.hpp"
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
        std::cerr << "Usage: save-channels <input.ppm> <output>" << std::endl;
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

    std::string outputName = argv[2];

    GrayLevelImage2D imgRed( img.w(), img.h() );
    
    //-----------------------------------------------------------------------------
    // vvvvvvvvv Toute la transformation couleur -> canal rouge est ici vvvvvvvvvvvv
    //

    // Servira à parcourir la composante verte de l'image couleur.
    typedef ColorImage2D::GenericIterator< ColorRedAccessor > ColorRedConstIterator;

    // Notez comment on appelle la méthode \b générique `begin` de `Image2D`.
    ColorRedConstIterator itRed = img.begin< ColorRedAccessor >();

    // On écrit la composante verte dans l'image en niveaux de gris.
    for ( GrayLevelIterator it = imgRed.begin(), itE = imgRed.end(); it != itE; ++it )
    {
        *it = *itRed;
        ++itRed;
        // NB: si on veut faire *itRed++, il faut redéfinir GenericConstIterator<T>::operator++(int).
    }

    //-----------------------------------------------------------------------------
    
    std::ofstream output( outputName + "-red.pgm" ); // récupère le 2eme argument.
    bool ok3 = GrayLevelImage2DWriter::write( imgRed, output, false );
    if ( !ok3 )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();

    GrayLevelImage2D imgGreen( img.w(), img.h() );
    
    //-----------------------------------------------------------------------------
    // vvvvvvvvv Toute la transformation couleur -> canal vert est ici vvvvvvvvvvvv
    //

    // Servira à parcourir la composante verte de l'image couleur.
    typedef ColorImage2D::GenericIterator< ColorGreenAccessor > ColorGreenConstIterator;

    // Notez comment on appelle la méthode \b générique `begin` de `Image2D`.
    ColorGreenConstIterator itGreen = img.begin< ColorGreenAccessor >();

    // On écrit la composante verte dans l'image en niveaux de gris.
    for ( GrayLevelIterator it = imgGreen.begin(), itE = imgGreen.end(); it != itE; ++it )
    {
        *it = *itGreen;
        ++itGreen;
        // NB: si on veut faire *itGreen++, il faut redéfinir GenericConstIterator<T>::operator++(int).
    }

    //-----------------------------------------------------------------------------
    std::ofstream output1( outputName + "-green.pgm" ); // récupère le 2eme argument.
    bool ok4 = GrayLevelImage2DWriter::write( imgGreen, output1, false );
    if ( !ok4 )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output1.close();

    GrayLevelImage2D imgBlue( img.w(), img.h() );
    
    //-----------------------------------------------------------------------------
    // vvvvvvvvv Toute la transformation couleur -> canal bleu est ici vvvvvvvvvvvv
    //

    // Servira à parcourir la composante bleue de l'image couleur.
    typedef ColorImage2D::GenericIterator< ColorBlueAccessor > ColorBlueConstIterator;

    // Notez comment on appelle la méthode \b générique `begin` de `Image2D`.
    ColorBlueConstIterator itBlue = img.begin< ColorBlueAccessor >();

    // On écrit la composante verte dans l'image en niveaux de gris.
    for ( GrayLevelIterator it = imgBlue.begin(), itE = imgBlue.end(); it != itE; ++it )
    {
        *it = *itBlue;
        ++itBlue;
        // NB: si on veut faire *itBlue++, il faut redéfinir GenericConstIterator<T>::operator++(int).
    }

    //-----------------------------------------------------------------------------
    std::ofstream output2( outputName + "-blue.pgm" ); // récupère le 2eme argument.
    bool ok2 = GrayLevelImage2DWriter::write( imgBlue, output2, false );
    if ( !ok2 )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output2.close();

    return 0;
}