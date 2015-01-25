#include "Window.h"
#include "macro.h"
#include "MainUILayer.h"
#include "Tab.h"
#define SELECTED_ICON_TAG 1

USING_NS_CC;


Window::Window()
{
	m_CaptionLabel = nullptr;
	m_Background = nullptr;
	m_TabMenu = nullptr;
	m_TabSelectIcon = nullptr;
	m_SelectedTabId = -1;
}

Window* Window::createWithCaption(std::string caption)
{
	Window* window = new Window();
	
	if (window && window->init())
	{
		window->setCaption(caption);
		window->autorelease();
		return window;
	}
	else
	{
		delete window;
		window = nullptr;
		
		return window;
	}
}

Window::~Window()
{

}

bool Window::init()
{
	if (!Node::init())
	{
		return false;
	}

	m_Background = Sprite::create("window.png");
	addChild(m_Background);
	m_Background->setPosition(Point(WND_WIDTH / 2, WND_HEIGHT / 2));

	m_CaptionLabel = Label::createWithSystemFont("", TEXT_FONT, 14);
	addChild(m_CaptionLabel);
	m_CaptionLabel->setAnchorPoint(Point(0, 1));
	m_CaptionLabel->setPosition(Point(105, 430));
	m_CaptionLabel->setColor(TEXT_COLOR);

	auto exitButton = MenuItemImage::create("exitButton.png", "exitButton.png", CC_CALLBACK_1(Window::exitButtonCallback, this));
	auto menu = Menu::create(exitButton, nullptr);

	menu->alignItemsVertically();
	menu->setPosition(Point(580, 422));

	addChild(menu);

	m_TabSelectIcon = Sprite::create("tab_icon_selected.png");
	addChild(m_TabSelectIcon,1);
	m_TabSelectIcon->setVisible(false);

	return true;
}

void Window::setCaption(std::string caption)
{
	m_CaptionLabel->setString(caption);
}

void Window::exitButtonCallback(Ref* sender)
{
	auto parent = static_cast<MainUILayer*>(getParent());

	parent->setUIVisible(true);
	removeFromParent();
}

void Window::activateTab(int tabId)
{
	if (tabId >= 0 && tabId < m_Tabs.size())
	{
		m_TabSelectIcon->setVisible(true);

		if (m_SelectedTabId != -1)
		{
			m_Tabs[m_SelectedTabId]->setContentsVisible(false);
		}
		m_TabSelectIcon->setPosition(Point(71, 366 - tabId * 22));
		m_Tabs[tabId]->setContentsVisible(true);
		m_SelectedTabId = tabId;
	}
}

Window* Window::createWithTabs(std::string caption, Tab* tab, ...)
{
	Window* window = new Window();

	if (window && window->init())
	{
		window->setCaption(caption);
		va_list ap;

		va_start(ap, tab);

		std::vector<Tab*> tabs;

		tabs.push_back(tab);

		Tab* arg = va_arg(ap, Tab*);
		while (arg != nullptr)
		{
			tabs.push_back(arg);
			arg = va_arg(ap, Tab*);
		}
		va_end(ap);

		window->initTabs(tabs);
		window->activateTab(0);

		window->autorelease();
		return window;
	}
	else
	{
		delete window;
		window = nullptr;

		return window;
	}
}

void Window::initTabs(const std::vector<Tab*>& tabs)
{
	for (auto& tab : m_Tabs)
	{
		tab->removeFromParent();
	}

	m_Tabs.clear();

	if (m_TabMenu != nullptr)
	{
		m_TabMenu->removeFromParent();
	}

	Vector<MenuItem*> items;

	for (auto& tab : tabs)
	{
		auto item = MenuItemImage::create(tab->getIconName(), tab->getIconName(), CC_CALLBACK_1(Window::tabIconCallback, this));
		int tag = m_Tabs.size();
		item->setTag(tag);
		item->setPosition(Point(0, - tag * 22));
		items.pushBack(item);
		
		addChild(tab);
		tab->setContentsVisible(false);
		m_Tabs.push_back(tab);
		
	}

	m_TabMenu = Menu::createWithArray(items);
	addChild(m_TabMenu);
	m_TabMenu->setAnchorPoint(Point(0, 1));
	m_TabMenu->setPosition(Point(63, 366));
}

void Window::tabIconCallback(cocos2d::Ref* sender)
{
	MenuItem* item = static_cast<MenuItem*>(sender);
	int tag = item->getTag();

	activateTab(tag);
}