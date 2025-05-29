#include <SFML/Graphics.hpp>
#include "particle.hpp"
#include "binding_force.hpp"

// std
#include <vector>
#include <cmath>

namespace controls {
	class InputHandler {
		public:
			static void handleMouseClick(const sf::RenderWindow& window, std::vector<entities::Particle>& particles, std::vector<entities::BindingForce>& bindingForces);
		private:
			static void tearCloth(float mouseCursorX, float mouseCursorY, const std::vector<entities::BindingForce>& bindingForces);
			static entities::BindingForce* findNearestBindingForce(float mouseCursorX, float mouseCursorY, const std::vector<entities::BindingForce>& bindinForces);
			static float pointToSegmentDistance(float px, float py, float ax, float ay, float bx, float by);

	};
}
