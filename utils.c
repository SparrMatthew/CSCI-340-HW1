// Author: Matthew Sparr
// Class: 340 CSCI
// Teacher: Anthony Leclerc
// Date of Last Modification: Jan 31 2023 @ 8:15 pm
// Assignment : 1
// ---------------------------------------------------------------------
//
// I declare this is my sole work other than the work you gave the class
//
// ---------------------------------------------------------------------
// CSCI 340 - Operating Systems I
// Spring 2023 (Anthony Leclerc)
// utils.c implementation file
// Homework Assignment 1
// ---------------------------------------------------------------------

// these are the ONLY library header files that can be used. Under no
// circumstances can additional library header files be included.  In
// particular, this restriction means you CANNOT USE any function
// declared in <string.h>, which includes functions such as: strtok(),
// strchr(), strstr(), strlen(), index(), and others.

// NOTE: when you compile, DO NOT IGNORE WARNINGS!  These warnings are
// likely indicating you are doing something wrong, such as using a
// library function that you are not allowed to use or passing the
// wrong type of argument into a function.

#include <stdio.h>  // standard I/O functions
#include <stdlib.h> // atof()
#include <math.h>   // math functions
#include "utils.h"  // user defined functions

// see utils.h for the required function prototypes and specifications

// NOTE: you may add any "helper" functions you need to get the job done.
//       for example, if you need to determine the length of a string.

// put your IMPLEMENTATION of the function prototypes below:

// My code starts here: -->

/*
method calc_magnitude creates doubles from all p0 and p1
then creates two doubles from formulas x1-x0 and y1-y0
*/
double calc_magnitude(line_t *line_ptr)
{

    double x0 = line_ptr->p0.x;
    double y0 = line_ptr->p0.y;
    double x1 = line_ptr->p1.x;
    double y1 = line_ptr->p1.y;
    double dx = x1 - x0;
    double dy = y1 - y0;

    return sqrt(dx * dx + dy * dy);
}

/*
method calc_direction creates doubles for indexes that will then use
the atan2 formula and give us the direction for our array nums 
*/

double calc_direction(line_t *line_ptr)
{

    double x0 = line_ptr->p0.x;
    double y0 = line_ptr->p0.y;
    double x1 = line_ptr->p1.x;
    double y1 = line_ptr->p1.y;

    return atan2(y1 - y0, x1 - x0);
}

/*
Lines 79 till 113 are majority your code that you did in class
There are few but some lines that I created to implement the necesary fuctions
You can see differnt commented out printf statements from me doing error
checking
*/
int read_lines(char *filename, line_t *line_arr, int n)
{
    int line_number = 0;
    int i;
    char s[200];
    FILE *fp;

    // printf("%s %d\n", filename, n);
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("File was not found\n");
    }
    /*
    Formating to know what exactly you are looking at for each number
    */
    printf("|-------Mag--Radian--Degree-----p0----------p1----|\n");
    while (fgets(s, 200, fp) != NULL && line_number < n)
    {
        // printf("\ns = %s", s);
        line_number++;
        int j = 0;

        double first_num = atof(&s[j]);
        // printf("First value: %f\n", first_num);

        double array[4];
        array[0] = first_num;
        int parse_val = 0;

        for (i = 0; s[i] != '\n'; i++)
        {
            if (s[i] == ',')
            {
                j = i + 1;
                double f = atof(s + j);
                array[parse_val + 1] = f;
                parse_val++;
            }
        }
        // This was for checking which number was in my array: --->

        // printf("Array: ");
        // for(int i = 0; i < 4; i++){
        //     printf("%f\n", array[i]);
        // }

        /*
            Creation of points from the array indexes 
        */

        point_t p0;
        point_t p1;

        p0.x = array[0];
        p0.y = array[1];
        p1.x = array[2];
        p1.y = array[3];

        /* Creating line_t from main where we then declare it as newLine so that each
            (p0.x,p0.y)(p1.x,p1.y) will have a new line.
        */

        line_t newLine;

        newLine.p0.x = (p0.x);
        newLine.p0.y = (p0.y);
        newLine.p1.x = (p1.x);
        newLine.p1.y = (p1.y);

        double degree_direction = calc_direction(&newLine);
        /*
            Creation of a single printf line that way you can see the changes made
            with using a formula to get the degree_direction.
            Also tried doing it like java but the terminal did not like me for all my
            blank space.
        */
        printf("Line %d: %.2f, %.2f, %.2f, (%.2f,%.2f), (%.2f,%.2f)\n", line_number, calc_magnitude(&newLine), calc_direction(&newLine), (degree_direction) * (180 / M_PI), newLine.p0.x, newLine.p0.y, newLine.p1.x, newLine.p1.y);

        // printf("%f\n%f\n%f\n%f\n", newLine.p0.x, newLine.p0.y, newLine.p1.x, newLine.p1.y);
    }

    printf("Number of Lines Passed:");
    return line_number;
    printf("\n");
    fclose(fp);
}