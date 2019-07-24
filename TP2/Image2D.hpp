#ifndef _IMAGE2D_HPP_
#define _IMAGE2D_HPP_

#include <vector>
#include <algorithm>
#include "Color.hpp"

template <typename TValue>
class Image2D 
{
    public:
    typedef Image2D<TValue>    Self;      // le type de *this
    typedef TValue             Value;     // le type pour la valeur des pixels
    typedef std::vector<Value> Container; // le type pour stocker les valeurs des pixels de l'image.

    // Constructeur par défaut
    Image2D() : m_width(0), m_height(0), m_data(Container(0, Value())) { }

    // Constructeur avec taille w x h. Remplit tout avec la valeur g
    // (par défaut celle donnée par le constructeur par défaut).
    Image2D( int w, int h, Value g = Value() )
        : m_width(w), m_height(h), m_data(Container(w * h, g)) { }
    
    // Remplit l'image avec la valeur \a g. 
    void fill( Value g )
    {
        this -> m_data = Container(this -> m_width * this -> m_height, g);
    }
    
    /// @return la largeur de l'image.
    int w() const
    {
        return this -> m_width;
    }
    /// @return la hauteur de l'image.
    int h() const
    {
        return this -> m_height;
    }
    
    /// Accesseur read-only à la valeur d'un pixel.
    /// @return la valeur du pixel(i,j)
    Value at( int i, int j ) const
    {
        return this -> m_data.at(index(i, j));
    }
    
    /// Accesseur read-write à la valeur d'un pixel.
    /// @return une référence à la valeur du pixel(i,j)
    Value& at( int i, int j )
    {
        return this -> m_data.at(index(i, j));
    }

    struct Iterator : public Container::iterator 
    {
        Iterator( Self & image, int x, int y ) 
            : Container::iterator( image.m_data.begin() + image.index( x, y ) ) { }
    };

    /// @return un itérateur pointant sur le début de l'image
    Iterator begin() 
    { 
        return start( 0, 0 );
    }

    /// @return un itérateur pointant après la fin de l'image
    Iterator end()   
    { 
        return start( 0, h() ); 
    }

    /// @return un itérateur pointant sur le pixel (x,y)
    Iterator start( int x, int y ) 
    { 
        return Iterator( *this, x, y ); 
    }

    struct ConstIterator : public Container::const_iterator 
    {
        ConstIterator( const Self & image, int x, int y ) 
            : Container::const_iterator( image.m_data.begin() + image.index( x, y ) ) { }
    };

    /// @return un itérateur pointant sur le début de l'image
    ConstIterator begin() const
    { 
        return start( 0, 0 );
    }

    /// @return un itérateur pointant après la fin de l'image
    ConstIterator end() const
    { 
        return start( 0, h() ); 
    }

    /// @return un itérateur pointant sur le pixel (x,y)
    ConstIterator start( int x, int y ) const
    { 
        return ConstIterator( *this, x, y ); 
    }

    template <typename TAccessor> 
    struct GenericIterator : public Container::iterator 
    {
        typedef TAccessor Accessor;
        typedef typename Accessor::Argument  ImageValue; // Color ou unsigned char
        typedef typename Accessor::Value     Value;      // unsigned char (pour ColorGreenAccessor)
        typedef typename Accessor::Reference Reference;  // ColorGreenReference (pour ColorGreenAccessor)

        GenericIterator( Self & image, int x, int y ) 
            : Container::iterator( image.m_data.begin() + image.index( x, y ) ) { }

        // Accès en écriture (lvalue)
        Reference operator*()
        { 
            return Accessor::access( Container::iterator::operator*() ); 
        }
    };

    template <typename Accessor>
    GenericIterator< Accessor > begin()
    { 
        return GenericIterator< Accessor >( *this, 0, 0 ); 
    }

    template <typename Accessor>
    GenericIterator< Accessor > end()
    { 
        return GenericIterator< Accessor >( *this, 0, h() ); 
    }

    template <typename Accessor>
    GenericIterator< Accessor > start( int x = 0, int y = 0 )
    { 
        return GenericIterator< Accessor >( *this, x, y ); 
    }

    template <typename TAccessor> 
    struct GenericConstIterator : public Container::const_iterator 
    {
        typedef TAccessor Accessor;
        typedef typename Accessor::Argument  ImageValue; // Color ou unsigned char
        typedef typename Accessor::Value     Value;      // unsigned char (pour ColorGreenAccessor)
        typedef typename Accessor::Reference Reference;  // ColorGreenReference (pour ColorGreenAccessor)

        GenericConstIterator( const Image2D<ImageValue>& image, int x, int y )
            : Container::const_iterator( image.m_data.begin() + image.index( x, y )) { }

        // Accès en lecture (rvalue)
        Value operator*() const
        { 
            return Accessor::access( Container::const_iterator::operator*() ); 
        }
    };

    template <typename Accessor>
    GenericConstIterator< Accessor > begin() const
    { 
        return GenericConstIterator< Accessor >( *this, 0, 0 ); 
    }

    template <typename Accessor>
    GenericConstIterator< Accessor > end() const
    { 
        return GenericConstIterator< Accessor >( *this, 0, h() ); 
    }

    template <typename Accessor>
    GenericConstIterator< Accessor > start( int x = 0, int y = 0 ) const
    { 
        return GenericConstIterator< Accessor >( *this, x, y ); 
    }

    //Méthode de base appliquée si Image2D n'est pas de type <Color> ou <unsigned char>
    void sepiaFilter(Image2D<Color> & img)
    {
        std::cerr << "[Image2D<Value>::sepiaFilter] NOT IMPLEMENTED." << std::endl;
    }
    
    private:
    Container m_data; // mes données; évitera de faire les allocations dynamiques
    int m_width; // ma largeur
    int m_height; // ma hauteur
    
    /// @return l'index du pixel (x,y) dans le tableau \red m_data.
    int index( int i, int j ) const
    {
        return i + (j * this -> m_width);
    }
};

//L'argument n'est pas utile dans le cas d'une image de type <Color> en entrée
template <>
void Image2D<Color>::sepiaFilter(Image2D<Color> & img)
{
    for(Iterator it = this -> begin(), itE = this -> end(); it != itE; ++it)
    {
        Color oldColor = *it;

        Color newColor = oldColor;

        newColor.red = std::min((oldColor.red * .393) + (oldColor.green * .769) + (oldColor.blue * .189), 255.0);
        newColor.green = std::min((oldColor.red * .349) + (oldColor.green * .686) + (oldColor.blue * .168), 255.0);
        newColor.blue = std::min((oldColor.red * .272) + (oldColor.green * .534) + (oldColor.blue * .131), 255.0);

        *it = newColor;
    }
};

template <>
void Image2D<unsigned char>::sepiaFilter(Image2D<Color> & img)
{
    Image2D<Color>::Iterator cImgIt = img.begin();

    for(Iterator it = this -> begin(), itE = this -> end(); it != itE; ++it)
    {
        unsigned char red, green, blue;

        red = std::min((*it * .393) + (*it * .769) + (*it * .189), 255.0);
        green = std::min((*it * .349) + (*it * .686) + (*it * .168), 255.0);
        blue = std::min((*it * .272) + (*it * .534) + (*it * .131), 255.0);

        *cImgIt = Color(red, green, blue);

        ++cImgIt;
    }
};

#endif // _IMAGE2D_HPP_