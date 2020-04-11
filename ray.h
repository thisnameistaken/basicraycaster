#ifndef ray
#define ray
#include <stdio.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include "pi.h"


int maxint(int a, int b);
float minfloat(float a, float b);
float dist(float ax, float ay, float bx, float by, float ang);
void drawrays(int mapX, int mapY, int MAPPOWER, int MAPSIZE, int mapin[],  float pa, float px, float py);
void drawgun(int r);
#endif