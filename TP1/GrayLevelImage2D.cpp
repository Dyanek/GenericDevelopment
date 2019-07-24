#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include "GrayLevelImage2D.hpp"

GrayLevelImage2D::GrayLevelImage2D()
{
    this -> m_width = 0;
    this -> m_height = 0;
    this -> m_data = Container(0, 0);
}

GrayLevelImage2D::GrayLevelImage2D(int w, int h, GrayLevel g)
{
    this -> m_width = w;
    this -> m_height = h;
    this -> m_data = Container(w * h, g);
}

void GrayLevelImage2D::fill(GrayLevel g)
{
    this -> m_data = Container(this -> m_width * this -> m_height, g);
}

int GrayLevelImage2D::w() const
{
    return this -> m_width;
}

int GrayLevelImage2D::h() const
{
    return this -> m_height;
}

int GrayLevelImage2D::index(int x, int y) const
{
    return x + (y * this -> m_width);
}

GrayLevelImage2D::GrayLevel GrayLevelImage2D::at(int i, int j) const
{
    return this -> m_data.at(index(i, j));
}

GrayLevelImage2D::GrayLevel& GrayLevelImage2D::at( int i, int j )
{
    return this -> m_data.at(index(i, j));
}

GrayLevelImage2D::Iterator::Iterator(GrayLevelImage2D& Image, int x, int y)
:Container::iterator(Image.m_data.begin() + Image.index(x, y))
{  
}

GrayLevelImage2D::Iterator GrayLevelImage2D::begin()
{
    return start(0, 0);
}

GrayLevelImage2D::Iterator GrayLevelImage2D::end()
{
    return start(this -> m_width , this -> m_height - 1);
}

GrayLevelImage2D::Iterator GrayLevelImage2D::start(int x, int y)
{
    return Iterator(*this, x, y);
}

bool GrayLevelImage2D::importPGM(std::istream & input)
{
    if (!input.good()) // Teste si tout va bien
        std::cerr << "Problème !";

    std::string line;
    int i = 1;
    bool commentaires = false;

    while(i <= 4)
    {
        getline(input, line);

        while(line.substr(0) == "#") 
        { 
            getline(input, line);
            commentaires = true;
        } 

        if(i == 2 && !commentaires)
        {
            std::istringstream istr( line );
            istr >> this -> m_width >> this -> m_height;
            this -> m_data.resize(this -> m_width * this -> m_height);
        }
        else if(i == 3)
        {
            std::istringstream istr( line );
            istr >> this -> m_width >> this -> m_height;
            this -> m_data.resize(this -> m_width * this -> m_height); 
        }

        i++;
    }

    input >> std::noskipws;
    for ( GrayLevelImage2D::Iterator it = this -> begin(), itE = this -> end(); it != itE; ++it )
        input >> *it;

    return true;
}

bool GrayLevelImage2D::exportPGM(std::ostream & output, bool ascii)
{
    // Définition du header
    if(!ascii)
            output << "P5\n";
    else
        output << "P2\n";

    output << this -> m_width << " " << this -> m_height << "\n";
    output << "255\n";
    
    for ( GrayLevelImage2D::Iterator it = begin(), itE = end(); it != itE; ++it )
        output << *it;

    return true;
}

bool GrayLevelImage2D::filtrageMedian(int matrix_side)
{
    int matrix_size = matrix_side * matrix_side;
    GrayLevelImage2D new_image = GrayLevelImage2D(this -> w(), this -> h());
    new_image.m_data = this -> m_data;
    GrayLevel window[matrix_size];
    
    int edge = floor(matrix_side / 2);

    for (int x = edge; x < this -> w() - edge; ++x )
    {
        for(int y = edge; y < this -> h() - edge; ++y)
        {
            for (int fx = 0, i = 0; fx < matrix_side; ++fx)
            {
                for (int fy = 0; fy < matrix_side; ++fy, ++i)
                    window[i] = this -> at(x + fx - edge, y + fy - edge);
            }

            std::sort(window, window + matrix_size);
            new_image.at(x, y) = window[matrix_size / 2];
        }
    }

    this -> m_data = new_image.m_data;

    return true;
}

bool GrayLevelImage2D::affiner(int coefficient)
{  
    GrayLevelImage2D new_image = GrayLevelImage2D(this -> w(), this -> h());
    new_image.m_data = this -> m_data;
    int matrix[] = {0, -coefficient / 4, 0,
                    -coefficient / 4, 1 + coefficient, -coefficient / 4,
                    0, -coefficient / 4, 0};

    for ( int x = 1; x < this -> w() - 1; ++x ) 
    {
        for (int y = 1; y < this -> h() - 1; ++y)
        {
            int accumulator = 0;

            for (int fx = 0; fx < 3; ++fx)
            {
                for (int fy = 0; fy < 3; ++fy) 
                {
                    int matrix_value = matrix[fx + (3 * fy)];
                    int pixel_val = this -> at(x + fx - 1, y + fy - 1);
                    
                    accumulator += pixel_val * matrix_value;
                }
            }

            new_image.at(x, y) = (GrayLevel) accumulator;
        }
    }    

    this -> m_data = new_image.m_data;

    return true;
}