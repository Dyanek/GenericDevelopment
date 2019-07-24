#ifndef _IMAGE2DREADER_HPP_
#define _IMAGE2DREADER_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include "Color.hpp"
#include "Image2D.hpp"

template <typename TValue>
class Image2DReader 
{
    public:
    typedef TValue Value;
    typedef Image2D<Value> Image;

    static bool write( Image & img, std::ostream & output, bool ascii )
    {
        std::cerr << "[Image2DWriter<TValue>::write] NOT IMPLEMENTED." << std::endl;
        return false;
    }
};

/// Specialization for gray-level images.
template <>
class Image2DReader<unsigned char> 
{
    public:
    typedef unsigned char Value;
    typedef Image2D<Value> Image;

    static bool read( Image & image, std::istream & input )
    {
        if (!input.good()) // Teste si tout va bien
        std::cerr << "Problème !";

        std::string line;
        int i = 1;
        bool commentaires = false;

        int width;
        int height;

        while(i <= 4)
        {
            getline(input, line);
            
            if(i == 2 && line.substr(0) != "#")
            {
                std::istringstream istr( line );
                istr >> width >> height;
            }
            else if(i == 2)
            {
                while(line.substr(0) == "#") 
                    getline(input, line);

                ++i; 
            }
            else if(i == 3 && width == 0 && height == 0)
            { 
                std::istringstream istr( line );
                istr >> width >> height;
            }

            ++i;
        }

        image = Image(width, height, 0);

        input >> std::noskipws;
        for ( Image::Iterator it = image.begin(), itE = image.end(); it != itE; ++it )
            input >> *it;

        return true;
    }
};

/// Specialization for color images.
template <>
class Image2DReader<Color> 
{
    public:
    typedef Color Value;
    typedef Image2D<Value> Image;

    static bool read( Image & image, std::istream & input )
    {
        typedef unsigned char Byte;

        if (!input.good()) // Teste si tout va bien
            std::cerr << "Problème !";

        std::string line;
        int i = 1;

        int width = 0;
        int height = 0;

        while(i <= 4)
        {
            getline(input, line);
            
            if(i == 2 && line.substr(0) != "#")
            {
                std::istringstream istr( line );
                istr >> width >> height;
            }
            else if(i == 2)
            {
                while(line.substr(0) == "#") 
                    getline(input, line); 
            }
            else if(i == 3 && width == 0 && height == 0)
            { 
                std::istringstream istr( line );
                istr >> width >> height;
            }

            ++i;
        }

        image = Image(width, height);

        input >> std::noskipws;
        for ( Image::Iterator it = image.begin(), itE = image.end(); it != itE; ++it )
        {
            Byte redVal, greenVal, blueVal;

            /*
            Les couleurs sont affichées correctemment avec cet ordre
            (bleu, rouge, vert) mais je ne saurais expliquer pourquoi.
            Avant que je n'implémente certaines parties du code, l'ordre
            standard fonctionnait sans souci.
            */
            input >> redVal >> greenVal >> blueVal;
            
            *it = Color(redVal, greenVal, blueVal);
        }

        return true;
    }
};

#endif // _IMAGE2DREADER_HPP_