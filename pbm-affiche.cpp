#include <stdexcept>
/** @file
 * Affichage d'une image PBM
 **/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/// BEGIN affichePBM

/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param source le nom d'un fichier PBM
 **/
void affichePBM(string source)  {
    ifstream input(source); // Ouvre le fichier en lecture 
    if(!input) // Vérifie que le fichier s'est bien ouvert
        throw invalid_argument("Erreur d'ouverture!");
    string type;
    int x, width, height, count = 0;
    input >> type; // Lire le type de fichier PBM qui doit être P1
    if(type != "P1")
        throw invalid_argument("Mauvais type!");
    input >> width >> height;
    // cerr << "Image de taille " << width << " x " << height << endl; (ligne de debug optionnelle)
    while(input >> x)
    {
        if(x == 1)
            cout << "@ ";
        else
            cout << "  "; 
        count++; //le count ne sert qu'à revenir à la ligne 
        if(count == width)
            count = 0, cout << endl; //quand la longueur et atteint, on revient à la ligne, on remet count à 0.
    }
    input.close();
    return;
}

/** Echange le noir et le blanc dans une image PBM
 * @param source le nom du fichier PBM à lire
 * @param cible le nom du nouveau fichier PMB créé
 **/
void inversePBM(string source, string cible) {
    ifstream input(source); // Ouvre le fichier source en lecture 
    ofstream output(cible); // Ouvre le fichier cible en écriture 
    if(!input)
        throw invalid_argument("Erreur d'ouverture!");
    string type;
    int x, width, height, count = 0;
    input >> type;
    if(type != "P1")
        throw invalid_argument("Mauvais type!");
    input >> width >> height;
    output << type << endl; // On ecrit P1 dans le cible
    output << width << " " << height << endl; //On ecrit la taille de l'image dans le cible 
    while(input >> x)
    {
        if(x == 1)
            output << "0 "; // 1 devient 0 
        else
            output << "1 "; // 0 devient 1
        count++;
        if(count == width)
            count = 0, output << endl; // revient à la ligne  
    }
    input.close();
    output.close(); //Fermer les deux fichier mais optionnelles 
    return; //return est également optionnel dans une fonction void 
}


int main(){
    cout << "Affichage du smiley " << endl;
    affichePBM("./images/smiley.pbm"); // print the original one
    cout << "Fabrication du smiley inversé (vérifiez que le nouveau fichier a été créé dans le dossier pbm/smiley-inverse.pbm" << endl;
    inversePBM("./images/smiley.pbm","./pbm/smiley-inverse.pbm"); // inverse the image (black/white)
    cout << "Affichage du smiley inversé" << endl;
    affichePBM("./pbm/smiley-inverse.pbm"); // print the inversed one
    return 0;
}

