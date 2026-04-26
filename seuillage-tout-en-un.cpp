#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
using namespace std;

/** Structure de donnee pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;

double maximum;

/** Infrastructure minimale de test **/
#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl


/** Une image 4x4 en teintes de gris pour faire des tests **/
ImageGris imgGrisTest = {
    {0, 255, 54.213, 236.589},
    {18.411, 182.376, 200.787, 120},
    {139.583, 172.841, 94.0878, 88.4974},
    {158.278, 172.841, 89.0236, 80.0384}
};

/** Une image 4x4 en teintes de gris pour les tests de renormalisation **/
ImageGris imgGrisRenorm = {
    {0, 50, 0, 50},
    {0, 50, 0, 50},
    {0, 50, 0, 50},
    {0, 50, 0, 50},
};

/** filtre de lissage
 * @param img une image en teintes de gris
 * @return une image en teintes de gris lissée en remplacant la valeur de chaque pixel par la moyenne des 8 voisins et lui-meme.
 **/
ImageGris Lissage(ImageGris img)
{
    int height = img.size();
    int width = img[0].size();
    ImageGris ans(height, vector<double>(width, 0.0));
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
        {
            double sum = 0.0;
            int count = 0;
            for(int di = -1; di <= 1; di++)
                for(int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;
                    if(ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sum += img[ni][nj];
                        count++;
                    }
                }
            ans[i][j] = sum / count;
        }
    return ans;
}

/** filtre de Sobel
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite de img
 **/
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


/** Construire une image en teintes de gris depuis un fichier PGM
 * @param source le nom d'un fichier PGM
 * @return une image en teintes de gris
 **/
ImageGris lirePGM(string source) {
    ifstream input(source);
    if(!input)
        throw invalid_argument("Open error: cannot open file " + source);
    string type, line;
    double x, width, height;
    // second version (including comments beginning with '#')
    getline(input, type);
    if(type[0] != 'P' || type[1] != '2')
        throw invalid_argument("Wrong type!");
    do {
        getline(input, line);
    } while (line.size() == 0 || line[0] == '#');
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
    // return Lissage(ans);
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
            output << round(x) << ' ';
        output << endl;
    }
    output.close();
    return;
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


/// BEGIN renormalise

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
            if(x < Min) Min = x; // Pour identifier les pixels maximum et minimum de l'image
        }
    ImageGris ans(height, vector<double> (width, 0.0)); // Créer un nouveau image avec la même taille
    // cerr << Max << " " << Min <<endl; (pas obligatoire)
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
            ans[i][j] = 255.0 * (img[i][j] - Min) / (Max - Min); // transformation, on n'utilise pas for each car on doit utiliser à la fois img[i][j] et ans[i][j]
    return ans;
}

void renormaliseTest() {
    CHECK( ImageGrisEgal(renormalise( imgGrisRenorm),
              ImageGris( {
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
              }),
              0.001) );

}
/// BEGIN seuillage

/** Filtre de seuillage
 * @param img
 * @param seuil un entier dans l'intervalle [0,255]
 * @return image en noir et blanc obtenue en remplacant la teinte de
 *  chaque pixel par
 *  - du blanc si teinte <= seuil
 *  - du noir  si teinte > seuil
 **/
ImageGris seuillage(ImageGris img, int seuil) {
    int height = img.size(), width = img[0].size();
    ImageGris ans(height, vector<double> (width, 0.0));
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
        {
            if(img[i][j] > seuil)
                ans[i][j] = 0.0; // Pixel noir car teinte > seuil
            else
                ans[i][j] = 255.0;   //  Pixel blanc car teinte <= seuil
        }
    return ans;
}

/// BEGIN doubleSeuillage

/** Filtre de double seuillage
 * @param imgIntensite image d'intensite
 * @param imgContour image codant un ensemble de pixels selectionnes
 * @param seuil un entier de l'intervalle [0,255]
 * @return une copie d'imgIntensite modifiee de sorte que:
 *  -si teinte > seuil et voisin d'un pixel de imgContour, alors pixel noir
 *  -sinon pixel blanc
 **/
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
                        if(Check) break; //optimization, pas besoin de checker les autres voisins si on a déjà trouver un. 
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

/// BEGIN doubleSeuillageIteratif

/** Filtre de double seuillage iteratif
 * @param imgIntensite image d'intensité
 * @param seuilFort un entier de l'intervalle [0,255]
 * @param seuilFaible un entier de l'intervalle [0,255]
 * @param nbAmeliorations un entier non negatif: le nombre d'itérations
 * @return le double seuillage de img
 **/
ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, int seuilFaible, int nbAmeliorations) {
    ImageGris imgContour = seuillage(imgIntensite, seuilFort);
    for(int times = 0; times < nbAmeliorations; times++)
        imgContour = doubleSeuillage(imgIntensite, imgContour, seuilFaible); // refine contour
    return imgContour;
}

/** Filtre de double seuillage iteratif - amélioration avec file d'attente
 * @param imgIntensite image d'intensité
 * @param seuilFort un entier de l'intervalle [0,255]
 * @param seuilFaible un entier de l'intervalle [0,255]
 * @return le double seuillage de img
 **/
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


