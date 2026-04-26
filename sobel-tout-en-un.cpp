#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

/** Structure de donnee pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;

double maximum; // default maximum value

/** Infrastructure minimale de test **/
#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl


/** Une image 4x4 en teintes de gris pour faire des tests **/
ImageGris imgGrisTest = {
    {0, 255, 54.213, 236.589},
    {18.411, 182.376, 200.787, 120},
    {139.583, 172.841, 94.0878, 88.4974},
    {158.278, 172.841, 89.0236, 80.0384}
};



/** Construire une image en teintes de gris depuis un fichier PGM
 * @param source le nom d'un fichier PGM
 * @return une image en teintes de gris
 **/
ImageGris lirePGM(string source) {
    ifstream input(source);
    if(!input)
        throw invalid_argument("Open error!");
    string type, line, comment;
    double x, width, height;
    
    /*
        first version (normal one)
        input >> type;
        if(type != "P2")
            throw invalid_argument("Wrong type!");
        input >> width >> height;
    */

    // second version (including comments beginning with '#')
    getline(input, type);
    if(type[0] != 'P' || type[1] != '2')
        throw invalid_argument("Wrong type!");
    do {
        getline(input, line);
    } while (line.size() == 0 || line[0] == '#');
    // getline(input, comment);
    stringstream ss;
    ss = stringstream(line);
    ss >> width >> height;
    input >> maximum;
    // end of second version
    ImageGris ans(0); // initialize the outer vector
    // cerr << "Image de taille " << width << " x " << height << endl;
    for(int i = 0; i < height; i++)
    {
        vector<double> newline (0);
        for(int j = 0; j < width; j++)
        {
            input >> x;
            // ans[i][j] = x;
            newline.push_back(x);
        }
        ans.push_back(newline);
    }
    input.close();
    return ans;
}



/** Ecrit une image en teintes de gris dans un fichier PGM
 * @param img une image en teintes de gris
 * @param cible le nom d'un fichier PGM
 **/
void ecrirePGM(ImageGris img, string cible) {
    ofstream output(cible);
    int height = img.size(), width = img[0].size();
    output << "P2" << endl;
    output << width << ' ' << height << endl;
    output << maximum << endl; // maximum value
    for(auto line : img)   // better choice
    {
        for(auto x : line)
        {
            if(x < 0) x = 0;
            if(x > 255) x = 255;
            output << round(x) << ' ';    
        }
        
        output << endl;
    }
    output.close();
    return;
}

/** Renormalize une image en teinte de gris, les ramenant dans l'intervalle [0,255]
 * @param img un image en teintes de gris
 * @return une image en teintes de gris
 **/
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





/** Teste si deux images en teintes de gris sont égales modulo imprécision numérique
 * En cas de différence un message est affiché
 * @param a une image en teintes de gris
 * @param b une image en teintes de gris
 * @param precision un flottant positif: la précision souhaitée; typiquement 0.001
 * @return vrai si les images sont égales et faux sinon
 **/
bool ImageGrisEgal(ImageGris a, ImageGris b, float precision) {
    if (a.size() != b.size())  {
        cout << "Nombre de lignes différent" << endl;
        return false;
    }
    for (int i=0; i<a[0].size(); i++)
        if (a[0].size() != b[i].size()) {
            cout << "Nombre de colonnes différent" << endl;
            return false;
        }
    for (int i=0; i<a.size(); i++)
        for (int j=0; j<a[0].size(); j++)
            if (abs(a[i][j] - b[i][j]) > precision) {
                cout << "Valeur differentes en position " << i << "," << j
             << ": " << a[i][j] << " au lieu de " << b[i][j] << endl;
                return false;
            }
    return true;
}

/// BEGIN intensiteH

/** filtre de Sobel horizontal
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite horizontale de img
 **/
ImageGris intensiteH(ImageGris img) {
    int height = img.size();
    int width = img[0].size();
    ImageGris ans(height, vector<double>(width, 0.0)); // Création d'une nouvelle image de même taille, initialisée à 0
    for(int i = 1; i < height - 1; i++) // on commence à 1 comme on évite les bords 
    {
        for(int j = 1; j < width - 1; j++)
        {
            double x = img[i-1][j-1] + 2*img[i][j-1] + img[i+1][j-1] - img[i-1][j+1] - 2*img[i][j+1] - img[i+1][j+1];
            ans[i][j] = x;
        }
    }
    return ans;
}


/// BEGIN intensiteV

/** filtre de Sobel vertical
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite verticale de img
 **/
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


/// BEGIN intensiteHV

/** filtre de Sobel
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite de img
 **/
ImageGris intensite(ImageGris img) {
    int height = img.size();
    int width = img[0].size();
    ImageGris ans(height, vector<double>(width, 0.0));
    // ImageGris ih = intensiteH(img);
    // ImageGris iv = intensiteV(img); si on veut utiliser deux fonctions définies précédemment. 
    // double x = sqrt(ih[i][j] * ih[i][j] + iv[i][j] * iv[i][j]);
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


void testSobel() {
    CHECK( ImageGrisEgal(intensiteH(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, -373.47, 227.507, 0},
                  {0, -22.1312, 323.866, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(intensiteV(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, -15.1398, 150.501, 0},
                  {0, -9.0336, 273.023, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(intensite(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, 373.777, 272.782, 0},
                  {0, 23.9039, 423.593, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );

    cout << "Vérifier que les images obtenues dans 'sobel/' sont semblables à celles fournies dans 'sobel/correction/'" << endl;
    ecrirePGM(renormalise(intensite(lirePGM("images/Willis.512.pgm" ))), "sobel/Willis_renormalise.512.pgm");
    ecrirePGM(renormalise(intensite(lirePGM("images/Baboon.512.pgm" ))), "sobel/Baboon_renormalise.512.pgm");
    ecrirePGM(renormalise(intensite(lirePGM("images/Billes.256.pgm" ))), "sobel/Billes_renormalise.256.pgm");
    ecrirePGM(renormalise(intensite(lirePGM("images/Embryos.512.pgm"))), "sobel/Embryos_renormalise.512.pgm");
    ecrirePGM(renormalise(intensite(lirePGM("images/House.256.pgm"  ))), "sobel/House_renormalise.256.pgm");
    ecrirePGM(intensite(lirePGM("images/Willis.512.pgm" )), "sobel/Willis.512.pgm");
    ecrirePGM(intensite(lirePGM("images/Baboon.512.pgm" )), "sobel/Baboon.512.pgm");
    ecrirePGM(intensite(lirePGM("images/Billes.256.pgm" )), "sobel/Billes.256.pgm");
    ecrirePGM(intensite(lirePGM("images/Embryos.512.pgm")), "sobel/Embryos.512.pgm");
    ecrirePGM(intensite(lirePGM("images/House.256.pgm"  )), "sobel/House.256.pgm");
}



int main(){

    testSobel();
    return 0 ;
}

