#include "User.h"
#include <iostream>
#include<algorithm>
#include<unordered_map>
#include<vector>
#include<string>
#include"Event.h"
#include <fstream>
#include <conio.h>
#include <thread>
#include <cmath>
#include <stack>
#include <deque>
#pragma warning(disable : 4996)
using namespace std;


//deafult
User::User()
{
	this->username = "";
	this->password = "";
	this->firstname = "";
	this->lastname = "";
}

//paramitrized
User::User(string username, string password, string firstname, string lastname)
{
	this->username = username;
	this->password = password;
	this->firstname = firstname;
	this->lastname = lastname;
}

//load user info from file to deque
void User::load_user_info()
{
	d1.clear();
	ifstream file("login_file.txt");
	string value;
	while (file >> value) {
		d1.push_back(value);
	}
	file.close();
}


//register
void User::registery() {
	string answer;
	transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

l1:
	cout << "\t\t\t\tDO YOU HAVE AN ACCOUNT? [YES/NO]" << endl;
	cout << "\t\t\t\t";
	cin >> answer;

	if (answer == "yes") {
		login();
	}
	else if (answer == "no") {
	l2:
		ofstream outfile("login_file.txt", ios::app);

		cout << "\t\t\t\tENTER YOUR FIRST NAME: ";
		cin >> firstname;


		cout << "\t\t\t\tENTER YOUR LAST NAME: ";
		cin >> lastname;

		cout << "\t\t\t\tENTER YOUR USERNAME: ";
		cin >> username;
		bool username_exists = false;
		string line1;
		ifstream infilee("login_file.txt");
		if (infilee.is_open()) {
			while (getline(infilee, line1)) {
				if (line1 == username) {
					username_exists = true;
					break;
				}
			}
			infilee.close();
		}

		cout << "\t\t\t\tENTER YOUR PASSWORD: ";
		cin >> password;
		bool password_exists = false;
		string line2;
		ifstream infile("login_file.txt");
		if (infile.is_open()) {
			while (getline(infile, line2)) {
				if (line2 == password) {
					password_exists = true;
					break;
				}
			}
			infile.close();
		}
		if (username_exists == true && password_exists == true)
		{
			cout << "\t\t\t\tTHE USERNAME OR PASSWORD ALREADY USED...ENTER YOUR DATA AGAIN" << endl;
			goto l2;
		}
		else
		{
			outfile << firstname << endl;
			outfile << lastname << endl;
			outfile << username << endl;
			outfile << password << endl;
			cout << "\t\t\t\tREGISTRATION DONE" << endl;
		}

		outfile.close();
	}
	else {
		cout << "\t\t\t\tINVALID ANSWER...TRY AGAIN" << endl;
		goto l1;
	}
}


//log in
void User::login()
{
	load_user_info();
	string username, password;
	cout << "\t\t\t\tENTER YOUR USERNAME : ";
	cin >> username;
	bool username_exists = false;
	for (auto i = d1.begin(); i != d1.end(); i++)
	{
		if (username.compare(*i) == 0){
			username_exists = true;
		}
	}
	cout << "\t\t\t\tENTER YOUR PASSWORD : ";
	cin >> password;
	bool password_exists = false;
	for (auto i = d1.begin(); i != d1.end(); i++)
	{
		if (password.compare(*i) == 0) {
			password_exists = true;
		}
	}

	if (username_exists == true && password_exists == true)
	{
		cout << "\t\t\t\tLOG IN SUCCESSFULLY" << endl;
	}
	else
	{
		cout << "\t\t\t\tWRONG USERNAME OR PASSWORD...TRY AGAIN" << endl;
		registery();
	}
}


//time overlapping
bool User::intersect(string start_time, string end_time)
{
	bool bad = 0;
	vec.push_back(start_time);
	vec.push_back(end_time);
	sort(vec.begin(), vec.end());
	for (int i = 0; i < vec.size() - 1; i++)
	{
		if (mp[vec[i]] == 0 && mp[vec[i + 1]] == 0)
		{
			bad = 1;
			break;
		}
		else if (mp[vec[i]] == 1 && mp[vec[i + 1]] == 1)
		{
			bad = 1;
			break;
		}
	}
	return bad;
}


//concatinating with 0
string User::fix(int x)
{
	string s = to_string(x);
	if (s.size() == 1) {
		string s2 = "0";
		s = s2 + s;
	}
	return s;
}
 

