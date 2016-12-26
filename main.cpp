#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "headers/Screen.hpp"
#include "headers/Particle.hpp"
#include "headers/Swarm.hpp"


int main(int argc, char **argv) {
	
	particleEX::Screen appScreen;

	std::srand(std::time(NULL));

	if (appScreen.init() == false) {
		std::cout << "Failed to init application" << std::endl;
	}

	const int HALF_WIDTH = (particleEX::Screen::SCREEN_WIDTH / 2);
	const int HALF_HEIGHT = (particleEX::Screen::SCREEN_HEIGHT / 2);
	
	particleEX::Swarm swarm;

	while (true)
	{
		// Update particles
		// Draw particles
		
		auto timeElapsed = SDL_GetTicks();
		unsigned char red = static_cast<unsigned char>((1 + std::sin(timeElapsed * 0.0001)) * 128);
		unsigned char green = static_cast<unsigned char>((1 + std::sin(timeElapsed * 0.0002)) * 128);
		unsigned char blue = static_cast<unsigned char>((1 + std::sin(timeElapsed * 0.0003)) * 128);

		swarm.update(timeElapsed);


		const particleEX::Particle *const customParticles = swarm.getParticles();

		for (int i = 0; i < particleEX::Swarm::NPARTICLES; ++i)
		{
			particleEX::Particle singleParticle = customParticles[i];

			int x = (singleParticle._pointX + 1) * HALF_WIDTH;
			int y = (singleParticle._pointY * HALF_WIDTH) + HALF_HEIGHT;

			appScreen.setPixel(x, y, red, green, blue);
		}

		//call the blur method to makr things smooth
		appScreen.boxBlur();
	
		// Draw/Update the screen
		appScreen.update();

		// Check for any events
		if (appScreen.processEvents() == false)
		{
			break;
		}
	}

	// flush the screen
	appScreen.close();


	return 0;
}