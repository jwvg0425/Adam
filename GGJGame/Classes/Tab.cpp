#include "Tab.h"
#include "macro.h"

USING_NS_CC;

Tab::Tab()
{
	m_TabId = -1;
	m_Caption = nullptr;
}

Tab::~Tab()
{

}

bool Tab::init()
{
	if (!Node::init())
	{
		return false;
	}

	m_Caption = Label::createWithSystemFont("default", TEXT_FONT, 14);

	addChild(m_Caption);
	m_Caption->setVisible(false);
	m_Caption->setAnchorPoint(Point(0, 1));
	m_Caption->setPosition(Point(96, 393));
	m_Caption->setColor(TEXT_COLOR);

	return true;
}

bool Tab::initWithCaptionAndIcon(const std::string& caption, const std::string& iconFileName)
{
	if (!Node::init())
	{
		return false;
	}
	m_Caption = Label::createWithSystemFont(caption, TEXT_FONT, 14);
	addChild(m_Caption);
	m_Caption->setVisible(false);
	m_Caption->setAnchorPoint(Point(0, 1));
	m_Caption->setPosition(Point(96, 393));
	m_Caption->setColor(TEXT_COLOR);

	m_IconName = iconFileName;

	return true;
}

Tab* Tab::createWithCaptionAndIcon(const std::string& caption, const std::string& iconFileName)
{
	Tab* tab = new Tab();

	if (tab && tab->initWithCaptionAndIcon( caption, iconFileName))
	{
		tab->autorelease();
		return tab;
	}
	else
	{
		delete tab;
		tab = nullptr;

		return tab;
	}
}

void Tab::setContentsVisible(bool visible)
{
	m_Caption->setVisible(visible);
}

int Tab::getTabId()
{
	return m_TabId;
}

void Tab::setTabId(int tabId)
{
	m_TabId = tabId;
}

const std::string& Tab::getIconName()
{
	return m_IconName;
}
