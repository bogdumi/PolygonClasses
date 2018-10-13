/* Classifies a given polygon */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

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

// User interface ---------------------------------------------------

// Get number of sides
void star(){
	printf("Look around yourself! The world is full of polygons. Look at one and count its sides: ");
	int sides;
	scanf("%d", &sides);
}


int main(int n, char *args[n]){
	setbuf(stdout, NULL);
    if (n == 1) {
        //test();
    }
    else if (n == 2 && !strcmp(args[1], "start")) {
        star();
    }
    else {
        fprintf(stderr, "Use e.g.: ./polygons start\n");
        exit(1);
    }
    return 0;
}
