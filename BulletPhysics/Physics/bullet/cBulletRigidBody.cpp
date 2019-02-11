#include "cBulletRigidBody.h"
#include "nConvert.h"

namespace nPhysics {

	cBulletRigidBody::cBulletRigidBody(const sRigidBodyDef& def)
	{
		btCollisionShape* colShape = new btSphereShape(btScalar(1.));
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar mass(def.Mass);
		bool isDynamic = (mass != 0.f);
		btVector3 localInertia(0, 0, 0);

		if (isDynamic)
		{
			colShape->calculateLocalInertia(mass, localInertia);
		}
		startTransform.setOrigin(nConvert::ToBullet(def.Position));
		mMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, mMotionState, colShape, localInertia);
		mBody = new btRigidBody(rbInfo);
		mBody->setLinearVelocity(nConvert::ToBullet(def.Velocity));
			
	}

	cBulletRigidBody::~cBulletRigidBody()
	{
		delete mBody;
		mBody = 0;
		delete mMotionState;
		mMotionState = 0;
	}

	glm::mat4 cBulletRigidBody::GetTransform()
	{	
		btTransform tranform;
		mMotionState->getWorldTransform(tranform);	
		return nConvert::ToSimple(tranform);
	}

	void cBulletRigidBody::SetVelocity(glm::vec3 velocity)
	{
	}
}