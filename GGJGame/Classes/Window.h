#ifndef _WINDOW_H_
#define _WINDOW_H_
#include "cocos2d.h"

class Tab;
class Window : public cocos2d::Node
{
public:
	Window();
	~Window();
	virtual bool init();

	void exitButtonCallback(Ref* sender);
	void setCaption(std::string caption);
	void activateTab(int tabId);
	static Window* createWithCaption(std::string caption);
	static Window* createWithTabs(std::string caption, Tab* tab, ...);
	void initTabs(const std::vector<Tab*>& tabs);
	void tabIconCallback(cocos2d::Ref* sender);
	CREATE_FUNC(Window);

private:
	int m_SelectedTabId;
	cocos2d::Label* m_CaptionLabel;
	cocos2d::Sprite* m_Background;
	std::vector<Tab*> m_Tabs;
	cocos2d::Menu* m_TabMenu;
	cocos2d::Sprite* m_TabSelectIcon;
};

#endif