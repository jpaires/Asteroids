#include "TopCamera.h"

namespace asteroids {

    TopCamera::TopCamera() : Entity("TopCamera") {
	}
    TopCamera::~TopCamera() {
	}
    void TopCamera::init() {
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		
		GLfloat light_position[] = { 0, 0, -1, 0};
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		
		GLfloat model[] = {0.8, 0.8, 0.8, 1};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model);
	}

    void TopCamera::draw() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,_winWidth,0,_winHeight,100,-100);
/*        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
		glTranslated(_winWidth/2, _winHeight/2, 0);
		glRotated(145, -1, 0, 0);
		glTranslated(-_winWidth/2, -_winHeight/2, 0);
		*/
    }
	void TopCamera::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
	}
} //namespace asteroids
