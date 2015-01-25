#include "ResearchTab.h"
#include "macro.h"

USING_NS_CC;

ResearchTab::ResearchTab()
{
	m_TechTree = nullptr;
}

ResearchTab::~ResearchTab()
{

}

bool ResearchTab::init()
{
	if (!Tab::initWithCaptionAndIcon("research", "research_icon.png"))
	{
		return false;
	}

	m_TechTree = Sprite::create("research\\tech_tree.png");
	addChild(m_TechTree);
	m_TechTree->setPosition(WND_WIDTH / 2, WND_HEIGHT / 2);

	return true;
}

ResearchData::ResearchData()
{
	m_Name = "";
	m_Description = "";
	m_IconName = "";
	m_NeedResource = 0;
	m_NeedPeriod = 0;
	m_Process = 0;
	m_IsCompleted = false;

}

ResearchData::ResearchData(const std::string& name, const std::string& description,
	const std::string& iconName, int needResource, int needPeriod)
{
	m_Name = name;
	m_Description = description;
	m_IconName = iconName;
	m_NeedResource = needResource;
	m_NeedPeriod = needPeriod;
	m_Process = 0;
	m_IsCompleted = false;
}

ResearchData::~ResearchData()
{

}