//load data from the file to the events vector
void User::load_data() {
	ifstream open_event;
	open_event.open("upcoming_events.txt");
	string name;
	string place;
	string M;
	int start_date_day;
	int start_date_month;
	int start_date_year;
	int end_date_day;
	int end_date_month;
	int end_date_year;
	int start_time;
	int start_time_min;
	int end_time;
	int end_time_min;
	bool done;
	
	getline(open_event, name);
	getline(open_event, place);
	open_event >> start_date_day;
	open_event >> start_date_month;
	open_event >> start_date_year;
	open_event >> end_date_day;
	open_event >> end_date_month;
	open_event >> end_date_year;
	open_event >> start_time;
	open_event >> start_time_min;
	open_event >> end_time;
	open_event >> end_time_min;
	getline(open_event, M);
	getline(open_event, M);
	open_event >> done;

	while (!open_event.eof())
	{
		Event eve(name, start_date_day, start_date_month, start_date_year, end_date_day, end_date_month, end_date_year, place, start_time, end_time, start_time_min, end_time_min, done, M);
		events.push_back(eve);
		getline(open_event >> ws, name);
		getline(open_event, place);
		open_event >> start_date_day;
		open_event >> start_date_month;
		open_event >> start_date_year;
		open_event >> end_date_day;
		open_event >> end_date_month;
		open_event >> end_date_year;
		open_event >> start_time;
		open_event >> start_time_min;
		open_event >> end_time;
		open_event >> end_time_min;
		getline(open_event >> ws, M);
		open_event >> done;
	}
	open_event.close();
}


