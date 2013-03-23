#ifndef PARTICLESMANAGER_H_
#define PARTICLESMANAGER_H_

#include <string>
#include <vector>
#include "cg/cg.h"


namespace asteroids {
	template<class P>
	class ParticlesManager : public cg::Group, public cg::GroupDraw, public cg::GroupUpdate {
		protected:
			int _particlesCounter, _createdCounter;
			std::vector<std::string> _toRemove;
			std::vector<P*> _toAdd;
			std::string _baseId;
		public:
			ParticlesManager(std::string id, std::string baseId) : cg::Group(id) {
				_createdCounter = 0;
				_baseId = baseId;
			}

			~ParticlesManager() {}

			void createEntities() {}

			void postUpdate(unsigned long elapsed_millis) {
				unsigned int i = 0;
				
				for (i = 0; i < _toAdd.size(); i++) {
					add((cg::Entity*) _toAdd[i]);	
				}
				_toAdd.clear();

				for (i = 0; i < _toRemove.size(); i++) {
					destroy(_toRemove[0]);
				}
				_toRemove.clear();
			}
			
			void removeParticle(std::string id) {	_toRemove.push_back(id); }
			
			void addParticle(P *particle)		{	_toAdd.push_back(particle); }
			
			std::string ParticlesManager::getNewId() {
				std::string str = _baseId;
				std::stringstream out;
				out << ++_createdCounter;	
				return str.append(out.str());
			}

			void reset() { destroyAll(); }

	};
}	//namespace asteroids

#endif 