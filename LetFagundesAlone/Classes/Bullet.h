#pragma once
#include "cocos2d.h"
#include "Character.h"
USING_NS_CC;


#ifndef __BULLET_H__
#define __BULLET_H__

class Bullet : public ICollidable
{
public:
	Node* target;
	float speed = 150;

	static Bullet* CreateBullet(const char *sprite);
	void MoveBullet(float delta);
	void update(float) override;
	void Init(Node & ptarget);
	bool onContactBegin(PhysicsContact& contact) override;
	bool onContactFinished(PhysicsContact& contact) override;
	void DestroyDelayed();
	Bullet();
	~Bullet();
};

#endif // __BULLET_H__