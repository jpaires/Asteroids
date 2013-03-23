#include "AsteroidsManager.h"
#include "LevelsManager.h"
#include "Asteroid.h"
#include "utils.h"

namespace asteroids {
	AsteroidsManager::AsteroidsManager(std::string id) : ParticlesManager<Asteroid>(id, "Ast") {
		_levelsManager = (LevelsManager*) cg::Registry::instance()->get("LevelsManager");
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;
		_minimap = cg::Properties::instance()->getInt("MINIMAP");
	}
	
	AsteroidsManager::~AsteroidsManager() {}
	
	void AsteroidsManager::addAst(int min, int max) {
		addParticle(new Asteroid(getNewId(), min, max));
	}

	void AsteroidsManager::addAst(int min, int max, double posx, double posy) {
		addParticle(new Asteroid(getNewId(), min, max, posx, posy));
	}

	void AsteroidsManager::postUpdate(unsigned long elapsed_millis) {
		ParticlesManager::postUpdate(elapsed_millis);
		if ( _entities.size() == 0)
			_levelsManager->nextLevel();
	}

	void AsteroidsManager::drawOverlay() {
		glMatrixMode(GL_MODELVIEW);
		glDisable(GL_LIGHTING);
		glColor3d(1,1,1);
		std::ostringstream os;
		os << "Asteroids: " << _entities.size();
		std::string str = os.str();
		cg::Util::instance()->drawBitmapString(str, _winWidth/2 - 25, 600 - 30);
		glEnable(GL_LIGHTING);
	}

	void AsteroidsManager::draw() {
		cg::GroupDraw::draw();
		if (_minimap == 0) return;
		// Minimap is on Draw and not DrawOverlay because of the spheres (drawOverlay chops them down like animals).
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glClear (GL_DEPTH_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		//GLfloat ambient[] = {0.1, 0.1, 0.1, 1};
		//GLfloat diffuse[] = {0.5, 0, 0, 0.9};
		//GLfloat specular[] = {0.1, 0.1, 0.1, 1};
		//glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		//glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		//glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		//glShadeModel(GL_SMOOTH);
		glColor4d(0.8, 0.3, 0.3, 0.4);
		unsigned int i = 0;
		for(i = 0; i < _entities.size(); i++) {
			glPushMatrix();
			glTranslated(_winWidth - _winWidth/5, 0, 0);
			glTranslated(((Asteroid*)_entities[i])->getXPosition()/5, ((Asteroid*)_entities[i])->getYPosition()/5, 0);			
			glutSolidSphere(6, 15, 15);
			glPopMatrix();
		}
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glColor4f(0, 0.5, 0, 0.2);
		glBegin(GL_QUADS);
		glVertex3f(_winWidth, 0, 0);
		glVertex3f(_winWidth, _winHeight/5 + 15, 0);
		glVertex3f(_winWidth - _winWidth/5 - 15, _winHeight/5 + 15, 0);
		glVertex3f(_winWidth - _winWidth/5 - 15, 0, 0);
		glEnd();
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
	}
} //namespace asteroids


