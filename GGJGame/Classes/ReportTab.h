
#ifndef _REPORT_TAB_H_
#define _REPORT_TAB_H_

#include "Tab.h"

class ReportTab : public Tab
{
public:
	ReportTab();
	~ReportTab();

	virtual bool init();

	CREATE_FUNC(ReportTab);
private:
};

#endif