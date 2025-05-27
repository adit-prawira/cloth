#pragma once
#include "particle.hpp"
namespace utilities {
	class Constraint {
		public:
			Constraint(entities::Particle *currentParticle, entities::Particle *nextParticle);

			void apply();
		private:
			entities::Particle* currentParticle;
			entities::Particle* nextParticle;
			float initialLength;
	};
}
