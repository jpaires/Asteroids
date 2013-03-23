#include "Ship2.h"
#include "Physics.h"
#include "WeaponsManager.h"

namespace asteroids {
	
	Ship2::Ship2(std::string id) : Ship(id){
		}
		Ship2::~Ship2() {
		}
		void Ship2::init() {
			Ship::init();
			_playerNumber = 2;
			_initialPosition = cg::Vector2d(_winWidth/2, _winHeight/2 - 80);
			_physics->setPosition(_initialPosition);
			_physics->setAngle(PI);
			_enemy = _ship1 = (Ship *) cg::Registry::instance()->get("Ship");
		}
		
		void Ship2::draw() {			
			glClear (GL_DEPTH_BUFFER_BIT);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			_physics->placeOnWorld(0, 0, 1);
			glRotated(90, 1.0, 0.0, 0.0); // axis conversion
			GLfloat ambient[] = {0.2, 0.3, 0.3, 1};
			GLfloat diffuse[] = {0.5, 0.5, 0.3, 1};
			GLfloat specular[] = {0.3, 0.2, 0.2, 1};
			glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
			glShadeModel(GL_SMOOTH);
			glmDraw(_modelShip, GLM_SMOOTH);
			if (_invincibility) {
				glPushMatrix();
				glLoadIdentity();
				GLfloat ambient[] = {0.1, 0.1, 0.1, 1};
				GLfloat diffuse[] = {0.2, 0.2, 0, 0.9 * _invincibility/_invlimit};
				GLfloat specular[] = {0.1, 0.1, 0.1, 1};
				glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
				glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
				glShadeModel(GL_SMOOTH);
				glTranslatef( _physics->getXPosition(), _physics->getYPosition(), 0.0);
				glEnable (GL_BLEND);	// shield's Transparency
				glBlendFunc (GL_SRC_ALPHA, GL_ONE); 
				glutSolidSphere(_shieldrad,15,15);
				glDisable(GL_BLEND);
				glPopMatrix();
			}
			if (_isCharging == 1 && _energy > 0) {
				glPushMatrix();
				glLoadIdentity();
				GLfloat ambient[] = {0.8, 0.2, 0.2, 1};
				GLfloat diffuse[] = {0.5, 0.2, 0.2, 0.2 * _chargeTime/_chargeMaxTime};
				GLfloat specular[] = {0.5, 0.2, 0.1, 1};
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
				glShadeModel(GL_SMOOTH);
				glTranslatef( _physics->getXPosition()+ _chargeDistance*sin(- (_physics->getAngle())), _physics->getYPosition() + _chargeDistance*cos(-(_physics->getAngle())), 0.0);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				glutSolidSphere(20, 20, 20);
				glDisable(GL_BLEND);
				glPopMatrix();
			}
			glPopMatrix();			
		}


		void Ship2::drawOverlay() {
			glDisable(GL_LIGHTING);
			glColor3d(0.9,0.1,0.1);
			cg::Util::instance()->drawBitmapString("Player 2\n", _winWidth - 130, _winHeight - 20);
			glColor3d(1,1,1);
			std::ostringstream os;
			if (_duel) os << "Kills: " << _kills;
			else os << "Score: " << _score;
			std::string str = os.str();
			cg::Util::instance()->drawBitmapString(str, _winWidth - 130, _winHeight - 30);
			os.str("");
			os << "Lives: " << _lives;
			str = os.str();
			cg::Util::instance()->drawBitmapString(str, _winWidth - 130, _winHeight - 40);
			os.str("");
			os << "Mines: " << _mineAmmo;
			str = os.str();
			cg::Util::instance()->drawBitmapString(str, _winWidth - 70, _winHeight - 40);
			os.str("");
			os << "Speed: " << length(_physics->getVelocity()) << " Zegatrons";
			str = os.str();
			cg::Util::instance()->drawBitmapString(str, _winWidth - 130, _winHeight - 50);
			os.str("");
			cg::Util::instance()->drawBitmapString("Energy: ", _winWidth - 130, _winHeight - 60);
			int LarguraBarraEnergia = 2 + (_energy/_maxEnergy)* (_shieldbar - 2);
			cg::Vector3d corDireita = cg::Vector3d(1- (_energy/_maxEnergy), (_energy/_maxEnergy),0);
			drawBar(_winWidth - 130, _winWidth - 130 + LarguraBarraEnergia, _winHeight - 65, _winHeight - 75, cg::Vector3d(1,0,0), corDireita);
			glEnable(GL_LIGHTING);			
		}

		void Ship2::update(unsigned long elapsed_millis) {
			Ship::update(elapsed_millis);
			if (_ship1->isColliding(_physics->getPosition(),_shieldrad)) {
				if(_ship1->isInvincible() && isInvincible()) {
					cg::Vector2d collisionPoint = cg::Vector2d( (getXposition() + _ship1->getXposition())/2 , (getYposition() + _ship1->getYposition())/2);
					cg::Vector2d ship2Velocity = getVelocity();
					shock(collisionPoint, 0.5 * _ship1->getMass()*length(_ship1->getVelocity()));
					_ship1->shock(collisionPoint, 0.5 * _physics->getMass()*length(ship2Velocity));
					return;
				}
				explode();
				return;
			}
		}
				
		void Ship2::onKeyPressed(unsigned char key){
			switch(key) {
				case 'w':			_thrust = 1;
									break;
				case 'a':			_rotDirection = LEFT;
									break;
				case 'd':			_rotDirection = RIGHT;
									break;
				case 'f':			_isCharging = 1;
									break;
				case 'e':			if (_mineAmmo > 0) {
										_mineAmmo--;
										_weaponsManager->addMine(_playerNumber, _physics->getPosition(), _physics->getAngle());
									}
									break;
				case 'g':			_physics->setPosition(randomBetween(0, _winWidth), randomBetween(0, _winHeight));
									break;
				}
		}
		void Ship2::onKeyReleased(unsigned char key) {
			switch(key) {
				case 'w':			_thrust = 0;
									break;
				case 'a':			_rotDirection = 0;
									break;
				case 'd':			_rotDirection = 0;
									break;
				case 'f':			if (_isCharging) {
										shotMissile();
										_isCharging = 0;
										_chargeTime = 0;
									}
									break;
				}
		}

} //namespace asteroids
