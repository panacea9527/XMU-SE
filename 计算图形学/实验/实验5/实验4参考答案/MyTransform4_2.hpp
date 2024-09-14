#pragma once

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <iostream>
using namespace std;
#define PI 3.1415927

extern Eigen::Matrix4f mModelView;
extern Eigen::Matrix4f mProjection;
extern Eigen::Matrix4f mViewPort;


void Test()
{
	//矩阵用法
	Eigen::Matrix4f m;
	m.setZero();
	m(0, 0) = 1;
	m(3, 3) = 1;
	m(1, 1) = 2.3;   m(1, 2) = 0.99;
	m(2, 1) = 1.1;   m(2, 2) = 0;
	cout << "Matrix:" << endl;
	cout << m << endl;

	//向量用法
	Eigen::Vector4f v;
	v[0] = 1.0;
	v[1] = 2.0;
	v[2] = 3.0;
	v[3] = 1.0;
	//v[4] = 1.0;
	v.normalize();//归一化

	//输出矩阵与向量相乘的结果
	cout << "result:" << endl;
	cout << m * v << endl;
}

vector<Eigen::Vector3f> VertexTransform(vector<Eigen::Vector3f> vertices)
{
	vector<Eigen::Vector3f> rlt(vertices.size());
	Eigen::Vector4f v;

	Eigen::Matrix4f M = mViewPort * mProjection * mModelView;

	for (int i = 0; i < vertices.size(); ++i)
	{
		v[3] = 1.0;
		v.head<3>() = vertices[i];

		v = M * v;
		rlt[i][0] = v[0] / v[3];
		rlt[i][1] = v[1] / v[3];
		rlt[i][2] = v[2] / v[3];
	}
	return rlt;
}

Eigen::Matrix4f myLookAt(float ex, float ey, float ez, float atx, float aty, float atz, float upx, float upy, float upz)
{
	Eigen::Matrix4f m;
	m.setZero();

	//请在下面空白处完成此函数
	Eigen::Vector3f w;
	w[0] = -atx;
	w[1] = -aty;
	w[2] = -atz;
	w.normalize();

	Eigen::Vector3f u;
	u[0] = (upy * w[2] - upz * w[1]);
	u[1] = (upz * w[0] - upx * w[2]);
	u[2] = (upx * w[1] - upy * w[0]);
	u.normalize();

	Eigen::Vector3f v;
	v[0] = (w[1] * u[2] - w[2] * u[1]);
	v[1] = (w[2] * u[0] - w[0] * u[2]);
	v[2] = (w[0] * u[1] - w[1] * u[0]);

	Eigen::Matrix4f m1;
	m1.setZero();
	Eigen::Matrix4f m2;
	m2.setZero();

	m1(0, 0) = u[0], m1(0, 1) = u[1], m1(0, 2) = u[2], m1(0, 3) = 0;
	m1(1, 0) = v[0], m1(1, 1) = v[1], m1(1, 2) = v[2], m1(1, 3) = 0;
	m1(2, 0) = w[0], m1(2, 1) = w[1], m1(2, 2) = w[2], m1(2, 3) = 0;
	m1(3, 0) = 0, m1(3, 1) = 0, m1(3, 2) = 0, m1(3, 3) = 1;

	m2(0, 0) = 1, m2(0, 1) = 0, m2(0, 2) = 0, m2(0, 3) = -ex;
	m2(1, 0) = 0, m2(1, 1) = 1, m2(1, 2) = 0, m2(1, 3) = -ey;
	m2(2, 0) = 0, m2(2, 1) = 0, m2(2, 2) = 1, m2(2, 3) = -ez;
	m2(3, 0) = 0, m2(3, 1) = 0, m2(3, 2) = 0, m2(3, 3) = 1;

	m = m1 * m2;
	//m.setIdentity();//这句应该去掉


	//请在上面空白处完成此函数

	mModelView *= m;
	return m;
}

Eigen::Matrix4f myRotateX(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();
	float costheta = cos(theta);
	float sintheta = sin(theta);
	m(0, 0) = 1;
	m(3, 3) = 1;
	m(1, 1) = costheta;   m(1, 2) = -sintheta;
	m(2, 1) = sintheta;   m(2, 2) = costheta;

	mModelView *= m;
	return m;
}

