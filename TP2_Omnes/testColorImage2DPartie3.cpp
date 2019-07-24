#include <iostream>
#include <fstream>
#include <fstream>
#include "Image2D.hpp"
#include "Color.hpp"

using namespace std;

int main( int argc, char** argv )
{
    typedef Image2D<Color> ColorImage2D;

    ColorImage2D img( 3, 3, Color(125, 255, 0) ); // imagette 8x8 verte

    for ( int y = 0; y < img.h(); ++y )
    {
        for ( int x = 0; x < img.w(); ++x )
        {
            Color couleur = img.at(x, y);
            std::cout << " " << couleur.r()*255 << " " << couleur.g()*255 << " " << couleur.b()*255;
        }
            
        std::cout << std::endl;
    }

    return 0;
}