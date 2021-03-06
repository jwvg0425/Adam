﻿#include "MainUILayer.h"
#include "GameManager.h"
#include "macro.h"
#include "Window.h"
#include "ChatWindow.h"
#include "MapTab.h"
#include "ReportTab.h"
#include "ResearchTab.h"
#define UI_X (WND_WIDTH - 5)
#define UI_Y (WND_HEIGHT - 5)

USING_NS_CC;


MainUILayer::MainUILayer()
{
	m_MainUISprite = nullptr;
	m_MainMenu = nullptr;
	m_PrevPopulation = 0;
	m_PrevCivilization = 0;
	m_PrevCulture = 0;
	m_PrevResource = 0;
	m_PrevFood = 0;
	m_NextMonthMenu = nullptr;

	for (int i = 0; i < LABEL_NUM; i++)
	{
		m_Labels[i] = nullptr;
	}
}

MainUILayer::~MainUILayer()
{

}

bool MainUILayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_PrevMonth = GameManager::getInstance()->getMonth();
	m_PrevYear = GameManager::getInstance()->getYear();
	m_PrevPopulation = GameManager::getInstance()->getPopulation();
	m_PrevFood = GameManager::getInstance()->getFood();
	m_PrevResource = GameManager::getInstance()->getResource();
	m_PrevCulture = GameManager::getInstance()->getCulture();
	m_PrevCivilization = GameManager::getInstance()->getCivilization();

	m_MainUISprite = Sprite::create("graphic\\main_ui.png");

	addChild(m_MainUISprite);
	m_MainUISprite->setAnchorPoint(Point(1.0f, 1.0f));
	m_MainUISprite->setPosition(Point(UI_X, UI_Y));

	char labelStr[255] = { 0, };

	sprintf(labelStr, "%d", m_PrevMonth);

	m_Labels[LABEL_MONTH] = Label::createWithCharMap("graphic\\ui_numbers.png", 8, 10, '0');
	m_Labels[LABEL_MONTH]->setString(labelStr);
	m_Labels[LABEL_MONTH]->setAnchorPoint(Point(1.0f, 1.0f));
	m_Labels[LABEL_MONTH]->setPosition(Point(UI_X - 15, UI_Y - 5));
	addChild(m_Labels[LABEL_MONTH]);

	sprintf(labelStr, "%d", m_PrevYear);

	m_Labels[LABEL_YEAR] = Label::createWithCharMap("graphic\\ui_numbers.png", 8, 10, '0');
	m_Labels[LABEL_YEAR]->setString(labelStr);
	m_Labels[LABEL_YEAR]->setAnchorPoint(Point(1.0f, 1.0f));
	m_Labels[LABEL_YEAR]->setPosition(Point(UI_X - 75, UI_Y - 5));
	addChild(m_Labels[LABEL_YEAR]);

	sprintf(labelStr, "%d", m_PrevPopulation);

	m_Labels[LABEL_POPULATION] = Label::createWithCharMap("graphic\\ui_numbers.png", 8, 10, '0');
	m_Labels[LABEL_POPULATION]->setString(labelStr);
	m_Labels[LABEL_POPULATION]->setAnchorPoint(Point(1.0f, 1.0f));
	m_Labels[LABEL_POPULATION]->setPosition(Point(UI_X - 46, UI_Y - 35));
	addChild(m_Labels[LABEL_POPULATION]);

	sprintf(labelStr, "%d", m_PrevFood);

	m_Labels[LABEL_FOOD] = Label::createWithCharMap("graphic\\ui_numbers.png", 8, 10, '0');
	m_Labels[LABEL_FOOD]->setString(labelStr);
	m_Labels[LABEL_FOOD]->setAnchorPoint(Point(1.0f, 1.0f));
	m_Labels[LABEL_FOOD]->setPosition(Point(UI_X - 46, UI_Y - 57));
	addChild(m_Labels[LABEL_FOOD]);

	sprintf(labelStr, "%d", m_PrevResource);

	m_Labels[LABEL_RESOURCE] = Label::createWithCharMap("graphic\\ui_numbers.png", 8, 10, '0');
	m_Labels[LABEL_RESOURCE]->setString(labelStr);
	m_Labels[LABEL_RESOURCE]->setAnchorPoint(Point(1.0f, 1.0f));
	m_Labels[LABEL_RESOURCE]->setPosition(Point(UI_X - 46, UI_Y - 78));
	addChild(m_Labels[LABEL_RESOURCE]);

	sprintf(labelStr, "%d", m_PrevCulture);

	m_Labels[LABEL_CULTURE] = Label::createWithCharMap("graphic\\ui_numbers.png", 8, 10, '0');
	m_Labels[LABEL_CULTURE]->setString(labelStr);
	m_Labels[LABEL_CULTURE]->setAnchorPoint(Point(1.0f, 1.0f));
	m_Labels[LABEL_CULTURE]->setPosition(Point(UI_X - 46, UI_Y - 99));
	addChild(m_Labels[LABEL_CULTURE]);

	sprintf(labelStr, "%d", m_PrevCivilization);

	m_Labels[LABEL_CIVILIZATION] = Label::createWithCharMap("graphic\\ui_numbers.png", 8, 10, '0');
	m_Labels[LABEL_CIVILIZATION]->setString(labelStr);
	m_Labels[LABEL_CIVILIZATION]->setAnchorPoint(Point(1.0f, 1.0f));
	m_Labels[LABEL_CIVILIZATION]->setPosition(Point(UI_X - 46, UI_Y - 120));
	addChild(m_Labels[LABEL_CIVILIZATION]);

	//버튼 추가

	auto labButton = MenuItemImage::create("graphic\\button.png", "graphic\\button_down.png", CC_CALLBACK_1(MainUILayer::labButtonCallback, this));
	auto labLabel = Label::createWithSystemFont("연구", TEXT_FONT, 16);
	labLabel->setColor(TEXT_COLOR);
	labLabel->setPosition(48, 16);
	labButton->addChild(labLabel);

	auto reportButton = MenuItemImage::create("graphic\\button.png", "graphic\\button_down.png", CC_CALLBACK_1(MainUILayer::reportButtonCallback, this));
	auto reportLabel = Label::createWithSystemFont("보고서", TEXT_FONT, 16);
	reportLabel->setColor(TEXT_COLOR);
	reportLabel->setPosition(48, 16);
	reportButton->addChild(reportLabel);

	auto mapButton = MenuItemImage::create("graphic\\button.png", "graphic\\button_down.png", CC_CALLBACK_1(MainUILayer::mapButtonCallback, this));
	auto mapLabel = Label::createWithSystemFont("지도", TEXT_FONT, 16);
	mapLabel->setColor(TEXT_COLOR);
	mapLabel->setPosition(48, 16);
	mapButton->addChild(mapLabel);

	m_MainMenu = Menu::create(labButton, reportButton, mapButton, nullptr);
	m_MainMenu->alignItemsVerticallyWithPadding(4);
	addChild(m_MainMenu);
	m_MainMenu->setPosition(Point(53, WND_HEIGHT - 59));

	auto nextButton = MenuItemImage::create("graphic\\button.png", "graphic\\button_down.png", CC_CALLBACK_1(MainUILayer::nextMonthButtonCallback, this));
	auto nextLabel = Label::createWithSystemFont("다음 달로", TEXT_FONT, 16);
	nextLabel->setColor(TEXT_COLOR);
	nextLabel->setPosition(48, 16);
	nextButton->addChild(nextLabel);

	m_NextMonthMenu = Menu::create(nextButton, nullptr);
	addChild(m_NextMonthMenu);
	m_NextMonthMenu->setPosition(Point(WND_WIDTH - 60, 40));

	scheduleUpdate();

	return true;
}

