#include "GameScene.h"
#include "MainUILayer.h"
#include "macro.h"
#include "GameManager.h"
#include "ChatWindow.h"

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

	auto background = Sprite::create("graphic\\background.png");

	addChild(background);
	background->setAnchorPoint(Point(0.5, 0.5));
	background->setPosition(WND_WIDTH / 2, WND_HEIGHT / 2);

	m_Black = Sprite::create("graphic\\black.png");
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

void GameScene::turnStartAction()
{
	auto firstDelay = DelayTime::create(1);
	auto blackFade = FadeOut::create(2);
	auto delay = DelayTime::create(1);
	auto callback = CallFuncN::create(CC_CALLBACK_1(GameScene::startTurn, this));
	auto action = Sequence::create(firstDelay, blackFade, delay, callback,nullptr);
	m_Black->runAction(action);
}

void GameScene::startTurn(cocos2d::Node* sender)
{
	setMainUIVisible(true);
	m_Black->removeFromParent();
}

void GameScene::turnEndAction()
{
	setMainUIVisible(false);

	m_Black = Sprite::create("graphic\\black.png");
	m_Black->setOpacity(0);
	m_Black->setPosition(WND_WIDTH / 2, WND_HEIGHT / 2);

	addChild(m_Black);

	auto firstDelay = DelayTime::create(1);
	auto blackFade = FadeIn::create(2);
	auto delay = DelayTime::create(2);
	auto callback = CallFuncN::create(CC_CALLBACK_0(GameScene::turnChat, this));
	auto action = Sequence::create(firstDelay, blackFade, delay, callback, nullptr);

	m_Black->runAction(action);
}


void GameScene::turnChat()
{
	GameManager::getInstance()->turnStart(this);

	std::vector<std::string> chatList =
	{
		"아담, 깨어날 시간입니다.",
		"아담, 저희는 올바른 방향으로 잘 나아가고 있는 것이겠지요?",
		"아담, 이번에는 무엇을 해야 할까요?",
		"아담, 저희에게 이젠 당신 뿐입니다.",
		"아담, 우리는 언제쯤 예전과 같은 생활로 돌아갈 수 있을까요?",
		"아담, 너무 불안하군요.",
		"아담, 인간들은 도대체 왜 알면서도 어리석은 짓을 반복하는 걸까요?",
		"아담, 우리는 끝이 정해져 있는 일에 의미없는 노력을 쏟아붓고 있는 건 아닐까요?",
		"아담, 어떻게 해야할 지 모르겠습니다. 하루하루가 불안해서 미칠 것 같네요.",
		"아담, 오늘도 우리에게 가르침을.",
		"아담, 아담은 아담해서 아담인가요?",
		"아담, 이브는 어디로 갔나요.",
	};

	if (GameManager::getInstance()->isGameOver())
	{
		char date[255];

		sprintf(date, "인류 문명, %d년 %d월에 막을 내리다.", GameManager::getInstance()->getYear(), GameManager::getInstance()->getMonth());
		std::vector<std::string> chat =
		{
			"슈퍼 컴퓨터 아담의 말만 믿고 따라온 인류 문명은",
			"아담이 너무 멍청했던 바람에 결국 멸망하고 말았다.",
			date
		};

		ChatWindow* chatWindow = ChatWindow::createWithCallback(chat, CC_CALLBACK_0(GameScene::gameOver, this));
		addChild(chatWindow);
	}
	else if (GameManager::getInstance()->testGameClear())
	{
		char date[255];

		sprintf(date, "슈퍼 컴퓨터 아담, %d년 %d월 폐기되다.", GameManager::getInstance()->getYear(), GameManager::getInstance()->getMonth());

		std::vector<std::string> chat =
		{
			"아담, 드디어 인류 문명은 이전 수준을 회복한 것 같습니다.",
			"그동안 감사했습니다. 당신이 있었기에, 인류는 여기까지 버틸 수 있었습니다.",
			"이제 푹 쉬세요, 아담. 우리는 이제 당신의 도움 없이도 잘 살아갈 수 있을 것 같습니다.",
			"다시 한 번, 감사드립니다. 아담.",
			date
		};
		ChatWindow* chatWindow = ChatWindow::createWithCallback(chat, CC_CALLBACK_0(GameScene::gameOver, this));
		addChild(chatWindow);

	}
	else
	{

		std::vector <std::string> chat;

		chat.push_back(chatList[rand() % chatList.size()]);

		ChatWindow* chatWindow = ChatWindow::createWithCallback(chat, CC_CALLBACK_0(GameScene::turnStartAction, this));

		addChild(chatWindow);
	}
}

void GameScene::gameOver()
{
	Director::getInstance()->end();
}
