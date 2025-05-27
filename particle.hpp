#pragma once

#include <SFML/Graphics.hpp>

namespace entities {
  class Particle {
    public:
      Particle(float x, float y);
      sf::Vector2f position;

      void applyGravity(const sf::Vector2f &gravity);
      void update(float timeStep);
      void constraintByBound(float width, float height, float radius);

    private: 
      sf::Vector2f previousPosition;
      sf::Vector2f acceleration;
  };
}