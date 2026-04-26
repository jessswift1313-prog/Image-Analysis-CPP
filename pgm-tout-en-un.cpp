#include <stdexcept>
/** @file
 * Lecture et ecriture d'images en niveau de gris au format PGM
 **/
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <iomanip>
using namespace std;

/// BEGIN ImageGris

/** Structure de donnees pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;
/// END ImageGris

double maximum = 255.0; // default maximum value

/// BEGIN lirePGM

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
        if(type != "P1")
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

/// BEGIN ecrirePGM

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
            output << ((int)x) << ' ';
        output << endl;
    }
    output.close();
    return;
}

/** Construit une image cliché d'une image en niveau de gris
 * @param img une image en niveau de gris
 * @return l'image cliché qui inverse les niveaux de gris
 **/
ImageGris inversePGM(ImageGris img) {
    ImageGris ans(0); // initialize the outer vector
    for(auto line : img)
    {
        vector<double> newline(0);
        for(auto x : line)
        {
            newline.push_back(maximum - x); //inverse 'number' (0-255)
        }
        ans.push_back(newline);
    }
    return ans;
}

void lirePGMTest(){
    cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
    ecrirePGM(lirePGM("./images/brain.pgm"),  "./pgm/brain.pgm");
    ecrirePGM(lirePGM("./images/illusion.pgm"),  "./pgm/illusion.pgm");
}

void inversePGMTest() {
    ImageGris imageOriginale;
    cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
    imageOriginale = lirePGM("./images/brain.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "./pgm/brain-inverse.pgm");
    imageOriginale = lirePGM("./images/illusion.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "./pgm/illusion-inverse.pgm");
}

int main() {
    lirePGMTest();
    inversePGMTest();
    return 0;
}

