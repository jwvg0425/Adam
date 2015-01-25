#include "MapTab.h"
#include "Region.h"
#include "GameManager.h"
#include "RegionWindow.h"

USING_NS_CC;

MapTab::MapTab()
{
	m_Sea = nullptr;

	for (int i = 0; i < RT_NUM; i++)
	{
		m_Regions[i] = nullptr;
	}

	m_RegionWindow = nullptr;

	m_SelectedRegion = -1;
	m_MovedRegion = -1;
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

	m_RegionWindow = RegionWindow::create();
	m_RegionWindow->setVisible(false);

	addChild(m_RegionWindow);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(MapTab::onMouseMove, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(MapTab::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	scheduleUpdate();

	return true;
}

void MapTab::update(float dTime)
{
	for (int i = 0; i < RT_NUM; i++)
	{
		auto data = GameManager::getInstance()->getRegionData(static_cast<RegionType>(i));

		if (i == m_SelectedRegion)
		{
			m_Regions[i]->setRegionColor(REGION_SELECTED);
			continue;
		}

		if (i == m_MovedRegion)
		{
			m_Regions[i]->setRegionColor(REGION_MOVE);
			continue;
		}

		m_Regions[i]->setRegionColor(data.getStateColor());
	}
}

void MapTab::onMouseMove(cocos2d::Event* event)
{
	EventMouse* e = static_cast <EventMouse*>(event);
	Point cursor(e->getCursorX() - MAP_ORIGIN_X, -WND_HEIGHT - e->getCursorY() + MAP_ORIGIN_Y);

	if (!m_Sea->isVisible())
	{
		return;
	}

	int i = 0;
	for (i = 0; i < RT_NUM; i++)
	{
		auto data = GameManager::getInstance()->getRegionData(static_cast<RegionType>(i));

		if (data.m_Area.containsPoint(cursor))
		{
			m_MovedRegion = i;
			break;
		}
	}
	if (i == RT_NUM)
	{
		m_MovedRegion = -1;
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

void MapTab::onMouseDown(cocos2d::Event* event)
{
	EventMouse* e = static_cast <EventMouse*>(event);
	Point cursor(e->getCursorX() - MAP_ORIGIN_X, -WND_HEIGHT - e->getCursorY() + MAP_ORIGIN_Y);
	Rect buttonRect = m_RegionWindow->getButtonRect();
	int downedRegion = -1;

	if (!m_Sea->isVisible())
	{
		return;
	}

	if (m_RegionWindow->isVisible() && buttonRect.containsPoint(Point(cursor.x + MAP_ORIGIN_X, -cursor.y + MAP_ORIGIN_Y)))
	{
		return;
	}

	//왼쪽 클릭만 받아줍니다
	if (e->getMouseButton() != MOUSE_BUTTON_LEFT)
	{
		return;
	}

	for (int i = 0; i < RT_NUM; i++)
	{
		auto data = GameManager::getInstance()->getRegionData(static_cast<RegionType>(i));

		if (data.m_Area.containsPoint(cursor))
		{
			downedRegion = i;
			break;
		}
	}

	if (downedRegion == -1)
		return;

	//똑같은 영역 또 클릭하면 클릭 해제.
	if (m_SelectedRegion == downedRegion)
	{
		m_RegionWindow->setVisible(false);
		m_SelectedRegion = -1;
		return;
	}

	m_SelectedRegion = downedRegion;
	m_RegionWindow->setVisible(true);

	auto data = GameManager::getInstance()->getRegionData(static_cast<RegionType>(m_SelectedRegion));
	float x = MAP_ORIGIN_X + data.m_Area.getMidX();
	float y = MAP_ORIGIN_Y - data.m_Area.getMidY();

	m_RegionWindow->setPosition(x,y);
	m_RegionWindow->updateInfo(static_cast<RegionType>(m_SelectedRegion));
	
}

void MapTab::initSelectedRegion()
{
	m_SelectedRegion = -1;
}

RegionType MapTab::getSelectedRegion()
{
	return static_cast<RegionType>(m_SelectedRegion);
}
