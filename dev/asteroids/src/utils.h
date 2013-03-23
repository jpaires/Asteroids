#ifndef UTILS_H_
#define UTILS_H_

#include "cg/cg.h"

#define LEFT  1.0
#define RIGHT -1.0
#define PI 3.14159265358979323846
#define RADTODEG 57.29577951308232185913

double randomBetween(double min, double max);
void log (std::string str);
void drawBar(int p1, int p2, int p3, int p4, cg::Vector3d LeftColor, cg::Vector3d RightColor);
GLuint LoadTexture( const char * filename, int width, int height );
void FreeTexture(GLuint texture);
#endif

