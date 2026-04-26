#include <stdexcept>
/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/

#include <iostream>
#include <stdexcept>
using namespace std;
#include "pgm.hpp"
#include "image-test.hpp"

void lireEcrirePGMTest() {
    ecrirePGM(lirePGM("./images/brain.pgm"),  "./pgm/brain.pgm");
    ecrirePGM(lirePGM("./images/illusion.pgm"),  "./pgm/illusion.pgm");
}

void inversePGMTest() {
    ImageGris imageOriginale;
    imageOriginale = lirePGM("./images/brain.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "./pgm/brain-inverse.pgm");
    imageOriginale = lirePGM("./images/illusion.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "./pgm/illusion-inverse.pgm");
}

int main(){
    cout << "Tests des fonctions lirePGM et ecrirePGM" << endl;
    lireEcrirePGMTest();
    cout << "Tests de la fonction inverseePGM" << endl;
    inversePGMTest();
}

