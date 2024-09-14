#pragma once
#include "ray.hpp"
#include <Eigen/Core>
using namespace Eigen;

class Camera
{
public:
    Camera()
    {
        // 注意：这里为了方便，直接把这几个参数写死了
        _origin = Vector3f(0, 0, 0);
        _lower_left_corner = Vector3f(-2.0, -1.5, -1.0);
        _horizontal = Vector3f(4.0, 0.0, 0.0);
        _vertical = Vector3f(0.0, 3.0, 0.0);
    }

    // 生成光线的方法，现在接收时间参数
    Ray GenerateRay(float u, float v, float time)
    {
        return Ray(_origin,
            _lower_left_corner + u * _horizontal + v * _vertical - _origin,
            time);
    }

    Vector3f _origin;             // 相机中心
    Vector3f _lower_left_corner;  // 成像平面左下角
    Vector3f _horizontal;         // 成像平面的水平向量
    Vector3f _vertical;           // 成像平面的竖直向量
};
