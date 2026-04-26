#include <stdexcept>
/** @file
 * Filtre Super Pixel
 **/
#include <cmath>
#include "superpixel.hpp"

double distancePoints(Point p, Point c) {
    int dimension = p.size();
    if(dimension != c.size())
        throw invalid_argument("Different dimension!");
    double ans = 0;
    for(int i = 0; i < dimension; i++)
        ans += (p[i] - c[i]) * (p[i] - c[i]);
    return sqrt(ans);
}

double distanceAEnsemble(Point p, EnsemblePoints C) { //renvoie la distance minimale 
    if(C.size() == 0)
        throw invalid_argument("Empty ensemble!");
    double ans = 2e9;
    for(auto point : C)
        if(ans > distancePoints(p, point))
            ans = distancePoints(p, point);
    return ans; //mais c'est assez lent...
}

int plusProcheVoisin(Point p, EnsemblePoints C) { // renvoie le point de C dont la distance est la plus proche 
    if(C.size() == 0)
        throw invalid_argument("Empty ensemble!");
    double ans = 2e9;
    int id;
    for(int i = 0; i < C.size(); i++)
        if(ans > distancePoints(p, C[i]))
            ans = distancePoints(p, C[i]), id = i;
    return id;
}

EnsemblePoints sousEnsemble(EnsemblePoints P,EnsemblePoints C,int k) {
    if(k < 0 || k >= C.size())
        throw invalid_argument("Wrong index!");
    EnsemblePoints ans(0);
    for(auto p : P)
        if(k == plusProcheVoisin(p, C))
            ans.push_back(p);
    return ans;
}

Point barycentre(EnsemblePoints Q) {
    if(Q.size() == 0)
        throw invalid_argument("Empty ensemble!");
    int dimension = Q[0].size();
    Point ans(dimension, 0.0);
    for(auto p : Q)
        for(int i = 0; i < dimension; i++)
            ans[i] += p[i]; //For each dimension calculate the somme of each point separately
    for(int i = 0; i < dimension; i++)
        ans[i] = ans[i] / Q.size(); //For each dimension calculate the average
    return ans;
}

EnsemblePoints KMoyenne(EnsemblePoints P,EnsemblePoints C, int nbAmeliorations) {
    EnsemblePoints ans;
    ans = C;
    while(nbAmeliorations > 0)
    {
        for(int k = 0; k < C.size(); k++)
        {
            EnsemblePoints Q = sousEnsemble(P, C, k); //L'ensemble des points qui est associé au point pilote avec la relation : "le plus proche"
            ans[k] = barycentre(Q); //Chaque point pilote est déplacé au barycentre de (l'ensemble des points qui lui sont associés) -> (i.e. Q)
        }
        C = ans;
        nbAmeliorations--;
    }
    return C;
}

EnsemblePoints FAST_KMoyenne(EnsemblePoints P,EnsemblePoints C, int nbAmeliorations) {
    vector<int> label;
    label.resize(P.size());
    for(int n=0; n<nbAmeliorations; n++) {
        vector<int> clusterSize;
        clusterSize.resize(C.size(),0);
        for (int p=((int)P.size())-1; p>=0; p--) {
            double di = 0;
            int nn=0;
            for(int d=((int)P[0].size())-1; d>=0; d--)
                di+=(P[p][d]-C[0][d])*(P[p][d]-C[0][d]);
            for(int c=((int)C.size())-1; c>=1; c--) {
                double dt=0;
                for(int d=((int)P[0].size())-1; d>=0; d--)
                    dt+=(P[p][d]-C[c][d])*(P[p][d]-C[c][d]);
                if(dt<di) {
                    di=dt;
                    nn=c;
                }
            }
            label[p]=nn;
            clusterSize[nn]++;
        }
        for (int p=((int)P.size())-1; p>=0; p--)
            for(int d=((int)P[0].size())-1; d>=0; d--)
                C[label[p]][d]+=P[p][d];
        for(int c=((int)C.size())-1; c>=0; c--)
            if(clusterSize[c]!=0)
                for(int d=((int)P[0].size())-1; d>=0; d--)
                    C[c][d] = C[c][d]/(clusterSize[c]+1);
    }
    return C;
}

EnsemblePoints pivotSuperPixel(Image img, double lambda, int mu) {
    EnsemblePoints ans(0);
    int height = img.size(), width = img[0].size();
    for(int i = 0; i < height; i+=mu)
    {
        for(int j = 0; j < width; j+=mu)
        {
            Point x(5);
            x[0] = i, x[1] = j;
            x[2] = lambda * img[i][j].r;
            x[3] = lambda * img[i][j].g;
            x[4] = lambda * img[i][j].b;
            ans.push_back(x); 
        }
    }
    return ans;
}

EnsemblePoints superPixels(Image img,double lambda, int mu, int nbAmeliorations) {
    EnsemblePoints ans = pivotSuperPixel(img, lambda, mu); // the initiative pivot image
    EnsemblePoints x = pivotSuperPixel(img, lambda, 1); // the original image
    return ans = FAST_KMoyenne(x, ans, nbAmeliorations);
}

Image superPixel(Image img, double lambda, int mu, int nbAmeliorations) {
    EnsemblePoints C = superPixels(img, lambda, mu, nbAmeliorations);
    int height = img.size(), width = img[0].size();
    Image ans = img;
    vector<vector<int>> id(height, vector<int>(width, 0));
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            Point p(5);
            p[0] = i, p[1] = j;
            p[2] = lambda * img[i][j].r;
            p[3] = lambda * img[i][j].g;
            p[4] = lambda * img[i][j].b;
            int k = plusProcheVoisin(p, C);
            id[i][j] = k;
            ans[i][j].r = C[k][2] / lambda;
            ans[i][j].g = C[k][3] / lambda;
            ans[i][j].b = C[k][4] / lambda;
        }
    }
    // ajouter la frontiere des superpixels
    for(int i = 0; i < height;i++)
        for(int j = 0; j < width; j++)
        {
            int k = id[i][j];
            bool isBorder = false;
            for(int di = -1; di <= 1; di++)
                for(int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di, nj = j + dj;
                    if(ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {

                        if(id[ni][nj] != k)
                        {
                            isBorder = true;
                            break;
                        }
                    }
                    if(isBorder)
                        break;
                }
            if(isBorder)
                ans[i][j].r = 0, ans[i][j].g = 0, ans[i][j].b = 255; //blue frontier
        }
    return ans;
}


