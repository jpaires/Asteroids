#include "Asteroid.h"
#include "Physics.h"
#include "Ship.h"
#include "Ship2.h"
#include "AsteroidsManager.h"
#include "DebrisManager.h"
#include "ExplosionManager.h"
#include "WeaponsManager.h"
#include "PowerUpsManager.h"

namespace asteroids {
		Asteroid::Asteroid(std::string id, int minradius, int maxradius) : 
				cg::Entity(id), _minradius(minradius), _maxradius(maxradius) {
					cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
					_posx = randomBetween(0, win.width);
					_posy = randomBetween(0, win.height);
					init();
		}

		Asteroid::Asteroid(std::string id, int minradius, int maxradius, double posx, double posy) : 
				cg::Entity(id), _minradius(minradius), _maxradius(maxradius) {
					_posx = posx;
					_posy = posy;
					init();
		}
		
		Asteroid::~Asteroid() {
			delete _physics;
		}
		
		void Asteroid::init() {
		
			int sides = randomBetween(cg::Properties::instance()->getDouble("MINSIDES"),
								cg::Properties::instance()->getDouble("MAXSIDES"));

			_anglestep = cg::Properties::instance()->getDouble("ASTANGSTEP");
			int i, r, x, y, z;
			double theta;
			_medradius = 0;
			for (i=0; i < sides; i++) {
				theta = 2 * PI / sides * i;
				r = randomBetween(_minradius, _maxradius);
				_medradius += r;
				x = (int) -(r * sin(theta));
				y = (int) (r * cos(theta));
				z = randomBetween(-_maxradius, _maxradius);
				_points.push_back(cg::Vector3d(x, y, z));
			}
			
           _points.push_back(_points[0]);
			
			
			_medradius = _medradius / sides;
			_asteroidsManager = (AsteroidsManager*)cg::Registry::instance()->get("AsteroidsManager");
			_weaponsManager = (WeaponsManager*)cg::Registry::instance()->get("WeaponsManager");
			_debrisManager = (DebrisManager*) cg::Registry::instance()->get("DebrisManager");
			_explosionManager = (ExplosionManager*) cg::Registry::instance()->get("ExplosionManager");
			_powerUpsManager = (PowerUpsManager*) cg::Registry::instance()->get("PowerUpsManager");
			_ship1 = (Ship*)cg::Registry::instance()->get("Ship");
			_ship2 = (Ship2*)cg::Registry::instance()->get("ShipTwo");
			_mass = cg::Properties::instance()->getDouble("ASTMASS");
			_physics = new Physics(cg::Vector2d(_posx, _posy),
									cg::Vector2d(randomBetween(-200 + _medradius, 200 - _medradius)*1.5, 
									randomBetween(-200 + _medradius, 200 - _medradius)*1.5), _medradius, _mass);
									
			_physics->setAngle(randomBetween(0, 2 * PI));
		
			_topVertex = randomBetween(_medradius/4, _medradius/2); 
			_downVertex = randomBetween(_medradius/4, _medradius/2); 

			_rotx = cg::Properties::instance()->getDouble("ROTX");
			_roty = cg::Properties::instance()->getDouble("ROTY");
			_rotz = cg::Properties::instance()->getDouble("ROTZ");
		}
		
