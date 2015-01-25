#include "ChatWindow.h"
#include "macro.h"
#include "GameManager.h"

USING_NS_CC;


ChatWindow::ChatWindow()
{
	m_NextIcon = nullptr;
	m_WindowSprite = nullptr;
	m_ChatLabel = nullptr;
	m_IsChatEnd = false;
	m_OutputIndex = 0;
	m_ChatPage = 0;
	m_OutputPerSecond = 1.0f;
	m_Callback = nullptr;
}

ChatWindow::~ChatWindow()
{

}

bool ChatWindow::init()
{
	if (!Node::init())
	{
		return false;
	}

	m_WindowSprite = Sprite::create("chat_window.png");
	addChild(m_WindowSprite, 0);
	m_WindowSprite->setPosition(Point(WND_WIDTH / 2, 100));

	m_ChatLabel = Label::createWithSystemFont("", TEXT_FONT, 20, Size(480, 100));
	addChild(m_ChatLabel);
	m_ChatLabel->setColor(TEXT_COLOR);
	m_ChatLabel->setPosition(Point(WND_WIDTH / 2, 90));

	m_NextIcon = Sprite::create("next_icon.png");
	addChild(m_NextIcon, 2);
	m_NextIcon->setPosition(Point(WND_WIDTH / 2, 40));
	m_NextIcon->setVisible(false);

	scheduleUpdate();

	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(ChatWindow::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(ChatWindow::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(ChatWindow::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(ChatWindow::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	GameManager::getInstance()->setChatting(true);

	return true;
}

void ChatWindow::update(float dTime)
{
	static float time = 0.0f;
	//1글자 출력되기 위해 필요한 시간(초)
	float charSecond = 1 / m_OutputPerSecond;

	//현재 페이지 출력이 끝나면 대기.
	if (m_IsChatEnd)
	{
		time = 0.0f;
		return;
	}

	time += dTime;

	int prevIndex = m_OutputIndex;

	while (time > charSecond && m_OutputIndex < m_Chats[m_ChatPage].length())
	{
		//멀티바이트 문자면 한 번에 2바이트 진행하게 만든다.
		if (m_Chats[m_ChatPage][m_OutputIndex] < 0)
		{
			m_OutputIndex++;
		}

		m_OutputIndex++;
		time -= charSecond;
	}

	//더 출력될 글자가 생기면 라벨 갱신.
	if (prevIndex != m_OutputIndex)
	{
		if (m_Chats[m_ChatPage][m_OutputIndex] != ' ')
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("typing.wav");
		}
		std::string outputStr(&m_Chats[m_ChatPage][0], &m_Chats[m_ChatPage][m_OutputIndex]);

		m_ChatLabel->setString(outputStr);
	}

	if (m_OutputIndex == m_Chats[m_ChatPage].length())
	{
		m_IsChatEnd = true;
		m_NextIcon->runAction(RepeatForever::create(Blink::create(1, 2)));
	}
}

ChatWindow* ChatWindow::createWithStrings(const std::vector<std::string>& chats, float outputPerSecond /*= 10*/)
{
	ChatWindow* window = new ChatWindow();

	if (window && window->init())
	{
		window->setChats(chats);
		window->setOutputPerSecond(outputPerSecond);
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

void ChatWindow::setChats(const std::vector<std::string>& chats)
{
	m_Chats.clear();

	for (auto& chat : chats)
	{
		m_Chats.push_back(chat);
	}
}

void ChatWindow::setOutputPerSecond(float outputPerSecond)
{
	m_OutputPerSecond = outputPerSecond;
}

void ChatWindow::makeChatEnd()
{
	m_IsChatEnd = true;

	m_ChatLabel->setString(m_Chats[m_ChatPage]);
	m_NextIcon->runAction(RepeatForever::create(Blink::create(1, 2)));
}

void ChatWindow::onTouchEnded(cocos2d::Touch* touch, Event* unused_event)
{
	if (m_IsChatEnd)
	{
		if (m_ChatPage < m_Chats.size() - 1)
		{
			m_IsChatEnd = false;
			m_NextIcon->stopAllActions();
			m_NextIcon->setVisible(false);
			m_ChatPage++;
			m_OutputIndex = 0;
		}
		else
		{
			setVisible(false);
			GameManager::getInstance()->setChatting(false);
			if (m_Callback != nullptr)
			{
				m_Callback();
			}
			removeFromParent();
		}
	}
	else
	{
		makeChatEnd();
	}
}

bool ChatWindow::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	return true;
}

void ChatWindow::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void ChatWindow::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void ChatWindow::setCallback(std::function<void()> function)
{
	m_Callback = function;
}

ChatWindow* ChatWindow::createWithCallback(const std::vector<std::string>& chats, std::function<void()> function, float outputPerSecond /*= 10*/)
{
	ChatWindow* window = new ChatWindow();

	if (window && window->init())
	{
		window->setChats(chats);
		window->setOutputPerSecond(outputPerSecond);
		window->setCallback(function);
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
