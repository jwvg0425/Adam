﻿
#ifndef _REGION_WINDOW_H_
#define _REGION_WINDOW_H_

#include "cocos2d.h"
#include "macro.h"

class RegionWindow : public cocos2d::Node
{
public:
	RegionWindow();
	~RegionWindow();

	virtual bool init();
	void updateInfo(RegionType type);
	void buttonCallback(cocos2d::Ref* sender);
	cocos2d::Rect getButtonRect();

	CREATE_FUNC(RegionWindow);
private:
	RegionType m_Type;
	cocos2d::Sprite* m_BackgroundImage;
	cocos2d::Menu* m_ActMenu;
	cocos2d::Label* m_NameLabel;
	cocos2d::Label* m_DescLabel;
	cocos2d::Label* m_ActLabel;
	cocos2d::Label* m_StateLabel;
};

#endif