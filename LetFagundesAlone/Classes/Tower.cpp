#include "Tower.h"
#include <SimpleAudioEngine.h>


Tower * Tower::CreateTower(const char * sprite, float range)
{
	Tower* _tempTower = new Tower();
	if (_tempTower && _tempTower->initWithFile(sprite))
	{
		_tempTower->scheduleUpdate();
		_tempTower->autorelease();
		_tempTower->Init(range);
		return _tempTower;
	}

	CC_SAFE_DELETE(_tempTower);
	return NULL;
}

void Tower::Init(float range)
{
	SetBody(PhysicsBody::createCircle(range));
	setTag(BdTower);
	DrawRange(range + 10, boundingBox());
}

bool Tower::onContactBegin(PhysicsContact& contact)
{
	Node* nodeA = contact.getShapeA()->getBody()->getNode();
	Node* nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA->getTag() == BdCharacter)
		target = static_cast<Character*>(nodeA);
	if (nodeB->getTag() == BdCharacter)
		target = static_cast<Character*>(nodeB);

	return true;
}

bool Tower::onContactFinished(PhysicsContact& contact)
{
	target = nullptr;
	return true;
}

void Tower::DrawRange(float range, Rect center)
{
	const int radius = range;
	const int ncount = 150;
	drawnode = DrawNode::create();

	CCPoint Circle[ncount];
	for (int i = 0; i < ncount; i++) {
		float rads = i * (2.0f * M_PI / 150);
		Circle[i].x = (radius * (1.1f * cosf(rads)));
		Circle[i].y = (radius * sinf(rads));
	}
	addChild(drawnode);
	drawnode->setPosition(center.getMaxX(), +center.getMaxY());
	drawnode->drawPolygon(Circle, ncount, Color4F(255, 255, 255, 0), 2, Color4F(255, 255, 255, 0.5f));
}

void Tower::update(float delta)
{
	_timer += delta;
	if (target != nullptr && _timer > _shotCoolDown)
	{
		Shot("bullet.png", target);
		_timer = 0;
	}
}

void Tower::Shot(const char* sprite, Node* ptarget)
{
	_bullet = static_cast<Bullet*>(Bullet::CreateBullet(sprite));
	_bullet->setPosition(getPosition());
	_bullet->Init(*target);
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
}

Tower::~Tower()
{
}