		void Asteroid::draw() {
			
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
		
			glClear(GL_DEPTH_BUFFER_BIT);	
			
			GLfloat ambient[] = {0.2, 0.2, 0.2, 1};
			GLfloat diffuse[] = {0.4, 0.4, 0.4, 1};
			GLfloat specular[] = {0.2, 0.2, 0.2, 1};
			glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
			glShadeModel(GL_SMOOTH);

			_physics->placeOnWorld(_rotx, _roty, _rotz);
			
			
			glBegin(GL_TRIANGLE_FAN);
				glNormal3f (0, 0, 1);
				glVertex3f (0, 0, _minradius/2 + _topVertex);
				unsigned int i = 0;
				for (i=0; i < _points.size(); i++) {
					double leng = length(cg::Vector3d((_points[i])[0], (_points[i])[1], 0));
					glNormal3f ((_points[i])[0]/leng, (_points[i])[0]/leng, 0);
					glVertex3f((_points[i])[0], (_points[i])[1], _minradius/2);
				}
				glNormal3f (0, 0, 1);
				glVertex3f(0, 0, 20);
				glEnd();
			
			glBegin(GL_TRIANGLE_FAN);
				glNormal3f (0, 0, -1);
				glVertex3f (0, 0, -_minradius/2 - _downVertex);
				for (i=0; i < _points.size(); i++) {
					double leng = length(cg::Vector3d((_points[i])[0], (_points[i])[1], 0));
					glNormal3f ((_points[i])[0]/leng, (_points[i])[0]/leng, 0);
					glVertex3f((_points[i])[0], (_points[i])[1], -_minradius/2);
				}
				glNormal3f (0, 0, -1);
				glVertex3f(0, 0, -20);
				glEnd();

			glBegin(GL_QUAD_STRIP);
			for (i=0; i < _points.size(); i++) {
				double leng = length(cg::Vector3d((_points[i])[0], (_points[i])[1], 0));
				glNormal3f ((_points[i])[0]/leng, (_points[i])[0]/leng, 0);
				glVertex3f((_points[i])[0], (_points[i])[1], -_minradius/2);
				
				glNormal3f ((_points[i])[0]/leng, (_points[i])[0]/leng, 0);
				glVertex3f((_points[i])[0], (_points[i])[1], +_minradius/2);
			}

			glEnd();
			glPopMatrix();
		}
	
		void Asteroid::update(unsigned long elapsed_millis) {
			_physics->updatePosition(elapsed_millis);
			_physics->updateAngle(_anglestep);
			int _shotColliding = _weaponsManager->isColliding(_physics->getPosition(), _medradius);
			
			if ( _shotColliding == 1) {
				_ship1->addScore(getScore());
				explode();
				return;
			}

			if ( _shotColliding == 2) {
				_ship2->addScore(getScore());
				explode();
				return;
			}
			
			if (_ship1->isInvincible() && _ship1->isColliding(_physics->getPosition(), _medradius)) {
				cg::Vector2d collisionPoint = _physics->getCollisionPoint(_ship1->getPosition());
				double Force = _physics->getMass()*length(_physics->getVelocity());
				shock(collisionPoint);
				_ship1->shock(collisionPoint, Force);
				/*_ship1->addScore(getScore());
				explode();*/
				return;
			}
			_ship1->isColliding(_physics->getPosition(), _medradius);

			if (_ship2->isInvincible() && _ship2->isColliding(_physics->getPosition(), _medradius)) {
				cg::Vector2d collisionPoint = _physics->getCollisionPoint(_ship2->getPosition());
				double Force = _physics->getMass()*length(_physics->getVelocity());
				shock(collisionPoint);
				_ship2->shock(collisionPoint, Force);
				/*_ship1->addScore(getScore());
				explode();*/
				return;
			}
			_ship2->isColliding(_physics->getPosition(), _medradius);
		}

		void Asteroid::explode() {
			_asteroidsManager->removeParticle(Entity::getId());
			_debrisManager->debrisExplosion(_physics->getXPosition(), _physics->getYPosition());
			_explosionManager->explosion(_physics->getXPosition(), _physics->getYPosition());
			if (_medradius > cg::Properties::instance()->getInt("MINDIMENSION")) {
				_asteroidsManager->addAst(_medradius/2, _medradius/1.2, _physics->getXPosition() + randomBetween(-20, 20), _physics->getYPosition() + randomBetween(-20, 20));
				_asteroidsManager->addAst(_medradius/2, _medradius/1.2, _physics->getXPosition() + randomBetween(-20, 20), _physics->getYPosition() + randomBetween(-20, 20));
			}
			_powerUpsManager->addPowerUp(_physics->getXPosition()+ randomBetween(-20, 20), _physics->getYPosition()+ randomBetween(-20, 20));
		}

		double Asteroid::getScore() {
			return _medradius;
		}

	void Asteroid::shock(cg::Vector2d collisionPoint) {
		cg::Vector2d velocity = _physics->getVelocity();
		_physics->setVelocity(cg::Vector2d(0,0));
		_physics->shock(collisionPoint,_physics->getMass()*length(velocity));
	}

	double Asteroid::getXPosition() {
		return _physics->getXPosition();
	}

	double Asteroid::getYPosition() {
		return _physics->getYPosition();
	}

} //namespace asteroids
