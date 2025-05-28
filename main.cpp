#include "app.hpp"

// std
#include <iostream>

int main(){
	int gridSize;

	std::cout << "Enter the grid size: " << std::flush;
	std::cin >> gridSize;
	
	cloth::App app {gridSize};
	app.run();

	return EXIT_SUCCESS;
}
