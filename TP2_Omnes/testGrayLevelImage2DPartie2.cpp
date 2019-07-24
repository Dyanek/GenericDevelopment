#include <iostream>
#include <fstream>
#include "Image2D.hpp"

using namespace std;

int main( int argc, char** argv )
{
    typedef unsigned char GrayLevel;
    typedef Image2D<GrayLevel> GrayLevelImage2D;
        
    GrayLevelImage2D img( 8, 8, 5 ); // imagette 8x8 remplie de 5

    for ( int y = 0; y < img.h(); ++y )
    {
        for ( int x = 0; x < img.w(); ++x )
            std::cout << " " << (int) img.at( x, y ); // la conversion permet de voir les caractères sous forme d'entiers.
            
        std::cout << std::endl;
    }
    
    return 0;
}