#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

Bullet * Bullet::CreateBullet(const char * sprite)
{
	Bullet* _tempBullet = new Bullet();

	if (_tempBullet && _tempBullet->initWithFile(sprite))
	{
		_tempBullet->scheduleUpdate();
		_tempBullet->autorelease();
		_tempBullet->target = nullptr;
		_tempBullet->scheduleUpdate();
		return _tempBullet;
	}
	CC_SAFE_DELETE(_tempBullet);

	return nullptr;
}

void Bullet::update(float delta)
{
	if (target == nullptr)
		return;
	Character* t = static_cast<Character*>(target);

	if (!t->active)
	{
		this->removeFromParentAndCleanup(true);
		return;
	}

	float dy = t->getPosition().y - getPosition().y;

	float dx = t->getPosition().x - getPosition().x;

	if (dx == 0 || dy == 0)
		return;
	float d = sqrt((dy*dy) + (dx*dx));
	float f = (speed  * delta)/ d;
	if (f < 1) {
		dy = dy * f;
		dx = dx * f;
	}
	setPosition(ccp(getPosition().x + dx, getPosition().y + dy));
}

void Bullet::Init(Node& ptarget)
{
	SetBody(PhysicsBody::createBox(boundingBox().size));
	setTag(BdBullet);

	if (target == nullptr  && ptarget.getTag() == BdCharacter)
		target = &ptarget;
}

bool Bullet::onContactBegin(PhysicsContact& contact)
{
	Node* nodeA = contact.getShapeA()->getBody()->getNode();
	Node* nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA->getTag() == BdCharacter || nodeB->getTag() == BdCharacter)
		this->runAction(Sequence::create(
			DelayTime::create(0.1f),
			CallFunc::create(CC_CALLBACK_0(Bullet::DestroyDelayed, this)),
			nullptr));

	return true;
}

bool Bullet::onContactFinished(PhysicsContact& contact)
{
	return false;
}

void Bullet::DestroyDelayed()
{
	this->getParent()->removeChild(this);
}
