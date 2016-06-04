#pragma once
#include "cocos2d.h"
#include "Tower.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <SimpleAudioEngine.h>
#include "Character.h"
USING_NS_CC;


class EastSide :
	public cocos2d::Layer
{
protected:
	Vector<Tower*> towers;
	std::list<Vec2>  characterwayPoints;
	Vec2 startPosition;
	int countEnemies;
	Vector<Node*> towerWayPoints;
	Vector<Character*> characters;
	float _ratio = 2;
	float _timer = 3;

public:
	static cocos2d::Scene* createScene();
	bool init() override;
	void update(float delta) override;

	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*) override;
	void onTouchEnded(cocos2d::Touch*, cocos2d::Event*) override;
	void onTouchMoved(cocos2d::Touch*, cocos2d::Event*) override;
	void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*) override;

	virtual bool onContactBegin(PhysicsContact& contact);
	virtual bool onContactFinished(PhysicsContact& contact);
	CREATE_FUNC(EastSide);
	
	EastSide();
	~EastSide();
private:
	void AssignTouchCallbacks();
};
