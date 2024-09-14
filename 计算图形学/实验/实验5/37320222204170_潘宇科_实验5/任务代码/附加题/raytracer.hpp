#pragma once
#include "ray.hpp"
#include "scene.hpp"
#include <iostream>
#include <random>
#define MAXDEPTH 20

// ��������������ڲ���
std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(0.0, 1.0);

// ���亯�������ڼ����������
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

// ���������ɫ�ĺ�����֧�ֶ�̬ģ��������ӰЧ��
Vector3f RayColor(const Ray& ray, Scene& scene, int depth = 0, bool test = false)
{
    HitInfo closest_hp;
    closest_hp.t = FLT_MAX;
    closest_hp.objIdx = -1;
    // ���ߺ�����
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

    // ��Դλ�ú͹��ղ���
    Vector3f lightpos(0.0, 4, 2);
    Vector3f lightAmbient(0.6, 0.6, 0.6);
    Vector3f lightDiffuse(1.0, 1.0, 1.0);
    Vector3f lightSpecular(1.0, 1.0, 1.0);

    if (closest_hp.objIdx != -1) {
        int idx = closest_hp.objIdx;
        Material mtl = scene._scene[idx].second;

        // ������
        Vector3f ambient = lightAmbient.cwiseProduct(mtl._Ka);

        Vector3f color = ambient;
        bool isShadow = false;

        // Shadow ray �󽻣�����ӰЧ��
        Vector3f light_sample(0.0, 0.0, 0.0);  // ���ڴ洢��Դ����λ�õ�����

        for (int s = 0; s < 10; ++s) {  // �Թ�Դ���ж�β�����ģ������Ӱ
            // ���ɹ�Դ����λ�ã�ͨ���ڹ�Դλ�ø������ƫ�ƣ�ģ�������Դ
            light_sample = lightpos + Vector3f(distribution(generator) - 0.5f, distribution(generator) - 0.5f, distribution(generator) - 0.5f) * 0.2f;

            // �����е㷢��ָ���Դ����λ�õ� shadow ray
            Ray shadow_ray(closest_hp.position, light_sample - closest_hp.position);

            // ���������е��������壬��� shadow ray �Ƿ��������ཻ
            for (int i = 0; i < scene.ObjectCount(); ++i) {
                HitInfo ht;
                // ��� shadow ray �Ƿ���� i �������ཻ
                if (scene.GetObjectPtr(i)->Hit(shadow_ray, ht)) {
                    // ����ཻ���ڹ�Դ����λ�ú����е�֮�䣬˵�����ڵ�
                    if (ht.t > 0 && ht.t < (light_sample - closest_hp.position).norm()) {
                        isShadow = true;  // ������Ӱ��־
                        break;  // ����ѭ����ֹͣ���
                    }
                }
            }
            if (isShadow) break;  // ����Ѽ�⵽��Ӱ����������ѭ��
        }


        Vector3f eyedir = (Vector3f(0, 0, 0) - closest_hp.position).normalized();
        if (!isShadow) {  // ���������Ӱ����������
            // ������
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
        Ray reflectRay(closest_hp.position, reflectDir, ray.Time());  // ����ʱ�����
        reflectRay._origin = closest_hp.position + 1e-2 * reflectDir.normalized();
        if (mtl._reflective) {
            if (depth < MAXDEPTH) {
                reflectColor = RayColor(reflectRay, scene, depth + 1);
            }
        }

        // ���䣬���õݹ�
        Vector3f refractionColor(0.0, 0.0, 0.0);
        if (mtl._transparent) {
            Vector3f refractDir;
            float ni_over_nt;
            bool refract;
            if (ray.Direction().dot(closest_hp.normal) < 0) {  // ����
                ni_over_nt = 1.0 / mtl._refraction;
                refract = Refract(ray.Direction(), closest_hp.normal, ni_over_nt, refractDir);
            }
            else {  // ����
                ni_over_nt = mtl._refraction;
                refract = Refract(ray.Direction(), -closest_hp.normal, ni_over_nt, refractDir);
            }

            if (refract) {
                Ray refractRay(closest_hp.position, refractDir, ray.Time());  // ����ʱ�����
                refractRay._origin = closest_hp.position + 1e-2 * refractDir.normalized();
                if (depth < MAXDEPTH) {
                    refractionColor = RayColor(refractRay, scene, depth + 1);
                }
            }
        }

        color = color + 0.2 * reflectColor + 0.9 * refractionColor;
        return color.cwiseMin(Vector3f(1.0, 1.0, 1.0));
    }

    return Vector3f(0.6, 0.8, 0.8);  // ������ɫ
}
