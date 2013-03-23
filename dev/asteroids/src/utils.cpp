#include "utils.h"


double randomBetween(double min, double max) {
		return (rand() / (double)RAND_MAX * (max - min)) + min;
	}

void log(std::string str) {
	std::ofstream &logfile = cg::DebugFile::instance()->getOutputFileStream();
	logfile << str;
}

void drawBar(int p1, int p2, int p3, int p4, cg::Vector3d LeftColor, cg::Vector3d RightColor) {
	glBegin(GL_QUADS); //begin the four sided shape
		glColor3d(LeftColor[0], LeftColor[1], LeftColor[2]);
		glVertex3f(p1,p4,0.0); //first corner
		glVertex3f(p1,p3,0.0); //second corner
		glColor3d(RightColor[0], RightColor[1], RightColor[2]);
		glVertex3f(p2,p3,0.0); //third corner
		glVertex3f(p2,p4,0.0); //fourth corner
	glEnd();
}


GLuint LoadTexture( const char * filename, int width, int height ){
    GLuint texture;
    unsigned char * data;
    FILE * file;


    file = fopen(filename, "rb");
    if (file == NULL) return 0;
    data = (unsigned char *)malloc(width * height * 3);
    fread(data, width * height * 3, 1, file);
    fclose(file);

    glGenTextures(1, &texture); 
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    free(data);
    return texture;
}

  void FreeTexture(GLuint texture){
	  glDeleteTextures(1, &texture);
}


