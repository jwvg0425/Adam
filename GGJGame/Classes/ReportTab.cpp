#include "ReportTab.h"
#include "GameManager.h"
#define REPORT_PER_PAGE 8

USING_NS_CC;

ReportTab::ReportTab()
{
	m_Page = 0;
	m_SelectedReport = -1;
	m_Headers = nullptr;
	m_ContentHeaderLabel = nullptr;
	m_DayLabel = nullptr;
	m_ContentsLabel = nullptr;
}

ReportTab::~ReportTab()
{

}

bool ReportTab::init()
{
	if (!Tab::initWithCaptionAndIcon("article", "report_icon.png"))
	{
		return false;
	}

	m_Contents = Sprite::create("report_contents.png");

	addChild(m_Contents);
	m_Contents->setPosition(WND_WIDTH / 2, WND_HEIGHT / 2);

	m_ContentHeaderLabel = Label::createWithSystemFont("", TEXT_FONT, 22);
	m_ContentHeaderLabel->setAnchorPoint(Point(0, 1));
	m_ContentHeaderLabel->setPosition(WND_WIDTH / 2 - 30, WND_HEIGHT / 2 + 90);
	m_DayLabel = Label::createWithSystemFont("", TEXT_FONT, 12);
	m_DayLabel->setAnchorPoint(Point(0, 1));
	m_DayLabel->setPosition(WND_WIDTH / 2 - 30, WND_HEIGHT / 2 + 60);
	m_ContentsLabel = Label::createWithSystemFont("", TEXT_FONT, 16, Size(220, 480));
	m_ContentsLabel->setAnchorPoint(Point(0, 1));
	m_ContentsLabel->setPosition(WND_WIDTH / 2 - 30, WND_HEIGHT / 2 + 40);

	m_Contents->addChild(m_ContentHeaderLabel);
	m_Contents->addChild(m_DayLabel);
	m_Contents->addChild(m_ContentsLabel);

	initMenu(m_Page);

	return true;
}

void ReportTab::initMenu(int page)
{
	if (m_Headers != nullptr)
	{
		m_Headers->removeFromParent();
	}

	auto& reports = GameManager::getInstance()->getReportData();

	int firstIdx = page*REPORT_PER_PAGE;
	int lastIdx = (page + 1)*REPORT_PER_PAGE;
	Vector<MenuItem*> items;

	for (int i = firstIdx; i < reports.size() && i < lastIdx; i++)
	{
		auto item = MenuItemImage::create("report_header.png", "report_header.png",CC_CALLBACK_1(ReportTab::headerCallback,this));
		auto label = Label::createWithSystemFont(reports[i].m_Header, TEXT_FONT, 16);
		label->setColor(TEXT_COLOR);
		item->addChild(label);
		label->setPosition(113, 16);
		item->setTag(i);
		item->setAnchorPoint(Point(0, 1));
		item->setPosition(0, -37 * i);
		items.pushBack(item);
	}

	m_Headers = Menu::createWithArray(items);
	m_Headers->setAnchorPoint(Point(0, 1));
	m_Headers->setPosition(WND_WIDTH / 2 - 230, WND_HEIGHT / 2 + 135);
	addChild(m_Headers);
}

void ReportTab::headerCallback(cocos2d::Ref* sender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("click.wav");
	char date[256];
	auto item = static_cast<MenuItem*>(sender);
	int tag = item->getTag();
	auto& data = GameManager::getInstance()->getReport(tag);

	m_ContentHeaderLabel->setString(data.m_Header);

	sprintf(date, "%d년 %d월", data.m_Year, data.m_Month);

	m_DayLabel->setString(date);

	m_ContentsLabel->setString(data.m_Contents);
}

void ReportTab::setContentsVisible(bool visible)
{
	Tab::setContentsVisible(visible);

	m_Headers->setVisible(visible);
	m_Contents->setVisible(visible);
}

ReportData::ReportData()
{
	m_Header = "";
	m_Contents = "";
	m_Year = 0;
	m_Month = 0;
	m_IsRead = false;
}

ReportData::ReportData(const std::string header, const std::string contents, int year, int month)
{
	m_Header = header;
	m_Contents = contents;
	m_Year = year;
	m_Month = month;
	m_IsRead = false;
}

ReportData::~ReportData()
{

}
