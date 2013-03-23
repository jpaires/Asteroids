#include "Ship.h"
#include "Physics.h"
#include "WeaponsManager.h"
#include "ThrustManager.h"
#include "ExplosionManager.h"
#include "PowerUpsManager.h"
#include "GameMaster.h"

namespace asteroids {
		Ship::Ship(std::string id) : cg::Entity(id), _thrust(0), _score(0), _kills(0), _rotDirection(0) {
			
		}
		Ship::~Ship() {
			delete _physics;
			glmDelete(_modelShip);
		}
		void Ship::init() {
			_playerNumber = 1;
			_weaponsManager = (WeaponsManager*)cg::Registry::instance()->get("WeaponsManager");
			_thrustManager = (ThrustManager*)cg::Registry::instance()->get("ThrustManager");
			_explosionManager = (ExplosionManager*)cg::Registry::instance()->get("ExplosionManager");
			_powerUpsManager = (PowerUpsManager*)cg::Registry::instance()->get("PowerUpsManager");
			_gameMaster = (GameMaster*)cg::Registry::instance()->get("GameMaster");
			_enemy = (Ship*)cg::Registry::instance()->get("ShipTwo");
			_mouseControl = cg::Properties::instance()->getInt("MOUSECONTROL");
			_anglestep = cg::Properties::instance()->getDouble("SHIPANGSTEP");
			cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
			_winWidth = win.width;
			_winHeight = win.height;
			_astep = cg::Properties::instance()->getDouble("ASTEP");
			_alimit = cg::Properties::instance()->getDouble("ALIMIT");
			_dstep = cg::Properties::instance()->getDouble("DSTEP");
			_dlimit = cg::Properties::instance()->getDouble("DLIMIT");
			_shieldrad = cg::Properties::instance()->getDouble("SHIELDRAD");
			_shieldbar = cg::Properties::instance()->getDouble("SHIELDBAR");
			_shiprad = cg::Properties::instance()->getDouble("SHIPRAD");
			_invlimit = cg::Properties::instance()->getDouble("MAX_INV");
			_thrustDisableLimit = cg::Properties::instance()->getDouble("THRUSTDISABLE");
			_shootingDisableLimit = cg::Properties::instance()->getDouble("SHOOTDISABLE");
			_lives = cg::Properties::instance()->getInt("LIVES");
			_mass = cg::Properties::instance()->getDouble("SHIPMASS");
			_mineAmmo = cg::Properties::instance()->getDouble("MINEAMMO");
			_invincibility = _invlimit;
			_shotLevel = 0;
			_initialPosition = cg::Vector2d(_winWidth/2, _winHeight/2);
			_physics = new Physics(_initialPosition, cg::Vector2d(0,0), _shiprad, _mass);
			_maxEnergy = cg::Properties::instance()->getDouble("CHARGEENERGY");
			_energy = _maxEnergy;
			_chargeConsume = cg::Properties::instance()->getDouble("CHARGECONSUME");
			_isCharging = 0;
			_chargeTime = 0;
			_chargeDistance = cg::Properties::instance()->getInt("CHARGEDISTANCE");
			_chargeMaxTime = cg::Properties::instance()->getInt("CHARGEMAXTIME");
			_modelShip = glmReadOBJ("models/nave.obj");
			glmScale(_modelShip, cg::Properties::instance()->getDouble("SCALEFACTOR"));
		}
		void Ship::draw() {
			glClear (GL_DEPTH_BUFFER_BIT);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			_physics->placeOnWorld(0, 0, 1);
			glRotated(90, 1.0, 0.0, 0.0); // axis conversion
			GLfloat ambient[] = {0.3, 0.2, 0.2, 1};
			GLfloat diffuse[] = {0.3, 0.5, 0.5, 1};
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
				GLfloat diffuse[] = {0.1, 0.2, 0.3, 0.9 * _invincibility/_invlimit};
				GLfloat specular[] = {0.1, 0.1, 0.1, 1};
				glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
				glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
				glShadeModel(GL_SMOOTH);
				glTranslatef( _physics->getXPosition(), _physics->getYPosition(), 0.0);
				glEnable (GL_BLEND);	// shield's Transparency
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
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

		void Ship::drawOverlay() {
			glDisable(GL_LIGHTING);
			glColor3d(0.9,0.1,0.1);
			cg::Util::instance()->drawBitmapString("Player 1\n", 10, _winHeight - 20);
			glColor3d(1,1,1);
			std::ostringstream os;
			if (_duel) os << "Kills: " << _kills;
			else os << "Score: " << _score;
			std::string str = os.str();
			cg::Util::instance()->drawBitmapString(str, 10, _winHeight - 30);
			os.str("");
			os << "Lives: " << _lives;
			str = os.str();
			cg::Util::instance()->drawBitmapString(str, 10, _winHeight - 40);
			os.str("");
			os << "Mines: " << _mineAmmo;
			str = os.str();
			cg::Util::instance()->drawBitmapString(str, 70, _winHeight - 40);
			os.str("");
			os << "Speed: " << length(_physics->getVelocity()) << " Zegatrons";
			str = os.str();
			cg::Util::instance()->drawBitmapString(str, 10, _winHeight - 50);
			os.str("");
			cg::Util::instance()->drawBitmapString("Energy: ", 10, _winHeight - 60);
			int LarguraBarraEnergia = 2 + (_energy/_maxEnergy)* (_shieldbar - 2);
			cg::Vector3d corDireita = cg::Vector3d(1- (_energy/_maxEnergy), (_energy/_maxEnergy),0);
			drawBar(10, 10 + LarguraBarraEnergia, _winHeight - 65, _winHeight - 75, cg::Vector3d(1,0,0), corDireita);
			glEnable(GL_LIGHTING);
		}
		
		void Ship::update(unsigned long elapsed_millis) {
			if (_thrust && _thrustDisable == 0 ) {
                _physics->accelerate(_astep, _alimit);
				_thrustManager->thrust(_physics->getPosition(), _physics->getVelocity(), _physics->getAngle());
			} else {
                _physics->decelerate(_dstep, _dlimit);
			}

			_physics->updatePosition(elapsed_millis);
            
			
			if (_rotDirection != 0)
				_physics->updateAngle(_rotDirection * _anglestep);

			if (_invincibility > 0) {
				_invincibility -= elapsed_millis;
				_physics->setSize(_shieldrad);
			} else {
				_invincibility = 0;
				_physics->setSize(_shiprad);
			}
			_powerUpsManager->isColliding(_physics->getPosition(), _shiprad, this);
			if (_weaponsManager->isColliding(_physics->getPosition(), _shiprad) != 0) {
				if (_invincibility == 0) {
					explode();
				} else {
					cg::Vector2d collisionPoint = _weaponsManager->getCollisionPoint(_physics->getPosition(), _shiprad);
					shock(collisionPoint,_weaponsManager->getCollisionForce(_physics->getPosition(), _shiprad));
				}
			}
			if (_isCharging == 1 && _energy > 0) {
				if(_chargeTime >= _chargeMaxTime/5) {
					_energy -= _chargeConsume;
				}
				_chargeTime += elapsed_millis;
				if ( _chargeTime >= _chargeMaxTime) {
					_chargeTime = 0;
					_isCharging = 0;
					_weaponsManager->addChargeShot(_playerNumber, _physics->getPosition(), _physics->getAngle());
				}
			}
			if (_shootingDisable > 0) _shootingDisable -= elapsed_millis;
			if (_shootingDisable < 0) _shootingDisable = 0;
			if (_thrustDisable > 0) _thrustDisable -= elapsed_millis;
			if (_thrustDisable < 0) _thrustDisable = 0;
		}
		
		bool Ship::isColliding(cg::Vector2d position, int radius) {
			if (!state.isEnabled()) return false;
			if (_invincibility > 0) {
				_physics->setSize(_shieldrad);
			} else {
				_physics->setSize(_shiprad);
			}
			if (_physics->isColliding(position, radius)) {
				if (_invincibility == 0) {
					explode();
				}
				return true;
			}
			else return false;
		}

		void Ship::explode() {
			_enemy->addKill();
			_lives--;
			if (_lives == 0) {
				state.disable();
				_gameMaster->shipDied();
				return;
			}
			_explosionManager->explosion(_physics->getXPosition(), _physics->getYPosition());
			_chargeTime = 0;
			_isCharging = 0;
			_shotLevel = 0;
			_physics->setPosition(_initialPosition);
			_physics->setVelocity(0,0);
			_invincibility = _invlimit;
			_thrustDisable = 0;
			_shootingDisable = 0;
		}

		void Ship::shieldRegen(double bonus) {
			_invincibility = _invlimit + bonus;
		}

		void Ship::mineReload() {
			_mineAmmo = cg::Properties::instance()->getDouble("MINEAMMO");
		}

		void Ship::energyRecharge() {
			_energy = _maxEnergy;
		}

		void Ship::shotUpgrade() {
			if(_shotLevel < 2)
				_shotLevel++;
		}

		void Ship::addLife() {
			_lives++;
		}

		void Ship::disableShooting() {
			_shootingDisable = _shootingDisableLimit;
		}

		void Ship::disableThrust() {
			_thrustDisable = _thrustDisableLimit;
		}

		void Ship::shotMissile() {
			if (_shootingDisable > 0) return;
			if(_shotLevel == 0) 
				_weaponsManager->addMissile(_playerNumber, _physics->getPosition(), _physics->getAngle());
			double angleCosFactor = cos(_physics->getAngle());
			double angleSinFactor = sin(_physics->getAngle());
			if(_shotLevel == 1) {
					_weaponsManager->addMissile(_playerNumber, _physics->getPosition() + cg::Vector2d(20*angleCosFactor,20*angleSinFactor), _physics->getAngle());
					_weaponsManager->addMissile(_playerNumber, _physics->getPosition() - cg::Vector2d(20*angleCosFactor,20*angleSinFactor), _physics->getAngle());
			}
			if(_shotLevel >= 2) {
					_weaponsManager->addMissile(_playerNumber, _physics->getPosition() + cg::Vector2d(20*angleCosFactor,20*angleSinFactor), _physics->getAngle()+PI/8);
					_weaponsManager->addMissile(_playerNumber, _physics->getPosition() - cg::Vector2d(20*angleCosFactor,20*angleSinFactor), _physics->getAngle()-PI/8);
					_weaponsManager->addMissile(_playerNumber, _physics->getPosition() , _physics->getAngle());
			}
		}

		bool Ship::isInvincible() {
			if(_invincibility > 0) {
				return true;
			}
			return false;
		}

		void Ship::shock(cg::Vector2d collisionPoint, double Force) {
			_physics->shock(collisionPoint, Force);
		}

		void Ship::onKeyPressed(unsigned char key){
			if (key == '-') {
				_physics->setPosition(randomBetween(0, _winWidth), randomBetween(0, _winHeight));
			}
			if ((key == ',') && (_mouseControl == 0)) {
				if (_mineAmmo > 0) {
					_mineAmmo--;
					_weaponsManager->addMine(_playerNumber, _physics->getPosition(), _physics->getAngle());
				}
			}
			if (key == '.' && !_mouseControl) {
				_isCharging = 1;
			}
		}
		
		void Ship::onKeyReleased(unsigned char key) {
			if (key == '.' && !_mouseControl && _isCharging) {
					shotMissile();
					_isCharging = 0;
					_chargeTime = 0;
			}
		}

		void Ship::onSpecialKeyPressed(int key) {		
			if (_mouseControl == 0) {
				switch(key) {
					case GLUT_KEY_UP:	_thrust = 1;
										break;
					case GLUT_KEY_LEFT:	_rotDirection = LEFT;
										break;
					case GLUT_KEY_RIGHT:_rotDirection = RIGHT;
										break;
				}
			}
		}
		
		void Ship::onSpecialKeyReleased(int key) {
			if (_mouseControl == 0) {
				switch(key) {
					case GLUT_KEY_UP:	_thrust = 0;
										break;
					case GLUT_KEY_LEFT:	_rotDirection = 0;
										break;
					case GLUT_KEY_RIGHT:_rotDirection = 0;
										break;
				}
			}
		}

		void Ship::onMouse(int button, int state, int x, int y) {
			if (_mouseControl) {
				if (button == GLUT_RIGHT_BUTTON) {
					if (state == GLUT_DOWN) _thrust = 1;
					else _thrust = 0;
				} else if (button == GLUT_LEFT_BUTTON) {
					if (state == GLUT_UP && _isCharging) {
						//_weaponsManager->addMissile(_playerNumber, _physics->getPosition(), _physics->getAngle());
						shotMissile();
						_isCharging = 0;
						_chargeTime = 0;
					} else if (state == GLUT_DOWN) _isCharging = 1;
				} else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
					if (_mineAmmo > 0) {
						_mineAmmo--;
						_weaponsManager->addMine(_playerNumber, _physics->getPosition(), _physics->getAngle());
					}
				}
			}
		}

