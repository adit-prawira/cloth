#pragma once

#include "particle.hpp"
#include "binding_force.hpp"

// std
#include <vector>

namespace cloth{
  class App {
    public: 
      App(const int& gridSize);

      void run();

    private:
      std::vector<entities::Particle> particles;
      std::vector<entities::BindingForce> bindingForces;
      sf::RenderWindow window;

      int size;

      void initialise(const int& row, const int& col);
      void applyMotion();
      void draw();

  };
}