Eigen::Matrix4f myRotateY(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();
	float costheta = cos(theta);
	float sintheta = sin(theta);
	m(1, 1) = 1;
	m(3, 3) = 1;
	m(0, 0) = costheta;   m(0, 2) = sintheta;
	m(2, 0) = -sintheta;   m(2, 2) = costheta;

	mModelView *= m;
	//cout << m << endl;
	return m;
}

Eigen::Matrix4f myRotateZ(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();
	float costheta = cos(theta);
	float sintheta = sin(theta);
	m(2, 2) = 1;
	m(3, 3) = 1;
	m(0, 0) = costheta;   m(0, 1) = -sintheta;
	m(1, 0) = sintheta;   m(1, 1) = costheta;

	mModelView *= m;
	//cout << m << endl;
	return m;
}


Eigen::Matrix4f myTranslate(float x, float y, float z)
{
	Eigen::Matrix4f m;
	m.setZero();
	m(0, 0) = 1;
	m(1, 1) = 1;
	m(2, 2) = 1;
	m(3, 3) = 1;

	m(0, 3) = x;
	m(1, 3) = y;
	m(2, 3) = z;

	mModelView *= m;

	//cout << m << endl;
	return m;
}

Eigen::Matrix4f myRotate(float angle, float x, float y, float z)
{
	float theta = angle / 180.0 * PI;

	Eigen::Matrix4f m;

	m.setIdentity();//To be modified

	mModelView *= m;

	return m;
}

// 透视投影 
Eigen::Matrix4f myFrustum(float l, float r, float b, float t, float n, float f)
{
	Eigen::Matrix4f m;
	m.setZero();

	//请在下面空白处完成此函数
	m(0, 0) = 2 * n / (r - l);
	m(0, 2) = (r + l) / (r - l);
	m(1, 1) = 2 * n / (t - b);
	m(1, 2) = (t + b) / (t - b);
	m(2, 2) = -(f + n) / (f - n);
	m(2, 3) = -2 * (f * n) / (f - n);
	m(3, 2) = -1;

	//m.setIdentity();//这句应该去掉


	//请在上面空白处完成此函数

	mProjection *= m;
	return m;
}

// 正交投影 
Eigen::Matrix4f myOrtho(float l, float r, float b, float t, float n, float f)
{
	Eigen::Matrix4f m;
	m.setZero();

	//请在下面空白处完成此函数

	m(0, 0) = 2 / (r - l);
	m(0, 3) = -(r + l) / (r - l);
	m(1, 1) = 2 / (t - b);
	m(1, 3) = -(t + b) / (t - b);
	m(2, 2) = -2 / (f - n);
	m(2, 3) = -(f + n) / (f - n);
	m(3, 3) = 1;
	//m.setIdentity();//这句应该去掉


	//请在上面空白处完成此函数

	mProjection *= m;

	return m;
}

// 视口变换 
Eigen::Matrix4f myViewPort(float x, float y, float w, float h)
{
	Eigen::Matrix4f m;
	m.setZero();

	//请在下面空白处完成此函数


	//下面这段代码应该删掉
	m(0, 0) = w / 2.0f;
	m(0, 3) = m(0, 0) + x;
	m(1, 1) = -h / 2.0f;
	m(1, 3) = h / 2.0f + 500 - h - y;
	m(2, 2) = 1.0;
	m(3, 3) = 1.0;
	/*
	m(0, 0) = 125;
	m(1, 1) = 125.0;
	m(0, 3) = 125.0;
	m(1, 3) = 125.0;
	m(2, 2) = 1.0;
	m(3, 3) = 1.0;
	*/
	//上面这段代码应该删掉


	//请在上面空白处完成此函数

	mViewPort = m;

	return m;
}

// 透视投影 
Eigen::Matrix4f myPerspective(float fovy, float aspect, float zNear, float zFar)
{
	Eigen::Matrix4f m;
	m.setZero();
	const float pi = 3.1415926535897932384626433832795;

	//请在下面空白处完成此函数

	//m.setIdentity();//这句应该去掉
	float f = 1.0 / tan(fovy * pi / 360.0);
	m(0, 0) = f / aspect;
	m(1, 1) = f;
	m(2, 2) = (zFar + zNear) / (zNear - zFar);
	m(2, 3) = -1.0;
	m(3, 2) = (2.0 * zFar * zNear) / (zNear - zFar);

	//请在上面空白处完成此函数

	mProjection *= m;
	return m;
}
