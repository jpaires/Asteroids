#include "Weapon.h"
#include "WeaponsManager.h"
#include "Physics.h"
#include "ChargeGun.h"

namespace asteroids {
	
	ChargeGun::ChargeGun(std::string id, int playernumber, cg::Vector2d position, double angle) : Weapon(id, playernumber, position, angle)  {
			init();
		}

		ChargeGun::~ChargeGun() {
		}

		void ChargeGun::init() {
			Weapon::init();
			_life = cg::Properties::instance()->getDouble("CHARGESHOTLIFE");
			_vfactor = cg::Properties::instance()->getDouble("SHOTSPEED");
			_physics = new Physics(_initPosition,
					cg::Vector2d(_vfactor*sin(-_initAngle), _vfactor*cos(-_initAngle)), 
					cg::Properties::instance()->getDouble("CHARGESHOTSIZE"), cg::Properties::instance()->getDouble("CHARGESHOTMASS"));
			_physics->updatePosition(cg::Properties::instance()->getDouble("CHARGEINIT")); // advance a little
			_modelCharge = _weaponsManager->getModelCharge();
			_physics->setAngle(_initAngle - PI/2);
		}

		void ChargeGun::draw() {
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
			glRotated(90, 1.0, 0.0, 0.0);
			//glutSolidSphere(20, 20, 20);			
			glmDraw(_modelCharge, GLM_SMOOTH);
			glPopMatrix();
		}

		void ChargeGun::update(unsigned long elapsed_millis) {
			_life -= elapsed_millis;
			if (_life <= 0) {
				_weaponsManager->removeParticle(cg::Entity::getId());
			}
			_physics->updatePosition(elapsed_millis);
		}

		int ChargeGun::isColliding(cg::Vector2d position, int radius) {
			if (_physics->isColliding(position, radius)) {
				return _playerNumber;
			}
			return 0;
		}

} //namespace asteroids