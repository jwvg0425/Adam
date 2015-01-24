#ifndef _TAB_H_
#define _TAB_H_

#include "cocos2d.h"

class Tab : public cocos2d::Node
{
public:
	Tab();
	~Tab();

	virtual bool init();

	CREATE_FUNC(Tab);
private:
};

#endif