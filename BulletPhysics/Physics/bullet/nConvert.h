#pragma once
#include <glm/glm.hpp>
#include <LinearMath/btVector3.h>
#include <LinearMath/btTransform.h>
#include <glm/mat4x4.hpp>
//#include <glm/vec3.hpp>
namespace nPhysics {
	namespace nConvert
	{
		inline glm::vec3 ToSimple(const btVector3& vecIn)
		{
			return glm::vec3(vecIn.x(), vecIn.y(), vecIn.z());
		}
		inline void ToSimple(const btVector3 vecIn, glm::vec3& vecOut)
		{
			vecOut.x = vecOut.x;
			vecOut.y = vecOut.y;
			vecOut.z = vecOut.z;
		}
		inline btVector3 ToBullet(const glm::vec3& vecIn)
		{
			return btVector3(vecIn.x, vecIn.y, vecIn.z);
		}
		inline void ToBullet(const glm::vec3& vecIn, btVector3& vecOut)
		{
			vecOut.setValue(vecIn.x, vecIn.y, vecIn.z);
		}

		inline glm::mat4 ToSimple(const btTransform& transformIn)
		{
			glm::mat4 mat;
			transformIn.getOpenGLMatrix(&mat[0][0]);
			return mat;
		}
		inline void ToSimple(const btTransform& transform, glm::mat4 matOut)
		{

			transform.getOpenGLMatrix(&matOut[0][0]);

		}

	}



}