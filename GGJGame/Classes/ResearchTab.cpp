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
