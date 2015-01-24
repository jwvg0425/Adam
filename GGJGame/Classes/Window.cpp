#include "Window.h"
#include "macro.h"
#include "MainUILayer.h"

USING_NS_CC;


Window::Window()
{
	m_CaptionLabel = nullptr;
	m_Background = nullptr;
}

Window* Window::createWithCaption(std::string caption)
{
	Window* window = new Window();
	
	if (window && window->init())
	{
		window->setCaption(caption);
		window->autorelease();
		return window;
	}
	else
	{
		delete window;
		window = nullptr;
		
		return window;
	}
}

Window::~Window()
{

}

bool Window::init()
{
	if (!Node::init())
	{
		return false;
	}

	m_Background = Sprite::create("window.png");
	addChild(m_Background);
	m_Background->setPosition(Point(WND_WIDTH / 2, WND_HEIGHT / 2));

	m_CaptionLabel = Label::createWithSystemFont("", "Thonburi", 14);
	addChild(m_CaptionLabel);
	m_CaptionLabel->setAnchorPoint(Point(0, 1));
	m_CaptionLabel->setPosition(Point(105, 414));
	m_CaptionLabel->setColor(Color3B(191, 228, 230));

	auto exitButton = MenuItemImage::create("exitButton.png", "exitButton.png", CC_CALLBACK_1(Window::exitButtonCallback, this));
	auto menu = Menu::create(exitButton, nullptr);

	menu->alignItemsVertically();
	menu->setPosition(Point(580, 406));

	addChild(menu);

	return true;
}

void Window::setCaption(std::string caption)
{
	m_CaptionLabel->setString(caption);
}

void Window::exitButtonCallback(Ref* sender)
{
	auto menu = getParent()->getChildByTag(MAIN_MENU_TAG);
	menu->setVisible(true);
	removeFromParent();
}

