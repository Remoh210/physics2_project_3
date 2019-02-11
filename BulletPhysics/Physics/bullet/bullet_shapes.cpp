#include "bullet_shapes.h"

namespace nPhysics
{
	iBulletShapeInterface::iBulletShapeInterface()
		: iShape(SHAPE_TYPE_SPHERE)
	{
	}
	cBulletSphereShape::cBulletSphereShape(float radius)
		: iBulletShapeInterface()
		, iSphereShape()
		
	{
		mBulletShape = new btSphereShape(btScalar(radius));
	}
	cBulletSphereShape::~cBulletSphereShape()
	{
		delete mBulletShape;
	}
	float cBulletSphereShape::GetRadius()
	{
		return 0.0f;
	}

}
