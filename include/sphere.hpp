#pragma once

#include "hittable.hpp"
#include "vec3.hpp"

class sphere : public hittable {
	public:
		sphere(const point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}

		bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
			vec3 point2center{ center - r.origin() };
			auto a{ r.direction().length_squared() }; //ray direction magnitude squared
			auto h{ dot(r.direction(), point2center) }; //how much is the ray pointing toward the sphere center
			auto c{ point2center.length_squared() - radius * radius }; //is the point inside, on, or outside the sphere

			auto b{ -2 * h };

			auto discriminant{b * b - 4 * a * c};
			if (discriminant < 0)
				return false;

			auto sqrtd{ std::sqrt(discriminant) };

			// Find the nearest root that lies in an acceptable range
			auto root{ (-b - sqrtd) / (2 * a) };
			if (root <= ray_tmin || root >= ray_tmax) {
				root = (-b + sqrtd) / a;
				if (root <= ray_tmin || root >= ray_tmax) {
					return false;
				}
			}

			rec.t = root;
			rec.p = r.at(rec.t);
			vec3 outward_normal{ (rec.p - center) / radius };
			rec.set_face_normal(r, outward_normal);

			return true;

		}

	private:
		point3 center;
		double radius;
};