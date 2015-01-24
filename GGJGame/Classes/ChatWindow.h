#ifndef _CHAT_WINDOW_H_
#define _CHAT_WINDOW_H_

#include "cocos2d.h"

class ChatWindow : public cocos2d::Node
{
public:
	ChatWindow();
	~ChatWindow();

	virtual bool init();
	void update(float dTime);
	void setChats(const std::vector<std::string>& chats);
	void setOutputPerSecond(float outputPerSecond);
	void makeChatEnd();
	void setCallback(std::function<void()> function);

	static ChatWindow* createWithStrings(const std::vector<std::string>& chats, float outputPerSecond = 10);
	static ChatWindow* createWithCallback(const std::vector<std::string>& chats, std::function<void()> function, float outputPerSecond = 10);
	CREATE_FUNC(ChatWindow);

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);

private:
	cocos2d::Sprite* m_NextIcon;
	cocos2d::Sprite* m_WindowSprite;
	cocos2d::Label* m_ChatLabel;
	std::vector<std::string> m_Chats;
	bool m_IsChatEnd;
	int m_OutputIndex;
	int m_ChatPage;

	//1초에 몇 글자 출력할 건지
	float m_OutputPerSecond;
	std::function<void()> m_Callback;
};

#endif