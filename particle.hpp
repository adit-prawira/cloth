#pragma once

#include <SFML/Graphics.hpp>

namespace entities {
  class Particle {
    public:
      Particle(float x, float y, bool pinned);
      sf::Vector2f position;
      bool isPinned;

      void applyGravity(const sf::Vector2f &gravity);
      void update(float timeStep);
      void bindingForceByBound(float width, float height, float radius);

    private: 
      sf::Vector2f previousPosition;
      sf::Vector2f acceleration;
  };
}