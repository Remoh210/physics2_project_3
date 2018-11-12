#include "cFollowObjectCommand.h"

void cFollowObjectCommand::Initialize(std::vector<sNVPair> vecNVPairs)
{
	// Pull the data out of the vector
	this->idealCameraLocation = vecNVPairs[0].v3Value;	// idealCameraLocation
	this->minDistance = vecNVPairs[1].fValue;			// minDistance;	
	this->maxSpeedDistance = vecNVPairs[2].fValue;		// maxSpeedDistance
	this->maxSpeed = vecNVPairs[3].fValue;				// maxSpeed
	//
	//this->currentLocation = vecNVPairs[4].v3Value;

	return;
}

void cFollowObjectCommand::Update(double deltaTime)
{
	// Get the information from the object that is moving
	float currentDistance = glm::distance(this->idealCameraLocation, this->currentLocation);

	if (currentDistance <= this->minDistance)
	{
		// Yes, like Lady Gaga, I have arrived...
		this->m_bIsDone = true;
		return;
	}

	// Here, I am NOT where I'm supposed to be, so I need to move.
	// Calculate the direction vector to the target location
	glm::vec3 vDirection = this->idealCameraLocation - this->currentLocation;

	// To calc velocity, I will normalize
	glm::vec3 vVel = glm::normalize(vDirection);

	// Scale this with the speed we want to go...
	vVel = vVel * maxSpeed;

	// How far to move in THIS time step?
	glm::vec3 deltaMove = vVel * (float)deltaTime;

	//currentLocation += deltaMove;

	return;
}

bool cFollowObjectCommand::isFinished(void)
{
	return this->m_bIsDone;
}
