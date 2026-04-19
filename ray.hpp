#pragma once

#include "vec3.hpp"

class ray {
	private:
		point3 orig;
		vec3 dir;

	public:

		ray() : orig(0,0,0), dir(0,0,0) {} //default initialization
		
		ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

		const point3& origin() const { return orig; }
		const vec3& direction() const { return dir; }
	
		point3 at(double t) const {
			return orig + t * dir;
		}
};