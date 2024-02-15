//Filename: tests.c
//Author: Debi Majumdar

// A program to compute and compare trigonometric functions and their corresponding standard library implementations

#include "mathlib.h" // Header file containing custom math functions

#include <math.h> // Standard math library
#include <stdio.h> // Standard I/O library

int main(void) {
    // Opening file to write sine values
    FILE *sinFile;
    sinFile = fopen("sine.csv", "w");
    fprintf(sinFile, "x, y\n");

    // Generating sine values and writing to file
    for (double x = 0; x <= 2.0 * M_PI; x += 0.1) {
        double y
            = MySin(x) - sin(x); // Computing difference between custom and standard sine functions
        fprintf(sinFile, "%f, %.10f\n", x, y); // Writing values to file
    }

    fclose(sinFile); // Closing file after writing

    // Opening file to write cosine values
    FILE *cosFile;
    cosFile = fopen("cosine.csv", "w");
    fprintf(cosFile, "x, y\n");

    // Generating cosine values and writing to file
    for (double x = 0; x <= 2.0 * M_PI; x += 0.1) {
        double y = MyCos(x)
                   - cos(x); // Computing difference between custom and standard cosine functions
        fprintf(cosFile, "%f, %.10f\n", x, y); // Writing values to file
    }

    fclose(cosFile); // Closing file after writing

    // Opening file to write tangent values
    FILE *tanFile;
    tanFile = fopen("tangent.csv", "w");
    fprintf(tanFile, "x, y\n");

    // Generating tangent values and writing to file
    for (double x = 0; x <= 2.0 * M_PI; x += 0.1) {
        double y = MyTan(x)
                   - tan(x); // Computing difference between custom and standard tangent functions
        fprintf(tanFile, "%f, %.15f\n", x, y); // Writing values to file
    }

    fclose(tanFile); // Closing file after writing

    return 0; // Exiting program
}
