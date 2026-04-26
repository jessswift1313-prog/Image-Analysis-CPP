#include <stdexcept>
/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/

#include <iostream>
using namespace std;
#include "pgm.hpp"
#include "sobel.hpp"
#include "seuillage.hpp"
#include "image-test.hpp"


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

int main(){
    cout << "Tests de renormalisation..." << endl;
    renormaliseTest();
    cout << "Tests de seuillage..." << endl;
    seuillageTest();
    cout << "Tests de double seuillage..." << endl;
    doubleSeuillageTest();
    cout << "Tests de double seuillage itératif..." << endl;
    doubleSeuillageIteratifTest();
    cout << "Tous les tests sont passés !" << endl;
    return 0;
}

