#pragma once

#include <SFML/Graphics.hpp>

namespace entities {
  class Particle {
    public:
      Particle(float x, float y);

      void applyGravity(const sf::Vector2f &gravity);
      void update(float timeStep);
      void constraintByBound(float width, float height, float radius);

      sf::Vector2f getPosition(){
        return this->position;
      }
    private: 
      sf::Vector2f position;
      sf::Vector2f previousPosition;
      sf::Vector2f acceleration;
  };
}