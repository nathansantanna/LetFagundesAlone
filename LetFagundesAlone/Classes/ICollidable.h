#pragma once
#include "cocos2d.h"
#include "BodyTypes.h"
USING_NS_CC;

class ICollidable : public Sprite
{

public:

	void SetBody(PhysicsBody* body)
	{
		body->setGravityEnable(false);
		body->setCollisionBitmask(0x00000000);
		body->setContactTestBitmask(0xFFFFFFFF);
		body->setTag(BdICollidable);
		setPhysicsBody(body);
	}

	virtual bool onContactBegin(PhysicsContact& contact) = 0;
	virtual bool onContactFinished(PhysicsContact& contact) = 0;
};

