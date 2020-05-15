#pragma once
#include "core/Object3D.h"

enum class CameraType
{
	ORTHOGRAPHIC = 0,
	PERSPECTIVE = 1
};

class Camera : public Object3D
{
	public:
	CameraType type;
	glm::mat4 view, projection;

	Camera(std::string name, Object3D* parent, CameraType type, float width, float height);
	~Camera();

	void init();
	void initOrthographic();
	void initPerspective();
	void computeView();
	void computeProjection();
	void zoom(bool in);
	void zoomOrthographic(bool in);
	void zoomPerspective(bool in);
	void rotate(double yaw, double pitch);
	// TODO JT
	void test(float viewportWidth, float viewportHeight, float x, float y, float z);

	// Surcharge
	void draw();

	private:
	glm::vec3 target;

	float vWidth, vHeight, aspectRatio;
	float top, bottom, left, right;
	float near, far;
};
