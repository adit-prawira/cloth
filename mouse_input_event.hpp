#include <SFML/Graphics.hpp>
#include "particle.hpp"
#include "binding_force.hpp"

// std
#include <vector>
#include <cmath>

namespace controls {
	class MouseInputEvent {
		public:
			static void stream(const sf::RenderWindow& window, std::vector<entities::Particle>& particles, std::vector<entities::BindingForce>& bindingForces);
		private:
			static bool isDragging;
			static size_t draggingIndex;
			static sf::Vector2f dragOffset;

			static void dragParticle(float mouseCursorX, float mouseCursorY, std::vector<entities::Particle>& particles);
			static void tearCloth(float mouseCursorX, float mouseCursorY, const std::vector<entities::BindingForce>& bindingForces);
			static entities::BindingForce* findNearestBindingForce(float mouseCursorX, float mouseCursorY, const std::vector<entities::BindingForce>& bindinForces);
			static float pointToSegmentDistance(float px, float py, float ax, float ay, float bx, float by);
			static void resetDragState();
	};
}
