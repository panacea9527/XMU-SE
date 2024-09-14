#include <Eigen/Core>
#include "ppm.hpp"
#include "camera.hpp"
#include "raytracer.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace Eigen;

int main()
{
    int width = 1280, height = 960;
    Camera cam;

    // 初始化材质
    Material mtl, mtl2, mtl3, mtl4, mtl5;
    mtl.SetKa(Vector3f(0.5, 0.5, 0.5));
    mtl.SetKd(Vector3f(0.8, 0.6, 0.0));
    mtl.SetKs(Vector3f(0.7, 0.8, 0.8));
    mtl.SetTransparent(false);
    mtl.SetReflective(true);
    mtl.SetShiness(50);

    mtl2.SetKa(Vector3f(0.5, 0.5, 0.5));
    mtl2.SetKd(Vector3f(0.0, 0.6, 0.2));
    mtl2.SetKs(Vector3f(0.1, 1.0, 0.8));
    mtl2.SetTransparent(false);
    mtl2.SetReflective(false);
    mtl2.SetShiness(10);

    mtl3.SetKa(Vector3f(0.5, 0.5, 0.5));
    mtl3.SetKd(Vector3f(0.0, 0.3, 0.6));
    mtl3.SetKs(Vector3f(0.0, 0.0, 0.0));
    mtl3.SetTransparent(false);
    mtl3.SetReflective(false);
    mtl3.SetShiness(10);

    mtl4.SetKa(Vector3f(0.1, 0.1, 0.1));
    mtl4.SetKd(Vector3f(0.0, 0.0, 0.0));
    mtl4.SetKs(Vector3f(0.0, 0.0, 0.0));
    mtl4.SetTransparent(true);
    mtl4.SetReflective(false);
    mtl4.SetRefraction(1.33);
    mtl4.SetShiness(200);

    mtl5.SetKa(Vector3f(0.5, 0.5, 0.5));
    mtl5.SetKd(Vector3f(0.75, 0.56, 0.0));
    mtl5.SetKs(Vector3f(0.75, 0.56, 0.0));
    mtl5.SetTransparent(false);
    mtl5.SetReflective(false);
    mtl5.SetRefraction(1.33);
    mtl5.SetShiness(100);

    // 动画帧数
    int num_frames = 20;
    float gravity = -9.8;
    float delta_time = 0.2;//帧间隔
    float bounce_damping = 0.8;

    // 初始位置和速度
    Vector3f position(0, 2.0, -2);
    Vector3f velocity(0, 0, 0);

    for (int frame = 0; frame < num_frames; ++frame)
    {
        PPM outrlt(width, height);
        Scene world;

        // 初始化静止的球体
        Sphere sp2(Vector3f(0, -10000.5, -2), 10000.0);
        Sphere sp3(Vector3f(-2.0, 0, -2), 0.5);
        Sphere sp4(Vector3f(1.0, -0.2, -1.0), 0.3);
        Sphere sp5(Vector3f(3.0, 0, -2.2), 0.4);
        Sphere sp6(Vector3f(-1, 0.0, -0.8), 0.2);

        world.Insert(make_pair(sp2, mtl2));
        world.Insert(make_pair(sp3, mtl3));
        world.Insert(make_pair(sp4, mtl4));
        world.Insert(make_pair(sp5, mtl5));

        // 更新小球位置和速度
        velocity[1] += gravity * delta_time;
        position += velocity * delta_time;

        // 检查碰撞并处理弹跳
        if (position[1] <= 0.5)  // 假设地面在 y = 0.5
        {
            position[1] = 0.5;
            velocity[1] = -velocity[1] * bounce_damping;
        }

        // 动态模糊的小球
        Sphere sp1(position, 1.0);
        world.Insert(make_pair(sp1, mtl));  // 将小球插入到场景中

        for (int j = height - 1; j >= 0; --j)  // 遍历图像的每一行
        {
            for (int i = 0; i < width; ++i)  // 遍历图像的每一列
            {
                bool test = false;
                // 生成光线的方向向量
                float u = float(i) / float(width);
                float v = float(j) / float(height);

                // 初始化颜色向量
                Vector3f color(0, 0, 0);

                // 动态模糊的采样次数
                int samples = 5;  // 采样次数越多，动态模糊效果越明显，但计算量也越大
                for (int s = 0; s < samples; ++s) {  // 在时间段内进行多次采样
                    // 生成一个时间偏移量，模拟不同时间点上的光线
                    float time = (frame + distribution(generator)) * delta_time;

                    // 使用相机生成具有时间偏移的光线
                    Ray ray = cam.GenerateRay(u, v, time);

                    // 计算该时间点上光线的颜色，并累加到颜色向量中
                    color += RayColor(ray, world, test);
                }
                // 计算平均颜色值
                color /= float(samples);  // 将累加的颜色值除以采样次数，得到平均颜色值

                // 设置像素颜色值
                outrlt.SetPixel(j, i,
                    int(255.99 * color[0]), int(255.99 * color[1]), int(255.99 * color[2]));
            }
        }


        // 将帧保存为图像文件
        stringstream ss;
        ss << "frame_" << setw(4) << setfill('0') << frame << ".ppm";
        outrlt.Write2File(ss.str().c_str());
    }

    return 0;
}
