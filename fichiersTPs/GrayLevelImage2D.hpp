#ifndef _GRAYLEVELIMAGE2D_HPP_
#define _GRAYLEVELIMAGE2D_HPP_

#include <iostream>
#include <vector>
#include <exception>


class GrayLevelImage2D {

public:
  typedef unsigned char          GrayLevel;// le type pour les niveaux de gris.
  typedef std::vector<GrayLevel> Container;// le type pour stocker les niveaux de gris de l'image.

  /**
     Représente un itérateur sur toutes les valeurs d'une image.

     Model of DefaultConstructible, CopyConstructible, Assignable,
     RandomAccessIterator. */
  struct Iterator : public Container::iterator {
    Iterator( GrayLevelImage2D& Image, int x, int y );
  };


public:
  GrayLevelImage2D();
  GrayLevelImage2D( int w, int h, GrayLevel g = 0 );
  void fill( GrayLevel g );

  //! [gli2d-sec3]
  /// @return la largeur de l'image.
  int w() const;
  /// @return la hauteur de l'image.
  int h() const;

  /**
     Accesseur read-only à la valeur d'un pixel.
     @return la valeur du pixel(i,j)
  */
  GrayLevel at( int i, int j ) const;

  /**
     Accesseur read-write à la valeur d'un pixel.
     @return une référence à la valeur du pixel(i,j)
  */
  GrayLevel& at( int i, int j );
  //! [gli2d-sec3]



  Iterator begin();
  Iterator end();
  Iterator start( int x, int y );
  
  std::pair<int,int> position( Iterator it ) const;
  
  bool importPGM( std::istream & input );
  bool exportPGM( std::ostream & output, bool ascii = true );

  

private:
  // Calcule l'indice dans m_data du pixel (x,y).
  int index( int x, int y ) const;
  // Le tableau contenant les valeurs des pixels.
  Container m_data;
  // la largeur
  int       m_width;
  // la hauteur
  int       m_height;
};


#endif // #ifndef _GRAYLEVELIMAGE2D_HPP_
