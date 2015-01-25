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
	m_Population = 507;
	m_Food = 1000;
	m_Resource = 100;
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

		ReportData firstReport("인류 멸망의 위기", "사태가 심각합니다."
			"30년에 걸친 핵전쟁 끝에 지구 상에 존재하던 모든 국가는 멸망하고 말았습니다."
			"방사능으로 인해 인류가 발을 딛고 서 있을 수 있는 땅도 이젠 한 줌 밖에 남지 않았습니다. "
			"슈퍼 컴퓨터 아담, 이제 인류의 마지막 희망은 당신 뿐입니다."
			"이 절망적인 상황 속에서, 인류가 살아남기 위해선 어떻게 해야합니까?", 4000, 1);

		ReportData secondReport("마지막 남은 땅, 한반도", "현재 생존하는 것으로 확인된 인류는 500명 정도입니다."
			"현재 인류는 그나마 인간이 살 수 있는 환경을 갖춘 유일한 땅 한반도에 모두 모여 힘겹게 살아가고 있는 상황입니다.", 4000, 1);

		ReportData thirdReport("식량 부족 문제 심각", "모든 땅이 오염되어 더 이상 식량을 공급할 수단이 없습니다."
			"지금 추세대로라면 몇 개월 내로 모든 인류는 굶어죽게 될 것입니다.", 4000, 1);

		addReport(firstReport);
		addReport(secondReport);
		addReport(thirdReport);

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

const std::deque<ReportData>& GameManager::getReportData()
{
	return m_ReportData;
}

void GameManager::addReport(const ReportData& data)
{
	m_ReportData.push_front(data);
}

const ReportData& GameManager::getReport(int idx)
{
	if (idx >= 0 && idx < m_ReportData.size())
	{
		return m_ReportData[idx];
	}
	else
	{
		return *(new ReportData());
	}
}