//Add event 
bool User::add_event() {
	ifstream open_event;
	open_event.open("upcoming_events.txt");
	bool event_place_exist = false;
	//bool event_day_exist = false;
	//bool event_month_exist = false;

	/* the two commented variables above are in vain because the map already checks if
	* is any time overlapping so we want to check time overlapping(done by map )
	* AND im the same event place
	*/
	string name;
	string place;
	string M;
	int start_date_day;
	int start_date_month;
	int start_date_year;
	int end_date_day;
	int end_date_month;
	int end_date_year;
	int start_time;
	int start_time_min;
	int end_time;
	int end_time_min;
	bool done;
	//bool check1 = false;
	//bool check2 = false;
	//bool check3 = false;
	//bool check4 = false;
	
	//load data from the file to the events vector
	if (open_event) {
		events.clear();
		vec.clear();
		open_event.close();
		load_data();
	}
	
	//get time now
	time_t t = std::time(0);  
	tm* now = std::localtime(&t);
	int year = now->tm_year + 1900;
	int day = now->tm_mday;
	int month = (now->tm_mon + 1);

label:
	//take event name
again: cout << "\n\t\t\t\tENTER EVENT NAME : ";
	getline(cin>>ws, name);
	cout << endl;

	//take event place
	cout << "\t\t\t\tENTER EVENT PLACE : ";
	getline(cin, place);
	cout << endl;
	if (!events.empty()) {
		for (int i = 0; i < events.size(); i++)
		{

			if (events[i].place == place) {
				event_place_exist = true;
			}
		}
	}
	
	//take event start date
l1:cout << "\t\t\t\tENTER EVENT START DATE :" << endl;
	cout << "\t\t\t\tDAY [MUST BE A NUMBER] : ";
	while (cin >> start_date_day && (start_date_day < 1 || start_date_day >31)) {
		cout << "\t\t\t\tINVALID DAY...MUST BE IN Range [1-31]" << endl;
		cout << "\t\t\t\tDAY [MUST BE A NUMBER] : ";
	}

	cout << "\t\t\t\tMONTH [MUST BE A NUMBER] : ";
	while (cin >> start_date_month && (start_date_month < 1 || start_date_month > 12)) {
		cout << "\t\t\t\tINVALID MONTH...MUST BE IN Range [1-12]" << endl;
		cout << "\t\t\t\tMONTH [MUST BE A NUMBER] : ";
	}

	if ((start_date_month < month) || ((start_date_day <= day) && (start_date_month == month))) {
		cout << "\n\t\t\t\tPLEASE ENTER COMING DATE"<<endl;
		goto l1;
	}

cout << "\t\t\t\tYEAR [MUST BE A NUMBER] : ";
	while (cin >> start_date_year && (start_date_year > 2023 || start_date_year < 2023)) {
		cout << "\t\t\t\tYEAR SHOULD BE 2023" << endl;
		cout << "\t\t\t\tYEAR [MUST BE A NUMBER] : ";
	}
	cout << endl;
	
	//take event end date
	l4:cout << "\t\t\t\tENTER EVENT END DATE :" << endl;
	cout << "\t\t\t\t DAY [MUST BE A NUMBER] : ";
	while (cin >> end_date_day && (end_date_day < 1 || end_date_day >31)) {
		cout << "\t\t\t\t INVALID DAY...MUST BE IN Range [1-31]" << endl;
		cout << "\t\t\t\tDAY [MUST BE A NUMBER] : ";
	}

	cout << "\t\t\t\tMONTH [MUST BE A NUMBER] : ";
	while (cin >> end_date_month && (end_date_month < 1 || end_date_month > 12)) {
		cout << "\t\t\t\tINVALID MONTH...MUST BE IN Range [1-12]" << endl;
		cout << "\t\t\t\tmonth [MUST BE A NUMBER] : ";
	}

	if ((end_date_month < month) || (end_date_day <= day) && (end_date_month == month)) {
		cout << "\n\t\t\t\t PLEASE ENTER COMING DATE\n";
		goto l4;
	}
	
	cout << "\t\t\t\tYEAR [MUST BE A NUMBER] : ";
	while (cin >> end_date_year && (end_date_year > 2023 || end_date_year < 2023))
	{
		cout << "\t\t\t\tYEAR SHOULD BE 2023" << endl;
		cout << "\t\t\t\tYEAR [MUST BE A NUMBER] : ";
	}
	
	if ((end_date_day == start_date_day && end_date_month == start_date_month) || (end_date_day < start_date_day && end_date_month == start_date_month) || (end_date_month < start_date_month)) {
		cout << "\n\t\t\t\tEND DATE IS BEFORE START DATE ";
		cout << endl;
		goto l4;
	}
	cout << endl;

	//take event start time
	t:cout << "\t\t\t\tENTER EVENT START TIME HOUR : ";
	while (cin >> start_time && (start_time > 12 || start_time < 1)) {
		cout << "\t\t\t\tINVALID HOUR...MUST BE IN Range [1-12] ";
		cout << endl;
		cout << "\t\t\t\tENTER EVENT START TIME HOUR : ";
	}
	cout << endl;

	cout << "\t\t\t\tENTER EVENT START TIME MINUTE : ";
	while (cin >> start_time_min && (start_time_min > 59 || start_time_min < 0)) {
		cout << "\t\t\t\t INVALID MINUTE...MUST BE IN Range [0-59]";
		cout << endl;
		cout << "\t\t\t\tENTER EVENT START TIME MINUTE : ";
	}

yet2:cout << "\n\t\t\t\tENTER PM OR AM : ";
	cin >> M;
	transform(M.begin(), M.end(), M.begin(), ::toupper);
	if (M == "PM") {
		//check1 == true;
		goto yet;
	}
	else if (M == "AM")
	{
		//check2 == true;
		goto yet;
	}
	else {
		goto yet2;
	}
yet:cout << endl;

	//take event end time
	cout << "\t\t\t\tENTER EVENT END TIME HOUR : ";
	while (cin >> end_time && (end_time > 12 || end_time < 1)) {
		cout << "\t\t\t\tINVALID HOUR...MUST BE IN Range [1-12]  ";
		cout << endl;
		cout << "\t\t\t\tENTER EVENT END TIME HOUR ";
	}
	cout << endl;

	cout << "\t\t\t\tENTER EVENT END TIME MINUTE : ";
	while (cin >> end_time_min && (end_time_min > 59 || end_time_min < 0)) {
		cout << "\t\t\t\tINVALID MINUTE...MUST BE IN Range [0-59] ";
		cout << "\t\t\t\tENTER EVENT END TIME MINUTE : ";
	}

	//pm or am
yet3:cout << "\n\t\t\t\tENTER PM OR AM : ";
	cin >> M;
	transform(M.begin(), M.end(), M.begin(), ::toupper);
	if (M == "PM") {
		//check3 == true;
		goto yet4;
	}
	else if (M == "AM")
	{
		//check4 == true;
		goto yet4;
	}
	else {
		goto yet3;
	}

yet4:cout << endl;
	
	//if ((check1 == true && check3 == true && start_time > end_time) || (check2 == true && check4 == true && start_time > end_time) ) {
		//cout << "\t\t\t\tSTART TIME SHOULD BE BEFORE END TIME\n\n";
		//goto t;
	//}
	// //no need
	//no conditions on am pm or pm am because it is changable and unhandleable


	string s1, s2, s3, s4, s5, s6, s7, s8, start_time_s, end_time_s;
	
	//load time strings to the intersection vector
	for (int i = 0; i < events.size(); i++)
	{
		 s1 = fix(events[i].start_date_year);
		 s2 = fix(events[i].start_date_month);
		 s3 = fix(events[i].start_date_day);
		 s4 = fix(events[i].start_time);
		 start_time_s = s1 + s2 + s3 + s4;
		 s5 = fix(events[i].end_date_year);
		 s6 = fix(events[i].end_date_month);
		 s7 = fix(events[i].end_date_day);
		 s8 = fix(events[i].end_time);
		 end_time_s = s5 + s6 + s7 + s8;
		mp[start_time_s] = 1;
		mp[end_time_s] = 0;
		intersect(start_time_s, end_time_s);
	}
	
	//check the time intervals overlapping
	s1 = fix(start_date_year); 
	s2 = fix(start_date_month); 
	s3 = fix(start_date_day);
	s4 = fix(start_time);
	start_time_s = s1 + s2 + s3 + s4;
	s5 = fix(end_date_year);
	s6 = fix(end_date_month); 
	s7 = fix(end_date_day);
	s8 = fix(end_time);
	end_time_s = s5 + s6 + s7 + s8;
	mp[start_time_s] = 1;
	mp[end_time_s] = 0;
	//end checking overlapping
	if (event_place_exist == true)
	{
		goto labeltruee;
	}
	else {
		goto labelfalse;
	}

	
labeltruee: if (intersect(start_time_s, end_time_s))
	{
		int choice;
		for (int j = 0; j < vec.size(); j++)
		{
			if (vec[j] == start_time_s || vec[j] == end_time_s)
			{
				vec.erase(vec.begin() + j);
				j -= 1;
			}
		}
		cout << "\t\t\t\tTHERE IS AN EVENT IN THE SAME PLACE AND THE SAME TIME " << endl;
		again2:cout << "\t\t\t\tPRESS 1 TO ENTER DATA AGAIN OR 0 TO GO TO THE MAIN PAGE : ";
		cin >> choice;
		if (choice == 0) {
			return false;
		}
		else if (choice == 1) {
			goto label;
		}
		else {
			cout << "\t\t\t\tINVALID CHOICE ... TRY AGAIN\n";
			goto again2;
		}
	}
	

labelfalse:	Event eve(name, start_date_day, start_date_month, start_date_year, end_date_day, end_date_month, end_date_year, place, start_time, end_time, start_time_min, end_time_min, M);
		events.push_back(eve);
		insert_file(eve);
		cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t-:YOUR EVENT IS SUCCESSFULLY ADDED :-\n\n";
	
		
	return true;
}


