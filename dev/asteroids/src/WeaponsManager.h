#ifndef WEAPONSMANAGER_H_
#define WEAPONSMANAGER_H_

#include <string>
#include "glm.h"
#include "cg/cg.h"
#include "ParticlesManager.h"

namespace asteroids {
	class Weapon;
	class WeaponsManager : public ParticlesManager<Weapon> {
	private:
		GLMmodel* _modelMissile;
		GLMmodel* _modelMine;
		GLMmodel* _modelCharge;
	public:
		WeaponsManager(std::string id);
		~WeaponsManager();
		void addMissile(int playernumber, cg::Vector2d position, double angle);
		void addMine(int playernumber, cg::Vector2d position, double angle);
		void addChargeShot(int playernumber, cg::Vector2d position, double angle);
		int isColliding(cg::Vector2d position, int radius);
		cg::Vector2d getCollisionPoint(cg::Vector2d position, int radius);
		double getCollisionForce(cg::Vector2d position, int radius);
		GLMmodel* getModelMissile();
		GLMmodel* getModelMine();
		GLMmodel* getModelCharge();
	};
}//namespace asteroids

#endif
