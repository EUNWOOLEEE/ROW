#ifndef RTWEEKEND_HPP
# define RTWEEKEND_HPP

# include <cmath>
# include <limits>
# include <memory>
# include <random>

// Usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
inline double degrees_to_radians(double degrees){
	return (degrees * pi / 180.0);
}

// Random Generating
inline double random_double(){
	//Returns a random real in [0, 1]
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<double> dist(0.0, 1.0);
	return (dist(gen));
}

inline double random_double(double min, double max){
	//Returns a random real in [min, max]
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<double> dist(0.0, 1.0);
	return (min + (max - min) * dist(gen));
}

// Utility
inline double clamp(double x, double min, double max){
	if(x < min) return min;
	if(x > max) return max;
	return x;
}

# include "ray.hpp"
# include "vec3.hpp"

#endif