// insert event's data in a file
void User::insert_file(Event eve) {
	ofstream event_data;
	event_data.open("upcoming_events.txt", ios::app);
	event_data << eve.name;
	event_data << endl;
	event_data << eve.place;
	event_data << endl;
	event_data << eve.start_date_day;
	event_data << endl;
	event_data << eve.start_date_month;
	event_data << endl;
	event_data << eve.start_date_year;
	event_data << endl;
	event_data << eve.end_date_day;
	event_data << endl;
	event_data << eve.end_date_month;
	event_data << endl;
	event_data << eve.end_date_year;
	event_data << endl;
	event_data << eve.start_time;
	event_data << endl;
	event_data << eve.start_time_min;
	event_data << endl;
	event_data << eve.end_time;
	event_data << endl;
	event_data << eve.end_time_min;
	event_data << endl;
	event_data << eve.M;
	event_data << endl;
	event_data << eve.done;
	event_data << endl;
	event_data.close();
}


//Update event 
bool User::update_event(string name) {
	events.clear();
	vec.clear();
	ifstream open_event;
	open_event.open("upcoming_events.txt");

	//check if there are events or not
	if (!open_event) {
		cout << "\t\t\t\tTHERE ARE NO EVENTS YET" << endl;
		return false;
	}
	load_data();
	open_event.close();
	int indicator;
	string s1, s2, s3, s4, s5, s6, s7, s8, start_time_s, end_time_s;
	int choice;
	bool found = false;

	// get time now
	time_t t = std::time(0);
	tm* now = std::localtime(&t);
	int year = now->tm_year + 1900;
	int day = now->tm_mday;
	int month = (now->tm_mon + 1);

	for (int i = 0; i < events.size(); i++)
	{
		if (events[i].name.compare(name) == 0) {
			found = true;
		wrong:cout << "\t\t\t\tENTER THE ATTRIBUTE NUMBER YOU WANT TO UPDATE : " << endl;
			cout << "\t\t\t\t1- EVENT NAME\n";
			cout << "\t\t\t\t2- EVENT DATE AND TIME\n";
			cout << "\t\t\t\t3- EVENT PLACE\n";
			cout << "\t\t\t\tCHOICE : ";
			cin >> indicator;
			cout << endl;

			switch (indicator) {
				//to updaate event name
			case 1:
			label1:cout << "\t\t\t\tENTER EVENT NAME : ";
				getline(cin, events[i].name);
				getline(cin, events[i].name);
				for (int i = 0; i < events.size(); i++)
				{
					if (events[i].name.compare(name) == 0) {
						cout << "\t\t\t\tTHIS EVENT NAME ALREADY EXISTS\n";
						goto label1;
					}
				}
				break;

				//to update Event date and time
			case 2:
			l1:
			label2:cout << "\t\t\t\tENTER EVENT START DATE :" << endl;
				cout << "\t\t\t\tDAY [MUST BE A NUMBER] : ";
				while (cin >> events[i].start_date_day && (events[i].start_date_day < 1 || events[i].start_date_day >31)) {
					cout << endl;
					cout << "\t\t\t\tINVALID DAY...MUST BE IN Range [1-31]" << endl;
					cout << "\t\t\t\tDAY [MUST BE A NUMBER] : ";
				}

				cout << "\t\t\t\MONTH [MUST BE A NUMBER] : ";
				while (cin >> events[i].start_date_month && (events[i].start_date_month < 1 || events[i].start_date_month > 12)) {
					cout << endl;
					cout << "\t\t\t\tINVALID MONTH...MUST BE IN Range [1-12]" << endl;
					cout << "\t\t\t\tMONTH [MUST BE A NUMBER] : ";
				}

				if ((events[i].start_date_month < month) || ((events[i].start_date_day <= day) && (events[i].start_date_month == month))) {
					cout << "\n\t\t\t\tPLEASE ENTER COMING DATE\n";
					goto l1;
				}

				cout << "\t\t\t\tYEAR [MUST BE A NUMBER] : ";
				while (cin >> events[i].start_date_year && (events[i].start_date_year > 2023 || events[i].start_date_year < 2023)) {
					cout << endl;
					cout << "\t\t\t\tYEAR SHOULD BE 2023" << endl;
					cout << "\t\t\t\tYEAR [MUST BE A NUMBER] : ";
				}
				cout << endl;

			l4:cout << "\t\t\t\tENTER EVENT END DATE :" << endl;
				cout << "\t\t\t\tDAY [MUST BE A NUMBER] : ";
				while (cin >> events[i].end_date_day && (events[i].end_date_day < 1 || events[i].end_date_day >31)) {
					cout << endl;
					cout << "\t\t\t\tINVALID DAY...MUST BE IN Range [1-31]" << endl;
					cout << "\t\t\t\tDAY [MUST BE A NUMBER] : ";
				}

				cout << "\t\t\t\tMONTH [MUST BE A NUMBER] : ";
				while (cin >> events[i].end_date_month && (events[i].end_date_month < 1 || events[i].end_date_month > 12)) {
					cout << endl;
					cout << "\t\t\t\tINVALID MONTH...MUST BE IN Range [1-12]" << endl;
					cout << "\t\t\t\tMONTH [MUST BE A NUMBER] : ";
				}
				if ((events[i].end_date_month < month) || (events[i].end_date_day <= day) && (events[i].end_date_month == month)) {
					cout << "\n\t\t\t\t PLEASE ENTER COMING DATE\n";
					goto l4;
				}

				cout << "\t\t\t\tYEAR [MUST BE A NUMBER] : ";
				while (cin >> events[i].end_date_year && (events[i].end_date_year > 2023 || events[i].end_date_year < 2023)) {
					cout << endl;
					cout << "\t\t\t\tYEAR SHOULD BE 2023" << endl;
					cout << "\t\t\t\tYEAR [MUST BE A NUMBER] : ";
				}

				if ((events[i].end_date_day == events[i].start_date_day && events[i].end_date_month == events[i].start_date_month) || (events[i].end_date_day < events[i].start_date_day && events[i].end_date_month == events[i].start_date_month) || (events[i].end_date_month < events[i].start_date_month)) {
					cout << "\n\t\t\t\tEND DATE IS BEFORE START DATE OR EVENT LENGTH IS LESS THAN ONE DAY";
					cout << endl;
					goto l4;
				}
				cout << endl;

			t:cout << "\t\t\t\tENTER EVENT START TIME HOUR [MUST BE A NUMBER] :";
				while (cin >> events[i].start_time && (events[i].start_time > 12 || events[i].start_time < 1)) {
					cout << "\t\t\t\tINVALID HOUR...MUST BE IN Range [1-12] ";
					cout << endl;
					cout << "\t\t\t\tENTER EVENT START TIME HOUR [MUST BE A NUMBER] :";
				}
				cout << endl;

				cout << "\t\t\t\tENTER EVENT START TIME MINUTE [MUST BE A NUMBER] : ";
				while (cin >> events[i].start_time_min && (events[i].start_time_min > 59 || events[i].start_time_min < 0)) {
					cout << "\t\t\t\tINVALID HOUR...MUST BE IN Range [0-59] ";
					cout << endl;
					cout << "\t\t\t\tENTER EVENT START TIME MINUTE [MUST BE A NUMBER] : ";
				}
				cout << endl;

				cout << "\t\t\t\tENTER EVENT END TIME HOUR [MUST BE A NUMBER] : ";
				while (cin >> events[i].end_time && (events[i].end_time > 12 || events[i].end_time < 1)) {
					cout << "\t\t\t\tINVALID HOUR...MUST BE IN Range [1-12] ";
					cout << endl;
					cout << "\t\t\t\tENTER EVENT END TIME HOUR [MUST BE A NUMBER] : ";
				}
				cout << endl;

				cout << "\t\t\t\tENTER EVENT END TIME MINUTE [MUST BE A NUMBER] : ";
				cin >> events[i].end_time_min;
				while (cin >> events[i].end_time_min && (events[i].end_time_min > 59 || events[i].end_time_min < 0)) {
					cout << "\t\t\t\tINVALID MINUTE...MUST BE IN Range [0-59] ";
					cout << endl;
					cout << "\t\t\t\tENTER EVENT START TIME MINUTE [MUST BE A NUMBER] : ";
				}
				cout << endl;

			yet2:cout << "\n\t\t\t\tENTER PM OR AM : ";
				transform(events[i].M.begin(), events[i].M.end(), events[i].M.begin(), ::toupper);
				cin >> events[i].M;
				if (events[i].M == "PM" || events[i].M == "AM")
					goto yet;
				else
					goto yet2;
			yet:cout << endl;

				//load time strings to the intersection vector
				for (int i = 0; i < events.size(); i++)
				{
					s1 = fix(events[i].start_date_year);
					s2 = fix(events[i].start_date_month);
					s3 = fix(events[i].start_date_day);
					s4 = fix(events[i].start_time);
					start_time_s = s1 + s2 + s3 + s4;
					s5 = fix(events[i].end_date_year);
					s6 = fix(events[i].end_date_month);
					s7 = fix(events[i].end_date_day);
					s8 = fix(events[i].end_time);
					end_time_s = s5 + s6 + s7 + s8;
					intersect(start_time_s, end_time_s);
				}

				//check the time intervals overlapping
				s1 = fix(events[i].start_date_year);
				s2 = fix(events[i].start_date_month);
				s3 = fix(events[i].start_date_day);
				s4 = fix(events[i].start_time);
				start_time_s = s1 + s2 + s3 + s4;
				s5 = fix(events[i].end_date_year);
				s6 = fix(events[i].end_date_month);
				s7 = fix(events[i].end_date_day);
				s8 = fix(events[i].end_time);
				end_time_s = s5 + s6 + s7 + s8;
				mp[start_time_s] = 1;
				mp[end_time_s] = 0;
				if (intersect(start_time_s, end_time_s))
				{
					for (int j = 0; j < vec.size(); j++)
					{
						if (vec[j] == start_time_s || vec[j] == end_time_s)
						{
							vec.erase(vec.begin() + j);
							j -= 1;
						}
					}
					cout << "\t\t\t\tTHERE IS AN INTERSECTION" << endl;
					goto label2;
				}
				break;

				//to update event place
			case 3:
				cout << "\t\t\t\tENTER EVENT PLACE : ";
				getline(cin, events[i].place);
				getline(cin, events[i].place);
				break;
			}
		}
	}
	if (name == "") {
		return true;
	}

	if (!found) {
		cout << "\t\t\t\tTHERE IS NO EVENT WITH THIS NAME TO UPDATE\n\n";
	}
	update_file(events);
	return found;
}


