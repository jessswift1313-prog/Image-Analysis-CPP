---
jupytext:
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
kernelspec:
  display_name: Python 3 (ipykernel)
  language: python
  name: python3
---

# Rapport de projet Image


+++

## Auteurs

- **Nguyen Duy Bao Nguyen**, duy-bao-nguyen.nguyen@universite-paris-saclay.fr, LDD EM (Principalement responsable pour **le rapport**)
- **Jing Sichao**, sichao.jing@universite-paris-saclay.fr, LDD EM (Principalement responsable pour composer **les codes**)

+++

## Résumé du travail effectué

*Pour chaque partie du sujet, décrire brièvement l'avancement de votre
projet. Exemples de réponses: «non traitée», «réalisée, documentée,
testée», «réalisée, sauf 2.3», «réalisée mais non testée», «réalisée
sauf 2.4 pour lequel notre programme ne compile pas». Pour les
questions «Aller plus loin» plus ouvertes, décrire plus en détail ce
que vous avez choisi de réaliser.*

*En plus du rapport, la documentation de chaque fonction dans le code
devra préciser son auteur et votre degré de confiance dans
l'implantation et les éléments factuels motivant cette confiance:
présence de tests, bogues et limitations connus, etc.*

Tout est fini:)
- Partie 1: Fini
- Partie 2: Fini
- Partie 3: Fini
- Partie 4: Fini
- Partie 5: Fini
- Partie 6: Fini !!!

+++

## Démonstration

*Soutenez ce que vous affirmez dans la section précédente au moyen de
quelques exemples **bien choisis**. Vous pourrez par exemple compiler et
lancer certains de vos programmes, lancer des tests, afficher des images.*

*Ci-dessous, nous vous proposons un début de démonstration pour les différentes
parties*

*Ne gardez que des exemples pertinents qui mettent en valeur votre
travail. Inutile de perdre du temps sur le premier programme si vous
avez fait les suivants plus compliqués; l'auditeur se doutera bien que
vous avez réussi à le faire.*

+++

### Partie 1

*Les cellules commençant par `%%bash` sont interprétées comme des
commandes bash, comme dans un terminal* :

```{code-cell} ipython3
%%bash --login
g++ pbm-affiche.cpp -o pbm-affiche
```

