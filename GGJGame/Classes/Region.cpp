#include "Region.h"
#include "GameManager.h"

USING_NS_CC;

RegionData::RegionData(const std::string& name, const std::string& spriteName, const cocos2d::Rect& area)
{
	m_Name = name;
	m_SpriteName = spriteName;
	m_Area = area;
	m_IsDeveloped = false;
	m_IsKnown = false;

	int type = rand() % 4;

	switch (type)
	{
	case 0: //그나마 살만함
		m_Radioactivity = 500 + rand() % 500;
		m_Stablity = rand() % 100;
		break;
	case 1: //좀 힘듬
		m_Radioactivity = 1000 + rand() % 1000;
		m_Stablity = rand() % 50;
		break;
	case 2: //상황이 안 좋음
		m_Radioactivity = 2500 + rand() % 1000;
		m_Stablity = rand() % 10;
		break;
	case 3: //극악의 환경.
		m_Radioactivity = 4000 + rand() % 1000;
		m_Stablity = 0;
	}

	m_Wealthy = 0;
	m_DevelopTurn = 0;
	m_Distance = 0;
}

RegionData::RegionData()
{
	m_Name = "";
	m_SpriteName = "";
	m_Area = Rect(0, 0, 0, 0);
	m_IsDeveloped = false;
	m_IsKnown = false;
	m_Radioactivity = 1000;
	m_Wealthy = 0;
	m_Stablity = 0;
}

RegionData::~RegionData()
{

}

cocos2d::Color3B RegionData::getStateColor()
{
	if (m_IsDeveloped)
	{
		return REGION_DEVELOP;
	}
	else if (m_IsKnown)
	{
		//safe, caution, danger 3단계가 있음. 
		if (m_Radioactivity > 700 || m_Stablity < 200)
		{
			return REGION_DANGER;
		}
		else if (m_Radioactivity > 400 || m_Stablity < 400)
		{
			return REGION_CAUTION;
		}
		else
		{
			return REGION_SAFE;
		}
	}
	else
	{
		return REGION_UNKNOWN;
	}
}

int RegionData::getDistance()
{
	GameManager::getInstance()->initRegionDistance();

	std::queue<RegionData*> dataQueue;

	m_Distance = 0;

	dataQueue.push(this);

	while (!dataQueue.empty())
	{
		RegionData* region = dataQueue.front();

		dataQueue.pop();

		for (int i = 0; i < region->m_Neighbor.size(); i++)
		{
			if (region->m_Neighbor[i]->m_Distance == -1)
			{
				dataQueue.push(region->m_Neighbor[i]);
			}

			region->m_Neighbor[i]->m_Distance = region->m_Distance + 1;

			if (region->m_Neighbor[i]->m_IsDeveloped)
			{
				return region->m_Neighbor[i]->m_Distance;
			}
		}
	}

	return -1;
}

Region::Region()
{
	m_Type = RT_NONE;
	m_RegionSprite = nullptr;
}

Region::~Region()
{
}


bool Region::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

bool Region::initWithRegionType(RegionType type)
{
	if (!Node::init())
	{
		return false;
	}

	m_Type = type;
	auto data = GameManager::getInstance()->getRegionData(type);

	m_RegionSprite = Sprite::create(data.m_SpriteName);

	addChild(m_RegionSprite);
	m_RegionSprite->setAnchorPoint(Point(0, 1));
	setRegionColor(data.getStateColor());

	return true;
}

Region* Region::createWithRegionType(RegionType type)
{
	Region* region = new Region();

	if (region && region->initWithRegionType(type))
	{
		region->autorelease();
		return region;
	}
	else
	{
		delete region;
		region = nullptr;

		return region;
	}
}

void Region::setRegionColor(cocos2d::Color3B color)
{
	m_RegionSprite->setColor(color);
}
