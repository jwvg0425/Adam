
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
	const ResearchData&					getResearchData(ResearchType type);
private:
	GameManager();
	~GameManager();

	void					initRegion();
	void					initResearch();

	static GameManager* m_Instance;

	int m_Population;
	int m_Food;
	int m_Resource;
	int m_Culture;
	int m_Civilization;
	int m_Year;
	int m_Month;
	bool m_IsChatting;

	//몇 번째 차례인지. 겉으로 보이긴 year / month 가 기준이지만 실제로는 이 turn을 바탕으로 시뮬레이션 수행.
	int m_Turn;

	RegionData m_RegionData[RT_NUM];
	std::deque<ReportData> m_ReportData;
	ResearchData m_ResearchData[RES_NUM];
};

#endif