#include "EastSide.h"
USING_NS_CC;

EastSide::EastSide()
{

}

EastSide::~EastSide()
{

}

bool EastSide::init()
{
	if (!Layer::init())
		return false;
	AssignTouchCallbacks();

	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	Node* rootNode = CSLoader::createNode("MainScene.csb");
	this->scheduleUpdate();
	addChild(rootNode);
	
	
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

	// set the background music and continuously play it.
	audio->playBackgroundMusic("POL-unbeatable-guild-short.wav", true);

	int count = 0;
	countEnemies = 0;
	startPosition = rootNode->getChildByName("start")->getPosition();
	while(rootNode->getChildByName("waypoint_" + Value(count).asString()) != nullptr)
	{
		Vec2 v = rootNode->getChildByName("waypoint_" + Value(count).asString())->getPosition();
		characterwayPoints.insert(characterwayPoints.end(), v);
		count++;
	}
	count = 0;
	while (rootNode->getChildByName("tower_" + Value(count).asString()) != nullptr)
	{
		Node* v = rootNode->getChildByName("tower_" + Value(count).asString());
		
		towerWayPoints.insert(towerWayPoints.size(), v);
		count++;
	}
	
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(EastSide::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(EastSide::onContactFinished, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	
	return true;
}

void EastSide::AssignTouchCallbacks()
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(EastSide::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(EastSide::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(EastSide::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(EastSide::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}


Scene* EastSide::createScene()
{
	Scene *scene = Scene::createWithPhysics();
	EastSide *layer = create();
	scene->addChild(layer);
	
	return scene;
}

void EastSide::update(float delta)
{
	_timer += delta;
	if (countEnemies < 10 && _timer > _ratio)
	{
		Character* character = static_cast<Character *>(Character::CreateCharacter("char.png", characterwayPoints));
		character->setPosition(startPosition);
		this->addChild(character);
		_timer = 0;
		countEnemies++;
	}
}

bool EastSide::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void EastSide::onTouchEnded(Touch* touch, Event* event)
{
	bool t = false;
	Vec2  pontomaldito;
	for (size_t i = 0; i < towerWayPoints.size(); i++)
	{
		float ymin = towerWayPoints.at(i)->boundingBox().getMinY();
		float ymax = towerWayPoints.at(i)->boundingBox().getMaxY();
		float xmin = towerWayPoints.at(i)->boundingBox().getMinX();
		float xmax = towerWayPoints.at(i)->boundingBox().getMaxX();
		
		if (towerWayPoints.at(i)->boundingBox().containsPoint(touch->getLocation()))
		{
			
			pontomaldito = towerWayPoints.at(i)->getPosition();
			t = true;
			towerWayPoints.at(i)->removeFromParent();
			towerWayPoints.erase(i);
			break;
			
		}
	}

	if (t)
	{
		Tower* tower;
		tower = static_cast<Tower *>(Tower::CreateTower("tower.png", 150));
		tower->setPosition(pontomaldito);
		this->addChild(tower);
		towers.insert(towers.size(), tower);
		this->scheduleUpdate();
	}
}

void EastSide::onTouchMoved(Touch* touch, Event* event)
{

}

void EastSide::onTouchCancelled(Touch* touch, Event* event)
{

}

bool EastSide::onContactBegin(PhysicsContact& contact)
{
	auto *temp = contact.getShapeA()->getBody();
	if (temp->getTag() == BdICollidable)
		static_cast<ICollidable*>(temp->getNode())->onContactBegin(contact);

	temp = contact.getShapeB()->getBody();
	if (temp->getTag() == BdICollidable)
		static_cast<ICollidable*>(temp->getNode())->onContactBegin(contact);
	return true;
}

bool EastSide::onContactFinished(PhysicsContact& contact)
{
	auto *temp = contact.getShapeA()->getBody();
	if (temp->getTag() == BdICollidable)
		static_cast<ICollidable*>(temp->getNode())->onContactFinished(contact);

	temp = contact.getShapeB()->getBody();
	if (temp->getTag() == BdICollidable)
		static_cast<ICollidable*>(temp->getNode())->onContactFinished(contact);

	return true;
}