#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include "image.hpp"
#include "sobel.hpp"

ImageGris renormalise(ImageGris img) {
    int height = img.size(), width = img[0].size();
    double Max = img[0][0], Min = img[0][0];
    for(auto line : img)
        for(auto x : line)
        {
            if(x > Max) Max = x;
            if(x < Min) Min = x;
        }
    ImageGris ans(height, vector<double> (width, 0.0));
    // cerr << Max << " " << Min <<endl;
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
            ans[i][j] = 255.0 * (img[i][j] - Min) / (Max - Min); // transformation
    return ans;
}

ImageGris seuillage(ImageGris img, int seuil) {
    int height = img.size(), width = img[0].size();
    ImageGris ans(height, vector<double> (width, 0.0));
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
        {
            if(img[i][j] > seuil)
                ans[i][j] = 0.0; // Black pixel cause teinte > seuil
            else
                ans[i][j] = 255.0;   //  White pixel cause teinte <= seuil
        }
    return ans;
}

ImageGris doubleSeuillage(ImageGris imgIntensite, ImageGris imgContour, int seuil) {
    int height = imgIntensite.size(), width = imgIntensite[0].size();
    ImageGris ans(height, vector<double> (width, 0.0));
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
        {
            if (imgContour[i][j] == 0.0) // black pixel in contour image
            {
                ans[i][j] = 0.0;
                continue;
            }
            if(imgIntensite[i][j] > seuil)
            {
                // check neighbors
                bool Check = false;
                for(int di = -1; di <= 1; di++)
                {
                    if(Check) break; //optimization
                    for(int dj = -1; dj <= 1; dj++)
                    {
                        int ni = i + di, nj = j + dj;
                        if(ni >= 0 && ni < height && nj >= 0 && nj < width && !(di == 0 && dj == 0))
                        {
                            if(imgContour[ni][nj] == 0.0) // black pixel in contour image
                                Check = true;
                        }
                        if(Check) break; //optimization
                    }
                

                }
                // if(Check)
                //     ans[i][j] = 0.0; // Black pixel
                // else
                //     ans[i][j] = 255.0; // White pixel
                ans[i][j] = (Check ? 0.0 : 255.0);
            }
            else
                ans[i][j] = 255.0; // White pixel
        }
    return ans;
}

ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, int seuilFaible, int nbAmeliorations) {
    ImageGris imgContour = seuillage(imgIntensite, seuilFort);
    for(int times = 0; times < nbAmeliorations; times++)
        imgContour = doubleSeuillage(imgIntensite, imgContour, seuilFaible); // refine contour
    return imgContour;
}

ImageGris doubleSeuillageIteratif_Amelioration(ImageGris imgIntensite, int seuilFort, int seuilFaible)
{
    queue<pair<int,int>> Q; // queue to store pixels to explore ------------------(*)
    int height = imgIntensite.size(), width = imgIntensite[0].size();
    ImageGris ans(height, vector<double> (width, 0.0));
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
        {
            if(imgIntensite[i][j] > seuilFort)
                ans[i][j] = 0.0; // Black pixel cause teinte > seuil
            else
                ans[i][j] = 255.0;   //  White pixel cause teinte <= seuil
            //  Enqueue all black pixels pour n'explorer que le voisinage des pixels déjà sélectionnés----------(*)
            if(ans[i][j] == 0.0)
                Q.push({i,j});
        }
    while(!Q.empty())
    {
        pair<int,int> p = Q.front();
        int i = p.first, j = p.second;
        Q.pop();
        for(int di = -1; di <= 1; di++)
            for(int dj = -1; dj <= 1; dj++)
            {
                int ni = i + di, nj = j + dj;
                if(ni >= 0 && ni < height && nj >= 0 && nj < width && !(di == 0 && dj == 0))
                {
                    if(imgIntensite[ni][nj] > seuilFaible && ans[ni][nj] == 255.0) // white pixel in contour image
                    {
                        ans[ni][nj] = 0.0; // make it black
                        Q.push({ni, nj}); //continuer ce processus tant que de nouveaux pixels sont sélectionnés----------(*)
                    }
                }
            }
    }
    return ans;
}