void MainUILayer::update(float dTime)
{
	int month = GameManager::getInstance()->getMonth();
	int year = GameManager::getInstance()->getYear();
	int population = GameManager::getInstance()->getPopulation();
	int food = GameManager::getInstance()->getFood();
	int resource = GameManager::getInstance()->getResource();
	int culture = GameManager::getInstance()->getCulture();
	int civilization = GameManager::getInstance()->getCivilization();
	char labelStr[256] = { 0, };

	if (month != m_PrevMonth)
	{
		sprintf(labelStr, "%d", month);
		m_Labels[LABEL_MONTH]->setString(labelStr);
		m_PrevMonth = month;
	}
	if (year != m_PrevYear)
	{
		sprintf(labelStr, "%d", year);
		m_Labels[LABEL_YEAR]->setString(labelStr);
		m_PrevYear = year;
	}
	if (population != m_PrevPopulation)
	{
		sprintf(labelStr, "%d", population);
		m_Labels[LABEL_POPULATION]->setString(labelStr);
		m_PrevPopulation = population;
	}
	if (food != m_PrevFood)
	{
		sprintf(labelStr, "%d", food);
		m_Labels[LABEL_FOOD]->setString(labelStr);
		m_PrevFood = food;
	}
	if (resource != m_PrevResource)
	{
		sprintf(labelStr, "%d", resource);
		m_Labels[LABEL_RESOURCE]->setString(labelStr);
		m_PrevResource = resource;
	}
	if (culture != m_PrevCulture)
	{
		sprintf(labelStr, "%d", culture);
		m_Labels[LABEL_CULTURE]->setString(labelStr);
		m_PrevCulture = culture;
	}
	if (civilization != m_PrevCivilization)
	{
		sprintf(labelStr, "%d", civilization);
		m_Labels[LABEL_CIVILIZATION]->setString(labelStr);
		m_PrevCivilization = civilization;
	}
}

void MainUILayer::labButtonCallback(cocos2d::Ref* sender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound\\click.wav");
	ResearchTab* researchTab = ResearchTab::create();
	Window* window = Window::createWithTabs("research", researchTab, nullptr);
	addChild(window);
	setUIVisible(false);
}

void MainUILayer::reportButtonCallback(cocos2d::Ref* sender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound\\click.wav");
	ReportTab* reportTab = ReportTab::create();
	Window* window = Window::createWithTabs("report", reportTab, nullptr);
	addChild(window);
	setUIVisible(false);
}

void MainUILayer::nextMonthButtonCallback(cocos2d::Ref* sender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound\\click.wav");
	GameManager::getInstance()->turnEnd(static_cast<Layer*>(getParent()));
}

void MainUILayer::setUIVisible(bool visible)
{
	m_MainMenu->setVisible(visible);
	m_NextMonthMenu->setVisible(visible);
}

void MainUILayer::mapButtonCallback(cocos2d::Ref* sender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound\\click.wav");
	MapTab* mapTab = MapTab::create();
	Window* window = Window::createWithTabs("map", mapTab, nullptr);
	addChild(window);
	setUIVisible(false);
}