//update events in the file
void User::update_file(vector<Event> update) {
	ofstream updated_events("upcoming_events.txt", ios::out | ios::trunc);
	updated_events.close();
	for (int i = 0; i < update.size(); i++)
	{
		insert_file(update[i]);
	}
}


//Delete event 
bool User::delete_event(string name, bool is_done) {
	events.clear();
	done_events.clear();
	ifstream open_event;
	open_event.open("upcoming_events.txt");
	
	//check if there are events or not
	if (!open_event.is_open()) {
		cout << "\n\t\t\t\tTHERE ARE NO EVENTS YET" << endl;
		return false;
	}
	open_event.close();
	load_data();
	
	bool flag = false;

	for (int i = 0; i < events.size(); i++)
	{
		
		if (events[i].name.compare(name) == 0) {
				string is_done1;
			aga:cout << "\n\t\t\t\tIS THIS EVENT DONE? [YES/NO]: ";
				cin >> is_done1;
				cout << endl;
				transform(is_done1.begin(), is_done1.end(), is_done1.begin(), ::tolower);
				if (is_done1 == "yes") {
					is_done = true;
				}
				else if (is_done1 == "no") {
					is_done = false;
				}
				else {
					cout << "THIS CHOICE IS INVALID\n";
					goto aga;
				}
				cout << "\n\t\t\t\t\t\t\t\t\t\t\t-:YOUR EVENT IS SUCCESSFULLY DELETED:-\n\n";
			
			flag = true;
			if (is_done) {
				done_events.push_back(events[i]);
				events.erase(events.begin() + i);
			}
			else {
				events.erase(events.begin() + i);
			}
		}
	}
	
	if (name == "") {
		return true;
	}
	
	if (!flag) {
		cout << "\n\t\t\t\tTHERE IS NO EVENT WITH THIS NAME TO DELETE\n\n";
	}
	delete_file(events);
	insert_done_events(done_events);
	return flag;
}


