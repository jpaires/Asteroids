#include "FireParticle.h"
#include "Physics.h"
#include "Explosion.h"

namespace asteroids {
	FireParticle::FireParticle(std::string id, double posx, double posy, Explosion* explosion) : Entity(id) {
		_initialPosition = cg::Vector2d(posx, posy);
		_explosion = explosion;
		init();
	}

	FireParticle::~FireParticle() {
	}

	void FireParticle::init() {
		_maxlife = randomBetween(400, 800);
		_life = _maxlife;
		_physics = new Physics(_initialPosition,
						cg::Vector2d(randomBetween(-20, 20), 
						randomBetween(-20, 20)), 0, 0);
		_physics->setAngle(randomBetween(0, 2 * PI));
	}

	void FireParticle::draw() {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		
		GLfloat color[4];
		color[0] = 0.8;
		color[2] = 0;
		color[3] = 0.1;
		if (_life > _maxlife/2)
			color[1] = 0.7;
		else if (_life > _maxlife/3)
			color[1] = 0.5;
		else if (_life > _maxlife/4)
			color[1] = 0.3;
		else {
			color[1] = 0.2;
		}
		GLfloat specular[] = {0.2, 0.2, 0.2, 1};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		glShadeModel(GL_SMOOTH);
		
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		_physics->placeOnWorld(0, 0, 0);
		glutSolidSphere(20 * (_maxlife - _life) / _maxlife, 15, 15);
		glPopMatrix();
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	}

	void FireParticle::update(unsigned long elapsed_millis) {
		_life -= elapsed_millis;
		if (_life <= 0) {
			_explosion->removeParticle(cg::Entity::getId());
		}
		_physics->updatePosition(elapsed_millis);
	}

} // namespace asteroids