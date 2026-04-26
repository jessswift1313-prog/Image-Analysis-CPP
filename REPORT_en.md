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

# Image Processing Project Report

## Executive Summary
This project implements an end-to-end image processing pipeline in C++ and Python (using Jupyter notebooks). We implemented routines to read, write, and invert PBM/PGM/PPM images, performed Sobel edge detection (with dynamic normalization), implemented a custom double-threshold edge-linking algorithm (using BFS), and demonstrated superpixel segmentation via K-means in a five-dimensional feature space (combining spatial and color information). 

We validated the results visually (for example, by generating a QR code that redirects to "Salut Bob."). All components were successfully completed: one team member focused on the code implementation, while the other wrote the report. This project provided valuable hands-on experience in image processing and collaborative software development.

## Authors
- **Nguyen Duy Bao Nguyen**, duy-bao-nguyen.nguyen@universite-paris-saclay.fr, LDD EM – Primarily responsible for the **report**.
- **Jing Sichao**, sichao.jing@universite-paris-saclay.fr, LDD EM – Primarily responsible for writing the **code**.

## Work Summary
All parts of the project have been completed successfully:
- Part 1: Completed.
- Part 2: Completed.
- Part 3: Completed.
- Part 4: Completed.
- Part 5: Completed.
- Part 6: Completed.

+++

## Demonstration

The following examples illustrate some of the results obtained for each part of the project, including code compilation and output images.

### Part 1
*Cells starting with `%%bash` are executed in a Bash shell (like a terminal).*

```{code-cell} ipython3
%%bash --login
clang++ -g pbm-affiche.cpp -o pbm-affiche
```

```{code-cell} ipython3
%%bash --login
./pbm-affiche
```

```{code-cell} ipython3
# Display one of the generated images
from open_ppm import open_ppm
im = open_ppm("pbm/smiley-inverse.pbm")
im.resize((256*im.width // im.height, 256))
```

```{code-cell} ipython3
%%bash --login
g++ pbm-tout-en-un.cpp -o pbm-tout-en-un
```

```{code-cell} ipython3
%%bash --login
./pbm-tout-en-un
```

