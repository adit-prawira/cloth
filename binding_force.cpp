#include "binding_force.hpp"

// std
#include <cmath>

namespace entities {
  BindingForce::BindingForce(entities::Particle* currentParticle, entities::Particle* nextParticle): currentParticle(currentParticle), nextParticle(nextParticle) {
    sf::Vector2f delta = this->nextParticle->position - this->currentParticle->position;
    this->initialLength = std::hypot(delta.x, delta.y);
    this->active = true;
  }

  void BindingForce::apply(){
    if(!this->active) return;
    sf::Vector2f delta = this->nextParticle->position - this->currentParticle->position;
    float currentLength = std::hypot(delta.x, delta.y);
    float deltaDistance = (currentLength - this->initialLength)/currentLength;
    sf::Vector2f correction = 0.5f * delta * deltaDistance;

    // current particle's vector point toward the next particle
    // only apply position correction of unpinned particles
    if(!this->currentParticle->isPinned) this->currentParticle->position += correction;

    // next particle's vector point toward the current particle
    // only apply position correction of unpinned particles
    if(!this->nextParticle->isPinned) this->nextParticle->position -= correction;
  }

  void BindingForce::deactivate(){
    this->active = false;
  }

  bool BindingForce::isActive(){
    return this->active;
  }
}