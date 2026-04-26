#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
#include "sobel.hpp"

ImageGris intensiteH(ImageGris img) {
    int height = img.size();
    int width = img[0].size();
    ImageGris ans(height, vector<double>(width, 0.0));
    for(int i = 1; i < height - 1; i++)
    {
        for(int j = 1; j < width - 1; j++)
        {
            double x = img[i-1][j-1] + 2*img[i][j-1] + img[i+1][j-1] - img[i-1][j+1] - 2*img[i][j+1] - img[i+1][j+1];
            ans[i][j] = x;
        }
    }
    return ans;
}

ImageGris intensiteV(ImageGris img) {
    int height = img.size();
    int width = img[0].size();
    ImageGris ans(height, vector<double>(width, 0.0));
    for(int i = 1; i < height - 1; i++)
    {
        for(int j = 1; j < width - 1; j++)
        {
            double x = img[i-1][j-1] + 2*img[i-1][j] + img[i-1][j+1] - img[i+1][j-1] - 2*img[i+1][j] - img[i+1][j+1];
            ans[i][j] = x;
        }
    }
    return ans;
}

ImageGris intensite(ImageGris img) {
    int height = img.size();
    int width = img[0].size();
    ImageGris ans(height, vector<double>(width, 0.0));
    // ImageGris ih = intensiteH(img);
    // ImageGris iv = intensiteV(img);
    for(int i = 1; i < height - 1; i++)
    {
        for(int j = 1; j < width - 1; j++)
        {
            double a = img[i-1][j-1] + 2*img[i][j-1] + img[i+1][j-1] - img[i-1][j+1] - 2*img[i][j+1] - img[i+1][j+1], b = img[i-1][j-1] + 2*img[i-1][j] + img[i-1][j+1] - img[i+1][j-1] - 2*img[i+1][j] - img[i+1][j+1];
            double x = sqrt(a * a + b * b);
            ans[i][j] = x;
        }
    }
    return ans;
}

