#pragma once

#include "cSimpleRigidBody.h"
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp>



namespace nPhysics
{
	cSimpleRigidBody::cSimpleRigidBody() 
		: iRigidBody() 
	{

	}
	cSimpleRigidBody::cSimpleRigidBody(const cSimpleRigidBody& other) 
		: iRigidBody(other)
	{

	}
	cSimpleRigidBody& cSimpleRigidBody:: operator = (const cSimpleRigidBody& other) 
	{
		return *this; 
	}

	cSimpleRigidBody::cSimpleRigidBody(const sRigidBodyDef& def, iShape* shape) 
		: mMass(def.Mass)
		, mPosition(def.Position)
		, mVelocity(def.Velocity)
		, mShape(shape)
	{

	}
	cSimpleRigidBody::~cSimpleRigidBody()
	{

	}


	//Getters

	iShape* cSimpleRigidBody::GetShape()
	{
		return this->mShape;

	}

	glm::mat4 cSimpleRigidBody::GetTransform()
	{
		return glm::translate(glm::mat4(), mPosition);
		//TODO: Orientation
	}

	glm::vec3 cSimpleRigidBody::GetPosition()
	{
		return this->mPosition;
	}

	glm::vec3 cSimpleRigidBody::GeRotation()
	{
		
		return  glm::eulerAngles(mRotation);
	}

	glm::vec3 cSimpleRigidBody::GetVelocity()
	{
		return this->mVelocity;
	}

	glm::vec3 cSimpleRigidBody::GetAccel()
	{
		return this->mAcceleration;
	}
	float cSimpleRigidBody::GetMass()
	{
		return this->mMass;
	}


	//Setters
	void cSimpleRigidBody::SetPosition(glm::vec3 position)
	{
		this->mPosition = position;
	}

	void cSimpleRigidBody::SetRotation(glm::vec3 rotation)
	{
		this->mRotation = glm::quat(rotation);
	}

	void cSimpleRigidBody::SettAccel(glm::vec3 accel)
	{
		this->mAcceleration = accel;
	}

	void cSimpleRigidBody::SetVelocity(glm::vec3 velocity)
	{
		this->mVelocity = velocity;
	}


	void cSimpleRigidBody::SetMass(float mass)
	{
		this->mMass = mass;
	}




}