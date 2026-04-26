#include <stdexcept>
/** @file
 * Lecture et ecriture d'images binaires au format PBM
 **/
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

/// BEGIN ImageNB
/** Structure de données pour représenter une image binaire **/
typedef vector<vector<int> > ImageNB;
/// END ImageNB

/// BEGIN lirePBM

/** Construire une image binaire depuis un fichier PBM
 * @param source le nom d'un fichier PBM
 * @return une image binaire (0/1)
 **/
ImageNB lirePBM(string source) {

    ifstream input(source);
    if(!input)
        throw invalid_argument("Erreur d'ouverture!");
    string type, line, comment;
    int x, width, height;
    
    /*
        première version (celle qui ne gère pas les commentaires)
        input >> type;
        if(type != "P1")
            throw invalid_argument("Wrong type!");
        input >> width >> height;
    */

    // deuxième version (including comments beginning with '#')
    getline(input, type); // on lit dans le flux input, on utilise getline pour pouvoir lire toute la ligne (de plus, le getline garde les espaces à contrario de >>) 
    if(type[0] != 'P' || type[1] != '1')
        throw invalid_argument("Mauvais type!");
    do {
        getline(input, line);
    } while (line.size() == 0 || line[0] == '#'); //Tant que la ligne est vide ou commence par #(commentaire), on recommence jusqu'à arriver à la ligne qui contient la longueur et le largeur. (faut que les commentaires se situent entre P1 et width height pour notre code ) 
    // getline(input, comment);
    stringstream ss(line); // on transforme line en flux pour pouvoir lire les deux entiers width et height. 
    ss >> width >> height; 

    // fin de la deuxième version. 
    ImageNB ans(0); // initialiser le vecteur ans. 
    // cerr << "Image de taille " << width << " x " << height << endl; (ligne de debug optionnelle comme dans ex 1.1)
    for(int i = 0; i < height; i++) //Pour chaque ligne de l'image
    {
        vector<int> newline (0);
        for(int j = 0; j < width; j++) //Pour chaque colonne de l'image 
        {
            input >> x; 
            // ans[i][j] = x;
            newline.push_back(x);
        }
        ans.push_back(newline); // on ajoute la ligne complète à ans
    }
    input.close();
    return ans;
}
/// BEGIN ecrirePBM

/** Ecrit une image binaire dans un fichier PBM
 * @param img une image binaire (0/1)
 * @param cible le nom d'un fichier PBM
 **/
void ecrirePBM(ImageNB img, string cible) {
    ofstream output(cible);
    int height = img.size(), width = img[0].size();
    output << "P1" << endl;
    output << width << ' ' << height << endl;
    for(auto line : img){  // Comme on doit parcourir chaque pixel (sous forme d'un élément de ImageNB) de l'ímage, l'utilisation de for auto est plus adaptée.
        for(auto x : line){
            output << x << ' ';
        }
       output << endl; //Pas obligatoire mais plus facile pour humain à lire:)
    }
    output.close();
    return;
}


/// BEGIN affichePBM

/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param img une image binaire (0/1)
 **/
void affichePBM(ImageNB img) {
    for(auto line : img)   // Même raisonnement 
    {
        for(auto x : line)
        {
            if(x == 1)
                cout << "@ ";
            else
                cout << "  ";
        }
        cout << endl;
    }
    return;
}

/// BEGIN inversePBM

/** Echange le noir et le blanc dans une image PBM
 * @param img une image binaire (0/1)
 * @return l'image où le blanc et le noir ont été inversés
 **/
ImageNB inversePBM(ImageNB img) {
    ImageNB ans(0); // initialiser le vecteur ans 
    for(auto line : img)
    {
        vector<int> newLine(0); //on crée un nouveau vecteur pour chaque line 
        for(auto x : line)
        {
            if(x == 1)
                newLine.push_back(0);
            else
                newLine.push_back(1); // inverse de 1 et 0 
        }
        ans.push_back(newLine);
    }
    return ans;
}

void testLirePBM(){
    cout << "Vérifier que les images obtenues dans 'pbm/' sont semblables à celles fournies dans 'pbm/correction/'" << endl;
    ecrirePBM(lirePBM("images/smiley.pbm"),  "pbm/smiley.pbm");
    ecrirePBM(lirePBM("images/cercle.pbm"),  "pbm/cercle.pbm");
    ecrirePBM(lirePBM("images/code.pbm"), "pbm/code.pbm");
    ecrirePBM(lirePBM("images/damier.pbm"), "pbm/damier.pbm");
    
}

void testinversePBM(){
    cout << "Vérifier que les images obtenues dans 'pbm/' sont semblables à celles fournies dans 'pbm/correction/'" << endl;
    ecrirePBM(inversePBM(lirePBM("images/smiley.pbm")),  "pbm/smiley-inverse.pbm");
    ecrirePBM(inversePBM(lirePBM("images/cercle.pbm")),  "pbm/cercle-inverse.pbm");
    ecrirePBM(inversePBM(lirePBM("images/code.pbm")), "pbm/code-inverse.pbm");
    ecrirePBM(inversePBM(lirePBM("images/damier.pbm")), "pbm/damier-inverse.pbm");
    
}

void testaffichePBM(string source)
{
    cout << "Affichage de l'image " << source << endl;
    affichePBM(lirePBM(source));
}
int main(){
    // read and write PBM files
    testLirePBM();
    // inverse PBM images
    testinversePBM();
    // display PBM images
    testaffichePBM("images/smiley.pbm");
    testaffichePBM("pbm/smiley-inverse.pbm");
    // testaffichePBM("images/cercle.pbm");
    // testaffichePBM("pbm/cercle-inverse.pbm");
    // testaffichePBM("images/code.pbm");
    // testaffichePBM("pbm/code-inverse.pbm");
    // testaffichePBM("images/damier.pbm");
    // testaffichePBM("pbm/damier-inverse.pbm");

    return 0;
}