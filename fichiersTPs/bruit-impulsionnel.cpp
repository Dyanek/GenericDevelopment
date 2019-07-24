// bruit-impulsionnel.cpp
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "GrayLevelImage2D.hpp"

using namespace std;

double rand01()
{
  return (double)random() / (double)RAND_MAX;
}

int main( int argc, char** argv )
{
  typedef GrayLevelImage2D::GrayLevel GrayLevel;
  typedef GrayLevelImage2D::Iterator Iterator;
  if ( argc < 3 ) 
    { 
      std::cerr << "Usage: bruit-impulsionnel <input.pgm> <output.pgm> <prob>" << std::endl;
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

  double prob = (argc > 3) ? atof( argv[ 3 ] ) : 0.01; // récupère la probabilité de bruit
  for ( Iterator it = img.begin(), itE = img.end(); it != itE; ++it )
    {
      if ( rand01() < prob )
	{ // sature dans un sens (noir=0) ou l'autre (blanc=255)
	  *it = ( rand01() < 0.5 ) ? 0 : 255;
	}
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
