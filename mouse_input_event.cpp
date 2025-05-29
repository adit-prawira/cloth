#include "mouse_input_event.hpp"
#include "constant.hpp"

// std
#include <iostream>
#include <cmath>

namespace controls {
  sf::Vector2f MouseInputEvent::dragOffset = {0.0f, 0.0f};
  size_t MouseInputEvent::draggingIndex = -1;
  bool MouseInputEvent::isDragging = false;

  // Publics
  void MouseInputEvent::stream(const sf::RenderWindow& window, std::vector<entities::Particle>& particles, std::vector<entities::BindingForce>& bindingForces){
      
      bool isMouseLeftClick = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

      bool isMouseRightClick = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
      sf::Vector2i position = sf::Mouse::getPosition(window);
      float mouseCursorX = static_cast<float>(position.x);
      float mouseCursorY = static_cast<float>(position.y);

      if(isMouseLeftClick){
        controls::MouseInputEvent::dragParticle(mouseCursorX, mouseCursorY, particles);
      }else {
        controls::MouseInputEvent::resetDragState();
      }

      if(isMouseRightClick) controls::MouseInputEvent::tearCloth(mouseCursorX, mouseCursorY, bindingForces);


  }

  // Privates
  void MouseInputEvent::dragParticle(float mouseCursorX, float mouseCursorY, std::vector<entities::Particle>& particles){
    
    for(size_t i = 0; i < particles.size(); i ++){
      auto& particle = particles[i];
      sf::Vector2f circleCenter = particle.position + sf::Vector2f(particle.getRadius(), particle.getRadius());
      float deltaX = mouseCursorX  - circleCenter.x;
      float deltaY = mouseCursorY - circleCenter.y;
      float distance = std::sqrt((deltaX*deltaX) + (deltaY*deltaY));
      bool isParticleClicked = distance <= (particle.getRadius() * particle.getRadius());
      if(isParticleClicked && !particle.isPinned){
        controls::MouseInputEvent::draggingIndex = i;
        controls::MouseInputEvent::isDragging = true;
        float offSetX = particle.position.x - mouseCursorX;
        float offSetY = particle.position.y - mouseCursorY;
        controls::MouseInputEvent::dragOffset = {offSetX, offSetY};
      }
    }

    bool isValidToUpdatePosition = controls::MouseInputEvent::isDragging 
      && (controls::MouseInputEvent::draggingIndex != -1) 
      && (controls::MouseInputEvent::dragOffset.x != 0.0f)
      && (controls::MouseInputEvent::dragOffset.y != 0.0f);
    if(isValidToUpdatePosition){
      particles[controls::MouseInputEvent::draggingIndex].setPosition(
        mouseCursorX + controls::MouseInputEvent::dragOffset.x,
        mouseCursorY + controls::MouseInputEvent::dragOffset.y
      );
    }
  }

  void MouseInputEvent::tearCloth(float mouseCursorX, float mouseCursorY, const std::vector<entities::BindingForce>& bindingForces){  
      entities::BindingForce* nearestBindingForce = controls::MouseInputEvent::findNearestBindingForce(mouseCursorX, mouseCursorY, bindingForces);
    
      // binding force touched by mouse is found
      if(nearestBindingForce)  nearestBindingForce->deactivate();
  }

  entities::BindingForce* MouseInputEvent::findNearestBindingForce(float mouseCursorX, float mouseCursorY, const std::vector<entities::BindingForce>& bindinForces){
    entities::BindingForce* nearestBindingForce = nullptr;
    float minimumDistance = constants::CLICK_TOLERANCE;
    for(const auto &bindingForce : bindinForces){
      float distance = controls::MouseInputEvent::pointToSegmentDistance(
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

  float MouseInputEvent::pointToSegmentDistance(float px, float py, float ax, float ay, float bx, float by){
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

  void MouseInputEvent::resetDragState(){
    controls::MouseInputEvent::dragOffset = {0.0f, 0.0f};
    controls::MouseInputEvent::draggingIndex = -1;
    controls::MouseInputEvent::isDragging = false;
  }
}