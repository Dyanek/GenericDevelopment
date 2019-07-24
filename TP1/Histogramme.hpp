#ifndef _HISTOGRAMME_HPP_
#define _HISTOGRAMME_HPP_
#include "GrayLevelImage2D.cpp"

struct Histogramme
{
    int histogramme_image[256] = { 0 };
    int histogramme_cumule[256] = { 0 };

    GrayLevelImage2D image;

    void init(GrayLevelImage2D & img);

    int egalisation(int j) const;
};

#endif // #ifndef _HISTOGRAMME_HPP_