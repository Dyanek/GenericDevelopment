#include "Histogramme.hpp"

using namespace std;

void Histogramme::init(GrayLevelImage2D & img)
{
    for ( GrayLevelImage2D::Iterator it = img.begin(), itE = img.end(); it != itE; ++it )
        this -> histogramme_image[*it]++;
    
    this -> histogramme_cumule[0] = histogramme_image[0];
    for(int i = 1; i <= 255; i++)
        this -> histogramme_cumule[i] = histogramme_cumule[i-1] + histogramme_image[i];
}

int Histogramme::egalisation(int j) const
{
    return (histogramme_cumule[j]/255 > 255) ? 255 : histogramme_cumule[j]/255;
}