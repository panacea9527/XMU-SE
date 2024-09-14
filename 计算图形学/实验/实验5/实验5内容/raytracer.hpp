#pragma once
#include "ray.hpp"
#include "scene.hpp"
#include <iostream>
#include <random>
#define MAXDEPTH 20

// 随机数生成器用于采样
std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(0.0, 1.0);

// 折射函数，用于计算折射光线
bool Refract(const Vector3f& d, const Vector3f& n, float ni_over_nt, Vector3f& refracted)
{
    Vector3f unit_d = d.normalized();
    float dt = unit_d.dot(n);
    float disc = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if (disc > 0) {
        refracted = ni_over_nt * (unit_d - n * dt) - n * sqrt(disc);
        return true;
    }
    return false;
}

// 计算光线颜色的函数，支持动态模糊和软阴影效果
Vector3f RayColor(const Ray& ray, Scene& scene, int depth = 0, bool test = false)
{
    HitInfo closest_hp;
    closest_hp.t = FLT_MAX;
    closest_hp.objIdx = -1;
    // 光线和球求交
    for (int i = 0; i < scene.ObjectCount(); ++i) {
        HitInfo ht;
        bool bhit = scene.GetObjectPtr(i)->Hit(ray, ht);
        if (bhit) {
            if (ht.t > 0 && ht.t < closest_hp.t) {
                closest_hp = ht;
                closest_hp.objIdx = i;
            }
        }
    }

    // 光源位置和光照参数
    Vector3f lightpos(0.0, 4, 2);
    Vector3f lightAmbient(0.6, 0.6, 0.6);
    Vector3f lightDiffuse(1.0, 1.0, 1.0);
    Vector3f lightSpecular(1.0, 1.0, 1.0);

    if (closest_hp.objIdx != -1) {
        int idx = closest_hp.objIdx;
        Material mtl = scene._scene[idx].second;

        // 环境光
        Vector3f ambient = lightAmbient.cwiseProduct(mtl._Ka);

        Vector3f color = ambient;
        bool isShadow = false;

        // Shadow ray 求交，软阴影效果
        Vector3f light_sample(0.0, 0.0, 0.0);  // 用于存储光源采样位置的向量

        for (int s = 0; s < 10; ++s) {  // 对光源进行多次采样，模拟软阴影
            // 生成光源采样位置，通过在光源位置附近随机偏移，模拟面积光源
            light_sample = lightpos + Vector3f(distribution(generator) - 0.5f, distribution(generator) - 0.5f, distribution(generator) - 0.5f) * 0.2f;

            // 从命中点发出指向光源采样位置的 shadow ray
            Ray shadow_ray(closest_hp.position, light_sample - closest_hp.position);

            // 遍历场景中的所有物体，检测 shadow ray 是否与物体相交
            for (int i = 0; i < scene.ObjectCount(); ++i) {
                HitInfo ht;
                // 检查 shadow ray 是否与第 i 个物体相交
                if (scene.GetObjectPtr(i)->Hit(shadow_ray, ht)) {
                    // 如果相交点在光源采样位置和命中点之间，说明被遮挡
                    if (ht.t > 0 && ht.t < (light_sample - closest_hp.position).norm()) {
                        isShadow = true;  // 设置阴影标志
                        break;  // 跳出循环，停止检测
                    }
                }
            }
            if (isShadow) break;  // 如果已检测到阴影，跳出采样循环
        }


        Vector3f eyedir = (Vector3f(0, 0, 0) - closest_hp.position).normalized();
        if (!isShadow) {  // 如果不是阴影，继续计算
            // 漫反射
            Vector3f lightdir = (lightpos - closest_hp.position).normalized();
            float coscoef = lightdir.dot(closest_hp.normal);
            if (coscoef < 0) coscoef = 0;
            Vector3f diffuse = mtl._Kd * coscoef;

            Vector3f half = (eyedir + (light_sample - closest_hp.position).normalized()).normalized();
            float specularcoef = half.dot(closest_hp.normal);
            if (specularcoef < 0) specularcoef = 0;
            else specularcoef = pow(specularcoef, mtl._shiness);
            Vector3f specular = lightSpecular.cwiseProduct(mtl._Ks) * specularcoef;

            color += diffuse + specular;
        }

        Vector3f reflectColor(0.0, 0.0, 0.0);
        Vector3f reflectDir = 2.0 * eyedir.dot(closest_hp.normal) * closest_hp.normal - eyedir;
        Ray reflectRay(closest_hp.position, reflectDir, ray.Time());  // 传递时间参数
        reflectRay._origin = closest_hp.position + 1e-2 * reflectDir.normalized();
        if (mtl._reflective) {
            if (depth < MAXDEPTH) {
                reflectColor = RayColor(reflectRay, scene, depth + 1);
            }
        }

        // 折射，调用递归
        Vector3f refractionColor(0.0, 0.0, 0.0);
        if (mtl._transparent) {
            Vector3f refractDir;
            float ni_over_nt;
            bool refract;
            if (ray.Direction().dot(closest_hp.normal) < 0) {  // 入射
                ni_over_nt = 1.0 / mtl._refraction;
                refract = Refract(ray.Direction(), closest_hp.normal, ni_over_nt, refractDir);
            }
            else {  // 出射
                ni_over_nt = mtl._refraction;
                refract = Refract(ray.Direction(), -closest_hp.normal, ni_over_nt, refractDir);
            }

            if (refract) {
                Ray refractRay(closest_hp.position, refractDir, ray.Time());  // 传递时间参数
                refractRay._origin = closest_hp.position + 1e-2 * refractDir.normalized();
                if (depth < MAXDEPTH) {
                    refractionColor = RayColor(refractRay, scene, depth + 1);
                }
            }
        }

        color = color + 0.2 * reflectColor + 0.9 * refractionColor;
        return color.cwiseMin(Vector3f(1.0, 1.0, 1.0));
    }

    return Vector3f(0.6, 0.8, 0.8);  // 背景颜色
}
