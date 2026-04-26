# Image Analysis in C++ (Computer Vision)

A C++ implementation of fundamental image processing and analysis algorithms.  
The project focuses on low-level image representation, convolution-based filtering, and classical computer vision techniques.

---

## Overview

This project implements core image processing operations from first principles in C++, with emphasis on:

- Pixel-level image manipulation
- Convolution and filtering operations
- Gradient-based edge detection
- Modular and extensible pipeline design

The goal is to develop a clear understanding of how classical computer vision methods operate at the implementation level.

---

## Features

- Image loading and preprocessing pipeline
- Linear and non-linear filtering (Gaussian, Median)
- Edge detection via gradient operators (Sobel / similar)
- Basic feature extraction methods
- Structured pipeline for sequential image transformations

---

## Technical Stack

- C++17
- Standard Template Library (STL)
- Optional: OpenCV (if applicable)
- CMake (if applicable)

---

## Example Results

Input image → processed output → edge detection pipeline

![input](images/Willis.512.jpg)

![output](seuillage/correction.Willis.512.jpg)

![edge](superpixel/correction/Willis.512.jpg)
