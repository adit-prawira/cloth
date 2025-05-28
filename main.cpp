#include <SFML/Graphics.hpp>
#include "particle.hpp"
#include "binding_force.hpp"

// std
#include <iostream>
#include <vector>
#include <array>


const int WIDTH = 1080;
const int HEIGHT = 640;
const int FRAMERATE_LIMIT = 60;
const float PARTICLE_RADIUS = 10.0f;
const float GRAVITY = 9.81f;
const float TIMES_STEP = 0.1f;

// Grid dimensions
const float DISTANCE = 50.0f;

int main(){
	int gridSize;

	std::cout << "Enter the grid size: " << std::flush;
	std::cin >> gridSize;
	
	const auto& totalRows = gridSize;
	const auto& totalColumns = gridSize;

	sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Cloth Particle Simulation");
	window.setFramerateLimit(FRAMERATE_LIMIT);

	std::vector<entities::Particle> particles;
	std::vector<entities::BindingForce> bindingForces;

	for(int i = 0; i < totalRows; i++){
		for(int j = 0; j < totalColumns; j ++){
			float positionX = (j*DISTANCE) + WIDTH/3;
			float positionY = (i*DISTANCE) + WIDTH/5;
			particles.emplace_back(positionX, positionY);
		}
	}

	for(int i = 0; i < totalRows; i++){
		for(int j = 0; j < totalColumns; j++){
			if(j < totalColumns - 1) bindingForces.emplace_back(&particles[i*totalRows + j], &particles[i*totalRows + j + 1]);
			if(i < totalRows -1) bindingForces.emplace_back(&particles[i*totalRows + j], &particles[(i+1) * totalColumns + j]);
		}
	}

	while(window.isOpen()){
		while(const std::optional event = window.pollEvent()){
			if(event->is<sf::Event::Closed>()){
				window.close();
			}
		}	

		// apply gravity as acceleration
		for(auto &particle:particles){
			particle.applyGravity(sf::Vector2f(0, GRAVITY));
			particle.update(TIMES_STEP);
			particle.BindingForceByBound(WIDTH, HEIGHT, PARTICLE_RADIUS);
		}

		for(auto &bindingForce: bindingForces){
			bindingForce.apply();
		}

		window.clear(sf::Color::Black);
		
		// drawing many particles
		for(auto &particle : particles){
			float positionX = particle.position.x - PARTICLE_RADIUS;
			float positionY = particle.position.y - PARTICLE_RADIUS;
			sf::CircleShape circle(PARTICLE_RADIUS);
			circle.setFillColor(sf::Color::White);
			circle.setPosition({positionX, positionY});
			
			window.draw(circle);
		}

		// drawing particle binding forces
		for(const auto &bindingForce:bindingForces){
			sf::Vector2f currentParticlePosition = bindingForce.currentParticle->position;
			sf::Vector2f nextParticlePosition = bindingForce.nextParticle->position;
			sf::Vertex currentParticleVertexPosition{currentParticlePosition, sf::Color::White};
			sf::Vertex nextParticleVertexPosition{nextParticlePosition, sf::Color::White};
			std::array line = {
				currentParticleVertexPosition,
				nextParticleVertexPosition
			};

			window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
		}

		window.display();
	}
	return EXIT_SUCCESS;
}
