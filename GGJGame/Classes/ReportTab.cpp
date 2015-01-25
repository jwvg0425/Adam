#include "ReportTab.h"

ReportTab::ReportTab()
{

}

ReportTab::~ReportTab()
{

}

bool ReportTab::init()
{
	if (!Tab::initWithCaptionAndIcon("report", "report_icon.png"))
	{
		return false;
	}

	return true;
}
