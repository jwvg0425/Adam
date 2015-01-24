#ifndef _WINDOW_H_
#define _WINDOW_H_
#include "cocos2d.h"

class Window : public cocos2d::Node
{
public:
	Window();
	~Window();
	virtual bool init();

	void exitButtonCallback(Ref* sender);
	void setCaption(std::string caption);
	static Window* createWithCaption(std::string caption);
	CREATE_FUNC(Window);

private:
	cocos2d::Label* m_CaptionLabel;
	cocos2d::Sprite* m_Background;
};

#endif