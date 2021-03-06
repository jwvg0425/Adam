﻿#include "GameManager.h"
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
	srand((unsigned)time(nullptr));

	m_Civilization = 0;
	m_Culture = 0;
	m_Population = 507;
	m_Food = 1000;
	m_Resource = 200;
	m_Year = 4000;
	m_Month = 1;
	m_Turn = 0;
	m_Research = RES_NONE;
	m_SurveyRegion = RT_NONE;
	m_DevelopRegion = RT_NONE;
	m_Technique = 30;
	m_FoodFactor = 1.0f;
	m_FoodExp = 0.4f;
	m_CivilInc = 1;
	m_CultureFactor = 1.0f;
	m_EcoFactor = 0;
	m_IsGameOver = false;
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound\\bgm.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound\\click.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound\\typing.wav");

	initRegion();
	initResearch();
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

		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound\\bgm.mp3", true);
		runningLayer->addChild(
			ChatWindow::createWithCallback(firstChat, 
			CC_CALLBACK_0(GameScene::turnStartAction, static_cast<GameScene*>(runningLayer)), 8.0f));
	}
	else
	{
		//날짜 갱신
		m_Month++;
		if (m_Month > 12)
		{
			m_Month = 1;
			m_Year++;
		}

		m_PrevPopulation = m_Population;
		m_PrevFood = m_Food;
		m_PrevResource = m_Resource;
		m_PrevCulture = m_Culture;
		m_PrevCivilization = m_Civilization;

		//이전 달까지의 상황을 바탕으로 시뮬레이트.
		simulate();

		if (m_Population <= 0)
		{
			m_IsGameOver = true;
		}

		//정기 보고서 추가
		addRegularReport();
	}

	m_Turn++;
}

