#include <iostream>
#include <fstream>
#include "GrayLevelImage2D.cpp"

using namespace std;

int main( int argc, char** argv )
{
    typedef GrayLevelImage2D::GrayLevel GrayLevel;
    typedef GrayLevelImage2D::Iterator  Iterator;

    if ( argc < 3 ) 
    { 
        std::cerr << "Usage: filtrage-median <input.pgm> <output.pgm> <matrix size>" << std::endl;
        return 0;
    }

    GrayLevelImage2D img;
    ifstream input( argv[1] ); // récupère le 1er argument.
    bool ok = img.importPGM( input );
    if ( !ok )
    {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();

    int matrix = (argc > 3) ? stoi( argv[ 3 ] ) : 3;
    ok = img.filtrageMedian( matrix );
    if ( !ok )
    {
        std::cerr << "Error filtrating the image." << std::endl;
        return 1;
    }

    ofstream output( argv[2] ); // récupère le 2ème argument.
    ok = img.exportPGM( output, false );
    if ( !ok )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();

    return 0;
}