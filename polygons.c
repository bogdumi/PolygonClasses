/* Classifies a given polygon */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>
#include <math.h>

#define PI 3.14159265

// Arrays of prefixes used for naming polygons ----------------------

const char tens_digit[10][15] = {"null", "null", "icosi", "triaconta", "tetraconta",
								"pentaconta", "hexaconta", "hexaconta", 
								"octaconta", "enneaconta"};
const char ones_digit[10][10] = {"", "hena", "di", "tri", "tetra", "penta", 
								"hexa", "hepta", "octa", "ennea"};

// User interface functions used throughout the program need prototype
// ------------------------------------------------------------------

// start() is used as a return to the starting point throughout the program
void start();
// getsName() is used throughout the program to return the name of the polygon
char *getsName(int sides);
// inputSides is used to ask the user for the lengths' of the polygon
void inputSides(int sides);
// Classify a triangle
void triangle(long a, long b, long c);
// Classify a quadrilateral
void quadri(long a, long b, long c, long d);


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
		printf("Please enter an integer. To exit, enter \"stop/exit/(q)uit\".\n");
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

	inputSides(sides);
	return;
}

// Check if all sides are equal
bool equalSides(int number_sides, long *sides_length){
	long expected_length = sides_length[0];
	for (int i = 0; i < number_sides ; i++)
		if (sides_length[i] != expected_length)
			return 0;
	return 1;
}

// Calculate the perimeter of a polygon given sides -----------------
long peri(int sides, long *sides_length){
	long perimeter = 0;
	for (int i = 0; i < sides; i++)
		perimeter += sides_length[i];
	return perimeter;
}

double area(int sides, long length){
	double area, numerator, denominator;
	numerator = length * length * sides;
	denominator = 4 * tan (PI / sides);
	area = numerator / denominator;
	return area;
}

// Perform operations on polygon's sides
void polygonOp(int sides, long *sides_length){
	char name[30]="";
	strcat(name, getsName(sides));
	
	if (sides == 3){
		triangle(sides_length[0], sides_length[1], sides_length[2]);
		return;
	}
	if(sides == 4){
		quadri(sides_length[0], sides_length[1], sides_length[2], sides_length[3]);
		return;
	}

	long perimeter = peri(sides, sides_length);
	printf ("The perimeter of your %s is %ld.\n", name, perimeter);

	if (equalSides(sides, sides_length)){
		double ar = area(sides, sides_length[0]);
		printf ("Because it is a regular polygon, ");
		printf ("the area of your %s is about %0.2lf.\n", name, ar);
	}
	start();
}

// Triangle classify functions --------------------------------------

