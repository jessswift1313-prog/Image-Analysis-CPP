#include <stdexcept>
/** @file
 * Lecture et ecriture d'images en niveau de gris au format PGM
 **/

#include <iostream>
#include <fstream>
#include "image.hpp"
#include "pgm.hpp"

int maximum1;

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
    input >> maximum1;
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

void ecrirePGM(ImageGris img, string cible) {
    ofstream output(cible);
    int height = img.size(), width = img[0].size();
    output << "P2" << endl;
    output << width << ' ' << height << endl;
    output << maximum1 << endl; // maximum value
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

ImageGris inversePGM(ImageGris img) {
    ImageGris ans(0); // initialize the outer vector
    for(auto line : img)
    {
        vector<double> newline(0);
        for(auto x : line)
        {
            newline.push_back(maximum1 - x); //inverse 'number' (0-255)
        }
        ans.push_back(newline);
    }
    return ans;
}

