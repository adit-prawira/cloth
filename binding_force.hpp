#pragma once
#include "particle.hpp"

namespace entities {
	class BindingForce {
		public:
			entities::Particle* currentParticle;
			entities::Particle* nextParticle;

			BindingForce(entities::Particle *currentParticle, entities::Particle *nextParticle);
			void apply();
			bool isActive();
			void deactivate();
		private:
			bool active;
			float initialLength;
	};
}
