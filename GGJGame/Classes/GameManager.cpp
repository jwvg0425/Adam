#include "GameManager.h"
#include "GameScene.h"
#include "ChatWindow.h"

USING_NS_CC;

GameManager* GameManager::m_Instance = nullptr;


GameManager* GameManager::getInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new GameManager;
	}

	return m_Instance;
}

void GameManager::releaseInstance()
{
	if (m_Instance != nullptr)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}

GameManager::GameManager()
{
	m_Civilization = 0;
	m_Culture = 0;
	m_Population = 5;
	m_Food = 3;
	m_Resource = 5;
	m_Year = 4000;
	m_Month = 1;
	m_Turn = 0;
}

GameManager::~GameManager()
{

}

int GameManager::getPopulation()
{
	return m_Population;
}

int GameManager::getFood()
{
	return m_Food;
}

int GameManager::getResource()
{
	return m_Resource;
}

int GameManager::getCulture()
{
	return m_Culture;
}

int GameManager::getCivilization()
{
	return m_Civilization;
}

int GameManager::getYear()
{
	return m_Year;
}

int GameManager::getMonth()
{
	return m_Month;
}

void GameManager::turnStart(cocos2d::Layer* runningLayer)
{
	if (m_Turn == 0)
	{
		std::vector<std::string> firstChat =
		{
			"아담.",
			"아담, 우린 이제 어떻게 해야 하죠?",
			"모든 게 무너졌습니다. 인류가 그 동안 쌓아올렸던 모든 것들이, 먼지처럼 사라져버렸습니다.",
			"아담, 당신이 우리의 마지막 희망입니다."
		};

		runningLayer->addChild(ChatWindow::createWithCallback(firstChat, CC_CALLBACK_0(GameScene::gameStartAction, static_cast<GameScene*>(runningLayer)),6.0f));
	}
}

void GameManager::turnEnd()
{

}

void GameManager::setChatting(bool chat)
{
	m_IsChatting = chat;
}

bool GameManager::isChatting()
{
	return m_IsChatting;
}
