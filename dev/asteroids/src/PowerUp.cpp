#include "PowerUp.h"
#include "PowerUpsManager.h"
#include "Physics.h"
#include "Ship.h"

namespace asteroids {
	
	PowerUp::PowerUp(std::string id, cg::Vector2d position, bool random) : cg::Entity(id) {
		_initPosition = position;
		_powerUpsManager =(PowerUpsManager*)cg::Registry::instance()->get("PowerUpsManager");
		_life = cg::Properties::instance()->getDouble("PUPLIFE");
		_random = random;
	}

	PowerUp::~PowerUp() {
	}

	void PowerUp::init() {
		_powerUpsManager = (PowerUpsManager*)cg::Registry::instance()->get("PowerUpsManager");
		_physics = new Physics(_initPosition, cg::Vector2d(randomBetween(-10,10),randomBetween(-10,10)), 10, 1);
	}
	
	void PowerUp::draw() {
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glClear(GL_DEPTH_BUFFER_BIT);
			glShadeModel(GL_SMOOTH);
			glDisable(GL_LIGHTING);	
			_physics->placeOnWorld(1, 1, 0);
			glEnable( GL_TEXTURE_2D );
			glColor4d(1,1,1,1);
			glBindTexture( GL_TEXTURE_2D, _texture ); //bind our texture to our shape
			glBegin (GL_QUADS);
			// Front Face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10, -10,  10);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 10, -10,  10);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 10,  10,  10);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10,  10,  10);
			// Back 
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-10, -10, -10);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-10,  10, -10);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 10,  10, -10);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 10, -10, -10);
			// Top Face
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10,  10, -10);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10,  10,  10);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 10,  10,  10);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 10,  10, -10);
			// Bottom Face
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-10, -10, -10);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 10, -10, -10);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 10, -10,  10);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-10, -10,  10);
			// Right face
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 10, -10, -10);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 10,  10, -10);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 10,  10,  10);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 10, -10,  10);
			// Left Face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10, -10, -10);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-10, -10,  10);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-10,  10,  10);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10,  10, -10);
			glEnd();
			glPopMatrix();
			glDisable( GL_TEXTURE_2D );
			glEnable(GL_LIGHTING);
	}

	int PowerUp::isColliding(cg::Vector2d position, int radius, Ship *ship) {
		if (_physics->isColliding(position, radius)) {
			_powerUpsManager->removeParticle(cg::Entity::getId());
			return 1;
		}
		return 0;
	}


	void PowerUp::update(unsigned long elapsed_millis) {
			_physics->updatePosition(elapsed_millis);
			_life -= elapsed_millis;
			if (_life <= 0) {
				_powerUpsManager->removeParticle(cg::Entity::getId());
				return;
			}
			_physics->updatePosition(elapsed_millis);
			_physics->updateAngle(100);
		}
} //namespace asteroids