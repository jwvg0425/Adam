#include "MapTab.h"

MapTab::MapTab()
{

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

	return true;
}
