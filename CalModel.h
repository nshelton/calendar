#pragma once
#include <ctime>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>

const char DAY_NAMES[7][4] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };
const char MONTH_NAMES[12][4] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };

class CalModel
{


public: 
    struct Day 
    {
        int dayOfYear;
        int dayOfMonth;
        int dayOfWeek;
        int month;

        std::string ToString()
        {
            std::ostringstream ss;
            ss << DAY_NAMES[dayOfWeek-1] << " " << MONTH_NAMES[month-1] << "." << dayOfMonth;
            return ss.str();
        };
    };

private:

    void disaster()
    {
        std::cout << "Disaster! Exiting ..." << std::endl;
        exit(-1);
    }

    bool isLeapYear(int year)
    {
        return   ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
    }
    int  weekdayStartOfYear(int year)
    {
        int day_start;
        int x1, x2, x3;
        x1 = (year - 1) / 4;
        x2 = (year - 1) / 100;
        x3 = (year - 1) / 400;
        day_start = (year + x1 - x2 + x3) % 7;
        return day_start;
    }
    int numOfDaysInMonth(int m, bool leap)
    {
        if (m == 1) return(31);
        else if (m == 2) if (leap) return(29); else return(28);
        else if (m == 3) return(31);
        else if (m == 4) return(30);
        else if (m == 5) return(31);
        else if (m == 6) return(30);
        else if (m == 7) return(31);
        else if (m == 8) return(31);
        else if (m == 9) return(30);
        else if (m == 10) return(31);
        else if (m == 11) return(30);
        else if (m == 12) return(31);
        else disaster();
    }

    //######################################

    static const int WEEKS_IN_YEAR = 53;
    static const int DAYS_IN_WEEK = 7;
    static const int NUM_DAYS_IN_YEAR = 375;


public:

    // starts on a monday, with null intro padding
    Day CalendarDays[NUM_DAYS_IN_YEAR + 14];

    int GetNumWeeks() 
    {
        return 53;
    }

    Day* GetWeek(int weekNum) 
    {
        return &CalendarDays[weekNum * 7];
    }

    std::string getWeekName(int weekNum)
    {
        CalModel::Day* day = GetWeek(weekNum);


        std::ostringstream ss;
        ss << MONTH_NAMES[day[0].month - 1] << "." << day[0].dayOfMonth;
        return ss.str();
    }

    CalModel(int year = 2020)
    {
          bool isLeap = isLeapYear(year);
        Day tmpDays[NUM_DAYS_IN_YEAR];

        int dayNum = 0;
        for (int i = 1; i <= 12; i++)
        {
            for (int j = 1; j <= numOfDaysInMonth(i, isLeap); j++)
            {
                std::cout << i << "/" << j << "\t" << dayNum << std::endl;

                tmpDays[dayNum].dayOfYear = dayNum;
                tmpDays[dayNum].dayOfMonth = j;
                tmpDays[dayNum].dayOfWeek = -1;
                tmpDays[dayNum].month = i;

                dayNum++;

            }
        }
        
        int pad = weekdayStartOfYear(year);

     for (int i = 0; i < NUM_DAYS_IN_YEAR + 14; i++)
        {
            if (i < pad)
            {
                CalendarDays[i].dayOfYear = -1;
                CalendarDays[i].dayOfMonth = -1;
                CalendarDays[i].dayOfWeek = -1;
                CalendarDays[i].month = -1;
            }

            else if (i - pad < NUM_DAYS_IN_YEAR) 
            {
                CalendarDays[i].dayOfYear = tmpDays[i - pad].dayOfYear;
                CalendarDays[i].dayOfMonth = tmpDays[i - pad].dayOfMonth;
                CalendarDays[i].dayOfWeek = tmpDays[i - pad].dayOfWeek;
                CalendarDays[i].month = tmpDays[i - pad].month;
                CalendarDays[i].dayOfWeek = (i % 7) + 1;
            }

        }
 
    }
};
