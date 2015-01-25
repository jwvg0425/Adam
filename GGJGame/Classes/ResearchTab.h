
#ifndef _RESEARCH_TAB_H_
#define _RESEARCH_TAB_H_
#include "Tab.h"
#include "macro.h"

struct ResearchData
{
	std::string m_Name;
	std::string m_Description;
	std::string m_IconName;

	int m_NeedResource;
	int m_NeedPeriod;
	int m_Progress;

	bool m_IsCompleted;
	std::vector<ResearchData*> m_NeedResearch;

	ResearchData();
	ResearchData(const std::string& name, const std::string& description,
		const std::string& iconName,  int needResource, int needPeriod);
	~ResearchData();

	cocos2d::Color3B getStateColor();
};

class ResearchTab : public Tab
{
public:
	ResearchTab();
	~ResearchTab();

	virtual bool init();
	void researchIconCallback(Ref* sender);
	void confirmResearchCallback(Ref* sender);

	virtual void update(float dTime);

	CREATE_FUNC(ResearchTab);
private:
	ResearchType m_Selected;

	cocos2d::Sprite* m_TechTree;
	cocos2d::Menu* m_IconMenu;
	cocos2d::Menu* m_ConfirmMenu;

	cocos2d::Label* m_ResearchNameLabel;
	cocos2d::Label* m_ResearchDescLabel;
	cocos2d::Label* m_ResearchResourceLabel;
	cocos2d::Label* m_ConfirmLabel;
};

#endif