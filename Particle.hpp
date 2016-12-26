#pragma once

namespace particleEX 
{
	struct Particle {
	
		double _pointX;
		double _pointY;
		double _speed;
		double _direction;
	
		Particle();
		void update(int interval);

	private:
		void init();
	};
}