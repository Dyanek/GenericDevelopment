#ifndef _IMAGE2DWRITER_HPP_
#define _IMAGE2DWRITER_HPP_

#include <iostream>
#include <string>
#include "Color.hpp"
#include "Image2D.hpp"

template <typename TValue>
class Image2DWriter 
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
class Image2DWriter<unsigned char> 
{
    public:
    typedef unsigned char Value;
    typedef Image2D<Value> Image;

    static bool write( Image & img, std::ostream & output, bool ascii )
    {
        // Définition du header
        if(!ascii)
            output << "P5\n";
        else
            output << "P2\n";

        output << img.w() << " " << img.h() << "\n";
        output << "255\n";
        
        const Image& cimg = img;
        for ( Image::ConstIterator it = cimg.begin(), itE = cimg.end(); it != itE; ++it )
            output << *it;

        return true;
    }
};

/// Specialization for color images.
template <>
class Image2DWriter<Color> 
{
    public:
    typedef Color Value;
    typedef Image2D<Value> Image;

    static bool write( Image & img, std::ostream & output, bool ascii )
    {
        if(!ascii)
            output << "P6" << std::endl; // PPM raw
        else
            output << "P3" << std::endl;

        output << img.w() << " " << img.h() << std::endl;
        output << "255" << std::endl;

        const Image& cimg = img; // Vue "constante" sur l'image img.
        for ( Image::ConstIterator it = cimg.begin(), itE = cimg.end(); it != itE; ++it )
        { 
            Color c = *it;
            output << c.red << c.green << c.blue;
        }

        return true;
    }
};

#endif // _IMAGE2DWRITER_HPP_