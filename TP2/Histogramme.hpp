#ifndef _HISTOGRAMME_HPP_
#define _HISTOGRAMME_HPP_

struct Histogramme
{
    int histogramme_image[256] = { 0 };
    int histogramme_cumule[256] = { 0 };

    template <typename InputIterator>
    void init(InputIterator it, InputIterator itE)
    {
        for (; it != itE; ++it )
            histogramme_image[*it]++;

        //Affiche dans le terminal le nombre de d'occurences de chaque valeur possible.
        //for(int i = 0; i <= 255; i++)
        //    std::cout << i<< ": " <<histogramme_image[i] << std::endl;
    
        histogramme_cumule[0] = histogramme_image[0];

        for(int i = 1; i <= 255; ++i)
            histogramme_cumule[i] = histogramme_cumule[i-1] + histogramme_image[i];
    }

    int egalisation(int j) const
    {
        return (histogramme_cumule[j] / 255 > 255) ? 255 : histogramme_cumule[j] / 255;
    }
};

#endif // _HISTOGRAMME_HPP_