		void Ship::onMouseMotion(int x, int y) {
			if (_mouseControl) {
				cg::Vector2d shipToMouseVector = cg::Vector2d(x, _winHeight - y) - _physics->getPosition();
				double mouseAngle = atan2((double)shipToMouseVector[1], (double)shipToMouseVector[0]);
				mouseAngle -= (PI/2);
				if (mouseAngle < 0) mouseAngle += 2 * PI;
				_physics->setAngle(mouseAngle);
			}
		}

		void Ship::onMousePassiveMotion(int x, int y) {
			if (_mouseControl) {
				cg::Vector2d shipToMouseVector = cg::Vector2d(x, _winHeight - y) - _physics->getPosition();;
				double mouseAngle = atan2((double)shipToMouseVector[1], (double)shipToMouseVector[0]);
				mouseAngle -= (PI/2);
				if (mouseAngle < 0) mouseAngle += 2 * PI;
				_physics->setAngle(mouseAngle);
			}
		}

		double Ship::getXposition() {
			return _physics->getXPosition();
		}

		double Ship::getYposition() {
			return _physics->getYPosition();
		}

		cg::Vector2d Ship::getPosition() {
			return _physics->getPosition();
		}


		double Ship::getAngle(){
			return _physics->getAngle();	
		}

		cg::Vector2d Ship::getVelocity() {
			return _physics->getVelocity();
		}

		double Ship::getMass() {
			return _physics->getMass();
		}

		void Ship::addScore(double score) {
			_score += score;
		}

		double Ship::getScore() {
			return _score;
		}

		void Ship::addKill() {
			_kills++;
		}

		void Ship::reset(bool duel) {
			_duel = duel;
			_score = 0;
			_kills = 0;
			_isCharging = 0;
			_chargeTime = 0;
			_lives = cg::Properties::instance()->getInt("LIVES");
			_thrust = _rotDirection = 0;
			_physics->setPosition(_initialPosition);
			_physics->setVelocity(0,0);
			_invincibility = _invlimit;
			_energy = _maxEnergy;
			_shotLevel = 0;
			_thrustDisable = 0;
			_shootingDisable = 0;
			_mineAmmo = cg::Properties::instance()->getDouble("MINEAMMO");
		}

		bool Ship::isAlive() {
			return (_lives > 0);
		}
} //namespace asteroids
