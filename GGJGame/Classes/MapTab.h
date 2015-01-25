#ifndef _MAP_TAB_H_
#define _MAP_TAB_H_
#include "Tab.h"

class MapTab : public Tab
{
public:
	MapTab();
	~MapTab();

	virtual bool init();

	CREATE_FUNC(MapTab);
private:
};

#endif