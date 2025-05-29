#include "input_handler.hpp"
#include "constant.hpp"

// std
#include <iostream>
#include <cmath>

namespace controls {
  // Publics
  void InputHandler::handleMouseClick(const sf::RenderWindow& window, std::vector<entities::Particle>& particles, std::vector<entities::BindingForce>& bindingForces){
      bool isMouseLeftClick = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
      bool isMouseRightClick = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
      sf::Vector2i position = sf::Mouse::getPosition(window);
      float mouseCursorX = static_cast<float>(position.x);
      float mouseCursorY = static_cast<float>(position.y);

      if(isMouseLeftClick) controls::InputHandler::dragParticle(mouseCursorX, mouseCursorY, particles);

      if(isMouseRightClick) controls::InputHandler::tearCloth(mouseCursorX, mouseCursorY, bindingForces);

  }

  // Privates
  void InputHandler::dragParticle(float mouseCursorX, float mouseCursorY, std::vector<entities::Particle>& particles){
    for(auto &particle:particles){
      sf::Vector2f circleCenter = particle.position + sf::Vector2f(particle.getRadius(), particle.getRadius());
      float deltaX = mouseCursorX  - circleCenter.x;
      float deltaY = mouseCursorY - circleCenter.y;
      float distance = std::sqrt((deltaX*deltaX) + (deltaY*deltaY));
      bool isParticleClicked = distance <= (particle.getRadius() * particle.getRadius());
      if(isParticleClicked && !particle.isPinned){
        particle.setPosition(mouseCursorX, mouseCursorY);
      }
    }
  }

  void InputHandler::tearCloth(float mouseCursorX, float mouseCursorY, const std::vector<entities::BindingForce>& bindingForces){  
      entities::BindingForce* nearestBindingForce = controls::InputHandler::findNearestBindingForce(mouseCursorX, mouseCursorY, bindingForces);
    
      // binding force touched by mouse is found
      if(nearestBindingForce)  nearestBindingForce->deactivate();
  }

  entities::BindingForce* InputHandler::findNearestBindingForce(float mouseCursorX, float mouseCursorY, const std::vector<entities::BindingForce>& bindinForces){
    entities::BindingForce* nearestBindingForce = nullptr;
    float minimumDistance = constants::CLICK_TOLERANCE;
    for(const auto &bindingForce : bindinForces){
      float distance = controls::InputHandler::pointToSegmentDistance(
        mouseCursorX, 
        mouseCursorY, 
        bindingForce.currentParticle->position.x, 
        bindingForce.currentParticle->position.y,
        bindingForce.nextParticle->position.x, 
        bindingForce.nextParticle->position.y
      );
      if(distance < minimumDistance) {
        // set bindingForce and new minimum distance when mouse click 
        // touch the binding force line
        minimumDistance = distance;
        nearestBindingForce = const_cast<entities::BindingForce*>(&bindingForce);
      }
    }
    return nearestBindingForce;
  }

  float InputHandler::pointToSegmentDistance(float px, float py, float ax, float ay, float bx, float by){
    float ABx = bx - ax;
    float ABy = by - ay;

    float APx = px - ax;
    float APy = py - ay;

    float BPx = px - bx;
    float BPy = py - by;

    float dAB_AP = (ABx * APx) + (ABy * APy);
    float dAB_BP = (ABx * BPx) + (ABy * BPy);
    float m = dAB_AP / dAB_BP;

    // mouse cursor closer to point A
    if(m < 0.0f) return std::sqrt((APx*APx) + (APy*APy));

    // mouse cursor closer to point B    
    if (m > 1.0f) return std::sqrt((BPx * BPx) + (BPy * BPy));

    // mouse cursor on line segment
    float projectionX = ax + m*ABx;
    float projectionY = ay + m*ABy;
    float deltaX = px - projectionX;
    float deltaY = py - projectionY;
    return std::sqrt((deltaX * deltaX) + (deltaY*deltaY));
  }


}