#pragma once
#include "particle.hpp"

namespace entities {
	class BindingForce {
		public:
			entities::Particle* currentParticle;
			entities::Particle* nextParticle;

			BindingForce(entities::Particle *currentParticle, entities::Particle *nextParticle);
			void apply();

		private:
			
			float initialLength;
	};
}