### Results

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("pbm/code.pbm")
im.resize((160*im.width // im.height, 160))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("pbm/code-inverse.pbm")
im.resize((160*im.width // im.height, 160))
```

We attempted to scan the QR code, and it redirected to **"Salut Bob."**

```{code-cell} ipython3
from open_ppm import open_ppm
im1 = open_ppm("pbm/cercle.pbm")
im1.resize((160*im1.width // im1.height, 160))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("pbm/cercle-inverse.pbm")
im.resize((160*im.width // im.height, 160))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("pbm/smiley.pbm")
im.resize((80*im.width // im.height, 80))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("pbm/smiley-inverse.pbm")
im.resize((80*im.width // im.height, 80))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("pbm/damier.pbm")
im.resize((160*im.width // im.height, 160))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("pbm/damier-inverse.pbm")
im.resize((160*im.width // im.height, 160))
```

### Part 2
It's almost identical to Part 1; only minor modifications to the code were needed.

```{code-cell} ipython3
%%bash --login
g++ pgm-tout-en-un.cpp -o pgm-tout-en-un
```

```{code-cell} ipython3
%%bash --login
./pgm-tout-en-un
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("pgm/brain.pgm")
im.resize((100, 68))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("pgm/brain-inverse.pgm")
im.resize((100, 68))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("pgm/illusion.pgm")
im.resize((256*im.width // im.height, 256))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("pgm/illusion-inverse.pgm")
im.resize((256*im.width // im.height, 256))
```

### Summary
- **readPGM**
- **writePGM**
- **invertPGM**

+++

### Part 3
*(To simplify this demonstration, we show only the "Willis" image as a representative example; the same approach was used for all images.)*

The horizontal intensity difference at pixel `(i,j)` is given by:

```
img[i-1][j-1] + 2*img[i][j-1] + img[i+1][j-1] - img[i-1][j+1] - 2*img[i][j+1] - img[i+1][j+1]
```

The vertical intensity difference is:

```
img[i-1][j-1] + 2*img[i-1][j] + img[i-1][j+1] - img[i+1][j-1] - 2*img[i+1][j] - img[i+1][j+1]
```

The total intensity is the norm of these horizontal and vertical differences.

```{code-cell} ipython3
%%bash --login
g++ sobel-tout-en-un.cpp -o sobel-tout-en-un
```

```{code-cell} ipython3
! ./sobel-tout-en-un
```

*Note: There is no need to compute "intensiteH" and "intensiteV" separately. It is much more efficient to compute the combined intensity only once (instead of three times).*

### Renormalization
Renormalization is defined as:
$$
ans_{i,j} = 255.0 \times \frac{img_{i,j} - \min}{\max - \min}
$$
*(scaled proportionally to the intensity range)*

- First approach: if a pixel value exceeds 255, set it to 255 (clipping).
- Second approach: renormalize to preserve relative intensity differences (this yields lower contrast than the first approach).

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("sobel/Willis.512.pgm")
im.resize((512*im.width // im.height, 512))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("sobel/Willis_renormalise.512.pgm")
im.resize((512*im.width // im.height, 512))
```

### Thresholding: $(I = \sqrt{h^2 + v^2} > \text{Threshold})$?
If yes (above threshold), `img[i][j] = 255` → **black**; otherwise, `img[i][j] = 0` → **white**.

```{code-cell} ipython3
%%bash --login
g++ seuillage-tout-en-un.cpp -o seuillage-tout-en-un
```

```{code-cell} ipython3
! ./seuillage-tout-en-un
```

### Note
Use `!` to execute system commands from a notebook.

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("images/Willis.512.pgm")
im.resize((512*im.width // im.height, 512))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("seuillage/Willis.512.pgm")
im.resize((512*im.width // im.height, 512))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("seuillage/Billes.256.pgm")
im.resize((256*im.width // im.height, 256))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("seuillage/House.256.pgm")
im.resize((256*im.width // im.height, 256))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("seuillage/Embryos.512.pgm")
im.resize((512*im.width // im.height, 512))
```

## Double Thresholding
- If (intensity > threshold) and (the pixel has a neighbor in `imgContour`), set the pixel to black.
- Otherwise, set it to white.
- Also: any pixel already in `imgContour` remains black.

## Our algorithm (pixel connectivity: 8 neighbors)
``` 
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
                    if(Check) break; // optimization
                    for(int dj = -1; dj <= 1; dj++)
                    {
                        int ni = i + di, nj = j + dj;
                        if(ni >= 0 && ni < height && nj >= 0 && nj < width && !(di == 0 && dj == 0))
                        {
                            if(imgContour[ni][nj] == 0.0) // black pixel in contour image
                                Check = true;
                        }
                        if(Check) break; // optimization
                    }         
                }
                ans[i][j] = (Check ? 0.0 : 255.0);
            }
            else
                ans[i][j] = 255.0; // White pixel
        }
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("seuillage_double/Willis.512.pgm")
im.resize((512*im.width // im.height, 512))
```

## Iterative Optimization
Using the current edges (`imgContour`) as a starting point, find weak neighbors (intensity > `lowThreshold`) of these edges, mark them as edges, and form a new `imgContour`. Repeat this process a fixed number of times.

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("seuillage_double/iteratif_Willis.512.pgm")
im.resize((512*im.width // im.height, 512))
```

## Smoothing
Replace each pixel’s value with the average of itself and its 8 neighbors.

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("seuillage/Willis_lissage.512.pgm")
im.resize((512*im.width // im.height, 512))
```

## Improvement - BFS
Build a queue. Start by enqueuing all pixels above `strongThreshold`. For each pixel in the queue, check its neighbors that are above `weakThreshold` to find connected edge points.

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("seuillage_double/iteratif_Willis_Amelioration.512.pgm")
im.resize((512*im.width // im.height, 512))
```

### Part 4

**Note:** We use `#ifndef ... #define ... #endif` include guards so that each header is compiled only once, avoiding redefinition errors.

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
from open_ppm import open_ppm
im = open_ppm("pgm/brain.pgm")
im.resize((100, 68))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("pgm/brain-inverse.pgm")
im.resize((100, 68))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("pgm/illusion.pgm")
im.resize((256*im.width // im.height, 256))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("pgm/illusion-inverse.pgm")
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

### Thresholding

```{code-cell} ipython3
%%bash --login
make seuillage-test
```

```{code-cell} ipython3
! ./seuillage-test
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("seuillage/Willis.512.pgm")
im.resize((512*im.width // im.height, 512))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("seuillage_double/Willis.512.pgm")
im.resize((512*im.width // im.height, 512))
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
from open_ppm import open_ppm
im = open_ppm("seuillage/Willis.512.pgm")
im.resize((512*im.width // im.height, 512))
```

### Part 5

**Note:** Use `make images` to convert `*.jpg` files to `*.ppm` and `*.pgm`.

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
from open_ppm import open_ppm
im = open_ppm("ppm/Baboon.512.ppm")
im.resize((512*im.width // im.height, 512))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("gris-couleurs/Baboon.512.pgm")
im.resize((512*im.width // im.height, 512))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("ppm/Embryos.512.ppm")
im.resize((512*im.width // im.height, 512))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("gris-couleurs/Embryos.512.pgm")
im.resize((512*im.width // im.height, 512))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("ppm/Billes.256.ppm")
im.resize((256*im.width // im.height, 256))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("gris-couleurs/Billes.256.pgm")
im.resize((256*im.width // im.height, 256))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("ppm/House.256.ppm")
im.resize((256*im.width // im.height, 256))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("gris-couleurs/House.256.pgm")
im.resize((256*im.width // im.height, 256))
```

### Part 6

**Note:** The Euclidean distance between two points in $n$ dimensions is $d(p,c) = \sqrt{\sum (p_i - c_i)^2}$.

```{code-cell} ipython3
%%bash --login
make superpixel-test
```

```{code-cell} ipython3
! ./superpixel-test
```

- We represent each point by a five-dimensional vector (including its x,y position and RGB color), and apply K-means to cluster points that are similar in both position and color.
- The parameter $\lambda$ is used to balance the influence of spatial versus color components while keeping them in the same feature vector.

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("superpixel/Willis.512.ppm")
im.resize((512*im.width // im.height, 512))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("superpixel/Billes.256.ppm")
im.resize((256*im.width // im.height, 256))
```

```{code-cell} ipython3
from open_ppm import open_ppm
im = open_ppm("superpixel/Baboon.512.ppm")
im.resize((512*im.width // im.height, 512))
```

**Note:** The Baboon image naturally has significant color differences between adjacent regions, resembling the texture of animal fur.

+++

## Retrospective

We spent over 30 hours (including lab sessions and independent work) on this project; it was both challenging and rewarding. Sichao took the lead on implementing the more complex parts of the code, while I (Nguyen) focused on the report/documentation and on the simpler tasks. Once the first part was completed — which was the most time-consuming — the later steps proceeded quite naturally. We of course made some minor errors that cost us time (such as missing commas or redeclaring variables), and we also worked out simple examples on paper to understand how the functions should behave. At times we tried to optimize the code by making it more concise or by adding early `break` statements so that loops would stop once conditions were met. We found working in a pair with Jupyter very effective, especially when collaborating from two different computers with instant saving. The built-in Markdown support in Jupyter was also very helpful, providing a clearer and more pleasant presentation of our code and documentation. Overall, this project was an excellent preparation for our exams, pushing us to think critically and sometimes to search for solutions on the Internet; we finished it with a great sense of satisfaction.
```
