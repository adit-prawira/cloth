#include <SFML/Graphics.hpp>
#include "particle.hpp"

// std
#include <iostream>
#include <vector>

const int WIDTH = 1080;
const int HEIGHT = 640;
const int FRAMERATE_LIMIT = 60;
const float PARTICLE_RADIUS = 30.0f;
const float GRAVITY = 9.81f;
const float TIMES_STEP = 0.1f;

int main(){
	sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Cloth Particle Simulation");
	window.setFramerateLimit(FRAMERATE_LIMIT);

	std::vector<entities::Particle> particles;
	particles.emplace_back(WIDTH/2, HEIGHT/2);

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

		window.clear(sf::Color::Black);

		// drawing many particles
		for(auto &particle : particles){
			float positionX = particle.getPosition().x - PARTICLE_RADIUS;
			float positionY = particle.getPosition().y - PARTICLE_RADIUS;
			std::cout << "Position -> "  << "(" << positionX << ", " << positionY << ")" << std::endl;
			sf::CircleShape circle(PARTICLE_RADIUS);
			circle.setFillColor(sf::Color::White);
			circle.setPosition({positionX, positionY});
			window.draw(circle);
		}

		window.display();
	}
	return EXIT_SUCCESS;
}
