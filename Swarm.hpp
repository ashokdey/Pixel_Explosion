#pragma once
#include "Particle.hpp"


namespace particleEX {

	class Swarm {
	private:
		Particle *_particles;
		int _lastTime;
	public:
		static const int NPARTICLES = 8000;
	public:
		Swarm();
		~Swarm();
		const Particle *const getParticles() { return _particles;  }
		void update(int timePassed);
	};

}