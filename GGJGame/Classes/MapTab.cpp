#include "MapTab.h"
#include "Region.h"
#include "GameManager.h"

USING_NS_CC;

MapTab::MapTab()
{
	m_Sea = nullptr;

	for (int i = 0; i < RT_NUM; i++)
	{
		m_Regions[i] = nullptr;
	}
}

MapTab::~MapTab()
{

}

bool MapTab::init()
{
	if (!Tab::initWithCaptionAndIcon("map", "map_icon.png"))
	{
		return false;
	}

	m_Sea = Sprite::create("map\\sea.png");
	addChild(m_Sea);
	m_Sea->setAnchorPoint(Point(0, 1));
	m_Sea->setPosition(Point(MAP_ORIGIN_X, MAP_ORIGIN_Y));
	
	for (int i = 0; i < RT_NUM; i++)
	{
		m_Regions[i] = Region::createWithRegionType(static_cast<RegionType>(i));
		addChild(m_Regions[i]);
		m_Regions[i]->setAnchorPoint(Point(0, 1));
		m_Regions[i]->setPosition(MAP_ORIGIN_X,MAP_ORIGIN_Y);
	}

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(MapTab::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	scheduleUpdate();

	return true;
}

void MapTab::update(float dTime)
{

}

void MapTab::onMouseMove(cocos2d::Event* event)
{
	EventMouse* e = static_cast <EventMouse*>(event);
	Point cursor(e->getCursorX() - MAP_ORIGIN_X, -WND_HEIGHT - e->getCursorY() + MAP_ORIGIN_Y);
	int movedRegion = -1;

	for (int i = 0; i < RT_NUM; i++)
	{
		auto data = GameManager::getInstance()->getRegionData(static_cast<RegionType>(i));

		if (data.m_Area.containsPoint(cursor))
		{
			movedRegion = i;
			break;
		}
	}

	for (int i = 0; i < RT_NUM; i++)
	{
		auto data = GameManager::getInstance()->getRegionData(static_cast<RegionType>(i));

		if (i == movedRegion)
		{
			m_Regions[i]->setRegionColor(REGION_MOVE);
			continue;
		}

		m_Regions[i]->setRegionColor(data.getStateColor());
	}
}

void MapTab::setContentsVisible(bool visible)
{
	Tab::setContentsVisible(visible);

	m_Sea->setVisible(visible);

	for (int i = 0; i < RT_NUM; i++)
	{
		m_Regions[i]->setVisible(visible);
	}
}
