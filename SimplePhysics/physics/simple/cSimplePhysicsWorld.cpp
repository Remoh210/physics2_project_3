#pragma once
#include "cSimplePhysicsWorld.h"
#include <algorithm>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/projection.hpp>
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
			float radiusA;
			float radiusB;
			bodyA->mShape->GetSphereRadius(radiusA);
			bodyB->mShape->GetSphereRadius(radiusB);

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

				for (size_t idxB = 0; idxB < numBodies; idxB++)
				{

					cSimpleRigidBody* rbB = mBodies[idxB];
					if (rbA != rbB) 
					{
						if (CollisionTest(rbA, rbB))
						{
							if (rbA->GetShape()->GetShapeType() == nPhysics::SHAPE_TYPE_SPHERE && rbB->GetShape()->GetShapeType() == nPhysics::SHAPE_TYPE_SPHERE)
							{
								

								rbA->mPosition = rbA->mLastPos;
								rbB->mPosition = rbB->mLastPos;

								float massA = rbA->mMass;
								float massB = rbB->mMass;
								float totalMass = massA + massB;



								float fac1 = massA / totalMass;
								float fac2 = massB / totalMass;


								glm::vec3 x = rbA->mPosition - rbB->mPosition;
								x = glm::normalize(x);

								//	Then we calculate the x - direction velocity vector and the perpendicular y - vector.
								glm::vec3 v1 = rbA->mVelocity;
								float x1 = glm::dot(x, v1);// x.dot(vec{ v1 })
								glm::vec3 v1x = x * x1;
								glm::vec3 v1y = v1 - v1x;

								x = x * -1.0f;
								glm::vec3 v2 = rbB->mVelocity;
								float x2 = glm::dot(x, v2);
								glm::vec3 v2x = x * x2;
								glm::vec3 v2y = v2 - v2x;

								rbA->mVelocity = v1x * (massA - massB) / (massA + massB) +  v2x * (2 * massB) / (massA + massB) + v1y;
								rbB->mVelocity = v1x * (2 * massA) / (massA + massB) + v2x * (massB - massA) / (massA + massB) + v2y;
								rbA->mVelocity *= 0.95f;
								rbB->mVelocity *= 0.95f;
								//glm::vec3 norm2 = glm::normalize(rbB->mPosition - rbA->mPosition);
								//glm::vec3 reflectedVel2 = glm::reflect(rbB->mVelocity, norm2);
								//rbB->mVelocity = reflectedVel2 * fac2 * 0.95f;


								//glm::vec3 norm = glm::normalize(rbA->mPosition - rbB->mPosition);
								//glm::vec3 reflectedVel1 = glm::reflect(rbA->mVelocity, norm);
								//rbA->mVelocity = reflectedVel1 * fac1 * 0.95f;
							


								float rad;
								rbA->GetShape()->GetSphereRadius(rad);
								if (abs(rbA->mPosition.y) <= rad + 0.2f)
								{
									if (abs(rbA->mVelocity.x) <= 1.0f
										&& rbA->mVelocity.y <= 0.1f
									&& abs(rbA->mVelocity.z) <= 1.0f)
									{
										rbA->mPosition.y += 0.01;
										rbA->mVelocity = -(rbB->mVelocity * fac2);
									}
								}
	


							}


							if (rbB->GetShape()->GetShapeType() == nPhysics::SHAPE_TYPE_SPHERE && rbA->GetShape()->GetShapeType() == nPhysics::SHAPE_TYPE_PLANE)
							{


								

								rbB->mPosition = rbB->mLastPos;
								float radiusB;
								rbB->GetShape()->GetSphereRadius(radiusB);

								float constA;
								glm::vec3 normA;
								rbA->GetShape()->GetPlaneConstant(constA);
								rbA->GetShape()->GetPlaneNormal(normA);


								//if (abs(rbB->mVelocity.y) > 1.0f || normA.y != 1.0f)
								//{
								//	rbB->mVelocity = glm::reflect(rbB->mVelocity, normA);
								//	
								//}
								//rbB->mVelocity *= 0.95;

								//rbB->mVelocity *= 0.95;

								//rbB->mPosition = rbB->mLastPos;
								//float radiusB;
								//rbB->GetShape()->GetSphereRadius(radiusB);

								//float constA;
								//glm::vec3 normA;
								//rbA->GetShape()->GetPlaneConstant(constA);
								//rbA->GetShape()->GetPlaneNormal(normA);

								if(abs(rbB->mVelocity.y) > 1.0f && rbB->mPosition.y > 0.2f || normA.y != 1.0f)
								{
								rbB->mVelocity = glm::reflect(rbB->mVelocity, normA);
								glm::vec3 nComponent = glm::proj(rbB->mVelocity, normA);
								rbB->mVelocity -= nComponent * 0.2f;
								rbB->mVelocity *= 0.995f;
								}
								else {
									rbB->mVelocity *= 0.995f;
								}
								
								
								//	rbB->mVelocity *= 0.995f;
								
								


							}


						}
					}

				}




				if (rbA->GetShape()->GetShapeType() != nPhysics::SHAPE_TYPE_PLANE) {

					glm::vec3 horizontalDir = rbA->mVelocity - rbA->mPosition;
					horizontalDir.y = 0.0f;

					// Now the axis of rotation should be:
					glm::vec3 rotAxis = glm::normalize(glm::cross(horizontalDir, glm::vec3(0.0f, -1.0f, 0.0f)));

					// Kind of an Angular velocity
					float angVelocity = glm::length(glm::vec3(rbA->mVelocity.x, 0.0f, rbA->mVelocity.z)) * dt;

					glm::mat4 finalRotation(1.0f);
					finalRotation = glm::rotate(finalRotation, angVelocity/rbA->mMass, rotAxis);
					rbA->mRotation *= finalRotation;

					//float radius;
					//rbA->GetShape()->GetSphereRadius(radius);
					//
					//glm::vec3 Direction = rbA->mVelocity - rbA->mPosition;
					//glm::vec3 WorldPoint;
					//WorldPoint = rbA->mPosition + glm::normalize(Direction) * radius;
					//glm::vec3 SurfaceVelocity;
					//SurfaceVelocity = rbA->mVelocity + glm::cross(rbA->mAnguralVel, WorldPoint - rbA->mPosition);
					//glm::vec3 impulse = SurfaceVelocity * -0.2f * rbA->mMass;
					//rbA->mVelocity += impulse * (1 / rbA->mMass);
					//rbA->mAnguralVel += glm::cross(WorldPoint - rbA->mPosition, impulse *  (1 / rbA->mMass));
					//glm::mat4 finalRotation(1.0f);
					//glm::quat(glm::normalize(SurfaceVelocity));
					//rbA->mRotation = finalRotation;


					//RK4
					rbA->mLastPos = rbA->mPosition; 
					integrate(rbA->mPosition, rbA->mVelocity, mGravity, dt);
					//horizontalDir.y = 0.0f;
					//glm::vec3 rotAxis = glm::normalize(glm::cross(Direction, glm::vec3(0.0f, -1.0f, 0.0f)));
					//float angVelocity = glm::length(glm::vec3(rbA->mVelocity.x, 0.0f, rbA->mVelocity.z)) * dt;
				}

		}
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