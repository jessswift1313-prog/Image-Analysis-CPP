#include <stdexcept>
/** @file
 * Lecture et écriture d'images au format PPM
 **/


#include <iostream>
#include <fstream>
#include "image.hpp"
#include "ppm.hpp"

int maximum2;

Image lirePPM(string source) {
    ifstream input(source);
    if(!input)
        throw invalid_argument("Open error: cannot open file " + source);
    string type, line;
    double width, height;
    // second version (including comments beginning with '#')
    getline(input, type);
    if(type[0] != 'P' || type[1] != '3')
        throw invalid_argument("Wrong type!");
    do {
        getline(input, line);
    } while (line.size() == 0 || line[0] == '#');
    stringstream ss;
    ss = stringstream(line);
    ss >> width >> height;
    input >> maximum2;
    // end of second version
    Image ans(0); // initialize the outer vector
    for(int i = 0; i < height; i++)
    {
        vector<Couleur> newline (0);
        for(int j = 0; j < width; j++)
        {
            double r, g, b;
            input >> r >> g >> b;
            Couleur c = {r, g, b};
            newline.push_back(c);
        }
        ans.push_back(newline);
    }
    input.close();
    return ans;
}

void ecrirePPM(Image img, string cible) {
    ofstream output(cible);
    int height = img.size(), width = img[0].size();
    output << "P3" << endl;
    output << width << ' ' << height << endl;
    output << maximum2 << endl; // maximum value
    for(auto line : img)   // better choice
    {
        for(auto c : line)
            output << round(c.r) << ' ' << round(c.g) << ' ' << round(c.b) << ' ';
        output << endl; //ou utiliser (int())
    }
    output.close();
    return;
}

