#ifndef object_LIST_HPP
# define object_LIST_HPP

# include <memory>
# include <vector>
# include "object.hpp"

using std::shared_ptr;
using std::make_shared;

class object_list : public object{

	public:
		object_list() {}
		object_list(shared_ptr<object> object) { add(object); }

		void clear() { objects.clear(); }
		void add(shared_ptr<object> object) { objects.push_back(object); }

		virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

		std::vector<shared_ptr<object>> objects;
};

bool object_list::hit(const ray&r, double t_min, double t_max, hit_record& rec) const {
	hit_record temp_rec;
	bool hit_anything = false;
	auto closest_so_far = t_max;

	for(const auto& object : objects){
		if(object->hit(r, t_min, closest_so_far, temp_rec)){
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}

#endif