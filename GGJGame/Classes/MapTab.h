#ifndef _MAP_TAB_H_
#define _MAP_TAB_H_
#include "Tab.h"
#include "Macro.h"

class Region;
class MapTab : public Tab
{
public:
	MapTab();
	~MapTab();

	virtual bool init();

	void update(float dTime);

	void onMouseMove(cocos2d::Event* event);

	virtual void setContentsVisible(bool visible);

	CREATE_FUNC(MapTab);
private:
	cocos2d::Sprite* m_Sea;
	Region* m_Regions[RT_NUM];
};

#endif