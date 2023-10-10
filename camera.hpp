#ifndef CAMERA_HPP
# define CAMERA_HPP

# include "rtweekend.hpp"

class camera{

	public:
		camera(){
			auto aspect_ratio = 16.0 / 9.0;
			auto viewport_h = 2.0;
			auto viewport_w = viewport_h * aspect_ratio;
			auto focal_len = 1.0;

			origin = point3(0, 0, 0);
			horizontal = vec3(viewport_w, 0, 0);
			vertical = vec3(0, viewport_h, 0);
			lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_len);
		}

		ray get_ray(double u, double v) const {
			return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
		}

	private:
		point3 origin;
		point3 lower_left_corner;
		vec3 horizontal;
		vec3 vertical;
};

#endif