#include "CalView.h"
#include "imgui.h"
#include <stdio.h>

CalView::CalView(CalModel* pCalModel)
{
    pModel = pCalModel;
    selectedDay = 0;
    selectedHour = 0;
    selectedWeek = 0;
    showProgramWindow = false;
    LeftColWidth = 150;
    PADDING = 5;
    CORNER_ROUND = 5.0;
}

ImVec2 CalView::GetTimePos(float hour, int dayOfWeek, int side)
{
    float usableWidth = Width - (LeftColWidth + 2 * PADDING);
    float wOffset = (LeftColWidth + 2 * PADDING);

    float posX = wOffset + (dayOfWeek - 1 + side) * usableWidth / 7;
    return ImVec2(posX, hour * Height / 24);
}

void CalView::Draw(int display_w, int display_h)
{
    Width = display_w;
    Height = display_h;

    // Left Panel
    {
        ImGui::BeginChild("left pane", ImVec2(LeftColWidth, 0), true);
        for (int i = 0; i < pModel->GetNumWeeks(); i++)
        {
            if (ImGui::Selectable(pModel->getWeekName(i).c_str(), selectedWeek == i))
                selectedWeek = i;
        }

        ImGui::Separator();

        if (ImGui::Button(showProgramWindow ? "hide Programs" : "show Programs")) {
            showProgramWindow = !showProgramWindow;
        }

        if (showProgramWindow)
        {
            for (int i = 0; i < 10; i++)
            {
                ImGui::Text("ActiveProgram");
            }
        }

        ImGui::EndChild();

    }
    ImGui::SameLine();

    {
        ImGui::BeginGroup();
        ImGui::BeginChild("week view", ImVec2(0, display_h));

        static const int NUM_COLUMNS = 7;
        {

            ImGui::Columns(NUM_COLUMNS, "ff"); // 4-ways, with border
            
            CalModel::Day* day = pModel->GetWeek(selectedWeek);

            for (int j = 0; j < 7; j++)
            {
                ImGui::Text(day[j].ToString().c_str()); ImGui::NextColumn();
            }

            ImGui::Separator();
            char label[32];
            for (int h = 0; h < 24; h++)
            {
                for (int i = 0; i < NUM_COLUMNS; i++)
                {
                    sprintf(label, "%02d", h%12 == 00 ? 12 : h % 12);

                    if (ImGui::Selectable(label, selectedHour == h + i * 24, ImGuiSelectableFlags_None))
                        selectedHour = h + i * 24;

                    ImGui::NextColumn();
                }
                ImGui::Separator();
            }
        }



        ImGui::EndChild();
        ImGui::EndGroup();


        static ImVec4 col = ImVec4(1.0f, 1.0f, 0.4f, 0.5f);
        const ImU32 col32 = ImColor(col);
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        draw_list->AddRectFilled(GetTimePos(10, 1, 0), GetTimePos(11, 1, 1), col32, CORNER_ROUND);
        draw_list->AddRectFilled(GetTimePos(9, 2, 0), GetTimePos(12, 2, 1), col32, CORNER_ROUND);
        draw_list->AddRectFilled(GetTimePos(9, 3, 0), GetTimePos(11, 3, 1), col32, CORNER_ROUND);
        draw_list->AddRectFilled(GetTimePos(10, 4, 0), GetTimePos(13, 4, 1), col32, CORNER_ROUND);
        draw_list->AddRectFilled(GetTimePos(9, 5, 0), GetTimePos(13, 5, 1), col32, CORNER_ROUND);
        draw_list->AddRectFilled(GetTimePos(10, 6, 0), GetTimePos(13, 6, 1), col32, CORNER_ROUND);
        draw_list->AddRectFilled(GetTimePos(11, 7, 0), GetTimePos(13, 7, 1) , col32, CORNER_ROUND);
         
    }
}