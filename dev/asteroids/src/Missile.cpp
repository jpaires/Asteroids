#include "Weapon.h"
#include "WeaponsManager.h"
#include "Physics.h"
#include "Missile.h"

namespace asteroids {
	
	Missile::Missile(std::string id, int playernumber, cg::Vector2d position, double angle) : Weapon(id, playernumber, position, angle)  {
			init();
		}

		Missile::~Missile() {
		}

		void Missile::init() {
			Weapon::init();
			_life = cg::Properties::instance()->getDouble("SHOTLIFE");
			_vfactor = cg::Properties::instance()->getDouble("SHOTSPEED");
			_physics = new Physics(_initPosition,
					cg::Vector2d(_vfactor*sin(-_initAngle), _vfactor*cos(-_initAngle)), 
					cg::Properties::instance()->getDouble("SHOTSIZE"), cg::Properties::instance()->getDouble("SHOTMASS"));
			_physics->updatePosition(cg::Properties::instance()->getDouble("SHOTINIT")); // advance a little
			_physics->setAngle(_initAngle + PI);		// 2PI to correct the model
			_modelMissile = _weaponsManager->getModelMissile();
		}

		void Missile::draw() {
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
		
			glClear(GL_DEPTH_BUFFER_BIT);	
			
			GLfloat ambient[] = {0.8, 0.2, 0.2, 1};
			GLfloat diffuse[] = {0.5, 0.2, 0.2, 1};
			GLfloat specular[] = {0.5, 0.2, 0.1, 1};
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
			glShadeModel(GL_SMOOTH);

			_physics->placeOnWorld(0, 0, 1);
			glRotated(90, 1.0, 0.0, 0.0); // axis conversion
			glPushMatrix();
				glTranslated(-10, 0, 0);
				glmDraw(_modelMissile, GLM_SMOOTH);
			glPopMatrix();
				glTranslated(10, 0, 0);
				glmDraw(_modelMissile, GLM_SMOOTH);
			glPopMatrix();
			//glmDraw(_modelMissile, GLM_SMOOTH);
			glPopMatrix();
		}

		void Missile::update(unsigned long elapsed_millis) {
			_life -= elapsed_millis;
			if (_life <= 0) {
				_weaponsManager->removeParticle(cg::Entity::getId());
			}
			_physics->updatePosition(elapsed_millis);
		}

} //namespace asteroids