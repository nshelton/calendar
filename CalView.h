#pragma once

#include "CalModel.h"
#include "imgui.h"

class CalView
{

private:
	int selectedHour;
	int selectedDay;
	int selectedWeek;
	bool showProgramWindow;

	float LeftColWidth;
	float Width;
	float Height;
	float CORNER_ROUND;
	float PADDING;

	CalModel* pModel;


private:
	ImVec2 GetTimePos(float hour, int dayOfWeek, int side);

public:
	CalView(CalModel* pCalModel);
	void Draw(int w, int h);


};

