/* Classifies a given polygon */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

const char tens_digit[10][15] = {"null", "null", "icosi", "triaconta", "tetraconta",
								"pentaconta", "hexaconta", "hexaconta", 
								"octaconta", "enneaconta"};
const char ones_digit[10][10] = {"", "hena", "di", "tri", "tetra", "penta", 
								"hexa", "hepta", "octa", "ennea"};

// Functions used throughout the program ----------------------------

// start() is used as a return to the starting point throughout the program
void start();
// getsName() is used throughout the program to return the name of the polygon
char *getsName(int sides);

// Functions used to convert a string into an integer ---------------

// Check if string only contains digits
bool digitString(const char str[]){
    for (long i = 0; str[i] != '\0'; i++)
        if (str[i] < '0' || str[i] > '9')
            return 0;
    return 1;
}

// Convert a string into an integer.  Return -1 if it is not valid.
long convert(const char length[]) {
    if (length[0] != '0' || strlen(length) == 1)
        if (digitString(length)){
            long l = atoi(length);
            if (l > 0)
                return l;
        }
    return -1;
}

// Auxiliary functions ----------------------------------------------

// Control flow based on number of sides received as input
void controlFlow(int sides){
	if (sides == -1){
		printf("Please enter an integer.\n");
		start();
		return;
	}
	if (sides < 3){
		printf("You can't have a polygon with fewer than 3 sides. Try again!\n");
		start();
		return;
	}
	if (sides > 999){
		printf("That's a really complicated polygon! ");
		printf("Try a polygon with fewer sides\n");
		start();
		return ;
	}
	char name[100];
	strcat(name, getsName(sides));

	if (strchr("aeiou", name[0]))
		printf ("You're looking at an %s!\n", name);
	else
		printf ("You're looking at a %s!\n", name);

	
	
}

// Check if all sides are equal
bool equalSides(int number_sides, long *sides_length){
	long expected_length = sides_length[0];
	for (int i = 0; i < number_sides ; i++)
		if (sides_length[i] != expected_length)
			return 0;
	return 1;
}

// Triangle classify functions --------------------------------------

// Check if 2 numbers add up to the third
bool addUp(long a, long b, long c){
    if (a + b == c)
        return 1;
    if (b + c == a)
        return 1;
    if (a + c == b)
        return 1;
    return 0;
}

// Check if the squares of numbers add up
bool rightAngle(long a, long b, long c){
    a *= a;
    b *= b;
    c *= c;
    return addUp(a,b,c);
}

// Check if triangle can exist
bool impossibleTriangle(long a, long b, long c){
    if (a + b < c)
        return 1;
    if (a + c < b)
        return 1;
    if (b + c < a)
        return 1;
    return 0;
}

/*
// Classify a triangle, given side lengths as longs:
long triangle(long a, long b, long c) {
    if (a == b && b == c)
        return Equilateral;
    if (isosceles(a,b,c))
        return Isosceles;
    if (rightAngle(a,b,c))
        return Right;
    if (addUp(a,b,c))
        return Flat;
    if (impossibleTriangle(a,b,c))
        return Impossible;
    return Scalene;
}
*/

// Polygon naming functions -----------------------------------------

// Assign *prefix the names of polygons with a small number of sides (<=20)
// These polygons have individual names each
void nameSmallPolygon(int sides, char *prefix){
	switch (sides){
		case 3: strcat(prefix, "tri"); break;
		case 4: strcat(prefix, "tetra"); break;
		case 5: strcpy(prefix, "penta"); break;
		case 6: strcpy(prefix, "hexa"); break;
		case 7: strcpy(prefix, "hepta"); break;
		case 8: strcpy(prefix, "octa"); break;
		case 9: strcpy(prefix, "nona"); break;
		case 10: strcpy(prefix, "deca"); break;
		case 11: strcpy(prefix, "undeca"); break;
		case 12: strcpy(prefix, "dodeca"); break;
		case 13: strcpy(prefix, "triskaideca"); break;
		case 14: strcpy(prefix, "tetradeca"); break;
		case 15: strcpy(prefix, "pentadeca"); break;
		case 16: strcpy(prefix, "hexadeca"); break;
		case 17: strcpy(prefix, "heptadeca"); break;
		case 18: strcpy(prefix, "optadeca"); break;
		case 19: strcpy(prefix, "enneadeca"); break;
		case 20: strcpy(prefix, "icosa"); break;
	}
	return;
}

// Assign *prefix the names of polygons with a medium number of (20,100) sides
void nameMediumPolygon(int sides, char *prefix){
	int sides_tens = sides / 10;
	int sides_ones = sides % 10;

	strcat(prefix, tens_digit[sides_tens]);
	if(sides_ones){
		strcat(prefix, "kai");
		strcat(prefix, ones_digit[sides_ones]);
	}
	return;
}

// Assign *prefix the names of polygons with a large number of sides [100,999]
void nameLargePolygon(int sides, char *prefix){
	int sides_hundreds = sides / 100;
	int sides_tens = (sides / 10) % 10;
	int sides_ones = sides % 10;

	if (sides_hundreds != 1){
		strcat(prefix, ones_digit[sides_hundreds]);
	}
	strcat(prefix, "hecta");

	if(sides_tens)
		strcat(prefix, tens_digit[sides_tens]);

	if(sides_ones){
		strcat(prefix, "kai");
		strcat(prefix, ones_digit[sides_ones]);
	}
	return;
}

// Returns the name of polygon based on its sides
char* getsName(int sides){
	char name[100]="";
	if (sides <= 20)
		nameSmallPolygon(sides, name);
	else if (sides > 20 && sides < 100)
		nameMediumPolygon(sides, name);
	else if (sides <=999)
		nameLargePolygon(sides, name);

	strcat(name,"gon");
	return name;
}

// User interface ---------------------------------------------------

// That's not a polygon! It's a circle!
void easter(){
	printf("You might be looking at a circle (or another somewhat round object)! ");
	printf("Stop it, they're not polygons! ");
	printf("Let's try again.\n");
	start();
	return;
}

// Get number of sides
void start(){
	printf("Look around yourself! The world is full of polygons. "); 
	printf("Look at one and count its sides: ");

	char input[100];
	scanf("%s", input);

	if (!strcmp(input, "infinite")){
		easter();
		return;
	}

	int sides = convert(input);
	controlFlow(sides);
	return;
}

// Main function ----------------------------------------------------
int main(int n, char *args[n]){
	setbuf(stdout, NULL);

    if (n == 1) {
        //test();
    }
    else if (n == 2 && !strcmp(args[1], "start")) {
        start();
    }
    else {
        fprintf(stderr, "Use e.g.: ./polygons start\n");
        exit(1);
    }
    return 0;
}
