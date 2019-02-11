#pragma once
#include <Interfaces/iShape.h>
#include <Interfaces/shapes.h>
#include "btBulletCollisionCommon.h"

namespace nPhysics
{
	class iBulletShapeInterface : public virtual iShape
	{
	public:
		
		virtual ~iBulletShapeInterface() {}

		inline btCollisionShape* GetBulletShape()
		{
			return mBulletShape;
		}
	protected:
		iBulletShapeInterface();
		iBulletShapeInterface(const iBulletShapeInterface& other) : iShape(other) {}
		iBulletShapeInterface& operator=(const iBulletShapeInterface& other) { return *this; }
		btCollisionShape* mBulletShape;
	};

	class cBulletSphereShape : public iBulletShapeInterface, public iSphereShape
	{
	public:
		cBulletSphereShape(float radius);
		virtual ~cBulletSphereShape();
		virtual float GetRadius();
	protected:
		//iShape
		cBulletSphereShape(const cBulletSphereShape& other) : iSphereShape(other) {}
		cBulletSphereShape& operator=(const cBulletSphereShape& other) { return *this; }

	};

}