void GameManager::turnEnd(cocos2d::Layer* runningLayer)
{
	auto layer = static_cast<GameScene*>(runningLayer);

	layer->turnEndAction();
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
	m_RegionData[RT_KOREA].m_DevelopTurn = 1;

	m_RegionData[RT_KOREA].m_Neighbor.push_back(&m_RegionData[RT_CHINA]);
	m_RegionData[RT_KOREA].m_Neighbor.push_back(&m_RegionData[RT_JAPAN]);

	m_RegionData[RT_JAPAN].m_Neighbor.push_back(&m_RegionData[RT_KOREA]);
	m_RegionData[RT_JAPAN].m_Neighbor.push_back(&m_RegionData[RT_NORTH_ASIA]);

	m_RegionData[RT_CHINA].m_Neighbor.push_back(&m_RegionData[RT_KOREA]);
	m_RegionData[RT_CHINA].m_Neighbor.push_back(&m_RegionData[RT_SOUTH_EAST_ASIA]);
	m_RegionData[RT_CHINA].m_Neighbor.push_back(&m_RegionData[RT_INDO]);
	m_RegionData[RT_CHINA].m_Neighbor.push_back(&m_RegionData[RT_NORTH_ASIA]);

	m_RegionData[RT_NORTH_ASIA].m_Neighbor.push_back(&m_RegionData[RT_KOREA]);
	m_RegionData[RT_NORTH_ASIA].m_Neighbor.push_back(&m_RegionData[RT_JAPAN]);
	m_RegionData[RT_NORTH_ASIA].m_Neighbor.push_back(&m_RegionData[RT_CHINA]);
	m_RegionData[RT_NORTH_ASIA].m_Neighbor.push_back(&m_RegionData[RT_ALASKA_CANADA]);
	m_RegionData[RT_NORTH_ASIA].m_Neighbor.push_back(&m_RegionData[RT_EUROPE]);
	m_RegionData[RT_NORTH_ASIA].m_Neighbor.push_back(&m_RegionData[RT_SOUTH_WEST_ASIA]);
	m_RegionData[RT_NORTH_ASIA].m_Neighbor.push_back(&m_RegionData[RT_INDO]);

	m_RegionData[RT_SOUTH_EAST_ASIA].m_Neighbor.push_back(&m_RegionData[RT_CHINA]);
	m_RegionData[RT_SOUTH_EAST_ASIA].m_Neighbor.push_back(&m_RegionData[RT_INDO]);
	m_RegionData[RT_SOUTH_EAST_ASIA].m_Neighbor.push_back(&m_RegionData[RT_OCEANIA]);

	m_RegionData[RT_INDO].m_Neighbor.push_back(&m_RegionData[RT_CHINA]);
	m_RegionData[RT_INDO].m_Neighbor.push_back(&m_RegionData[RT_SOUTH_EAST_ASIA]);
	m_RegionData[RT_INDO].m_Neighbor.push_back(&m_RegionData[RT_SOUTH_WEST_ASIA]);

	m_RegionData[RT_ALASKA_CANADA].m_Neighbor.push_back(&m_RegionData[RT_NORTH_ASIA]);
	m_RegionData[RT_ALASKA_CANADA].m_Neighbor.push_back(&m_RegionData[RT_GREENLAND]);
	m_RegionData[RT_ALASKA_CANADA].m_Neighbor.push_back(&m_RegionData[RT_CENTRAL_AMERICA]);

	m_RegionData[RT_EUROPE].m_Neighbor.push_back(&m_RegionData[RT_NORTH_ASIA]);
	m_RegionData[RT_EUROPE].m_Neighbor.push_back(&m_RegionData[RT_SOUTH_WEST_ASIA]);
	m_RegionData[RT_EUROPE].m_Neighbor.push_back(&m_RegionData[RT_NORTH_AFRICA]);
	m_RegionData[RT_EUROPE].m_Neighbor.push_back(&m_RegionData[RT_GREENLAND]);

	m_RegionData[RT_SOUTH_WEST_ASIA].m_Neighbor.push_back(&m_RegionData[RT_NORTH_ASIA]);
	m_RegionData[RT_SOUTH_WEST_ASIA].m_Neighbor.push_back(&m_RegionData[RT_INDO]);
	m_RegionData[RT_SOUTH_WEST_ASIA].m_Neighbor.push_back(&m_RegionData[RT_EUROPE]);
	m_RegionData[RT_SOUTH_WEST_ASIA].m_Neighbor.push_back(&m_RegionData[RT_NORTH_AFRICA]);
	m_RegionData[RT_SOUTH_WEST_ASIA].m_Neighbor.push_back(&m_RegionData[RT_EAST_AFRICA]);

	m_RegionData[RT_OCEANIA].m_Neighbor.push_back(&m_RegionData[RT_SOUTH_EAST_ASIA]);

	m_RegionData[RT_GREENLAND].m_Neighbor.push_back(&m_RegionData[RT_ALASKA_CANADA]);
	m_RegionData[RT_GREENLAND].m_Neighbor.push_back(&m_RegionData[RT_EUROPE]);
	m_RegionData[RT_GREENLAND].m_Neighbor.push_back(&m_RegionData[RT_CENTRAL_AMERICA]);

	m_RegionData[RT_CENTRAL_AMERICA].m_Neighbor.push_back(&m_RegionData[RT_GREENLAND]);
	m_RegionData[RT_CENTRAL_AMERICA].m_Neighbor.push_back(&m_RegionData[RT_ALASKA_CANADA]);
	m_RegionData[RT_CENTRAL_AMERICA].m_Neighbor.push_back(&m_RegionData[RT_MEXICO]);

	m_RegionData[RT_NORTH_AFRICA].m_Neighbor.push_back(&m_RegionData[RT_EUROPE]);
	m_RegionData[RT_NORTH_AFRICA].m_Neighbor.push_back(&m_RegionData[RT_SOUTH_WEST_ASIA]);
	m_RegionData[RT_NORTH_AFRICA].m_Neighbor.push_back(&m_RegionData[RT_CENTRAL_AFRICA]);
	m_RegionData[RT_NORTH_AFRICA].m_Neighbor.push_back(&m_RegionData[RT_WEST_AFRICA]);
	m_RegionData[RT_NORTH_AFRICA].m_Neighbor.push_back(&m_RegionData[RT_EAST_AFRICA]);

	m_RegionData[RT_EAST_AFRICA].m_Neighbor.push_back(&m_RegionData[RT_SOUTH_WEST_ASIA]);
	m_RegionData[RT_EAST_AFRICA].m_Neighbor.push_back(&m_RegionData[RT_NORTH_AFRICA]);
	m_RegionData[RT_EAST_AFRICA].m_Neighbor.push_back(&m_RegionData[RT_CENTRAL_AFRICA]);
	m_RegionData[RT_EAST_AFRICA].m_Neighbor.push_back(&m_RegionData[RT_SOUTH_AFRICA]);

	m_RegionData[RT_MEXICO].m_Neighbor.push_back(&m_RegionData[RT_CENTRAL_AMERICA]);
	m_RegionData[RT_MEXICO].m_Neighbor.push_back(&m_RegionData[RT_CARIBBEAN]);

	m_RegionData[RT_CENTRAL_AFRICA].m_Neighbor.push_back(&m_RegionData[RT_NORTH_AFRICA]);
	m_RegionData[RT_CENTRAL_AFRICA].m_Neighbor.push_back(&m_RegionData[RT_EAST_AFRICA]);
	m_RegionData[RT_CENTRAL_AFRICA].m_Neighbor.push_back(&m_RegionData[RT_WEST_AFRICA]);
	m_RegionData[RT_CENTRAL_AFRICA].m_Neighbor.push_back(&m_RegionData[RT_SOUTH_AFRICA]);

	m_RegionData[RT_WEST_AFRICA].m_Neighbor.push_back(&m_RegionData[RT_NORTH_AFRICA]);
	m_RegionData[RT_WEST_AFRICA].m_Neighbor.push_back(&m_RegionData[RT_CENTRAL_AFRICA]);
	m_RegionData[RT_WEST_AFRICA].m_Neighbor.push_back(&m_RegionData[RT_BRAZIL]);

	m_RegionData[RT_SOUTH_AFRICA].m_Neighbor.push_back(&m_RegionData[RT_EAST_AFRICA]);
	m_RegionData[RT_SOUTH_AFRICA].m_Neighbor.push_back(&m_RegionData[RT_CENTRAL_AFRICA]);
	m_RegionData[RT_SOUTH_AFRICA].m_Neighbor.push_back(&m_RegionData[RT_BRAZIL]);

	m_RegionData[RT_CARIBBEAN].m_Neighbor.push_back(&m_RegionData[RT_MEXICO]);
	m_RegionData[RT_CARIBBEAN].m_Neighbor.push_back(&m_RegionData[RT_BRAZIL]);
	m_RegionData[RT_CARIBBEAN].m_Neighbor.push_back(&m_RegionData[RT_ARGENTINA_CHILE]);

	m_RegionData[RT_BRAZIL].m_Neighbor.push_back(&m_RegionData[RT_WEST_AFRICA]);
	m_RegionData[RT_BRAZIL].m_Neighbor.push_back(&m_RegionData[RT_SOUTH_AFRICA]);
	m_RegionData[RT_BRAZIL].m_Neighbor.push_back(&m_RegionData[RT_CARIBBEAN]);
	m_RegionData[RT_BRAZIL].m_Neighbor.push_back(&m_RegionData[RT_ARGENTINA_CHILE]);

	m_RegionData[RT_ARGENTINA_CHILE].m_Neighbor.push_back(&m_RegionData[RT_CARIBBEAN]);
	m_RegionData[RT_ARGENTINA_CHILE].m_Neighbor.push_back(&m_RegionData[RT_BRAZIL]);
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

void GameManager::initResearch()
{
	m_ResearchData[RES_UPGRADE_1] = ResearchData("성능 향상1",
		"컴퓨터의 성능을 향상시켜 전체 개발 속도를 높이고 효율적으로 만듭니다.",
		"research\\upgrade_1.png", 30, 50);
	m_ResearchData[RES_UPGRADE_2] = ResearchData("성능 향상2",
		"컴퓨터의 성능을 향상시켜 전체 개발 속도를 높이고 효율적으로 만듭니다.",
		"research\\upgrade_2.png", 100, 100);
	m_ResearchData[RES_UPGRADE_3] = ResearchData("성능 향상3",
		"컴퓨터의 성능을 향상시켜 전체 개발 속도를 높이고 효율적으로 만듭니다.",
		"research\\upgrade_3.png", 200, 200);
	m_ResearchData[RES_UPGRADE_4] = ResearchData("성능 향상4",
		"컴퓨터의 성능을 향상시켜 전체 개발 속도를 높이고 효율적으로 만듭니다.",
		"research\\upgrade_4.png", 350, 400);
	m_ResearchData[RES_UPGRADE_5] = ResearchData("성능 향상5",
		"컴퓨터의 성능을 향상시켜 전체 개발 속도를 높이고 효율적으로 만듭니다.",
		"research\\upgrade_5.png", 600, 800);
	m_ResearchData[RES_CIVIL_1] = ResearchData("문명화1",
		"인류의 문명 수준을 향상시킵니다.", "research\\civil_1.png", 100, 100);
	m_ResearchData[RES_CIVIL_2] = ResearchData("문명화2",
		"인류의 문명 수준을 향상시킵니다.", "research\\civil_2.png", 400, 400);
	m_ResearchData[RES_CULTURE_1] = ResearchData("문화화1",
		"인류의 문화 수준을 향상시킵니다.", "research\\culture_1.png", 200, 300);
	m_ResearchData[RES_CULTURE_2] = ResearchData("문화화2",
		"인류의 문화 수준을 향상시킵니다.", "research\\culture_2.png", 400, 600);
	m_ResearchData[RES_FOOD_1] = ResearchData("식량 연구1",
		"식량 보급 수단을 연구하여 전체 식량 생산량을 증가시킵니다.", "research\\food_1.png", 50, 50);
	m_ResearchData[RES_FOOD_2] = ResearchData("식량 연구2",
		"식량 보급 수단을 연구하여 전체 식량 생산량을 증가시킵니다.", "research\\food_2.png", 200, 300);
	m_ResearchData[RES_FOOD_3] = ResearchData("식량 연구3",
		"식량 보급 수단을 연구하여 전체 식량 생산량을 증가시킵니다.", "research\\food_3.png", 500, 600);
	m_ResearchData[RES_SPEED_1] = ResearchData("연산 향상1",
		"컴퓨터의 연산 속도를 극도로 향상시켜 전체 연구 속도를 획기적으로 단축시킵니다.",
		"research\\speed_1.png", 1000, 1000);
	m_ResearchData[RES_SPEED_2] = ResearchData("연산 향상2",
		"컴퓨터의 연산 속도를 극도로 향상시켜 전체 연구 속도를 획기적으로 단축시킵니다.",
		"research\\speed_2.png", 2000, 2000);
	m_ResearchData[RES_CURE_1] = ResearchData("질병 연구1",
		"각종 질병을 연구하여 그 치료법 및 예방법을 개발해냅니다.", "research\\cure_1.png", 300, 400);
	m_ResearchData[RES_CURE_2] = ResearchData("질병 연구2",
		"각종 질병을 연구하여 그 치료법 및 예방법을 개발해냅니다.", "research\\cure_2.png", 600, 800);
	m_ResearchData[RES_CURE_3] = ResearchData("질병 연구3",
		"각종 질병을 연구하여 그 치료법 및 예방법을 개발해냅니다.", "research\\cure_3.png", 900, 1200);
	m_ResearchData[RES_CURE_MASTER] = ResearchData("질병 면역",
		"모든 질병에 대해 연구를 끝마쳐서, 인류가 어떤 종류의 질병에도 면역력을 가질 수 있도록 만듭니다.", 
		"research\\cure_master.png", 2000, 4000);
	m_ResearchData[RES_ECO_1] = ResearchData("환경 개선1",
		"각 지역의 방사능 수치를 감소시키고, 기후를 안정화시킬 방법을 모색합니다.", 
		"research\\eco_1.png", 40, 100);
	m_ResearchData[RES_ECO_2] = ResearchData("환경 개선2",
		"각 지역의 방사능 수치를 감소시키고, 기후를 안정화시킬 방법을 모색합니다.", 
		"research\\eco_2.png", 300, 500);
	m_ResearchData[RES_ECO_3] = ResearchData("환경 개선3",
		"각 지역의 방사능 수치를 감소시키고, 기후를 안정화시킬 방법을 모색합니다.",
		"research\\eco_3.png", 900, 2000);
	m_ResearchData[RES_SENTINEL] = ResearchData("센티넬 개발",
		"각 지역을 탐색할 수 있는 정찰용 로봇을 개발합니다.", "research\\sentinel.png", 100, 100);
	m_ResearchData[RES_EDUCATION] = ResearchData("교육",
		"인류의 교육체계를 복원합니다. 모든 인류의 문명, 문화가 지속적으로 향상됩니다.",
		"research\\education.png", 300, 300);

	m_ResearchData[RES_UPGRADE_2].m_NeedResearch.push_back(&m_ResearchData[RES_UPGRADE_1]);
	m_ResearchData[RES_UPGRADE_3].m_NeedResearch.push_back(&m_ResearchData[RES_UPGRADE_2]);
	m_ResearchData[RES_UPGRADE_4].m_NeedResearch.push_back(&m_ResearchData[RES_UPGRADE_3]);
	m_ResearchData[RES_UPGRADE_5].m_NeedResearch.push_back(&m_ResearchData[RES_UPGRADE_4]);

	m_ResearchData[RES_SENTINEL].m_NeedResearch.push_back(&m_ResearchData[RES_UPGRADE_1]);
	m_ResearchData[RES_EDUCATION].m_NeedResearch.push_back(&m_ResearchData[RES_SENTINEL]);

	m_ResearchData[RES_ECO_2].m_NeedResearch.push_back(&m_ResearchData[RES_ECO_1]);
	m_ResearchData[RES_ECO_2].m_NeedResearch.push_back(&m_ResearchData[RES_SENTINEL]);
	m_ResearchData[RES_ECO_3].m_NeedResearch.push_back(&m_ResearchData[RES_ECO_2]);
	m_ResearchData[RES_ECO_3].m_NeedResearch.push_back(&m_ResearchData[RES_UPGRADE_4]);

	m_ResearchData[RES_CIVIL_2].m_NeedResearch.push_back(&m_ResearchData[RES_CIVIL_1]);

	m_ResearchData[RES_CULTURE_1].m_NeedResearch.push_back(&m_ResearchData[RES_ECO_1]);
	m_ResearchData[RES_CULTURE_2].m_NeedResearch.push_back(&m_ResearchData[RES_CULTURE_1]);

	m_ResearchData[RES_FOOD_2].m_NeedResearch.push_back(&m_ResearchData[RES_FOOD_1]);
	m_ResearchData[RES_FOOD_3].m_NeedResearch.push_back(&m_ResearchData[RES_FOOD_2]);

	m_ResearchData[RES_SPEED_1].m_NeedResearch.push_back(&m_ResearchData[RES_UPGRADE_3]);
	m_ResearchData[RES_SPEED_2].m_NeedResearch.push_back(&m_ResearchData[RES_SPEED_1]);

	m_ResearchData[RES_CURE_2].m_NeedResearch.push_back(&m_ResearchData[RES_CURE_1]);
	m_ResearchData[RES_CURE_3].m_NeedResearch.push_back(&m_ResearchData[RES_CURE_2]);
	m_ResearchData[RES_CURE_MASTER].m_NeedResearch.push_back(&m_ResearchData[RES_CURE_3]);
	m_ResearchData[RES_CURE_MASTER].m_NeedResearch.push_back(&m_ResearchData[RES_SPEED_1]);
}

const ResearchData& GameManager::getResearchData(ResearchType type)
{
	return m_ResearchData[type];
}

void GameManager::addRegularReport()
{
	char reportHeader[255];
	char reportContents[1024];

	sprintf(reportHeader, "%d년%d월 정기보고서", m_Year, m_Month);
	sprintf(reportContents, "지난 달 대비 변화는 다음과 같습니다.\n "
		"인구: %d -> %d\n"
		"식량: %d -> %d\n"
		"자원: %d -> %d\n"
		"문화: %d -> %d\n"
		"문명: %d -> %d\n",
		m_PrevPopulation, m_Population,
		m_PrevFood, m_Food,
		m_PrevResource, m_Resource,
		m_PrevCulture, m_Culture,
		m_PrevCivilization, m_Civilization);

	ReportData report(reportHeader, reportContents, m_Year, m_Month);

	addReport(report);
}

void GameManager::setResearch(ResearchType type)
{
	m_Research = type;
}

ResearchType GameManager::getResearch()
{
	return m_Research;
}

void GameManager::simulate()
{
	simulateFood();
	simulateResource();
	simulateCivilization();
	simulateCulture();
	simulatePopulation();
	simulateRegion();
	simulateTechnique();
	simulateEvent();

	//초기화 작업
	m_Research = RES_NONE;
	m_DevelopRegion = RT_NONE;
	m_SurveyRegion = RT_NONE;

	if (m_ResearchData[RES_EDUCATION].m_IsCompleted)
	{
		m_Technique++;
	}
}

int GameManager::getTurn()
{
	return m_Turn;
}

void GameManager::completeResearch(ResearchType type)
{
	switch (type)
	{
	case RES_UPGRADE_1:
		m_Technique += 15;
		break;
	case RES_UPGRADE_2:
		m_Technique += 25;
		break;
	case RES_UPGRADE_3:
		m_Technique += 25;
		break;
	case RES_UPGRADE_4:
		m_Technique += 30;
		break;
	case RES_UPGRADE_5:
		m_Technique += 45;
		break;
	case RES_FOOD_1:
		m_FoodFactor += 1.0f;
		m_FoodExp += 0.05f;
		break;
	case RES_FOOD_2:
		m_FoodFactor += 2.0f;
		m_FoodExp += 0.05f;
		break;
	case RES_FOOD_3:
		m_FoodFactor += 3.0f;
		m_FoodExp += 0.05f;
		break;
	case RES_CIVIL_1:
		m_CivilInc += 2;
		break;
	case RES_CIVIL_2:
		m_CivilInc += 4;
		break;
	case RES_CULTURE_1:
		m_CultureFactor += 1.0f;
		break;
	case RES_CULTURE_2:
		m_CultureFactor += 1.0f;
		break;
	case RES_EDUCATION:
		m_CivilInc += 1;
		m_CultureFactor += 0.5f;
		m_FoodFactor += 0.5f;
	case RES_ECO_1:
		m_EcoFactor += 10;
		break;
	case RES_ECO_2:
		m_EcoFactor += 20;
		break;
	case RES_ECO_3:
		m_EcoFactor += 40;
		break;
	}
}

int GameManager::getTechnique()
{
	return m_Technique;
}

void GameManager::simulatePopulation()
{
	float populationInc = pow(m_Civilization, 0.8);
	int totalTurn = 0;

	for (int i = 0; i < RT_NUM; i++)
	{
		if (m_RegionData[i].m_IsDeveloped)
		{
			int turn = m_Turn - m_RegionData[i].m_DevelopTurn;
			totalTurn += turn;
		}
	}

	for (int i = 0; i < RT_NUM; i++)
	{
		if (m_RegionData[i].m_IsDeveloped)
		{
			float turn = m_Turn - m_RegionData[i].m_DevelopTurn;
			float turnRatio = turn / totalTurn;
			if (totalTurn == 0)
			{
				turnRatio = 1;
			}
			float stableFactor = 100.0f / (m_RegionData[i].m_Stablity + 1);
			float radioactivityFactor = m_RegionData[i].m_Radioactivity / 8.0f;
			float wealthFactor = pow(m_RegionData[i].m_Wealthy, 0.6);

			populationInc += (wealthFactor - stableFactor - radioactivityFactor)*turnRatio;
		}
	}
	m_Population += populationInc;

	if (m_Population < 0)
		m_Population = 0;
}

void GameManager::simulateFood()
{
	int foodIncrease = (16 * pow(m_Population, m_FoodExp) + m_Culture*0.001 + m_Civilization*0.01)*m_FoodFactor;
	int minIncrease = foodIncrease * 0.9;
	int maxIncrease = foodIncrease * 1.1;
	int foodUp = minIncrease + rand() % (maxIncrease - minIncrease + 1);

	int foodDecrease = m_Population - m_Civilization*0.01 - m_Culture*0.01;

	if (foodDecrease < m_Population * 0.1)
	{
		foodDecrease = m_Population * 0.1;
	}

	int minDecrease = foodDecrease * 0.9;
	int maxDecrease = foodDecrease * 1.1;
	int foodDown = minDecrease + rand() % (maxDecrease - minDecrease + 1);

	m_Food = m_Food + foodUp - foodDown;

	//식량이 0이 되면 인구가 전 달의 80%로 줄어듬. 기타 등등 넣어야겠지만 일단 보류
	if (m_Food < 0)
	{
		m_Food = 0;
		m_Population *= 0.8;
	}
}

void GameManager::simulateResource()
{
	float resourceIncrease = m_Civilization*0.001;

	for (int i = 0; i < RT_NUM; i++)
	{
		if (m_RegionData[i].m_IsDeveloped)
		{
			int turn = m_Turn - m_RegionData[i].m_DevelopTurn;
			float wealthyFactor;

			//개발된지 오래된 지역일 수록 더 많은 영향을 끼침.
			if (turn > 100)
			{
				wealthyFactor = 1.0f;
			}
			else if (turn > 70)
			{
				wealthyFactor = 0.9f;
			}
			else if (turn > 50)
			{
				wealthyFactor = 0.7f;
			}
			else if (turn > 30)
			{
				wealthyFactor = 0.6f;
			}
			else if (turn > 10)
			{
				wealthyFactor = 0.4f;
			}
			else
			{
				wealthyFactor = 0.3f;
			}

			resourceIncrease += pow(m_RegionData[i].m_Wealthy, 0.7)*wealthyFactor;
		}
	}

	int minResInc = resourceIncrease * 0.9;
	int maxResInc = resourceIncrease * 1.1;
	int resInc = minResInc + rand() % (maxResInc - minResInc + 1);

	m_Resource += resInc;
}

void GameManager::simulateCulture()
{
	float cultureInc = m_Population * 0.01f;
	for (int i = 0; i < RT_NUM; i++)
	{
		if (m_RegionData[i].m_IsDeveloped)
		{
			int turn = m_Turn - m_RegionData[i].m_DevelopTurn;

			cultureInc += turn * 0.01f;

			if (m_RegionData[i].m_Wealthy >= 800)
			{
				cultureInc += turn * 0.01f;
			}
		}
	}
	cultureInc *= m_CultureFactor;
	int minCulInc = cultureInc * 0.9f;
	int maxCulInc = cultureInc * 1.1f;
	int culInc = minCulInc + rand() % (maxCulInc - minCulInc + 1);


	m_Culture += culInc;
}

void GameManager::simulateCivilization()
{
	int civilInc = m_CivilInc;

	for (int i = 0; i < RT_NUM; i++)
	{
		if (m_RegionData[i].m_IsDeveloped)
		{
			if (m_RegionData[i].m_Radioactivity <= 50)
			{
				civilInc++;
			}

			if (m_RegionData[i].m_Wealthy >= 800)
			{
				civilInc++;
			}

			if (m_RegionData[i].m_Stablity >= 500)
			{
				civilInc++;
			}

			int turn = m_Turn - m_RegionData[i].m_DevelopTurn;

			if (turn > 100)
			{
				civilInc += 2;
			}
			else if (turn > 50)
			{
				civilInc++;
			}

		}
	}

	m_Civilization += civilInc;
}

void GameManager::simulateTechnique()
{
	int technique = m_Technique + m_Civilization * 0.01;
	int minTechnique = technique * 0.9;
	int maxTechnique = technique * 1.1;
	int nowTechnique = minTechnique + rand() % (maxTechnique - minTechnique + 1);

	if (m_Research != RES_NONE)
	{
		m_ResearchData[m_Research].m_Progress += nowTechnique;
		m_Resource -= m_ResearchData[m_Research].m_NeedResource;
		if (m_Resource <= 0)
			m_Resource = 0;

		if (m_ResearchData[m_Research].m_Progress >= m_ResearchData[m_Research].m_NeedPeriod)
		{
			m_ResearchData[m_Research].m_IsCompleted = true;
			completeResearch(m_Research);
			char content[255];
			sprintf(content, "%s 기술의 연구가 완료되었습니다.", m_ResearchData[m_Research].m_Name.c_str());
			ReportData report("연구 완료", content, m_Year, m_Month);
			addReport(report);
		}
	}
}

void GameManager::simulateRegion()
{
	//조사, 개척 결과 생성


	//조사는 거리 + 센티넬에만 영향 받는다.
	if (m_SurveyRegion != RT_NONE)
	{
		int distance = m_RegionData[m_SurveyRegion].getDistance();
		float success = 0.8f / distance;

		//센티넬 개발됐으면 무조건 성공률 10% 상승
		if (m_ResearchData[RES_SENTINEL].m_IsCompleted)
		{
			success += 0.1f;
		}

		int rate = success * 1000;

		//성공
		if (rand() % 1000 < rate)
		{
			m_RegionData[m_SurveyRegion].m_IsKnown = true;

			std::string content = m_RegionData[m_SurveyRegion].m_Name + "지역의 탐사에 성공했습니다. 이제 이 지역의 환경 정보 등을 확인할 수 있으며, 지역의 개척도 가능합니다.";

			ReportData report("탐사 성공", content, m_Year, m_Month);

			addReport(report);
		}
		else
		{
			//실패한 경우 거리에 비례해서 더 많은 손실을 입음. 자기가 가진 재산 현황에 비례해서 타격을 입는다.
			int populationDesc = 20 + m_Population * 0.1f * distance;
			int foodDesc = 40 + m_Food * 0.1f * distance;
			int resourceDesc = 10 + m_Resource*0.1f * distance;

			if (m_ResearchData[RES_SENTINEL].m_IsCompleted)
			{
				populationDesc = 0;
				foodDesc = 0;
			}

			if (populationDesc > m_Population)
				populationDesc = m_Population;

			if (foodDesc > m_Food)
				foodDesc = m_Food;

			if (resourceDesc > m_Resource)
				resourceDesc = m_Resource;

			m_Population -= populationDesc;
			m_Food -= foodDesc;
			m_Resource -= resourceDesc;

			char content[255];
			sprintf(content, "%s 지역의 탐사에 실패했습니다... 그 과정에서 %d명의 사람이 죽었고,"
				"%d만큼의 식량이 손실됐으며, %d만큼의 자원도 잃었습니다. 정말 안타깝군요...", m_RegionData[m_SurveyRegion].m_Name.c_str(),
				populationDesc, foodDesc, resourceDesc);

			ReportData report("탐사 실패", content, m_Year, m_Month);
			addReport(report);
		}
	}

	//개척은 해당 지역의 방사능에 큰 영향을 받는다. 거리 멀어지면 성공률 떨어지는 건 똑같음.
	if (m_DevelopRegion != RT_NONE)
	{
		int distance = m_RegionData[m_DevelopRegion].getDistance();
		float success = 0.8f;
		int radioactivity = m_RegionData[m_DevelopRegion].m_Radioactivity;

		if (radioactivity > 1000)
		{
			success -= 0.3f;
		}
		else if (radioactivity > 500)
		{
			success -= 0.2f;
		}
		else if (radioactivity > 300)
		{
			success -= 0.1f;
		}

		success /= distance;

		int rate = success * 1000;

		//성공
		if (rand() % 1000 < rate)
		{
			m_RegionData[m_DevelopRegion].m_IsDeveloped = true;

			std::string content = m_RegionData[m_DevelopRegion].m_Name + "지역의 개척에 성공했습니다. 인류의 활동 반경이 점점 넓어지고 있군요. 좋은 추세입니다.";

			ReportData report("개척 성공", content, m_Year, m_Month);

			addReport(report);
		}
		else
		{
			//실패한 경우 거리에 비례해서 더 많은 손실을 입음. 자기가 가진 재산 현황에 비례해서 타격을 입는다.
			int populationDesc = 30 + m_Population * 0.2f * distance;
			int foodDesc = 50 + m_Food * 0.2f * distance;
			int resourceDesc = 20 + m_Resource*0.2f * distance;

			if (populationDesc > m_Population)
				populationDesc = m_Population;

			if (foodDesc > m_Food)
				foodDesc = m_Food;

			if (resourceDesc > m_Resource)
				resourceDesc = m_Resource;

			m_Population -= populationDesc;
			m_Food -= foodDesc;
			m_Resource -= resourceDesc;

			char content[255];
			sprintf(content, "%s 지역의 개척에 실패했습니다... 그 과정에서 %d명의 사람이 죽었고,"
				"%d만큼의 식량이 손실됐으며, %d만큼의 자원도 잃었습니다. 정말 크나큰 손실을 입었네요..", m_RegionData[m_DevelopRegion].m_Name.c_str(),
				populationDesc, foodDesc, resourceDesc);

			ReportData report("개척 실패", content, m_Year, m_Month);
			addReport(report);
		}
	}

	//각 지역의 환경 수치 및 부유함 계산
	for (int i = 0; i < RT_NUM; i++)
	{
		auto& data = m_RegionData[i];

		//매년 몇 정도씩은 꾸준히 감소함.
		if (data.m_Radioactivity>100)
		{
			data.m_Radioactivity -= rand() % 3;
			data.m_Radioactivity -= m_EcoFactor / 3;
		}

		//안정성도 어느정도씩은 기본적으로 꾸준히 증가.
		data.m_Stablity += rand() % 3;
		data.m_Stablity += m_EcoFactor / 4;

		if (data.m_IsDeveloped)
		{
			data.m_Radioactivity -= m_Population * 0.01 + m_Civilization * 0.01;
			if (data.m_Radioactivity < 0)
				data.m_Radioactivity = 0;

			data.m_Wealthy += (m_Population * 0.01 + m_Civilization * 0.01) * sqrt(m_Turn - data.m_DevelopTurn);
		}
	}
}

void GameManager::simulateEvent()
{
	for (int i = 0; i < RT_NUM; i++)
	{
		auto& data = m_RegionData[i];

		if (data.m_IsDeveloped)
		{
			if (data.m_Radioactivity > 1000)
			{
				//20%확률로 방사능으로 인한 인구 감소 현상 발생
				if (rand() % 100 < 20)
				{
					int desc = (data.m_Radioactivity / 10) + rand() % (data.m_Radioactivity / 100 + 1);
					m_Population -= desc;
					char content[255];

					sprintf(content, "%s 지역에서 방사능으로 인해 심각한 피해가 발생하고 있습니다."
						"방사능 질환으로 인해 이번 달에만 %d명의 사상자가 발생했으며,"
						"조속히 조치를 취하지 않는 한 앞으로도 피해는 증가할 것으로 보입니다.",
						data.m_Name.c_str(), desc);

					ReportData report("방사능 피해 발생", content, m_Year, m_Month);
					addReport(report);
				}
			}

			//기후가 불안정할 경우 여러가지 현상 발생
			if (data.m_Stablity < 200)
			{
				//5% 확률로 태풍, 5% 확률로 폭우 및 홍수, 5% 확률로 극심한 가뭄
				int prob = rand() % 100;
				int popl;
				int food;
				int resc;
				std::string dis;

				if (prob < 5)
				{
					dis = "갑자기 불어닥친 태풍으";
					popl = 40 + rand() % 20;
					food = 80 + rand() % 40;
					resc = 30 + rand() % 20;
				}
				else if (prob < 10)
				{
					dis = "급작스런 폭우 및 그로 인한 홍수";
					popl = 10 + rand() % 10;
					food = 110 + rand() % 60;
					resc = 40 + rand() % 30;
				}
				else if (prob < 15)
				{
					dis = "한 달간 비 한 방울 내리지 않은 극심한 가뭄으";
					popl = 30 + rand() % 20;
					food = 10 + rand() % 10;
					resc = 10 + rand() % 10;
				}

				if (prob< 15)
				{

					if (popl>m_Population)
						popl = m_Population;

					if (food > m_Food)
						food = m_Food;

					if (resc > m_Resource)
						resc = m_Resource;

					m_Population -= popl;
					m_Food -= food;
					m_Resource -= resc;

					char content[255];

					sprintf(content, "%s 지역에서 %s로 인해 심각한 피해가 발생했습니다.\n"
						"이 재난 때문에 %d 명의 사상자가 발생했으며, %d만큼의 식량과 %d만큼의 자원도 손실한 것으로 확인됩니다.",
						data.m_Name.c_str(), dis.c_str(), popl, food, resc);

					ReportData report("재난 발생", content, m_Year, m_Month);

					addReport(report);
				}
			}

			//질병 발생. 질병은 턴 수가 좀 높아지면 발생함.

			if (m_Turn > 30 && !m_ResearchData[RES_CURE_1].m_IsCompleted)
			{
				int prob = rand() % 100;
				int popl;

				//10%확률로 질병 발생.
				if (prob < 10)
				{
					popl = 50 + m_Population * 0.1;

					if (popl>m_Population)
						popl = m_Population;

					m_Population -= popl;

					char content[255];

					sprintf(content, "%s 지역에서 정체 불명의 질병이 발생했습니다."
						"이 질병으로 인해 %d명의 사상자가 발생했습니다.", data.m_Name.c_str(), popl);

					ReportData report("질병 발생", content, m_Year, m_Month);
					addReport(report);
				}
			}

			if (m_Turn > 50 && !m_ResearchData[RES_CURE_2].m_IsCompleted)
			{
				int prob = rand() % 100;
				int popl;

				//15%확률로 질병 발생.
				if (prob < 15)
				{
					popl = 80 + m_Population * 0.15;

					if (popl>m_Population)
						popl = m_Population;

					m_Population -= popl;

					char content[255];

					sprintf(content, "%s 지역에서 정체 불명의 질병이 발생했습니다."
						"이 질병으로 인해 %d명의 사상자가 발생했습니다. 이 질병은 살상력이 높아 굉장히 위험하기 때문에 빠른 대처가 필요할 것으로 보입니다.", data.m_Name.c_str(), popl);

					ReportData report("질병 발생", content, m_Year, m_Month);
					addReport(report);
				}
			}

			if (m_Turn > 80 && !m_ResearchData[RES_CURE_3].m_IsCompleted)
			{
				int prob = rand() % 100;
				int popl;

				//20%확률로 질병 발생.
				if (prob < 20)
				{
					popl = 130 + m_Population * 0.2;

					if (popl>m_Population)
						popl = m_Population;

					m_Population -= popl;

					char content[255];

					sprintf(content, "%s 지역에서 정체 불명의 질병이 발생했습니다."
						"이 질병으로 인해 %d명의 사상자가 발생했습니다. 이 질병은 살상력이 높고, 또 전염력도 굉장히 높은 것으로 보입니다."
						"빨리 대처하지 않으면 모든 인류가 이 질병으로 인해 멸망할지도 모릅니다.", data.m_Name.c_str(), popl);

					ReportData report("질병 발생", content, m_Year, m_Month);
					addReport(report);
				}
			}

			if (m_Turn > 110 && !m_ResearchData[RES_CURE_MASTER].m_IsCompleted)
			{
				int prob = rand() % 100;
				int popl;

				//25%확률로 질병 발생.
				if (prob < 25)
				{
					popl = 200 + m_Population * 0.25;

					if (popl>m_Population)
						popl = m_Population;

					m_Population -= popl;

					char content[255];

					sprintf(content, "%s 지역에서 정체 불명의 질병이 발생했습니다."
						"이 질병으로 인해 %d명의 사상자가 발생했습니다. 이 질병은 여태껏 관찰된 모든 병균을 훨씬 뛰어넘는 극악의 살상력과 전염성을 갖고 있습니다."
						"빠른 대처가 필요합니다.", data.m_Name.c_str(), popl);

					ReportData report("질병 발생", content, m_Year, m_Month);
					addReport(report);
				}
			}
		}
	}
}

void GameManager::setSurveyRegion(RegionType type)
{
	m_SurveyRegion = type;
}

void GameManager::setDevelopRegion(RegionType type)
{
	m_DevelopRegion = type;
}

RegionType GameManager::getSurveyRegion()
{
	return m_SurveyRegion;
}

RegionType GameManager::getDevelopRegion()
{
	return m_DevelopRegion;
}

void GameManager::initRegionDistance()
{
	for (int i = 0; i < RT_NUM; i++)
	{
		m_RegionData[i].m_Distance = -1;
	}
}

bool GameManager::isGameOver()
{
	return m_IsGameOver;
}

bool GameManager::testGameClear()
{

	//갖춰야 하는 스탯
	if (m_Population < 5000)
	{
		return false;
	}

	if (m_Civilization < 1000)
	{
		return false;
	}

	if (m_Culture < 2000)
	{
		return false;
	}

	//모든 지역이 열려있어야하함.
	for (int i = 0; i < RT_NUM; i++)
	{
		if (!m_RegionData[i].m_IsDeveloped)
		{
			return false;
		}
	}

	return true;
}
