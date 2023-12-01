#pragma once
#include<algorithm>
#include<unordered_map>
#include<vector>
#include<string>
#include"Event.h"
#include <stack>
#include <deque>
#include<iostream>
using namespace std;

class User
{
public:
	stack<string>s2;
	stack<string>s4;
	deque<string> d1;
	vector<Event> events;							//upcoming 
	vector<Event> done_events;						//done 
	vector<string>vec;								// intersect 
	unordered_map<string, bool>mp;					// intersect 
	vector<string>vec_disp;							// display   
	vector<pair<string , string>>vec_disp2;			// display 
	string username, password, firstname, lastname;
	User();
	User(string username, string password, string firstname, string lastname);
	void load_user_info();
	void registery();
	void login();
	bool intersect(string, string);
	string fix(int);
	void to_order(string, string , string);
	void load_data();
	bool add_event();
	void insert_file(Event);
	bool update_event(string);
	void update_file(vector<Event>);
	bool delete_event(string,bool);
	void delete_file(vector<Event>);
	bool display_in_order();
	void display_done_events();
	void insert_done_events(vector<Event>);
	bool check_doneevents_file();
	void undo_and_type();
	void undo();
};