#pragma once
#include<string>
#include<vector>
using namespace std;

struct reminder_t {
	int day_count;
	int month_count;
	int hour_count;
	int minute_count;
};

class Event
{
public:
	string name;
	string place;
	reminder_t r;
	string M;
	bool done;
	int start_date_day;
	int start_date_month;
	int start_date_year;
	int end_date_day;
	int end_date_month;
	int end_date_year;
	int start_time;
	int end_time;
	int start_time_min;
	int end_time_min;
	void reminder_date(int start_date_m,int start_date_d);
	void reminder_time(int hours,int min,string M);
	Event(string name, int start_date_day, int start_date_month, int start_date_year, int end_date_day, int end_date_month, int end_date_year, string place, int start_time, int end_time, int start_time_min, int end_time_min,bool done,string M);
	Event(string name, int start_date_day, int start_date_month, int start_date_year, int end_date_day, int end_date_month, int end_date_year, string place, int start_time,int end_time, int start_time_min, int end_time_min,string M);
};