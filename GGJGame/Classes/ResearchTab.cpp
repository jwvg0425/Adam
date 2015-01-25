#include "ResearchTab.h"
#include "GameManager.h"

USING_NS_CC;

ResearchTab::ResearchTab()
{
	m_TechTree = nullptr;
	m_IconMenu = nullptr;
	m_ConfirmMenu = nullptr;
	m_ResearchNameLabel = nullptr;
	m_ResearchDescLabel = nullptr;
	m_ResearchResourceLabel = nullptr;
}

ResearchTab::~ResearchTab()
{

}

bool ResearchTab::init()
{
	if (!Tab::initWithCaptionAndIcon("research", "research_icon.png"))
	{
		return false;
	}

	m_TechTree = Sprite::create("research\\tech_tree.png");
	addChild(m_TechTree);
	m_TechTree->setPosition(WND_WIDTH / 2, WND_HEIGHT / 2);

	Vector<MenuItem*> items;

	for (int i = 0; i < RES_NUM; i++)
	{
		auto data = GameManager::getInstance()->getResearchData(static_cast<ResearchType>(i));
		auto item = MenuItemImage::create(data.m_IconName, data.m_IconName, CC_CALLBACK_1(ResearchTab::researchIconCallback, this));
		item->setTag(i);
		items.pushBack(item);
	}

	items.at(RES_UPGRADE_1)->setPosition(-63, 115);
	items.at(RES_UPGRADE_2)->setPosition(-63, 115 - 44);
	items.at(RES_UPGRADE_3)->setPosition(-63, 115 - 44*2);
	items.at(RES_UPGRADE_4)->setPosition(-63, 115 - 44*3);
	items.at(RES_UPGRADE_5)->setPosition(-63, 115 - 44*4);
	items.at(RES_CURE_1)->setPosition(-63 + 44 * 2, 115);
	items.at(RES_CURE_2)->setPosition(-63 + 44 * 2, 115 - 44);
	items.at(RES_CURE_3)->setPosition(-63 + 44 * 2, 115 - 44*2);
	items.at(RES_CURE_MASTER)->setPosition(-63 + 44 * 2, 115 - 44*4);
	items.at(RES_SPEED_1)->setPosition(-63 + 44, 115 - 44 * 3);
	items.at(RES_SPEED_2)->setPosition(-63 + 44, 115 - 44 * 4);
	items.at(RES_SENTINEL)->setPosition(-63 - 44, 115 - 44);
	items.at(RES_EDUCATION)->setPosition(-63 - 44, 115 - 44 * 2);
	items.at(RES_ECO_1)->setPosition(-63 - 44*2, 115);
	items.at(RES_ECO_2)->setPosition(-63 - 44 * 2, 115 - 44*2);
	items.at(RES_ECO_3)->setPosition(-63 - 44 * 2, 115 - 44*4);
	items.at(RES_CULTURE_1)->setPosition(-63 - 44 * 3, 115 - 44);
	items.at(RES_CULTURE_2)->setPosition(-63 - 44 * 3, 115 - 44 * 2);
	items.at(RES_FOOD_1)->setPosition(-63 - 44 * 3, 115 - 44 * 3 - 22);
	items.at(RES_FOOD_2)->setPosition(-63 - 44 * 3, 115 - 44 * 4 - 22);
	items.at(RES_FOOD_3)->setPosition(-63 - 44 * 3, 115 - 44 * 5 - 22);
	items.at(RES_CIVIL_1)->setPosition(-63 - 44 - 22, 115 - 44 * 5);
	items.at(RES_CIVIL_2)->setPosition(-63 - 44 - 22, 115 - 44 * 6);

	m_IconMenu = Menu::createWithArray(items);
	
	addChild(m_IconMenu);

	m_ResearchNameLabel = Label::createWithSystemFont("", TEXT_FONT, 20);
	m_ResearchNameLabel->setColor(TEXT_COLOR);
	m_ResearchNameLabel->setAnchorPoint(Point(0, 1));
	m_ResearchNameLabel->setPosition(WND_WIDTH / 2 + 110, WND_HEIGHT / 2 + 120);

	m_ResearchDescLabel = Label::createWithSystemFont("", TEXT_FONT, 12, Size(120,120));
	m_ResearchDescLabel->setColor(TEXT_COLOR);
	m_ResearchDescLabel->setAnchorPoint(Point(0, 1));
	m_ResearchDescLabel->setPosition(WND_WIDTH / 2 + 110, WND_HEIGHT / 2 + 95);

	m_ResearchResourceLabel = Label::createWithSystemFont("필요 자원\n123\n456\n789", TEXT_FONT, 16);
	m_ResearchResourceLabel->setColor(TEXT_COLOR);

	addChild(m_ResearchNameLabel);
	addChild(m_ResearchDescLabel);
	addChild(m_ResearchResourceLabel);

	scheduleUpdate();

	return true;
}

void ResearchTab::researchIconCallback(Ref* sender)
{
	auto item = static_cast<MenuItem*>(sender);
	int tag = item->getTag();
	auto data = GameManager::getInstance()->getResearchData(static_cast<ResearchType>(tag));

	m_ResearchNameLabel->setString(data.m_Name);
	m_ResearchDescLabel->setString(data.m_Description);
}

void ResearchTab::update(float dTime)
{
	for (int i = 0; i < RES_NUM; i++)
	{
		auto item = m_IconMenu->getChildByTag(i);
		auto data = GameManager::getInstance()->getResearchData(static_cast<ResearchType>(i));

		item->setColor(data.getStateColor());
	}
}

ResearchData::ResearchData()
{
	m_Name = "";
	m_Description = "";
	m_IconName = "";
	m_NeedResource = 0;
	m_NeedPeriod = 0;
	m_Progress = 0;
	m_IsCompleted = false;

}

ResearchData::ResearchData(const std::string& name, const std::string& description,
	const std::string& iconName, int needResource, int needPeriod)
{
	m_Name = name;
	m_Description = description;
	m_IconName = iconName;
	m_NeedResource = needResource;
	m_NeedPeriod = needPeriod;
	m_Progress = 0;
	m_IsCompleted = false;
}

ResearchData::~ResearchData()
{

}

cocos2d::Color3B ResearchData::getStateColor()
{
	if (m_IsCompleted)
	{
		return RESEARCH_COMPLETE;
	}

	if (m_Progress > 0)
	{
		return RESEARCH_PROGRESS;
	}

	if (m_NeedResearch.size() != 0)
	{
		bool isValid = true;

		for (auto& research : m_NeedResearch)
		{
			if (!research.m_IsCompleted)
			{
				isValid = false;
			}
		}

		if (!isValid)
		{
			return RESEARCH_INVALID;
		}
	}

	return RESEARCH_VALID;
}
