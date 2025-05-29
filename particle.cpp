#include <particle.hpp>
#include "constant.hpp"

// std
#include<iostream>

namespace entities {
  Particle::Particle(float x, float y, bool pinned = false): position(x, y), previousPosition(x, y), acceleration(0,0), isPinned(pinned){}

  void Particle::applyGravity(const sf::Vector2f &gravity){
    if(this->isPinned) return;
    this->acceleration += gravity;
  }
  
  void Particle::update(float timeStep){
    if(this->isPinned) return;
    
    sf::Vector2f velocity = this->position - this->previousPosition;
    this->previousPosition = this->position;
    this->position += velocity + (this->acceleration*(timeStep*timeStep));
    // reset acceleration
    this->acceleration = sf::Vector2f(0.0f, 0.0f);
  };
  
  void Particle::bindingForceByBound(float width, float height, float radius){
    if(this->position.x < radius) this->position.x = radius;
    if(this->position.x > width - radius) this->position.x = width - radius;
    if(this->position.y < radius) this->position.y = radius;
    if(this->position.y > height - radius) this->position.y = height - radius;
  }

  void Particle::setPosition(float x, float y){
    this->position.x = x;
    this->position.y = y;
  }
  
  float Particle::getRadius(){
    return constants::PARTICLE_RADIUS;
  }
}