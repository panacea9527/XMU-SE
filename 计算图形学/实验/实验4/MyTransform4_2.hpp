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
	//�����÷�
	Eigen::Matrix4f m;
	m.setZero();
	m(0, 0) = 1;
	m(3, 3) = 1;
	m(1, 1) = 2.3;   m(1, 2) = 0.99;
	m(2, 1) = 1.1;   m(2, 2) = 0;
	cout << "Matrix:" << endl;
	cout << m << endl;

	//�����÷�
	Eigen::Vector4f v;
	v[0] = 1.0;
	v[1] = 2.0;
	v[2] = 3.0;
	v[3] = 1.0;
	//v[4] = 1.0;
	v.normalize();//��һ��

	//���������������˵Ľ��
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

	//��������հ״���ɴ˺���
	
	m.setIdentity();//���Ӧ��ȥ��

	//��������հ״���ɴ˺���

	mModelView *= m;
	return m;
}

Eigen::Matrix4f myRotateX(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();

	//��������ճ���ϴ�ʵ��Ĵ���

	m.setIdentity();//���Ӧ��ȥ��


	//��������ճ���ϴ�ʵ��Ĵ���

	mModelView *= m;
	return m;
}

Eigen::Matrix4f myRotateY(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();

	//��������ճ���ϴ�ʵ��Ĵ���

	m.setIdentity();//���Ӧ��ȥ��


	//��������ճ���ϴ�ʵ��Ĵ���

	mModelView *= m;
	return m;
}

Eigen::Matrix4f myRotateZ(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();

	//��������ճ���ϴ�ʵ��Ĵ���

	m.setIdentity();//���Ӧ��ȥ��


	//��������ճ���ϴ�ʵ��Ĵ���

	mModelView *= m;
	return m;
}


Eigen::Matrix4f myTranslate(float x, float y, float z)
{
	Eigen::Matrix4f m;
	m.setZero();

	//��������ճ���ϴ�ʵ��Ĵ���

	m.setIdentity();//���Ӧ��ȥ��


	//��������ճ���ϴ�ʵ��Ĵ���

	mModelView *= m;
	return m;
}

Eigen::Matrix4f myRotate(float angle, float x, float y, float z)
{
	float theta = angle / 180.0 * PI;

	Eigen::Matrix4f m;

	//��������ճ���ϴ�ʵ��Ĵ���

	m.setIdentity();//���Ӧ��ȥ��


	//��������ճ���ϴ�ʵ��Ĵ���

	mModelView *= m;

	return m;
}

Eigen::Matrix4f myFrustum(float l, float r, float b, float t, float n, float f)
{
	Eigen::Matrix4f m;
	m.setZero();

	//��������հ״���ɴ˺���
	
	//m.setIdentity();//���Ӧ��ȥ��

	//��������հ״���ɴ˺���

	mProjection *= m;
	return m;
}

Eigen::Matrix4f myOrtho(float l, float r, float b, float t, float n, float f)
{
	Eigen::Matrix4f m;
	m.setZero();

	//��������հ״���ɴ˺���

	//m.setIdentity();//���Ӧ��ȥ��


	//��������հ״���ɴ˺���

	mProjection *= m;

	return m;
}

Eigen::Matrix4f myViewPort(float x, float y, float w, float h)
{
	Eigen::Matrix4f m;
	m.setZero();

	//��������հ״���ɴ˺���


	//������δ���Ӧ��ɾ��
	m(0, 0) = 125;
	m(1, 1) = 125.0;
	m(0, 3) = 125.0;
	m(1, 3) = 125.0;
	m(2, 2) = 1.0;
	m(3, 3) = 1.0;
	//������δ���Ӧ��ɾ��

	//��������հ״���ɴ˺���

	mViewPort = m;

	return m;
}

Eigen::Matrix4f myPerspective(float fovy, float aspect, float zNear, float zFar)
{
	Eigen::Matrix4f m;
	m.setZero();
	const float pi = 3.1415926535897932384626433832795;

	//��������հ״���ɴ˺���

	m.setIdentity();//���Ӧ��ȥ��

	//��������հ״���ɴ˺���

	mProjection *= m;
	return m;
}