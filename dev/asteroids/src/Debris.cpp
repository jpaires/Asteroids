#include "Debris.h"
#include "Physics.h"
#include "DebrisCloud.h"

namespace asteroids {
	Debris::Debris(std::string id, double posx, double posy, DebrisCloud* debrisCloud) : Entity(id) {
		_initialPosition = cg::Vector2d(posx, posy);
		_debrisCloud = debrisCloud;
		init();
	}

	Debris::~Debris() {
	}

	void Debris::init() {
		_life = randomBetween(800, 1000);
		_physics = new Physics(_initialPosition,
						cg::Vector2d(randomBetween(-30, 30), 
						randomBetween(-30, 30)), 0, 0);
		_physics->setAngle(randomBetween(0, 2 * PI));
	}

	void Debris::draw() {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		
		GLfloat ambient[] = {0.2, 0.2, 0.2, 1};
		GLfloat diffuse[] = {0.2, 0.2, 0.2, 1};
		GLfloat specular[] = {0.2, 0.2, 0.2, 1};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
		glShadeModel(GL_SMOOTH);
		
		glDisable(GL_DEPTH_TEST);
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
		_physics->placeOnWorld(1, 1, 0);
		glutSolidCube(3);
		glPopMatrix();
		//glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	}

	void Debris::update(unsigned long elapsed_millis) {
		_life -= elapsed_millis;
		if (_life <= 0) {
			_debrisCloud->removeParticle(cg::Entity::getId());
		}
		_physics->updatePosition(elapsed_millis);
	}

} // namespace asteroids