#ifndef MATERIAL_HPP
# define MATERIAL_HPP

# include "vec3.hpp"
# include "rtweekend.hpp"

struct hit_record;

class material{
	
	public:
		virtual bool scatter(const ray& r_in, const hit_record& rec, \
							color& attenuation, ray& scattered) const = 0;
};

class lambertian : public material {

	public:
		lambertian(const color& a) : albedo(a) {}
		virtual ~lambertian() {}

		virtual bool scatter(const ray& r_in, const hit_record& rec, \
							color& attenuation, ray& scattered) const override {
			auto nothing = r_in.direction();
			unit_vector(nothing);
			auto scatter_direction = rec.normal + random_unit_vector();
			if(scatter_direction.near_zero())
				scatter_direction = rec.normal;
			scattered = ray(rec.p, scatter_direction);
			attenuation = albedo;
			return true;
		}

		color albedo;
};

class metal : public material {
	
	public:
		metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}
		virtual ~metal() {}

		virtual bool scatter(const ray& r_in, const hit_record& rec, \
							color& attenuation, ray& scattered) const override {
			vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
			scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
			attenuation = albedo;
			return (dot(scattered.direction(), rec.normal) > 0);
		}

		color albedo;
		double fuzz;
};

class dielectric : public material {

	public:
		dielectric(double index_of_refraction) : ir(index_of_refraction) {}
		virtual ~ dielectric() {}

		virtual bool scatter(const ray& r_in, const hit_record& rec, \
							color& attenuation, ray& scattered) const override {
			attenuation = color(1.0, 1.0, 1.0);
			double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

			vec3 unit_direction = unit_vector(r_in.direction());
			//여기에 수정해야됨

			scattered = ray(rec.p, direction);
			return true;
		}

		double ir;
};

#endif