//delete events from the file
void User::delete_file(vector<Event> deleted) {
	ofstream updated_events("upcoming_events.txt", ios::out | ios::trunc);
	updated_events.close();
	for (int i = 0; i < deleted.size(); i++)
	{
		insert_file(deleted[i]);
	}
}


//order events before displaying 
void User::to_order(string start_time, string end_time, string name) {
	vec_disp.push_back(start_time);
	vec_disp.push_back(end_time);
	sort(vec_disp.begin(), vec_disp.end());
	vec_disp2.push_back({ start_time, name });
	vec_disp2.push_back({ end_time ,name });
}


//display events ordered by start date and reminder time
bool User::display_in_order() {
	bool flag = false;
	ifstream display_event;
	display_event.open("upcoming_events.txt");
	if (!display_event) {
		return flag;
	}
	vector <Event> displayed_events;
	displayed_events.clear();
	vec_disp.clear();
	vec_disp2.clear();
	string name;
	string place;
	string s1, s2, s3, s4, s5, s6, s7, s8, start_time_s, end_time_s;
	string M;
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
	bool done;

	//load events from the file to the vector displayed_events
	getline(display_event, name);
	getline(display_event, place);
	display_event >> start_date_day;
	display_event >> start_date_month;
	display_event >> start_date_year;
	display_event >> end_date_day;
	display_event >> end_date_month;
	display_event >> end_date_year;
	display_event >> start_time;
	display_event >> start_time_min;
	display_event >> end_time;
	display_event >> end_time_min;
	getline(display_event, M);
	getline(display_event, M);
	display_event >> done;
	while (!display_event.eof())
	{
		Event eve(name, start_date_day, start_date_month, start_date_year, end_date_day, end_date_month, end_date_year, place, start_time, end_time, start_time_min, end_time_min, done, M);
		displayed_events.push_back(eve);
		getline(display_event >> ws, name);
		getline(display_event, place);
		display_event >> start_date_day;
		display_event >> start_date_month;
		display_event >> start_date_year;
		display_event >> end_date_day;
		display_event >> end_date_month;
		display_event >> end_date_year;
		display_event >> start_time;
		display_event >> start_time_min;
		display_event >> end_time;
		display_event >> end_time_min;
		getline(display_event >> ws, M);
		display_event >> done;
	}
	display_event.close();

	//load events from the file to the intersection vector
	for (int i = 0; i < displayed_events.size(); i++)
	{
		s1 = fix(displayed_events[i].start_date_year);
		s2 = fix(displayed_events[i].start_date_month);
		s3 = fix(displayed_events[i].start_date_day);
		s4 = fix(displayed_events[i].start_time);
		start_time_s = s1 + s2 + s3 + s4;
		s5 = fix(displayed_events[i].end_date_year);
		s6 = fix(displayed_events[i].end_date_month);
		s7 = fix(displayed_events[i].end_date_day);
		s8 = fix(displayed_events[i].end_time);
		end_time_s = s5 + s6 + s7 + s8;
		to_order(start_time_s, end_time_s, displayed_events[i].name);
	}

	//to display events
	int it = 0;
	for (int i = 0; i < vec_disp.size(); i += 2)
	{
		for (int j = 0; j < vec_disp2.size(); j += 2)
		{
			if (vec_disp2[j].first == vec_disp[i] && vec_disp2[j + 1].first == vec_disp[i + 1]) {
				for (int k = 0; k < displayed_events.size(); k++)
				{
					if (displayed_events[k].name.compare(vec_disp2[j].second) == 0) {
						flag = true;
						displayed_events[k].reminder_time(displayed_events[k].start_time, displayed_events[k].start_time_min, displayed_events[k].M);
						displayed_events[k].reminder_date(displayed_events[k].start_date_month, displayed_events[k].start_date_day);
						cout << "\n\t\t\t\t\t\t\t\t\t\t\t\t  -: EVENT" << it + 1 << " :-" << endl << endl;
						cout << "\t\t\t\t\t\tNAME: " << displayed_events[k].name << endl;
						cout << "\t\t\t\t\t\tPLACE: " << displayed_events[k].place << endl;
						cout << "\t\t\t\t\t\tSTART DATE: " << displayed_events[k].start_date_day << "/" << displayed_events[k].start_date_month << "/" << displayed_events[k].start_date_year << endl;
						cout << "\t\t\t\t\t\tEND DATE: " << displayed_events[k].end_date_day << "/" << displayed_events[k].end_date_month << "/" << displayed_events[k].end_date_year << endl;
						cout << "\t\t\t\t\t\tSTART TIME: " << displayed_events[k].start_time << ":" << displayed_events[k].start_time_min << endl;
						cout << "\t\t\t\t\t\tEND TIME: " << displayed_events[k].end_time << ":" << displayed_events[k].end_time_min << endl;
						cout << "\t\t\t\t\t\tREMINDER TIME: " << displayed_events[k].r.month_count << " MONTHES, " << displayed_events[k].r.day_count << " DAYE, " << displayed_events[k].r.hour_count << " HOURS, " << displayed_events[k].r.minute_count << " MINUTES" << endl;
						cout << "\t\t\t\t\t\t-->===================================================<-----" << endl << endl;
						it++;
					}

				}
			}
		}
	}
	return flag;
}


