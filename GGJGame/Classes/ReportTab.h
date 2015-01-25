
#ifndef _REPORT_TAB_H_
#define _REPORT_TAB_H_

#include "Tab.h"

struct ReportData
{
	ReportData();
	ReportData(const std::string header, const std::string contents, int year, int month);

	~ReportData();

	std::string m_Header;
	std::string m_Contents;
	int m_Year;
	int m_Month;
	bool m_IsRead;
};

class ReportTab : public Tab
{
public:
	ReportTab();
	~ReportTab();

	virtual bool init();

	CREATE_FUNC(ReportTab);

	void initMenu(int page);

	void headerCallback(cocos2d::Ref* sender);

	virtual void setContentsVisible(bool visible);

private:
	cocos2d::Menu* m_Headers;
	cocos2d::Sprite* m_Contents;
	int m_Page;
	int m_SelectedReport;
	cocos2d::Label* m_ContentHeaderLabel;
	cocos2d::Label* m_DayLabel;
	cocos2d::Label* m_ContentsLabel;
};

#endif