#include <iostream>
#include "color.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "rtweekend.hpp"
#include "hittable_list.hpp"
#include "vec3.hpp"
#include "material.hpp"

color ray_color(const ray& r, const hittable& world, int depth){
	hit_record rec;

	// If we've exceeded the ray bound limit, no more light is gathered
	if(depth <= 0)
		return color(0, 0, 0);
	if(world.hit(r, 0.001, infinity, rec)){
		ray scattered;
		color attenuation;
		if(rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return (attenuation * ray_color(scattered, world, depth - 1));
		return color(0, 0, 0);
	}
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main(){

	// Image
	const auto aspect_ratio = 16.0 / 9.0;
	const int img_w = 400;
	const int img_h = static_cast<int>(img_w / aspect_ratio);
	const int samples_per_pixel = 100;
	const int max_depth = 50;

	// World
	hittable_list world;

	auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
	auto material_center = make_shared<dielectric>(1.5);
	auto material_left = make_shared<dielectric>(1.5);
	auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

	world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
	world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

	// Camera
	camera cam;

	// Render
	std::cout << "P3\n" << img_w << ' ' << img_h << "\n255\n";

	for(int j = img_h - 1; j >= 0; j--)
	{
		std::cerr << "\rScanlines Remaining: " << j << std::flush;
		for(int i = 0; i < img_w; i++)
		{
			color pixel_color(0, 0, 0);
			for(int s = 0; s < samples_per_pixel; s++){
				auto u = (i + random_double()) / (img_w - 1);
				auto v = (j + random_double()) / (img_h - 1);
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}
			write_color(std::cout, pixel_color, samples_per_pixel);
		}
	}
	std::cerr << "\nDone.\n";

	return 0;
}