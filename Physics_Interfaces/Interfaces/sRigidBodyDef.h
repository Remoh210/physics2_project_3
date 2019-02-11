#pragma once

#include<glm/glm.hpp>

namespace nPhysics
{
	struct sRigidBodyDef
	{
		sRigidBodyDef() 
			: Mass(0.0f) 
			, Position(0.0f, 0.0f, 0.0f)
			, Velocity(0.0f, 0.0f, 0.0f)
			, Orientation(0.0f, 0.0f, 0.0f)
		{

		}
		
		glm::vec3 Position;
		glm::vec3 Velocity;
		glm::vec3 Orientation; //Euler Angles
		float Mass;
	};
}