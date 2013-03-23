#include "Background.h"

namespace asteroids {
	
		Background::Background() : cg::Entity("Background") {
		}

		Background::~Background() {
			//delete _img;
		}

		void Background::init() {
			int i = 0;
			cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
			for (i=0; i < cg::Properties::instance()->getInt("STARS"); i++)
				_starVector.push_back(cg::Vector2i(randomBetween(0,win.width), randomBetween(0,win.height)));
			//_img = new pixmap("images/bg.bmp");
		}
		void Background::draw() {
			glDisable(GL_LIGHTING);
						
			//glRasterPos2d(0, 0);
			//glDrawPixels(_img->width, _img->height, GL_RGB, GL_UNSIGNED_BYTE, _img->data);

			glClear (GL_DEPTH_BUFFER_BIT);

			unsigned int i = 0;
			glColor3d(1,1,1);
			glBegin(GL_POINTS);
			for (i=0; i < _starVector.size(); i++) {
		//		glPointSize(2.5 * (i+1)/_starVector.size());
		//		glBegin(GL_POINTS);
				glVertex3d((_starVector[i])[0], (_starVector[i])[1], 0);
		//		glEnd();
			}
			glEnd();
			glEnable(GL_LIGHTING); 
		}
	
} //namespace asteroids
