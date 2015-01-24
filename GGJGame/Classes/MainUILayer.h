﻿
#ifndef _MAIN_UI_LAYER_H_
#define _MAIN_UI_LAYER_H_

#include "cocos2d.h"
#define MAIN_MENU_TAG 1

class MainUILayer : public cocos2d::Layer
{
public:
	MainUILayer();
	~MainUILayer();

	virtual bool init();

	virtual void update(float dTime);

	void labButtonCallback(cocos2d::Ref* sender);
	void orderButtonCallback(cocos2d::Ref* sender);
	void reportButtonCallback(cocos2d::Ref* sender);

	CREATE_FUNC(MainUILayer);
private:
	enum LabelType
	{
		LABEL_YEAR,
		LABEL_MONTH,
		LABEL_POPULATION,
		LABEL_FOOD,
		LABEL_RESOURCE,
		LABEL_CULTURE,
		LABEL_CIVILIZATION,
		LABEL_NUM,
	};

	cocos2d::Sprite* m_MainUISprite;

	cocos2d::Label* m_Labels[LABEL_NUM];
	cocos2d::Menu* m_MainMenu;

	int m_PrevYear;
	int m_PrevMonth;
	int m_PrevPopulation;
	int m_PrevFood;
	int m_PrevResource;
	int m_PrevCulture;
	int m_PrevCivilization;
};

#endif