// Check if 2 sides are equal
bool isosceles(long a, long b, long c){
    if (a == b)
        return 1;
    if (b == c)
        return 1;
    if (c == a)
        return 1;
    return 0;
}

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
bool rightAngleTri(long a, long b, long c){
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

// Calculate area given sides of triangle
double triangleArea(long a, long b, long c){
	double p = (a + b + c) / 2;
	double multi = p * (p - a) * (p - b) * (p - c);
	double area = sqrt (multi);
	return area;
}

// Classify a triangle, given side lengths as longs
void triangle(long a, long b, long c) {
	char triangleType[50] = "";
	double ar = -1;

    if (a == b && b == c)
        strcat(triangleType, "equilateral");
    else if (isosceles(a,b,c))
        strcat(triangleType, "isosceles");
    if (rightAngleTri(a,b,c))
        strcat(triangleType, "right");
    if (addUp(a,b,c))
        strcat(triangleType, "flat");
    if (impossibleTriangle(a,b,c)){
    	printf("These sides can't belong to a triangle! Let's start over.\n");
    	start();
    	return;
    }
    if (!strcmp(triangleType, ""))
    	strcat(triangleType, "scalene");

    if (strchr("aeiou",triangleType[0]))
    	printf("You are looking at an %s trigon (more commonly known as a triangle!).\n", triangleType);
    else
    	printf("You are looking at a %s trigon (more commonly known as a triangle!).\n", triangleType);


    printf("Its perimeter is %ld,\n", a + b + c);
    ar = triangleArea(a,b,c);
    printf("Its area is about %0.2lf.\n", ar);
    start();
    return;
}

// Quadrilateral classify functions ----------------------------------------


// Check if quadri is a rhombus
bool rhombus(long a, long b, long c, long d){
	if (a == b && b == c && c == d)
		return 1;
	return 0;
}

// Check if quadri is kite
bool kite(long a, long b, long c, long d){
	if (a == b && c ==d)
		return 1;
	if (b == c && a == d)
		return 1;
	return 0;
}

// Check if quadri is parallelogram
bool parallelogram(long a, long b, long c, long d){
	if (a == c && b == d)
		return 1;
	return 0;
}

// Turn rhombus/parallelogram into square/rectangle if right angle
void rightAngleQuadri(char *quadriType){
	bool right_angle = 0;

	printf("Does this polygon have a right angle? (yes/no)\n");
	char answer[100];
	scanf("%s", answer);
	if (!strcmp(answer, "yes") || !strcmp(answer, "y"))
		right_angle = 1;

	if(right_angle){
		if(!strcmp(quadriType, "rhombus"))
			strcpy(quadriType, "square");
		if(!strcmp(quadriType, "parallelogram"))
			strcpy(quadriType, "rectangle");
	}
	return;
}

// Calculate area of quadri
double quadriArea(long a, long b, long c, long d){
	int p = (a + b + c + d) / 2;
	int multi = (p - a) * (p - b) * (p - c) * (p - d);
	double area = sqrt(multi);
	return area;
}

// Classify a quadri
void quadri(long a, long b, long c, long d){
	char quadriType[50] = "";
	double ar = -1;
	if (rhombus(a,b,c,d))
		strcat(quadriType, "rhombus");
	else if (kite(a,b,c,d))
		strcat(quadriType, "kite");
	else if (parallelogram(a,b,c,d))
		strcat(quadriType, "parallelogram");
	
	if(!strcmp(quadriType, "rhombus") || !strcmp(quadriType, "parallelogram"))
		rightAngleQuadri(quadriType);

	if(!strcmp(quadriType, ""))
		strcat(quadriType, "random quadrilateral");
	ar = quadriArea(a,b,c,d);

	printf("You're looking at a %s!\n", quadriType);

	printf("Its perimeter is %ld,\n", a + b + c + d);
    printf("Its area is about %0.2lf.\n", ar);
    start();
    return;

}


// Polygon naming functions -----------------------------------------

// Assign *prefix the names of polygons with a small number of sides (<=20)
// These polygons have individual names each
void nameSmallPolygon(int sides, char *prefix){
	switch (sides){
		case 3: strcpy(prefix, "tri"); break;
		case 4: strcpy(prefix, "tetra"); break;
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

// Ask for number of sides
void start(){
	printf("Look around! The world is full of polygons. "); 
	printf("Look at one and count its sides: ");

	char input[100];
	scanf("%s", input);

	if (!strcmp(input, "stop") || !strcmp(input, "exit") ||
		!strcmp(input, "quit") || !strcmp(input, "q"))
		return;

	if (!strcmp(input, "infinite")){
		easter();
		return;
	}

	int sides = convert(input);
	controlFlow(sides);
	return;
}

// Ask for sides' lengths
void inputSides(int sides){
	printf("Would you also like to input the sides' lengths? (yes/no)\n");
	char answer[100];
	scanf("%s", answer);
	long sides_length[1000];
	if (!strcmp(answer, "yes") || !strcmp(answer, "y")){
		printf("Please input the sides' lengths: \n");
		for (int i = 0; i < sides; i++){
			scanf("%s", answer);
			sides_length[i] = convert(answer);
			if(sides_length[i] <= 0){
				printf("Please input a valid number for the polygon's length. Let's start over.\n");
				start();
			}
		}
		polygonOp(sides, sides_length);
	}
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
