#include <SFML/Graphics.hpp>
#include "app.hpp"
#include "constant.hpp"

// std
#include <iostream>
#include <array>
#include <vector>

namespace cloth {
	App::App(const int& gridSize): 
		size(gridSize), 
		window(sf::VideoMode({constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT}), constants::NAME)
		{}

	// Publics
	void App::run(){
		const auto& totalRows = this->size;
		const auto& totalColumns = this->size;

		this->window.setFramerateLimit(constants::FRAMERATE_LIMIT);
		this->initialise(totalRows, totalColumns);

		std::cout << "run(): Starting cloth simulation" << std::endl;
		while(this->window.isOpen()){
			while(const std::optional event = this->window.pollEvent()){
				if(event->is<sf::Event::Closed>()){
					this->window.close();
				}
			}
			this->applyMotion();
			this->window.clear(sf::Color::Black);
			this->draw();
			this->window.display();
		}
		std::cout << "run(): Stopping cloth simulation" << std::endl;
		
	}

	// Privates
	void App::initialise(const int& row, const int& col){
		std::cout << "initialise(): Attempting to initialise particle grid of dimension -> " << row << " X " << col << std::endl;
		std::cout << "initialise(): Attached are initial coordinates of particles: " << std::endl;

		std::cout << std::endl;

		for(int i = 0; i < row; i++){
			for(int j  = 0; j < col; j++){
				float positionX = (j*constants::PARTICLE_DISTANCE) + constants::WINDOW_WIDTH/4;
				float positionY = (i*constants::PARTICLE_DISTANCE) + constants::WINDOW_HEIGHT/8;
				bool pinned = i == 0 && (j <= static_cast<int>(std::floor(col/3)));
				std::string indicator =  pinned?"*":"@";
				std::cout << indicator << "("<< positionX << ", " << positionY << ")" << " | ";
				this->particles.emplace_back(positionX, positionY, pinned);			
			}
			std::cout << std::endl;
		}

		for(int i = 0; i < row; i++){
			for(int j = 0; j < col; j++){
				if(j < col - 1) this->bindingForces.emplace_back(&this->particles[i*row + j], &this->particles[i*row + j + 1]);
				if(i < row - 1) this->bindingForces.emplace_back(&this->particles[i*row + j], &this->particles[(i+1)*col + j]);
			}
		}
		std::cout << std::endl;
		std::cout << "initialise(): Successfully initialize particle grid of dimension" << std::endl;
	}

	void App::applyMotion(){
		for(auto &particle: this->particles){
			particle.applyGravity(sf::Vector2f(0, constants::GRAVITY));
			particle.update(constants::TIMES_STEP);
			particle.bindingForceByBound(constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT, constants::PARTICLE_RADIUS);
		}
		for(auto &bindingForce: this->bindingForces){
			bindingForce.apply();
		}
	}

	void App::draw(){

		for(auto &particle: this->particles){
			float positionX = particle.position.x - constants::PARTICLE_RADIUS;
			float positionY = particle.position.y - constants::PARTICLE_RADIUS;
			sf::CircleShape circle(constants::PARTICLE_RADIUS);
			circle.setFillColor(sf::Color::White);
			circle.setPosition({positionX, positionY});
			this->window.draw(circle);
		}

		for(const auto &bindingForce: this->bindingForces){
			sf::Vector2f currentParticlePosition = bindingForce.currentParticle->position;
			sf::Vertex currentParticleVertexPosition{currentParticlePosition, sf::Color::White};

			sf::Vector2f nextParticlePosition = bindingForce.nextParticle->position;
			sf::Vertex nextParticleVertexPosition{nextParticlePosition, sf::Color::White};

			std::array line = {
				currentParticleVertexPosition,
				nextParticleVertexPosition
			};
			this->window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
		}
	}

}
