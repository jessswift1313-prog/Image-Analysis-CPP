#include <stdexcept>
/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/
#include "gris-couleurs.hpp"

ImageGris CouleurAuGris( Image img ) {
    int height = img.size(), width = img[0].size();
    ImageGris ans(height, vector<double> (width, 0.0));
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
            ans[i][j] = 0.2126 * img[i][j].r+0.7152 * img[i][j].g + 0.0722 * img[i][j].b;
    return ans;
}

Image GrisACouleur( ImageGris img ) {
    int height = img.size(), width = img[0].size();
    Image ans(height, vector<Couleur> (width, {0.0, 0.0, 0.0}));
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
            ans[i][j] = {img[i][j], img[i][j], img[i][j]}; // comme r==c,g==c,b==c. 
    return ans;
}

