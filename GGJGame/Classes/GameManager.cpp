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

	initRegion();
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

		runningLayer->addChild(
			ChatWindow::createWithCallback(firstChat, 
			CC_CALLBACK_0(GameScene::gameStartAction, static_cast<GameScene*>(runningLayer)), 8.0f));
	}
	else
	{
		m_Month++;
		if (m_Month > 12)
		{
			m_Month = 1;
			m_Year++;
		}
	}

	m_Turn++;
}

void GameManager::turnEnd(cocos2d::Layer* runningLayer)
{
	turnStart(runningLayer);
}

void GameManager::setChatting(bool chat)
{
	m_IsChatting = chat;
}

bool GameManager::isChatting()
{
	return m_IsChatting;
}

void GameManager::initRegion()
{
	m_RegionData[RT_ALASKA_CANADA] = RegionData("알래스카 / 캐나다", "map\\alaska_canada.png", Rect(276, 24, 154, 76));
	m_RegionData[RT_ARGENTINA_CHILE] = RegionData("아르헨티나 / 칠레", "map\\argentina_chile.png", Rect(399, 242, 40, 71));
	m_RegionData[RT_BRAZIL] = RegionData("브라질", "map\\brazil.png", Rect(412, 192, 50, 76));
	m_RegionData[RT_CARIBBEAN] = RegionData("카리브", "map\\caribbean.png", Rect(391, 183, 39, 65));
	m_RegionData[RT_CENTRAL_AFRICA] = RegionData("중앙 아프리카", "map\\central_africa.png", Rect(34, 161, 39, 53));
	m_RegionData[RT_CENTRAL_AMERICA] = RegionData("중앙 아메리카", "map\\central_america.png", Rect(321, 88, 118, 82));
	m_RegionData[RT_CHINA] = RegionData("중국", "map\\china.png", Rect(137, 94, 68, 51));
	m_RegionData[RT_EAST_AFRICA] = RegionData("동 아프리카", "map\\east_africa.png", Rect(69, 165, 36, 51));
	m_RegionData[RT_EUROPE] = RegionData("유럽", "map\\europe.png", Rect(19, 46, 50, 76));
	m_RegionData[RT_GREENLAND] = RegionData("그린란드", "map\\greenland.png", Rect(411, 20, 70, 55));
	m_RegionData[RT_INDO] = RegionData("인도", "map\\indo.png", Rect(111, 125, 48, 45));
	m_RegionData[RT_JAPAN] = RegionData("일본 열도", "map\\japan.png", Rect(223, 101, 26, 27));
	m_RegionData[RT_KOREA] = RegionData("한국", "map\\korea.png", Rect(209, 115, 10, 10));
	m_RegionData[RT_MEXICO] = RegionData("멕시코", "map\\mexico.png", Rect(349, 154, 62, 41));
	m_RegionData[RT_NORTH_AFRICA] = RegionData("북 아프리카", "map\\north_africa.png", Rect(16, 126, 59, 40));
	m_RegionData[RT_NORTH_ASIA] = RegionData("북 아시아", "map\\north_asia.png", Rect(66, 47, 202, 50));
	m_RegionData[RT_OCEANIA] = RegionData("오세아니아", "map\\oceania.png", Rect(177, 193, 91, 66));
	m_RegionData[RT_SOUTH_AFRICA] = RegionData("남 아프리카", "map\\south_africa.png", Rect(39, 212, 68, 50));
	m_RegionData[RT_SOUTH_EAST_ASIA] = RegionData("동남 아시아", "map\\south_east_asia.png", Rect(155, 141, 80, 65));
	m_RegionData[RT_SOUTH_WEST_ASIA] = RegionData("서남 아시아", "map\\south_west_asia.png", Rect(64, 114, 51, 45));
	m_RegionData[RT_WEST_AFRICA] = RegionData("서 아프리카", "map\\west_africa.png", Rect(3, 126, 52, 70));

	m_RegionData[RT_KOREA].m_IsDeveloped = true;
	m_RegionData[RT_KOREA].m_IsKnown = true;
	m_RegionData[RT_KOREA].m_Radioactivity = 100;
	m_RegionData[RT_KOREA].m_Stablity = 200;
	m_RegionData[RT_KOREA].m_Wealthy = 50;
}

const RegionData& GameManager::getRegionData(RegionType type)
{
	return m_RegionData[type];
}
