
#ifndef _RESEARCH_TAB_H_
#define _RESEARCH_TAB_H_
#include "Tab.h"

struct ResearchData
{
	std::string m_Name;
	std::string m_Description;
	std::string m_IconName;

	int m_NeedResource;
	int m_NeedPeriod;
	int m_Process;

	bool m_IsCompleted;
	std::vector<std::string> m_NeedResearch;

	ResearchData();
	ResearchData(const std::string& name, const std::string& description,
		const std::string& iconName,  int needResource, int needPeriod);
	~ResearchData();
};

class ResearchTab : public Tab
{
public:
	ResearchTab();
	~ResearchTab();

	virtual bool init();

	CREATE_FUNC(ResearchTab);
private:
	cocos2d::Sprite* m_TechTree;
};

#endif