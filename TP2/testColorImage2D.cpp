#include <iostream>
#include <fstream>
#include <fstream>
#include "Image2D.hpp"
#include "Color.hpp"
#include "Image2DWriter.hpp"
#include "Image2DReader.hpp"

using namespace std;

int main( int argc, char** argv )
{
    /*{
        typedef Image2D<Color> ColorImage2D;

        ColorImage2D img( 3, 3, Color(255, 255, 0) ); // imagette 8x8 verte

        for ( int y = 0; y < img.h(); ++y )
        {
            for ( int x = 0; x < img.w(); ++x )
            {
                Color c = img.at(x, y);
                std::cout << " " << c.r()*255 << " " << c.g()*255 << " " << c.b()*255;
            }
            
            std::cout << std::endl;
        }
    }

    /*{
        typedef Image2D<Color> ColorImage2D;
        typedef ColorImage2D::Iterator Iterator;
        typedef ColorImage2D::ConstIterator ConstIterator;

        ColorImage2D img( 256, 256, Color( 0, 0, 0 ) );
        Iterator it = img.begin();

        for ( int y = 0; y < 256; ++y )
        {
            for ( int x = 0; x < 256; ++x )    
                *it++ = Color( y, x, (2*x+2*y) % 256 );
        }

        std::ofstream output( "colors.ppm" );

        output << "P6" << std::endl; // PPM raw
        output << "# Generated by You !" << std::endl;
        output << img.w() << " " << img.h() << std::endl;
        output << "255" << std::endl;

        for ( Iterator it = img.begin(), itE = img.end(); it != itE; ++it ) // (*)
        { 
            Color c = *it;
            output << c.red << c.green << c.blue;
        }
        

        const ColorImage2D& cimg = img; // Vue "constante" sur l'image img.
        for ( ConstIterator it = cimg.begin(), itE = cimg.end(); it != itE; ++it ) // (*)
        { 
            Color c = *it;
            output << c.red << c.green << c.blue;
        }

        output.close();
    }*/

    /*{
        typedef Image2D<Color> ColorImage2D;
        typedef ColorImage2D::Iterator Iterator;
        typedef ColorImage2D::ConstIterator ConstIterator;

        ColorImage2D img( 256, 256, Color( 0, 0, 0 ) );
        Iterator it = img.begin();

        for ( int y = 0; y < 256; ++y )
        {
            for ( int x = 0; x < 256; ++x )    
                *it++ = Color( y, x, (2*x+2*y) % 256 );
        }

        ofstream output( "colors.ppm" );
        bool ok2 = Image2DWriter<Color>::write( img, output, false );
        if ( !ok2 ) 
        {
            std::cerr << "Error writing output file." << std::endl;
            return 1;
        }
        output.close();
    }*/

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
        
        ofstream output( argv[2] );
        bool ok2 = Image2DWriter<Color>::write( img, output, false );
        if ( !ok2 ) 
        {
            std::cerr << "Error writing output file." << std::endl;
            return 1;
        }
        output.close();
    }

    return 0;
}