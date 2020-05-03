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

	Camera(unsigned int id, std::string name, Object3D* parent, CameraType type, float width, float height);
	~Camera();

	void init();
	void initOrthographic();
	void initPerspective();
	void computeView();
	void computeProjection();
	void zoom(bool in);
	void zoomOrthographic(bool in);
	void zoomPerspective(bool in);

	// Surcharge
	void draw();

	private:
	glm::vec3 target;

	float vWidth, vHeight, aspectRatio;
	float top, bottom, left, right;
	float near, far;
};
