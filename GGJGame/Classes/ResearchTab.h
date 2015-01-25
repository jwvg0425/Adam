
#ifndef _RESEARCH_TAB_H_
#define _RESEARCH_TAB_H_
#include "Tab.h"

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