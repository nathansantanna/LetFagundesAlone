#include "Character.h"

Character::Character()
{
}

Character * Character::CreateCharacter(const char * sprite, std::list<Vec2>  wayPoints)
{
	Character* _tempCharacter = new Character();
	if (_tempCharacter && _tempCharacter->initWithFile(sprite))
	{
		_tempCharacter->wayPoints = wayPoints;
		_tempCharacter->autorelease();
		_tempCharacter->Init();
		_tempCharacter->scheduleUpdate();
		return _tempCharacter;
	}
	CC_SAFE_DELETE(_tempCharacter);

	return nullptr;
}

void Character::update(float delta)
{
	float dy = target.y - getPosition().y;

	float dx = target.x - getPosition().x;

	if (dx == 0 || dy == 0)
		return;
	float d = sqrt((dy*dy) + (dx*dx));
	float f = (speed * delta) / d;
	if (f < 1) {
		dy = dy * f;
		dx = dx * f;
	}
	setPosition(ccp(getPosition().x + dx, getPosition().y + dy));
	if (getPosition().x == target.x && getPosition().y == target.y)
		SetTarget();
}

void Character::Init()
{
	active = true;
	SetBody(PhysicsBody::createBox(boundingBox().size));
	setTag(BdCharacter);
	SetTarget();

}

void Character::SetTarget()
{
	if ( !wayPoints.empty())
	{
		
		target = wayPoints.front();
		wayPoints.pop_front();
			
	}
}

bool Character::onContactBegin(PhysicsContact& contact)
{
	Node* nodeA = contact.getShapeA()->getBody()->getNode();
	Node* nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA->getTag() == BdBullet || nodeB->getTag() == BdBullet)
		this->runAction(Sequence::create(
			DelayTime::create(0.1f),
			CallFunc::create(CC_CALLBACK_0(Character::DestroyDelayed, this)),
			nullptr));

	return true;
}

bool Character::onContactFinished(PhysicsContact & contact)
{
	return true;
}

void Character::DestroyDelayed()
{
	this->removeFromParentAndCleanup(true);
	active = false;
}

Character::~Character()
{
	this->release();
}
