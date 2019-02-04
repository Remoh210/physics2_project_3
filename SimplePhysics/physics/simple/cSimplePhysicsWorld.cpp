#pragma once
#include "cSimplePhysicsWorld.h"
#include <algorithm>
namespace nPhysics
{
	cSimplePhysicsWorld::cSimplePhysicsWorld()
		:mDebugRenderer(0)
	{

	}

	cSimplePhysicsWorld::~cSimplePhysicsWorld() 
	{
		
	}
	void cSimplePhysicsWorld::SetDebugRenderer(iDebugRenderer* debugRenderer)
	{
		mDebugRenderer = debugRenderer;
	}
	void cSimplePhysicsWorld::DrawDebug()
	{
		if (!mDebugRenderer)
		{
			return;
		}
		for (size_t i = 0; i < mBodies.size(); i++)
		{
			//1 get the shape of body i
			//2 sphere - draw sphere
			//3 etc
		}
	}
	void cSimplePhysicsWorld::SetGravity(const glm::vec3& gravity)
	{
		this->mGravity = gravity;
	}

	bool cSimplePhysicsWorld::AddBody(iRigidBody* body)
	{
		//TODO: Check if already exists
		mBodies.push_back(body);
		return true;
	}

	bool cSimplePhysicsWorld::RemoveBody(iRigidBody* body)
	{
		return true;
	}

	void cSimplePhysicsWorld::Update(float dt)
	{
		//STEP 1 Integrate all rigid bodies
		//DO collison staff
		std::vector<std::pair<iRigidBody*, iRigidBody*>> collisions;
		size_t numBodies = mBodies.size();
		for (size_t idxA = 0; idxA < numBodies - 1; idxA++)
		{
			for (size_t idxB = idxA + 1; idxB < numBodies; idxB++)
			{
				if (Collide(mBodies[idxA], mBodies[idxB]))
				{
					collisions.push_back(std::make_pair(mBodies[idxA], mBodies[idxB]));
				}
			}
		}
		//STEP 3: TEll about coll
		//rip through
	}
	
	bool cSimplePhysicsWorld::Collide(iRigidBody* bodyA, iRigidBody* bodyB)
	{

		return false;
	}

}