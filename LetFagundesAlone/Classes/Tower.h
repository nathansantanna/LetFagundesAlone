#pragma once
#include "cocos2d.h"
#include "Bullet.h"
#include "Character.h"

#ifndef __TOWER_H__
#define __TOWER_H__

using namespace cocos2d;

class Tower : public ICollidable
{
private:
	void DrawRange(float range, Rect center);
	
public:
	float _shotCoolDown = 3;
	float _timer = 3;

	Bullet * _bullet;
	PhysicsBody * _physicsBody;
	DrawNode *drawnode;
	Character* target;

	static Tower* CreateTower(const char *sprite, 
		float range);
	void Init(float range);
	void ShootWeapon(float delta);
	bool onContactBegin(PhysicsContact& contact) override;
	bool onContactFinished(PhysicsContact& contact) override;


	void update(float delta) override;
	void Shot(const char *sprite , Node* ptarget);
	CREATE_FUNC(Tower);

	~Tower();
};
#endif // __TOWER_H__
