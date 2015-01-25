﻿#include "Region.h"
#include "GameManager.h"

USING_NS_CC;

RegionData::RegionData(const std::string& name, const std::string& spriteName, const cocos2d::Rect& area)
{
	m_Name = name;
	m_SpriteName = spriteName;
	m_Area = area;
	m_IsDeveloped = false;
}

RegionData::RegionData()
{
	m_Name = "";
	m_SpriteName = "";
	m_Area = Rect(0, 0, 0, 0);
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
	else
	{
		return REGION_UNKNOWN;
	}
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
