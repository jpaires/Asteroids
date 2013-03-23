#include "ThrustParticle.h"
#include "Physics.h"
#include "ThrustJet.h"
#include "Ship.h"

namespace asteroids {
	ThrustParticle::ThrustParticle(std::string id, cg::Vector2d position, cg::Vector2d velocity, double angle, ThrustJet* thrustJet) : Entity(id) {
		_initialPosition = position;
		_velocity = velocity;
		_angle = angle;
		_thrustJet = thrustJet;
		init();
	}

	ThrustParticle::~ThrustParticle() {
	}

	void ThrustParticle::init() {
		_maxlife = 50; /*randomBetween(5, 10);*/
		_life = _maxlife;
		//_angle += randomBetween(-PI/8, PI/8);
		_physics = new Physics(_initialPosition, _velocity, 0, 0);
		_physics->setPosition(_initialPosition - cg::Vector2d(15*sin(-_angle), 15*cos(-_angle)));
		_physics->updatePosition(40);
		//_physics->setVelocity(cg::Vector2d(0,0));
		_physics->setVelocity(cg::Vector2d(randomBetween(-50, 50), randomBetween(-50, 50)));
		_physics->updatePosition(40);
	}

	void ThrustParticle::draw() {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		
		GLfloat color[4] = {0, 0, 0.3, 0.8};

		if (_life > _maxlife/2) {
			color[0] = 0.4;
			color[1] = 0.4;
			color[2] = 0.6;
			color[3] = 0.5;
		} else if (_life > _maxlife/6) {
			color[0] = 0.2;
			color[1] = 0.2;
			color[2] = 0.6;
			color[3] = 0.5;
		}

		GLfloat specular[] = {0.2, 0.2, 0.2, 1};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		glShadeModel(GL_SMOOTH);
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		_physics->placeOnWorld(0, 0, 0);
		glutSolidSphere(4 * _life/_maxlife, 15, 15);
		glPopMatrix();
		glDisable(GL_BLEND);
	}

	void ThrustParticle::update(unsigned long elapsed_millis) {
		_life -= elapsed_millis;
		if (_life <= 0) {
			_thrustJet->removeParticle(cg::Entity::getId());
		}
		_physics->updatePosition(elapsed_millis);
	}

} // namespace asteroids