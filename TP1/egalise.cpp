#include "Histogramme.cpp"

using namespace std;

int main( int argc, char** argv )
{
    typedef GrayLevelImage2D::GrayLevel GrayLevel;
    typedef GrayLevelImage2D::Iterator Iterator;
    GrayLevelImage2D img;
    Histogramme hist;
    
    ifstream input( argv[1] );
    try 
    {
        img.importPGM( input );
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
    
    hist.init(img);

    for ( Iterator it = img.begin(), itE = img.end(); it != itE; ++it )
         *it = hist.egalisation(*it);

    ofstream output( argv[2] );
    img.exportPGM( output, false );
    std::cout << std::endl;

    return 0;
}