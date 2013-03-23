#include "Weapon.h"
#include "WeaponsManager.h"
#include "Physics.h"
#include "Mine.h"

namespace asteroids {
	
	Mine::Mine(std::string id, int playernumber, cg::Vector2d position, double angle) : Weapon(id, playernumber, position, angle)  {
			init();
		}

		Mine::~Mine() {
		}

		void Mine::init() {
			_shotColliding = 0;
			_mineInit = cg::Properties::instance()->getDouble("MINEINIT");
			Weapon::init();
			_physics = new Physics(_initPosition,
					cg::Vector2d(0,0), cg::Properties::instance()->getDouble("MINESIZE"), cg::Properties::instance()->getDouble("MINEMASS"));
			_physics->setPosition(_initPosition + cg::Vector2d(_mineInit*sin(-_initAngle), _mineInit*cos(-_initAngle))); // go back a little
			_modelMine = _weaponsManager->getModelMine();
		}

		void Mine::draw() {
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
		
			glClear(GL_DEPTH_BUFFER_BIT);	
			
			GLfloat ambient[] = {0.2, 0.2, 0.2, 1};
			GLfloat diffuse[] = {0.2, 0.2, 0.2, 1};
			GLfloat specular[] = {0.3, 0.3, 0.4, 1};
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
			glShadeModel(GL_SMOOTH);
	
			_physics->placeOnWorld(1, 0, 1);
		
			glmDraw(_modelMine, GLM_SMOOTH);
			glPopMatrix();
		}

		void Mine::update(unsigned long elapsed_millis) {
			_physics->updateAngle(300);
			
			/*int _shotColliding = _weaponsManager->isColliding(_physics->getPosition(), MINESIZE);

			if ( _shotColliding != 0) {
				explode();
				return;
			}*/
		}

		void Mine::explode() {
			_weaponsManager->removeParticle(Entity::getId());
		}

		
		
} //namespace asteroids