//display done events
void User::display_done_events() {
	ifstream displayed_done;
	displayed_done.open("done_events.txt");
	
	//check if there are done events in the file or not
	if (check_doneevents_file()) {
		cout << endl;
		cout << "\t\t\t\tNO DONE EVENTS YET\n";
		return;
	}
	string name;
	string place;
	string M;
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
	bool done;

	//load done events from the file to display them
	getline(displayed_done, name);
	getline(displayed_done, place);
	displayed_done >> start_date_day;
	displayed_done >> start_date_month;
	displayed_done >> start_date_year;
	displayed_done >> end_date_day;
	displayed_done >> end_date_month;
	displayed_done >> end_date_year;
	displayed_done >> start_time;
	displayed_done >> start_time_min;
	displayed_done >> end_time;
	displayed_done >> end_time_min;
	getline(displayed_done, M);
	getline(displayed_done, M);
	displayed_done >> done;
	int it = 0;
	while (!displayed_done.eof())
	{
		cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t\t  -: EVENT" << it + 1 << " :-" << endl << endl;
		cout << "\t\t\t\t\t\tNAME: " << name << endl;
		cout << "\t\t\t\t\t\tPLACE: " << place << endl;
		cout << "\t\t\t\t\t\tSTART DATE: " << start_date_day << "/" << start_date_month << "/" << start_date_year << endl;
		cout << "\t\t\t\t\t\tEND DATE: " <<end_date_day << "/" << end_date_month << "/" << end_date_year << endl;
		cout << "\t\t\t\t\t\tDONE: |YES|" << endl;
		cout << "\t\t\t\t\t\t-->===================================================<-----" << endl << endl;
		it++;
		getline(displayed_done >> ws, name);
		getline(displayed_done, place);
		displayed_done >> start_date_day;
		displayed_done >> start_date_month;
		displayed_done >> start_date_year;
		displayed_done >> end_date_day;
		displayed_done >> end_date_month;
		displayed_done >> end_date_year;
		displayed_done >> start_time;
		displayed_done >> start_time_min;
		displayed_done >> end_time;
		displayed_done >> end_time_min;
		getline(displayed_done >> ws, M);
		displayed_done >> done;
	}
	displayed_done.close();
}


