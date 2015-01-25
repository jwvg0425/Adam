#ifndef _TAB_H_
#define _TAB_H_

#include "cocos2d.h"

class Tab : public cocos2d::Node
{
public:
	Tab();
	~Tab();

	virtual bool init();
	bool initWithCaptionAndIcon
		(const std::string& caption, const std::string& iconFileName);

	static Tab* createWithCaptionAndIcon
		(const std::string& caption, const std::string& iconFileName);

	virtual void setContentsVisible(bool visible);

	void setTabId(int tabId);
	int getTabId();
	const std::string& getIconName();

	CREATE_FUNC(Tab);
private:
	int m_TabId;
	cocos2d::Label* m_Caption;
	std::string m_IconName;
};

#endif