```{code-cell} ipython3
%%bash --login
./pbm-affiche
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pbm/smiley-inverse.pbm")      # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

Remarque: **noir - 1; blanc - 0**

Pour l’exercice 1.3, nous avons ajouté le morceau de code utilisant getline afin de nous **assurer que la fonction vérifie correctement que le fichier commence bien par P1 et ignore les lignes de commentaires.** Ainsi, nous disposons de deux versions : l’une, sans getline, qui lit les données mais ne permet pas de distinguer les lignes commençant par #, et l’autre, plus robuste, qui saute explicitement les commentaires avant de lire les dimensions de l’image.

Pour l’exercice 1.4, nous avons choisi d’utiliser une boucle for-each plutôt qu’une boucle classique **afin d’éviter les erreurs d’indices.** En plus d’être plus sûre, cette forme de boucle exprime mieux notre intention : parcourir chaque ligne puis chaque élément du tableau pour écrire directement l’image binaire.

```{code-cell} ipython3
%%bash --login
g++ pbm-tout-en-un.cpp -o pbm-tout-en-un
```

# Présentation de nos résultats

```{code-cell} ipython3
%%bash --login
./pbm-tout-en-un
```

```{code-cell} ipython3
# Vérification d'une des images obtenues
from open_ppm import open_ppm               # importe la commande open_ppm fournie
im = open_ppm("pbm/code.pbm")               # charge l'image
im.resize((160*im.width // im.height, 160))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# Vérification d'une des images obtenues
from open_ppm import open_ppm               # importe la commande open_ppm fournie
im = open_ppm("pbm/code-inverse.pbm")               # charge l'image
im.resize((160*im.width // im.height, 160))                         # affiche l'image avec une taille donnée
```

On a essayé de flasher le qr code, et on a obtenu une redirection vers "***Salut Bob.***"

```{code-cell} ipython3
# Vérification d'une des images obtenues
from open_ppm import open_ppm               # importe la commande open_ppm fournie
im1 = open_ppm("pbm/cercle.pbm")               # charge l'image
im1.resize((160*im1.width // im1.height, 160))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# Vérification d'une des images obtenues
from open_ppm import open_ppm               # importe la commande open_ppm fournie
im = open_ppm("pbm/cercle-inverse.pbm")               # charge l'image
im.resize((160*im1.width // im.height, 160))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
from open_ppm import open_ppm               # importe la commande open_ppm fournie
im = open_ppm("pbm/smiley.pbm")               # charge l'image
im.resize((80*im.width // im.height, 80))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
from open_ppm import open_ppm               # importe la commande open_ppm fournie
im = open_ppm("pbm/smiley-inverse.pbm")               # charge l'image
im.resize((80*im.width // im.height, 80))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# Vérification d'une des images obtenues
from open_ppm import open_ppm               # importe la commande open_ppm fournie
im = open_ppm("pbm/damier.pbm")               # charge l'image
im.resize((160*im.width // im.height, 160))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# Vérification d'une des images obtenues
from open_ppm import open_ppm               # importe la commande open_ppm fournie
im = open_ppm("pbm/damier-inverse.pbm")               # charge l'image
im.resize((160*im.width // im.height, 160))                         # affiche l'image avec une taille donnée
```

### On a tout fait ;)

+++

### Partie 2

+++

C'est presque la même chose que la partie 1, il faut juste modifier un peu les codes de la partie 1.

```{code-cell} ipython3
%%bash --login
g++ pgm-tout-en-un.cpp -o pgm-tout-en-un
```

```{code-cell} ipython3
%%bash --login
./pgm-tout-en-un
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/brain.pgm")               # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/brain-inverse.pgm")       # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/illusion.pgm")               # charge l'image
im.resize((256*im.width // im.height, 256))                        # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/illusion-inverse.pgm")               # charge l'image
im.resize((256*im.width // im.height, 256))     # affiche l'image avec une taille donnée
```

### Juste les choses comme partie 1 >.<

+++

## Résumé

- **lirePGM**

- **écrirePGM**

- **inversePGM**

+++

### Partie 3
**（Pour simplifier notre rapport, nous ne montrons généralement que l'image de Willis, mais nous avons procédé de la même manière pour tous les images.）**

+++

L'intensité des différences d'intensité **horizontales** au niveau du pixel (i,j) dans l'image img est donnée par:

```img[i-1][j-1] + 2*img[i][j-1] + img[i+1][j-1] - img[i-1][j+1] - 2*img[i][j+1] - img[i+1][j+1]```

L'intensité des différences d'intensité **verticales** est de même donnée par:

```img[i-1][j-1] + 2*img[i-1][j] + img[i-1][j+1] - img[i+1][j-1] - 2*img[i+1][j] - img[i+1][j+1]```

L'intensité totale est la norme des intensités horizontale et verticale (voir le rappel plus loin).

```{code-cell} ipython3
%%bash --login
g++ sobel-tout-en-un.cpp -o sobel-tout-en-un
```

```{code-cell} ipython3
! ./sobel-tout-en-un
```

*Remarque: Pas besoin de utiliser "intensiteH, intensiteV" pour faire "intensite"* 

**En fait, c'est beaucoup plus efficace si on juste calculer une fois (au lieu de 3 fois !!!)**

+++

### Renormalisation : $ans_{i,j} = 255.0 * \frac{img_{i,j} - Min}{Max-Min}$（Du point de vue des proportions）

+++

# !!!Remarque: 
* Première méthode : si la valeur du pixel est supérieure à 255, on pose pixel = 255.
* Deuxième méthode : renormalisation, qui préserve la différence d’intensité, mais le résultat visuel (contraste) est moins bon que celui de la première méthode.

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("sobel/Willis.512.pgm")        # charge l'image
im.resize((512*im.width // im.height, 512))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("sobel/Willis_renormalise.512.pgm")        # charge l'image
im.resize((512*im.width // im.height, 512))  # affiche l'image avec une taille donnée
```

### Seuillage : $(I = \sqrt{h^2 + v^2} > Seuil )$ ? 

Si oui ```img[i][j] = 255 ``` -> **noir**

Si non ```img[i][j] = 0 ``` -> **blanc**

```{code-cell} ipython3
%%bash --login
g++ seuillage-tout-en-un.cpp -o seuillage-tout-en-un
```

```{code-cell} ipython3
! ./seuillage-tout-en-un
```

## Remarque

 **"!"** pour exécution de commandes système dans Notebook

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("images/Willis.512.pgm")        # charge l'image
im.resize((512*im.width // im.height, 512))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage/Willis.512.pgm")        # charge l'image
im.resize((512*im.width // im.height, 512))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage/Billes.256.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage/House.256.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage/Embryos.512.pgm")        # charge l'image
im.resize((512*im.width // im.height, 512))  # affiche l'image avec une taille donnée
```

## DoubleSeuillage
 *   Si （teinte > seuil） et （voisin d'un pixel de imgContour）, alors pixel noir.
 *   Sinon pixel blanc.
 *  Ajouter: S'il est un pixel de imgContour, alors pixel noir.

+++

## Notre algorithme (un pixel est connecté à un graine s'il est voisin immédiat de ce pixel graine dans 8 directions (haut,bas,gauche,droite, les diagonaux):
## (3×3 - 8 voisins et lui-meme）
    
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
                        if(Check) break; //optimization
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

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/Willis.512.pgm")        # charge l'image
im.resize((512*im.width // im.height, 512))  # affiche l'image avec une taille donnée
```

## Optimisation itérative

>$imgContour = doubleSeuillage(imgIntensite, imgContour, seuilFaible); $

En utilisant l'arête actuellement déterminée (imgContour) comme « point de départ », trouvez ses voisins faibles (force > seuilFaible), marquez également ces voisins faibles comme arêtes et renvoyez un nouveau imgContour.

**Répéter un certain nombre de fois pour itérer**

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/iteratif_Willis.512.pgm")        # charge l'image
im.resize((512*im.width // im.height, 512))  # affiche l'image avec une taille donnée
```

## *Lissage
On remplace la valeur de chaque pixel par la moyenne des 8 voisins et lui-meme

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage/Willis_lissage.512.pgm")        # charge l'image
im.resize((512*im.width // im.height, 512))  # affiche l'image avec une taille donnée
```

## *Amélioration - BFS
Constituez une “queue”. Commencez par y insérer les éléments supérieurs à `seuilFort`. Ensuite, vérifiez si les voisinages à chaque élément de la file d'attente sont supérieurs à `seuilFaible` afin de trouver les points d'arête consécutifs.

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/iteratif_Willis_Amelioration.512.pgm")        # charge l'image
im.resize((512*im.width // im.height, 512))  # affiche l'image avec une taille donnée
```

### Partie 4

+++

Remarque: 
 ```
    #ifndef _IMAGE_H //if not defined
    #define _IMAGE_H //define...
    #endif //the end
```
Pour qu'il ne soit compilé qu'**une seule fois** afin d'éviter les redéfinitions.

+++

### PGM

```{code-cell} ipython3
%%bash --login
clang++ -g pgm.cpp pgm-test.cpp -o pgm.test
```

```{code-cell} ipython3
%%bash --login
make pgm-test
```

```{code-cell} ipython3
%%bash --login
./pgm-test
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/brain.pgm")       # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/brain-inverse.pgm")       # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/illusion.pgm")       # charge l'image
im.resize((256*im.width // im.height, 256))
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/illusion-inverse.pgm")       # charge l'image
im.resize((256*im.width // im.height, 256))
```

### Sobel

```{code-cell} ipython3
%%bash --login
make sobel-test
```

```{code-cell} ipython3
! ./sobel-test
```

### Seuillage

```{code-cell} ipython3
%%bash --login
make seuillage-test
```

```{code-cell} ipython3
! ./seuillage-test
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage/Willis.512.pgm")        # charge l'image
im.resize((512*im.width // im.height, 512))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/Willis.512.pgm")        # charge l'image
im.resize((512*im.width // im.height, 512))  # affiche l'image avec une taille donnée
```

### TIN

```{code-cell} ipython3
%%bash --login
make TIN
```

```{code-cell} ipython3
%%bash --login
./TIN -e images/Willis.512.pgm seuillage/Willis.512.pgm
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage/Willis.512.pgm")        # charge l'image
im.resize((512*im.width // im.height, 512))  # affiche l'image avec une taille donnée
```

### Partie 5

+++

Remarque: utilise `make images` pour convertir *. jpg -> *. ppm *. pgm

```{code-cell} ipython3
%%bash --login
make images
```

```{code-cell} ipython3
%%bash --login
make ppm-test
```

```{code-cell} ipython3
! ./ppm-test
```

```{code-cell} ipython3
%%bash --login
make gris-couleurs-test
```

```{code-cell} ipython3
! ./gris-couleurs-test
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("ppm/Baboon.512.ppm")        # charge l'image
im.resize((512*im.width // im.height, 512))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("gris-couleurs/Baboon.512.pgm")        # charge l'image
im.resize((512*im.width // im.height, 512))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("ppm/Embryos.512.ppm")        # charge l'image
im.resize((512*im.width // im.height, 512))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("gris-couleurs/Embryos.512.pgm")        # charge l'image
im.resize((512*im.width // im.height, 512))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("ppm/Billes.256.ppm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("gris-couleurs/Billes.256.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("ppm/House.256.ppm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("gris-couleurs/House.256.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

### Partie 6

+++

Petit remarque: 

La distance euclidienne entre deux points de $n$ dimensions est $d(p,c) = \sqrt{∑(pi-ci)^2}$

```{code-cell} ipython3
%%bash --login
make superpixel-test
```

```{code-cell} ipython3
! ./superpixel-test
```

### Remarque
- Utilisez une variable à cinq dimensions pour représenter chaque point, puis l'algorithme KMoyenne pour trouver le point le plus proche, c'est-à-dire que **les positions** et **les couleurs** sont similaires !

- Pourquoi $\lambda$ ?
Pour distinguer les informations de position et de couleur tout en les conservant dans le même tableau

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("superpixel/Willis.512.ppm")        # charge l'image
im.resize((512*im.width // im.height, 512))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("superpixel/Billes.256.ppm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("superpixel/Baboon.512.ppm")        # charge l'image
im.resize((512*im.width // im.height, 512))  # affiche l'image avec une taille donnée
```

Note：Cette image présente intrinsèquement des différences de couleur importantes entre les blocs de couleur adjacents. La fourrure animale ressemble à ceci.

+++

## Prise de recul

+++

Nous avons consacré au total plus de 30 heures (heures de TP + travail à la BU) à ce projet, un véritable voyage à la fois exigeant et stimulant :). Sichao s’est principalement chargé des parties de code les plus complexes, tandis que Nguyen a travaillé sur le rapport/documentation ainsi que sur les parties plus simples. Pour nous, une fois la première partie réalisée – qui a été la plus longue à développer – les étapes suivantes se sont enchaînées de manière assez naturelle.

Bien sûr, nous avons commis quelques erreurs bêtes qui nous ont fait perdre du temps (oubli de virgule, variables définies plusieurs fois, par exemple une variable locale et une variable globale). Nous avons également dû réaliser des exemples simples sur papier afin de visualiser le fonctionnement des fonctions, surtout lorsque celles-ci étaient longues.

Parfois, nous avons essayé d’optimiser le code, en le rendant plus concis ou en faisant en sorte que certaines boucles s’arrêtent dès que les conditions sont satisfaites (par exemple grâce à break).

Nous avons trouvé que travailler en binôme avec Jupyter était très efficace, surtout lorsque nous pouvions collaborer simultanément depuis deux ordinateurs différents, avec des sauvegardes instantanées. La fonction Markdown intégrée à Jupyter a également été très utile, offrant un rendu visuel plus clair et agréable pour notre code.

Au final, ce projet a été une excellente préparation pour les examens, nous poussant à réfléchir et parfois à chercher des méthodes sur Internet. Nous avons pu le terminer avec une grande satisfaction.

```{code-cell} ipython3

```
