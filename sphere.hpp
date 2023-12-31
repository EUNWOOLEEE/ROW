#ifndef SPHERE_H
# define SPHERE_H

# include "vec3.hpp"
# include "hittable.hpp"

class sphere : public object{
	
	public:
		sphere() {}
		sphere(point3 cen, double r, shared_ptr<material> m) : center(cen), radius(r), mat_ptr(m) {}
		virtual ~sphere() {}

		virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

		point3 center;
		double radius;
		shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	auto a = r.direction().length_squared();
	auto half_b = dot(oc, r.direction());
	auto c = oc.length_squared() - radius * radius;

	auto discriminant = half_b * half_b - a * c;
	if(discriminant < 0)
		return false;
	auto sqrtd = sqrt(discriminant);

	// Find the nearest root that lies in the acceptable range
	auto root = (-half_b - sqrtd) / a;
	if(root < t_min || t_max < root){
		root = (-half_b + sqrtd) / a;
		if(root < t_min || t_max < root)
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	vec3 outward_normal = (rec.p - center) / radius;
	rec.set_face_normal(r, outward_normal); //normal의 방향을 계산하는 부분
	rec.mat_ptr = mat_ptr;

	return true;
}

#endif