#include "cSimpleDebugRenderer.h"
#include "globalStuff.h"


cSimpleDebugRenderer::cSimpleDebugRenderer(cMeshObject* mUnitSphere, GLuint IDprogram)
	:mUnitSphere(mUnitSphere),
	mShaderProgram(IDprogram)
{

}

void cSimpleDebugRenderer::drawSphere(glm::vec3 pos, float rad)
{
	glm::mat4 iden(1.0f);
	mUnitSphere->position = pos;
	mUnitSphere->setDiffuseColour(glm::vec3(0.0f, 1.0f, 0.0f));
	mUnitSphere->setUniformScale(rad);
	mUnitSphere->bIsVisible = true;
	DrawObject(mUnitSphere, iden, mShaderProgram);
	mUnitSphere->bIsVisible = false;
}