void seuillageTest() {
    CHECK( ImageGrisEgal(seuillage( imgGrisTest, 80),
              ImageGris( {
                  {255, 0, 255, 0},
                  {255, 0, 0, 0},
                  {0, 0, 0, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(seuillage( intensite(imgGrisTest), 80),
              ImageGris( {
                  {255, 255, 255, 255},
                  {255, 0, 0, 255},
                  {255, 255, 0, 255},
                  {255, 255, 255, 255}
              }),
              0.001) );


    cout << "Vérifier que les images obtenues dans 'seuillage/' sont semblables à celles fournies dans 'seuillage/correction/'" << endl;
    ecrirePGM(seuillage(intensite(lirePGM("images/Billes.256.pgm")), 80), "seuillage/Billes.256.pgm");
    ecrirePGM(seuillage(intensite(lirePGM("images/Willis.512.pgm"  )), 120), "seuillage/Willis.512.pgm");
    cout << "\tProposer des seuils pour Embryos.512.pgm et House.256.pgm" << endl;
    double seuil = 100;
    // cin >> seuil;
    // cerr << seuil << endl;
    ecrirePGM(seuillage(intensite(lirePGM("images/Embryos.512.pgm")), seuil), "seuillage/Embryos.512.pgm");
    ecrirePGM(seuillage(intensite(lirePGM("images/House.256.pgm"  )), seuil), "seuillage/House.256.pgm");

}

void doubleSeuillageTest(){
    CHECK( ImageGrisEgal(doubleSeuillage(intensite(imgGrisTest), 400, 80, 4 ),
        ImageGris( {
            {255, 255, 255, 255},
            {255, 0, 0, 255},
            {255, 255, 0, 255},
            {255, 255, 255, 255}
        }),
        0.001) );

    cout << "Vérifier que les images obtenues dans 'seuillage_double/' sont semblables à celles fournies dans 'seuillage_double/correction/'" << endl;
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Willis.512.pgm")), seuillage(intensite(lirePGM("images/Willis.512.pgm")), 100), 80), "seuillage_double/Willis.512.pgm");
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Billes.256.pgm")), seuillage(intensite(lirePGM("images/Billes.256.pgm")), 100), 80), "seuillage_double/Billes.256.pgm");
    cout << "\tProposer des seuils pour Embryos.512.pgm et House.256.pgm" << endl;
    double seuil = 100;
    // cin >> seuil;
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Embryos.512.pgm")), seuillage(intensite(lirePGM("images/Embryos.512.pgm")), seuil), seuil - 20), "seuillage_double/Embryos.512.pgm");
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/House.256.pgm")), seuillage(intensite(lirePGM("images/House.256.pgm")), seuil), seuil - 20), "seuillage_double/House.256.pgm");
}

void doubleSeuillageIteratifTest() {
    cout << "Vérifier que les images obtenues dans 'seuillage_double/' sont semblables à celles fournies dans 'seuillage_double/correction/'" << endl;
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Willis.512.pgm")), 500, 80, 100), "seuillage_double/iteratif_Willis.512.pgm");

    cout << "\tProposer des seuils pour Billes.256.pgm, Embryos.512.pgm et House.256.pgm" << endl;
    
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Billes.256.pgm")), 500, 80, 100), "seuillage_double/iteratif_Billes.256.pgm");
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Embryos.512.pgm")), 500, 80, 100), "seuillage_double/iteratif_Embryos.512.pgm");
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/House.256.pgm")), 500, 80, 100), "seuillage_double/iteratif_House.256.pgm");

    ecrirePGM(doubleSeuillageIteratif_Amelioration(intensite(lirePGM("images/Willis.512.pgm")), 500, 80), "seuillage_double/iteratif_Willis_Amelioration.512.pgm");
    ecrirePGM(doubleSeuillageIteratif_Amelioration(intensite(lirePGM("images/Billes.256.pgm")), 500, 80), "seuillage_double/iteratif_Billes_Amelioration.256.pgm");
    ecrirePGM(doubleSeuillageIteratif_Amelioration(intensite(lirePGM("images/Embryos.512.pgm")), 500, 80), "seuillage_double/iteratif_Embryos_Amelioration.512.pgm");
    ecrirePGM(doubleSeuillageIteratif_Amelioration(intensite(lirePGM("images/House.256.pgm")), 500, 80), "seuillage_double/iteratif_House_Amelioration.256.pgm");
}

void lissageTest()
{
    ecrirePGM(seuillage(intensite(Lissage(lirePGM("images/Billes.256.pgm"))), 80), "seuillage/Billes_lissage.256.pgm");
    ecrirePGM(seuillage(intensite(Lissage(lirePGM("images/Willis.512.pgm"  ))), 120), "seuillage/Willis_lissage.512.pgm");
    double seuil = 100;
    // cin >> seuil;
    // cerr << seuil << endl;
    ecrirePGM(seuillage(intensite(Lissage(lirePGM("images/Embryos.512.pgm"))), seuil), "seuillage/Embryos_lissage.512.pgm");
    ecrirePGM(seuillage(intensite(Lissage(lirePGM("images/House.256.pgm"  ))), seuil), "seuillage/House_lissage.256.pgm");
}

int main(){
    // Ajouter les appels aux fonctions de test nécessaire

    renormaliseTest();
    
    seuillageTest();

    doubleSeuillageTest();

    doubleSeuillageIteratifTest();

    lissageTest();

    return 0;
}