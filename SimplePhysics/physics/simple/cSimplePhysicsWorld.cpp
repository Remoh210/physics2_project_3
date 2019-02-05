#pragma once
#include "cSimplePhysicsWorld.h"
#include <algorithm>
#include <glm/gtx/transform.hpp>
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

		cSimpleRigidBody* rb = dynamic_cast<cSimpleRigidBody*>(body);
		if (!rb)
		{
			return false;
		}
		std::vector<cSimpleRigidBody*>::iterator itRigidBody;
		itRigidBody = std::find(mBodies.begin(), mBodies.end(), rb);
		if (itRigidBody == mBodies.end())
		{
			mBodies.push_back(rb);
		}
		return true;
	}




	bool cSimplePhysicsWorld::CollisionTest(cSimpleRigidBody* bodyA, cSimpleRigidBody* bodyB)
	{

		// Sphere - sphere
		if ((bodyA->GetShape()->GetShapeType() == nPhysics::SHAPE_TYPE_SPHERE) &&
			(bodyB->GetShape()->GetShapeType() == nPhysics::SHAPE_TYPE_SPHERE))
		{
			float radiusA = bodyA->mShape->GetSphereRadius(radiusA);
			float radiusB = bodyB->mShape->GetSphereRadius(radiusB);
			float distance = glm::distance(bodyA->mPosition, bodyB->mPosition);
			if (distance <= radiusA + radiusB)
			{
				return true;
			}
		}
		else if ((bodyA->GetShape()->GetShapeType() == nPhysics::SHAPE_TYPE_PLANE) &&
			(bodyB->GetShape()->GetShapeType() == nPhysics::SHAPE_TYPE_SPHERE))
		{
			float constA;
			bodyA->mShape->GetPlaneConstant(constA);
			glm::vec3 normA;
			bodyA->mShape->GetPlaneNormal(normA);
			float radiusB;
			bodyB->mShape->GetSphereRadius(radiusB);

			// for a point gives the signed distance of the point to the plane
			float dist = glm::dot(bodyB->mPosition, normA) - constA;
			// If sphere center within +/-radius from plane, plane intersects sphere
			if (abs(dist) <= radiusB) {
				return true;
			}
		}
		return false;
		//else

	}


	bool cSimplePhysicsWorld::RemoveBody(iRigidBody* body)
	{
		return true;
	}

	void cSimplePhysicsWorld::Update(float dt)
	{
		//STEP 1 Integrate all rigid bodie

		if (mBodies.size() == 0) { return; }

		//DO collison staff
		std::vector<std::pair<cSimpleRigidBody*, cSimpleRigidBody*>> collisions;
		size_t numBodies = mBodies.size();
		for (size_t idxA = 0; idxA < numBodies; idxA++)
		{

			cSimpleRigidBody* rbA = mBodies[idxA];

			////rbA->GetShape()->GetShapeType()
			//switch (rbA->GetShape()->GetShapeType())
			//{
			//case nPhysics::SHAPE_TYPE_PLANE:
			//	continue;   // Do not update physics to planes
			//	break;
			//case nPhysics::SHAPE_TYPE_SPHERE:
			//{
				for (size_t idxB = 0; idxB < numBodies; idxB++)
				{

					cSimpleRigidBody* rbB = mBodies[idxB];
					if (rbA != rbB) 
					{
						if (CollisionTest(rbA, rbB))
						{
							if (rbA->GetShape()->GetShapeType() == nPhysics::SHAPE_TYPE_SPHERE && rbB->GetShape()->GetShapeType() == nPhysics::SHAPE_TYPE_SPHERE)
							{
								float massA = rbA->mMass;
								float massB = rbB->mMass;
								float totalMass = massA + massB;

								rbA->mPosition = rbA->mLastPos;
								rbB->mPosition = rbB->mLastPos;

								glm::vec3 velA = rbA->mVelocity;
								glm::vec3 velB = rbB->mVelocity;
								float cR = 0.2f;

								rbA->mVelocity = (cR * massB*(velB - velA) + massA * velA + massB * velB) / totalMass;
								rbB->mVelocity = (cR * massB*(velA - velB) + massB * velB + massA * velA) / totalMass;

							}


							if (rbB->GetShape()->GetShapeType() == nPhysics::SHAPE_TYPE_SPHERE && rbA->GetShape()->GetShapeType() == nPhysics::SHAPE_TYPE_PLANE)
							{

								float radiusB;
								rbB->GetShape()->GetSphereRadius(radiusB);
								
								{
									rbB->mPosition = rbB->mLastPos;
									float constA;
									glm::vec3 normA;
									rbA->GetShape()->GetPlaneConstant(constA);
									rbA->GetShape()->GetPlaneNormal(normA);

									rbB->mVelocity = glm::reflect(rbB->mVelocity, normA) * 0.95f;


									//rb1->mPosition.y = rb2->mPosition.y + sphere1->getRadius();// +0.01f;
									//rb1->mVelocity.y = -(rb1->mVelocity.y);

								}

							}


						}
					}

				}

	//		}
		//	default:
		//		break;
		//	}




				if (rbA->GetShape()->GetShapeType() != nPhysics::SHAPE_TYPE_PLANE) {
					// Rotation
					// Let's consider only the velocity of the object in Z local axis
					// Also getting rid of pitch information (Y axis)
					glm::vec3 horizontalDir = rbA->mVelocity - rbA->mPosition;
					horizontalDir.y = 0.0f;

					// Now the axis of rotation should be:
					glm::vec3 rotAxis = glm::normalize(glm::cross(horizontalDir, glm::vec3(0.0f, -1.0f, 0.0f)));

					// Kind of an Angular velocity
					float angVelocity = glm::length(glm::vec3(rbA->mVelocity.x, 0.0f, rbA->mVelocity.z)) * dt;

					glm::mat4 finalRotation(1.0f);
					finalRotation = glm::rotate(finalRotation, angVelocity, rotAxis);
					rbA->mRotation *= finalRotation;




					// Get the per second velocity of the bal





					//RK4
					rbA->mLastPos = rbA->mPosition; // Save the last position
					integrate(rbA->mPosition, rbA->mVelocity, mGravity, dt);
				}










			/*for (size_t idxB = idxA + 1; idxB < numBodies; idxB++)
			{
				if (Collide(mBodies[idxA], mBodies[idxB]))
				{
					collisions.push_back(std::make_pair(mBodies[idxA], mBodies[idxB]));
				}
			}*/
		}
		//STEP 3: TEll about coll
		//rip through
	}
	


	void cSimplePhysicsWorld::integrate(glm::vec3& pos, glm::vec3& vel, glm::vec3 accel, float dt)
	{
		{
			// Put the acceleration into the velocity
			glm::vec3 newVel = vel + accel * dt;

			RK4_State state;
			state.x = pos;
			state.v = newVel;

			RK4_Derivative a, b, c, d;

			a = evaluate(state, 0.0f, RK4_Derivative());
			b = evaluate(state, dt*0.5f, a);
			c = evaluate(state, dt*0.5f, b);
			d = evaluate(state, dt, c);

			glm::vec3 dxdt = 1.0f / 6.0f *
				(a.dx + 2.0f * (b.dx + c.dx) + d.dx);

			glm::vec3 dvdt = 1.0f / 6.0f *
				(a.dv + 2.0f * (b.dv + c.dv) + d.dv);

			pos = state.x + dxdt * dt;
			vel = state.v + dvdt * dt;
		}
	}

	cSimplePhysicsWorld::RK4_Derivative cSimplePhysicsWorld::evaluate(const RK4_State& initial, float dt, const RK4_Derivative& d)
	{
		RK4_State state;
		state.x = initial.x + d.dx*dt;
		state.v = initial.v + d.dv*dt;

		RK4_Derivative output;
		output.dx = state.v;
		return output;
	}

}