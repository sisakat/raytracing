#pragma once
#include "hittable.hpp"

#include <memory>
#include <vector>

class HittableList : public Hittable
{
public:
    using HittablePtr = std::shared_ptr<Hittable>;

    HittableList() {}
    HittableList(HittablePtr object) : m_objects{object} {}

    void clear() { m_objects.clear(); }
    void add(HittablePtr object) { m_objects.push_back(object); }

    bool hit(const Ray& r, double t_min, double t_max,
             HitRecord& rec) const override;

private:
    std::vector<HittablePtr> m_objects;
};