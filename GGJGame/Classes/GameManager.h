
#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "cocos2d.h"
#include "Region.h"
#include "ReportTab.h"
#include "ResearchTab.h"

class GameManager
{
public:
	static GameManager*					getInstance();
	static void							releaseInstance();

	int									getPopulation();
	int									getFood();
	int									getResource();
	int									getCulture();
	int									getCivilization();
	int									getYear();
	int									getMonth();
	void								turnStart(cocos2d::Layer* runningLayer);
	void								turnEnd(cocos2d::Layer* runningLayer);
	void								setChatting(bool chat);
	bool								isChatting();
	const RegionData&					getRegionData(RegionType type);
	const std::deque<ReportData>&		getReportData();
	const ReportData&					getReport(int idx);
	void								addReport(const ReportData& data);
	void								addRegularReport();
	const ResearchData&					getResearchData(ResearchType type);
	void								setResearch(ResearchType type);
	ResearchType						getResearch();
	void								simulate();
	int									getTurn();
	int									getTechnique();
	void								setSurveyRegion(RegionType type);
	void								setDevelopRegion(RegionType type);
	RegionType							getSurveyRegion();
	RegionType							getDevelopRegion();
	void								initRegionDistance();

private:
	GameManager();
	~GameManager();

	void					initRegion();
	void					initResearch();
	void					completeResearch(ResearchType type);

	void					simulatePopulation();
	void					simulateFood();
	void					simulateResource();
	void					simulateCulture();
	void					simulateCivilization();
	void					simulateTechnique();
	void					simulateRegion();
	void					simulateEvent();

	static GameManager* m_Instance;

	int m_Population;
	int m_Food;
	int m_Resource;
	int m_Culture;
	int m_Civilization;

	int m_Year;
	int m_Month;

	int m_PrevPopulation;
	int m_PrevFood;
	int m_PrevResource;
	int m_PrevCulture;
	int m_PrevCivilization;

	bool m_IsChatting;
	ResearchType m_Research;
	RegionType m_SurveyRegion;
	RegionType m_DevelopRegion;

	//몇 번째 차례인지. 겉으로 보이긴 year / month 가 기준이지만 실제로는 이 turn을 바탕으로 시뮬레이션 수행.
	int m_Turn;

	RegionData m_RegionData[RT_NUM];
	std::deque<ReportData> m_ReportData;
	ResearchData m_ResearchData[RES_NUM];

	int m_Technique;
	int m_EcoFactor;
	float m_FoodFactor;
	float m_FoodExp;
	float m_CivilInc;
	float m_CultureFactor;
};

#endif