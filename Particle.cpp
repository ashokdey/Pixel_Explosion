#include "Particle.hpp"
#include "Screen.hpp"
#include <cstdlib>
#include <cmath>

namespace particleEX {
	Particle::Particle() {
		init();
	}

	void Particle::init()
	{
		_pointX = 0;
		_pointY = 0;
		_direction = (2 * M_PI * rand()) / RAND_MAX;
		_speed = (0.08 * rand()) / RAND_MAX;
		_speed *= _speed;
	}

	void Particle::update(int interval) 
	{
		_direction += interval * 0.000635;

		double speedX = _speed * std::cos(_direction);
		double speedY = _speed * std::sin(_direction);

		_pointX += speedX * interval;
		_pointY += speedY * interval;

		if (rand() < RAND_MAX / 100) {
			init();
		}
	}
}