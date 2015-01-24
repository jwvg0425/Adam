#include "GameScene.h"
#include "MainUILayer.h"
#include "macro.h"
#include "GameManager.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	
	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer,0,SCENE_LAYER_TAG);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	if ( !LayerColor::initWithColor(Color4B(48,48,48,255)))
	{
		return false;
	}

	auto background = Sprite::create("background.png");

	addChild(background);
	background->setAnchorPoint(Point(0.5, 0.5));
	background->setPosition(WND_WIDTH / 2, WND_HEIGHT / 2);

	m_Black = Sprite::create("black.png");
	addChild(m_Black);
	m_Black->setAnchorPoint(Point(0.5, 0.5));
	m_Black->setPosition(WND_WIDTH / 2, WND_HEIGHT / 2);

	GameManager::getInstance()->turnStart(this);
	
	m_MainUILayer = MainUILayer::create();
	addChild(m_MainUILayer);
	m_MainUILayer->setVisible(false);

	scheduleUpdate();
	
	return true;
}

void GameScene::setMainUIVisible(bool visible)
{
	m_MainUILayer->setVisible(visible);
}
