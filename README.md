# Polygon Classes

`polygons.c` is used to name a polygon given a number of sides. In special cases, it outputs more information about the polygon.

## Install

A Makefile is included in the repo with the necessary flags, and it will work on Windows, MacOS and any Linux distro, so just type `make` in the console in the folder with the `huff.c` source file.

## Running

The program is run with `./polygons start`

## Extra information

A prompt will ask the user for the number of sides in a polygon and will then name it (for example, a 435-sided polygon is called a tetrahectatriacontakaipentagon). The working range is from 3 up to 999 sides, and the program redirects the user to the same prompt if the input doesn’t match the working range. At this prompt, the program can be exited by inputting `q/quit/exit/stop`.

The program then asks the user if they want to input the lengths of the polygon’s sides. If they answer yes, the program will output the polygon’s perimeter and, if it is a regular polygon, its area.

If it is a 3-sided polygon (a triangle), the program will classify it (equilateral, isosceles, right, flat, scalene) according to the sides’ lengths and will output the area and the perimeter regardless of whether or not it is a regular triangle.

If it is a 4-sided polygon (a quadrilateral), the program will classify it (rhombus, square, parallelogram, rectangle, kite, random) according to the sides’ lengths and, if needed, additional input (a rhombus with a right angle is a square). It will then output the area and the perimeter regardless of whether or not it is a regular quadrilateral.

## Resources used:

- Naming polygons: http://faculty.kutztown.edu/schaeffe/tutorials/general/polygons.html

- Area of a regular polygon: https://www.mathopenref.com/polygonregulararea.html

- Area of a triangle: https://en.wikipedia.org/wiki/Heron%27s_formula

- Area of a quadrilateral: https://en.wikipedia.org/wiki/Brahmagupta%27s_formula

