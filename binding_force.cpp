#include "binding_force.hpp"

// std
#include <cmath>

namespace entities {
  BindingForce::BindingForce(entities::Particle* currentParticle, entities::Particle* nextParticle): currentParticle(currentParticle), nextParticle(nextParticle) {
    sf::Vector2f delta = this->nextParticle->position - this->currentParticle->position;
    this->initialLength = std::hypot(delta.x, delta.y);
  }

  void BindingForce::apply(){
    sf::Vector2f delta = this->nextParticle->position - this->currentParticle->position;
    float currentLength = std::hypot(delta.x, delta.y);
    float deltaDistance = (currentLength - this->initialLength)/currentLength;
    sf::Vector2f correction = 0.5f * delta * deltaDistance;

    // current particle's vector point toward the next particle
    this->currentParticle->position += correction;

    // next particle's vector point toward the current particle
    this->nextParticle->position -= correction;
  }
}