//Filename: tests.c
//Author: Debi Majumdar

// A program to compute and compare trigonometric functions and their corresponding standard library implementations

#include "mathlib.h" // Header file containing custom math functions

#include <math.h> // Standard math library
#include <stdio.h> // Standard I/O library

int main(void) {
// Opening file to write sine values 
   //graphing sine
    FILE *Sine;

    Sine = fopen("sin.csv", "w");

    fprintf(Sine, "x, y\n");
// Generating sine values and writing to file
    for (double x = 0; x <= 2.0 * M_PI; x += 0.1) {
        double y = Sin(x) - sin(x);

        fprintf(Sine, "%f, %.10f\n", x, y);
    }

    fclose(Sine);

    //graphing cosine
    FILE *Cosine;

    Cosine = fopen("cos.csv", "w");

    fprintf(Cosine, "x, y\n");

    for (double x = 0; x <= 2.0 * M_PI; x += 0.1) {
        double y = Cos(x) - cos(x);

        fprintf(Sine, "%f, %.10f\n", x, y);
    }

    fclose(Cosine);

    //graping tangent
    FILE *Tangent;

    Tangent = fopen("tan.csv", "w");

    fprintf(Tangent, "x, y\n");

    for (double x = 0; x <= 2.0 * M_PI; x += 0.1) {
        double y = Tan(x) - tan(x);
// Computing difference between custom and standard tangent functions
        fprintf(Sine, "%f, %.15f\n", x, y);
    }

    fclose(Tangent);

    return 0;
}
