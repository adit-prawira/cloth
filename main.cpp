#include <SFML/Graphics.hpp>
#include "particle.hpp"
#include "constraint.hpp"

// std
#include <iostream>
#include <vector>

const int WIDTH = 1080;
const int HEIGHT = 640;
const int FRAMERATE_LIMIT = 60;
const float PARTICLE_RADIUS = 10.0f;
const float GRAVITY = 9.81f;
const float TIMES_STEP = 0.1f;

// Grid dimensions
const int ROW = 8;
const int COL = 8;
const float DISTANCE = 30.0f;

int main(){
	sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Cloth Particle Simulation");
	window.setFramerateLimit(FRAMERATE_LIMIT);

	std::vector<entities::Particle> particles;
	std::vector<utilities::Constraint> constraints;

	for(int i = 0; i < ROW; i++){
		for(int j = 0; j < COL; j ++){
			float positionX = (j*DISTANCE) + WIDTH/3;
			float positionY = (i*DISTANCE) + WIDTH/3;
			particles.emplace_back(positionX, positionY);
		}
	}

	for(int i = 0; i < ROW; i++){
		for(int j = 0; j < COL; j++){
			if(j < COL - 1) constraints.emplace_back(&particles[i*ROW + j], &particles[i*ROW + j + 1]);
			if(i < ROW -1) constraints.emplace_back(&particles[i*ROW + j], &particles[(i+1) * COL + j]);
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
			particle.constraintByBound(WIDTH, HEIGHT, PARTICLE_RADIUS);
		}

		for(auto &constraint: constraints){
			constraint.apply();
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

		window.display();
	}
	return EXIT_SUCCESS;
}
