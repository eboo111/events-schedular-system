#include "Event.h"
#include <ctime>
#include <string>
#include <algorithm>
#include <iostream>
#pragma warning(disable : 4996)
using namespace std;


// no done 
Event::Event(string name, int start_date_day, int start_date_month, int start_date_year, int end_date_day, int end_date_month, int end_date_year, string place, int start_time,int end_time, int start_time_min, int end_time_min,string M) {
	Event::name = name;
	Event::start_date_day = start_date_day;
	Event::start_date_month = start_date_month;
	Event::start_date_year = start_date_year;
	Event::end_date_day = end_date_day;
	Event::end_date_month = end_date_month;
	Event::end_date_year = end_date_year;
	Event::place = place;
	Event::start_time = start_time;
	Event::end_time = end_time;
    Event::start_time_min = start_time_min;
    Event::end_time_min = end_time_min;
	Event::M = M;
	done = false;
}


// done 
Event::Event(string name, int start_date_day, int start_date_month, int start_date_year, int end_date_day, int end_date_month, int end_date_year, string place, int start_time, int end_time, int start_time_min, int end_time_min,bool done,string M) {
    Event::name = name;
    Event::start_date_day = start_date_day;
    Event::start_date_month = start_date_month;
    Event::start_date_year = start_date_year;
    Event::end_date_day = end_date_day;
    Event::end_date_month = end_date_month;
    Event::end_date_year = end_date_year;
    Event::place = place;
    Event::start_time = start_time;
    Event::end_time = end_time;
    Event::start_time_min = start_time_min;
    Event::end_time_min = end_time_min;
	Event::M = M;
    Event::done = done;
}


//reminder monthes and days
void Event::reminder_date(int start_date_month, int start_date_day) {
	int start_month = start_date_month, start_day = start_date_day;
	int day_count = 0, month_count = 0, num_Days = 0, current_month = 0, current_day = 0, target_day = 0, days, dayys;

	if (start_month == 1 || start_month == 3 || start_month == 5 || start_month == 7 || start_month == 8 || start_month == 10 || start_month == 12)
	{
		num_Days = 31;
	}
	else if (start_month == 2)
	{
		num_Days = 28;
	}
	else
	{
		num_Days = 30;
	};
	switch (start_month)
	{
	case 2: dayys = 31;
		break;
	case 3: dayys = 59;
		break;
	case 4: dayys = 90;
		break;
	case 5: dayys = 120;
		break;
	case 6: dayys = 151;
		break;
	case 7: dayys = 181;
		break;
	case 8: dayys = 212;
		break;
	case 9: dayys = 243;
		break;
	case 10: dayys = 273;
		break;
	case 11: dayys = 304;
		break;
	case 12: dayys = 334;
		break;
	default: dayys = 0;
		break;
	};


	time_t t = time(0);
	tm* now = localtime(&t);

	switch (now->tm_mon + 1)
	{
	case 2: days = 31;
		break;
	case 3: days = 59;
		break;
	case 4: days = 90;
		break;
	case 5: days = 120;
		break;
	case 6: days = 151;
		break;
	case 7: days = 181;
		break;
	case 8: days = 212;
		break;
	case 9: days = 243;
		break;
	case 10: days = 273;
		break;
	case 11: days = 304;
		break;
	case 12: days = 334;
		break;
	default: days = 0;
		break;
	};

	current_month = now->tm_mon + 1;
	current_day = now->tm_mday + days;
	target_day = dayys + start_day;



	for (int i = current_day; i <= target_day; i++)
	{

		if (day_count < num_Days)
		{
			day_count++;
		}
		else
		{
			month_count++;
			current_month++;
			day_count = 0;
		}


	}
	r.month_count = month_count;
	r.day_count = day_count;
}


//reminfer hours and minutes
void Event::reminder_time(int start_time_hour, int start_time_min, string M) {

	int start_hour = start_time_hour, start_min = start_time_min;
	string A = M;
	int hour_count = 0, min_count = 0, num_min = 60, current_hour, target_hour, min = 60, miin = 60;

	transform(A.begin(), A.end(), A.begin(), ::toupper);
	time_t t = time(0);
	tm* now = localtime(&t);

	if (A == "PM")
	{
		start_hour += 12;
	};

	switch (start_hour)
	{
	case 1: min *= 1;
		break;
	case 2: min *= 2;
		break;
	case 3: min *= 3;
		break;
	case 4: min *= 4;
		break;
	case 5: min *= 5;
		break;
	case 6: min *= 6;
		break;
	case 7: min *= 7;
		break;
	case 8: min *= 8;
		break;
	case 9: min *= 9;
		break;
	case 10: min *= 10;
		break;
	case 11: min *= 11;
		break;
	case 12: min *= 12;
		break;
	case 13: min *= 13;
		break;
	case 14: min *= 14;
		break;
	case 15: min *= 15;
		break;
	case 16: min *= 16;
		break;
	case 17: min *= 17;
		break;
	case 18: min *= 18;
		break;
	case 19: min *= 19;
		break;
	case 20: min *= 20;
		break;
	case 21: min *= 21;
		break;
	case 22: min *= 22;
		break;
	case 23: min *= 23;
		break;

	default:  min *= 0;
		break;
	};

	switch (now->tm_hour)
	{
	case 1: miin *= 1;
		break;
	case 2: miin *= 2;
		break;
	case 3: miin *= 3;
		break;
	case 4: miin *= 4;
		break;
	case 5: miin *= 5;
		break;
	case 6: miin *= 6;
		break;
	case 7: miin *= 7;
		break;
	case 8: miin *= 8;
		break;
	case 9: miin *= 9;
		break;
	case 10: miin *= 10;
		break;
	case 11: miin *= 11;
		break;
	case 12: miin *= 12;
		break;
	case 13: miin *= 13;
		break;
	case 14: miin *= 14;
		break;
	case 15: miin *= 15;
		break;
	case 16: miin *= 16;
		break;
	case 17: miin *= 17;
		break;
	case 18: miin *= 18;
		break;
	case 19: miin *= 19;
		break;
	case 20: miin *= 20;
		break;
	case 21: miin *= 21;
		break;
	case 22: miin *= 22;
		break;
	case 23: miin *= 23;
		break;

	default:  miin *= 0;
		break;
	};

	current_hour = now->tm_min + miin;
	target_hour = min + start_min;

	if (current_hour >= target_hour)
	{
		if (A == "PM")
			target_hour += (1440 + 21);
		else
			target_hour += (1440 + 17);

	};

	for (int i = current_hour; i <= target_hour; i++)
	{
		if (min_count < num_min)
		{
			min_count++;
		}
		else
		{
			hour_count++;
			min_count = 0;
		}
	};
	r.hour_count = hour_count;
	r.minute_count = min_count;
}