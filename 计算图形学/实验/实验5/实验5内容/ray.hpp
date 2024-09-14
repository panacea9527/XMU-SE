#pragma once
#include <Eigen/Core>
using namespace Eigen;

class Ray
{
public:
    Ray(const Vector3f& origin, const Vector3f& direction, float time = 0.0f)
        : _origin(origin), _direction(direction), _time(time) {}

    Vector3f Origin() const { return _origin; }
    Vector3f Direction() const { return _direction; }
    float Time() const { return _time; }

    Vector3f PointAtT(float t) const {
        return _origin + t * _direction;
    }
Vector3f _origin;
private:
    
    Vector3f _direction;
    float _time; // 时间参数，用于动态模糊
};