//insert done events in the file
void User::insert_done_events(vector <Event> done_eve) {
	if (done_eve.empty()) {
		return;
	}
	
	else {
		ofstream done_data;
		done_data.open("done_events.txt", ios::app);
		for (int i = 0; i < done_eve.size(); i++)
		{
			done_data << done_eve[i].name;
			done_data << endl;
			done_data << done_eve[i].place;
			done_data << endl;
			done_data << done_eve[i].start_date_day;
			done_data << endl;
			done_data << done_eve[i].start_date_month;
			done_data << endl;
			done_data << done_eve[i].start_date_year;
			done_data << endl;
			done_data << done_eve[i].end_date_day;
			done_data << endl;
			done_data << done_eve[i].end_date_month;
			done_data << endl;
			done_data << done_eve[i].end_date_year;
			done_data << endl;
			done_data << done_eve[i].start_time;
			done_data << endl;
			done_data << done_eve[i].start_time_min;
			done_data << endl;
			done_data << done_eve[i].end_time;
			done_data << endl;
			done_data << done_eve[i].end_time_min;
			done_data << endl;
			done_data << done_eve[i].M;
			done_data << endl;
			done_data << done_eve[i].done;
			done_data << endl;
		}
		done_data.close();
	}
}


//check done events file empty or not
bool User::check_doneevents_file()
{
	ifstream file("done_events.txt");
	if (file.peek() == ifstream::traits_type::eof()) {
		return true;
	}
	else {
		return false;
	}
	file.close();
}


//undo and back the done events to the file
void User::undo_and_type()
{
	while (!s4.empty())
	{
		s2.push(s4.top());
		s4.pop();
	}
	std::ofstream file("done_events.txt");
	while (!s2.empty()) {
		string value = s2.top();
		file << value << std::endl;
		s2.pop();
	}
	file.close();
}


//undo,saving the done events to stack,deleting the done events file contents and redy for the above function
void User::undo()
{
	ifstream ifs("done_events.txt");
	if (ifs.is_open()) {
		string line;
		while (getline(ifs, line)) {
			s4.push(line);
		}
		ifs.close();
		std::ofstream ofs("done_events.txt", std::ios::trunc);
		ofs.close();
	}
	else {
		cout << "Unable to open file" << endl;
	}
}










//################################################finish#######################################