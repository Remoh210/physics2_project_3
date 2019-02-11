#pragma once
#include <Interfaces/iRigidBody.h>
#include <Interfaces/sRigidBodyDef.h>
#include <btBulletDynamicsCommon.h>


namespace nPhysics
{
	class cBulletRigidBody : public iRigidBody
	{

	public:
		cBulletRigidBody(const sRigidBodyDef& def);
		~cBulletRigidBody();
		glm::mat4 GetTransform();
		//glm::vec3 GetPosition();
		//glm::vec3 GetEulerRotation();
		//glm::mat4 GetMatRotation();
		//float GetMass();
		//glm::vec3 GetVelocity();
		//glm::vec3 GetAccel();


		//void SetPosition(glm::vec3 position);
		//void SetEulerRotation(glm::vec3 rotation);
		//void SetMatRotation(glm::mat4 rotation);
		//void SetMass(float mass);
		void SetVelocity(glm::vec3 velocity);
		inline btRigidBody* GetBulletBody() { return mBody; }
		//void SettAccel(glm::vec3 accel);
	private:
		btDefaultMotionState* mMotionState;
		btRigidBody* mBody;
		btCollisionShape* mShape;
	};

}