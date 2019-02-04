#pragma once
#include "physics_interfaces.h"
#include <vector>


namespace nPhysics
{
	class cSimplePhysicsWorld : public iPhysicsWorld {
	public:
		cSimplePhysicsWorld();
		virtual ~cSimplePhysicsWorld();
		virtual void SetDebugRenderer(iDebugRenderer* debugRenderer);
		virtual void DrawDebug();
		virtual void SetGravity(const glm::vec3& gravity);
		virtual bool AddBody(iRigidBody* body);
		virtual bool RemoveBody(iRigidBody* body);
		virtual void Update(float dt);

	private:
		iDebugRenderer* mDebugRenderer;
		bool Collide(iRigidBody* bodyA, iRigidBody* bodyB); 
		glm::vec3 mGravity;
		std::vector<iRigidBody*> mBodies;

	};
}