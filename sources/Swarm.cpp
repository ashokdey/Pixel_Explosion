#include "headers/Swarm.hpp"

namespace particleEX
{
	Swarm::Swarm(): _lastTime(0) {
		_particles = new Particle[NPARTICLES];
	}

	Swarm::~Swarm() {
		delete[] _particles;
	}

	void Swarm::update(int timePassed) {

		int interval = timePassed - _lastTime;

		for (int i = 0; i < particleEX::Swarm::NPARTICLES; ++i)
		{
			_particles[i].update(interval);
		}

		_lastTime = timePassed;
	}
}