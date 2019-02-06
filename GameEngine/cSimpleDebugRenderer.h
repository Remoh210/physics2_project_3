#pragma once
#include "cMeshObject.h"
#include "globalOpenGLStuff.h"
class cSimpleDebugRenderer
{
public:
	cSimpleDebugRenderer(cMeshObject* mUnitSphere, GLuint IDprogram);

	void drawSphere(glm::vec3 pos, float rad);
	

private:
	cMeshObject* mUnitSphere;
	cMeshObject* mUnitPlane;
	GLuint mShaderProgram;
};