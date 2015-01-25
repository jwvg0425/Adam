
#ifndef _REGION_H_
#define _REGION_H_
#include "cocos2d.h"
#include "macro.h"

struct RegionData
{
	RegionData(const std::string& name, const std::string& spriteName, const cocos2d::Rect& area);
	RegionData();
	~RegionData();
	cocos2d::Color3B getStateColor();

	std::string m_Name;
	std::string m_SpriteName;
	cocos2d::Rect m_Area;
	float m_IsDeveloped;
	float m_IsKnown;
	int m_Radioactivity;
	int m_Wealthy;
	int m_Stablity;
};

class Region : public cocos2d::Node
{
public:
	Region();
	~Region();

	virtual bool init();
	bool initWithRegionType(RegionType type);

	static Region* createWithRegionType(RegionType type);
	CREATE_FUNC(Region);

	void setRegionColor(cocos2d::Color3B color);

private:
	RegionType m_Type;
	cocos2d::Sprite* m_RegionSprite;
};

#endif