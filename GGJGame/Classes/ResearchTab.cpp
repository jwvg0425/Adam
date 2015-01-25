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
	m_Selected = RES_NONE;
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

	m_ResearchResourceLabel = Label::createWithSystemFont("", TEXT_FONT, 12, Size(120,120));
	m_ResearchResourceLabel->setColor(TEXT_COLOR);
	m_ResearchResourceLabel->setAnchorPoint(Point(0, 1));
	m_ResearchResourceLabel->setPosition(WND_WIDTH / 2 + 110, WND_HEIGHT / 2 + 15);

	addChild(m_ResearchNameLabel);
	addChild(m_ResearchDescLabel);
	addChild(m_ResearchResourceLabel);

	auto confirm = MenuItemImage::create("button.png", "button_down.png", CC_CALLBACK_1(ResearchTab::confirmResearchCallback, this));
	auto label = Label::createWithSystemFont("연구", TEXT_FONT, 20);
	label->setColor(TEXT_COLOR);
	label->setPosition(48, 16);
	confirm->addChild(label);

	m_ConfirmMenu = Menu::create(confirm,nullptr);
	m_ConfirmMenu->setPosition(WND_WIDTH / 2 + 170, WND_HEIGHT / 2 - 120);
	m_ConfirmMenu->setVisible(false);

	addChild(m_ConfirmMenu);

	char confirmStr[255] = { 0, };
	ResearchType type = GameManager::getInstance()->getResearch();

	sprintf(confirmStr, "이번 달 연구 예정: %s", type == RES_NONE ? "" : GameManager::getInstance()->getResearchData(type).m_Name.c_str());

	m_ConfirmLabel = Label::createWithSystemFont(confirmStr, TEXT_FONT, 16);
	m_ConfirmLabel->setColor(TEXT_COLOR);
	m_ConfirmLabel->setAnchorPoint(Point(0, 1));
	m_ConfirmLabel->setPosition(WND_WIDTH / 2, WND_HEIGHT / 2 - 145);

	addChild(m_ConfirmLabel);

	scheduleUpdate();

	return true;
}

void ResearchTab::researchIconCallback(Ref* sender)
{
	auto item = static_cast<MenuItem*>(sender);
	int tag = item->getTag();
	auto data = GameManager::getInstance()->getResearchData(static_cast<ResearchType>(tag));
	auto state = data.getStateColor();
	char resource[255] = { 0, };
	int period = (data.m_NeedPeriod - data.m_Progress) / GameManager::getInstance()->getTechnique();

	if (period == 0)
	{
		period = 1;
	}

	m_ResearchNameLabel->setString(data.m_Name);
	m_ResearchDescLabel->setString(data.m_Description);
	
	sprintf(resource, "진행률 : %.2f %% \n"
		"예상 소요시간 : %d 개월\n"
		"필요 자원 : %d / %d",
		(static_cast<float>(data.m_Progress) / data.m_NeedPeriod) * 100,
		period,
		data.m_NeedResource, GameManager::getInstance()->getResource());

	m_ResearchResourceLabel->setString(resource);

	if (state == RESEARCH_COMPLETE)
	{
		m_ResearchResourceLabel->setVisible(false);
	}
	else
	{
		m_ResearchResourceLabel->setVisible(true);
	}

	if (state == RESEARCH_VALID || state == RESEARCH_PROGRESS)
	{
		m_ConfirmMenu->setVisible(true);
	}
	else
	{
		m_ConfirmMenu->setVisible(false);
	}

	m_Selected = static_cast<ResearchType>(tag);
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

void ResearchTab::confirmResearchCallback(Ref* sender)
{
	auto data = GameManager::getInstance()->getResearchData(m_Selected);
	char confirmStr[255] = { 0, };

	sprintf(confirmStr, "이번 달 연구 예정: %s", data.m_Name.c_str());

	m_ConfirmLabel->setString(confirmStr);

	GameManager::getInstance()->setResearch(m_Selected);
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
			if (!research->m_IsCompleted)
			{
				isValid = false;
			}
		}

		if (!isValid)
		{
			return RESEARCH_INVALID;
		}
	}


	//자원이 부족한 경우
	if (m_NeedResource > GameManager::getInstance()->getResource())
	{
		return RESEARCH_INVALID;
	}

	return RESEARCH_VALID;
}
