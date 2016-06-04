#pragma once
#include "cocos2d.h"
#include "ICollidable.h"

using namespace cocos2d;

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

class Character : public ICollidable
{
public:
	bool active;
	std::list<Vec2>  wayPoints;
	Vec2  target;
	float speed = 90;

	Character();
	static Character* CreateCharacter(const char *sprite, std::list<Vec2> wayPoints);
	virtual void update(float delta);
	void Init();
	void SetTarget();
	bool onContactBegin(PhysicsContact& contact) override;
	bool onContactFinished(PhysicsContact& contact) override;
	void DestroyDelayed();

	~Character();
};

#endif // _CHARACTER_H_