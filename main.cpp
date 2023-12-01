#include<iostream>
#include<fstream>
#include "User.h"
#include "Event.h"
#include <string>
#include <stack>
#include <thread>
using namespace std;
void menu();
void menu() {
startlabel:	int response;
	User obj;
	cout << endl;
	cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tWELCOME" << endl;
	cout << endl;
	cout << "\t\t\t\tPRESS 1 TO REGISTER AND 2 TO LOGIN" << endl;
	cout << "\t\t\t\tCHOICE : ";
	cin >> response;
	if (response==1) {
		obj.registery();
	}
	else if (response==2) {
		obj.login();
	}
	else {
		cout << "\t\t\t\tINVALID ANSWER...TRY AGAIN" << endl;
		system("cls");
		goto startlabel;
	}
	ifstream ifs("done_events.txt");
	int choice;
	User user;
	string updated_name;
	string deleted_name;
	bool done;
	int del;
	string is_done;
	string yes;
	cout << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t EVENTS SCHEDULER\n";
	cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
label:cout << "\t\t\t\t\t\t\t\t\t -: THIS APPLICATION ALLOWS YOU TO ADD,DELETE OR UPDATE ANY EVENT:-\n";
	cout << endl;
	cout << "\t\t\t\tPLEASE CHOOSE THE NUMBER OF THE OPERATION YOU WANT TO PERFORM:\n";
	cout << "\t\t\t\t1- ADD EVENT :-\n";
	cout << "\t\t\t\t2- DELETE EVENT :-\n";
	cout << "\t\t\t\t3- UPDATE EVENT :-\n";
	cout << "\t\t\t\t4- DISPLAY UPCOMING EVENTS :-\n";
	cout << "\t\t\t\t5- DISPLAY DONE EVENTS :-\n";
	cout << "\t\t\t\t6- EXIT :-\n\n";
cho:cout << "\t\t\t\tCHOICE : ";
	cin >> choice;

	switch (choice) {
		//add event choice
	case 1:
		system("cls");
		cout << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tEVENTS SCHEDULER\n";
		cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t -: ADD EVENT :-";
	add:if (user.add_event()) {
		while (true) {
			string yes_or_no;
		yes:cout << "\t\t\t\tDO YOU WANT TO ADD ANOTHER EVENT ? [YES/NO]: ";
			cin >> yes_or_no;
			transform(yes_or_no.begin(), yes_or_no.end(), yes_or_no.begin(), ::toupper);
			if (yes_or_no == "YES") {
				goto add;
			}
			else if (yes_or_no == "NO") {
				system("cls");
				cout << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t\t\tEVENTS SCHEDULER\n";
				cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
				goto label;
			}
			else {
				cout << "\t\t\t\tTHIS CHOICE IS INVALID\n";
				goto yes;
			}
		}
	}
	else {
		system("cls");
		cout << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tEVENTS SCHEDULER \n";
		cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
		goto label;
	}
	break;

	//delete event choice
	case 2:
		system("cls");
		cout << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tEVENTS SCHEDULER\n";
		cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t -: DELETE EVENT :-\n\n";

		if (!user.delete_event("", false)) {
		z:cout << "\n\t\t\t\tPRESS 0 TO GO TO THE MAIN PAGE : ";
			cin >> del;
			if (del != 0) {
				goto z;
			}
			system("cls");
			cout << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tEVENTS SCHEDULER\n";
			cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
			goto label;
		}

	del:cout << "\n\t\t\t\tENTER EVENT NAME YOU WANT TO DELETE : ";
		getline(cin, deleted_name);
		getline(cin, deleted_name);
		user.delete_event(deleted_name, false);
	con2:cout << "\t\t\t\tDO YOU WANT TO CONTINUE DELETING ? [Yes/No]: ";
		cin >> yes;
		transform(yes.begin(), yes.end(), yes.begin(), ::toupper);
		if (yes == "YES") {
			goto del;
		}
		else if (yes == "NO") {
			system("cls");
			cout << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tEVENTS SCHEDULER\n";
			cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
			goto label;
		}
		else {
			cout << "\t\t\t\tTHIS CHOICE IS INVALID\n";
			goto con2;
		}
		break;

		//update event choice
	case 3:
		system("cls");
		cout << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tEVENTS SCHEDULER\n";
		cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t -: UPDATE EVENT :-\n\n";
		if (!user.update_event("")) {
		zz:cout << "\n\t\t\t\tPRESS 0 TO GO TO THE MAIN PAGE : ";
			cin >> del;
			if (del != 0) {
				goto zz;
			}
			system("cls");
			cout << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tEVENTS SCHEDULER\n";
			cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
			goto label;
		}
	up:cout << "\n\t\t\t\tENTER EVENT NAME THAT YOU WANT TO UPDATE : ";
		getline(cin, updated_name);
		getline(cin, updated_name);
		cout << endl;
		if (!user.update_event(updated_name)) {
		con:cout << "\t\t\t\tDO YOU WANT TO CONTINUE UPDATING ? [YES/NO]: ";
			transform(yes.begin(), yes.end(), yes.begin(), ::tolower);
			cin >> yes;
			if (yes == "yes") {
				goto up;
			}
			else if (yes == "no") {
				system("cls");
				cout << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t\t\tEVENTS SCHEDULER\n";
				cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
				goto label;
			}
			else {
				cout << "\t\t\t\tTHIS CHOICE IS INVALID\n";
				goto con;
			}
		}
		while (true) {
			string yes_or_no;
			cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t-:YOUR EVENT IS SUCCESSFULLY UPDATED :-\n\n";
		ag2:cout << "\t\t\t\tDO YOU WANT TO UPDATE ANOTHER EVENT ? [YES/NO] : ";
			transform(yes.begin(), yes.end(), yes.begin(), ::tolower);
			cin >> yes_or_no;
			if (yes_or_no == "yes") {
				goto up;
			}
			else if (yes_or_no == "no") {
				system("cls");
				cout << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t\t\tEVENTS SCHEDULER\n";
				cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
				goto label;
			}
			else {
				cout << "\t\t\t\tTHIS CHOICE IS INVALID\n";
				goto ag2;
			}
		}
		break;

		//display upcoming events choice
	case 4:
		system("cls");
		cout << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tEVENTS SCHEDULER\n";
		cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t -: UPCOMING EVENTS :-\n\n";
		if (!user.display_in_order()) {
			cout << "\t\t\t\tNO UPCOMING EVENTS YET\n";
		}

	p:cout << "\n\t\t\t\tPRESS 0 TO GO TO THE MAIN PAGE : ";
		cin >> del;
		if (del != 0) {
			goto p;
		}

		else {
			system("cls");
			cout << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tEVENTS SCHEDULER\n";
			cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
			goto label;
		}
		break;

		//display done events choice
	case 5:
		if (user.check_doneevents_file()) {
			cout << "\t\t\t\tTHERE IS NO DONE EVENTS YET" << endl;
			goto label;
		}
		else{
			system("cls");
			cout << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tEVENTS SCHEDULER\n";
			cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
			cout << "\t\t\t\t\t\t\t\t\t\t\t\t -: DONE EVENTS :-\n\n";
			user.display_done_events(); {

			pp2:cout << "\n\t\t\t\tPRESS 0 TO GO TO THE MAIN PAGE OR 1 TO CLEAR THEM : \n\n";
				cout << "\t\t\t\t";
				cin >> del;
				if (del == 1) {
					if (ifs.is_open())
					{
						user.undo();
						cout << "\n\t\t\t\tEVENTS ARE CLEARED SUCCESSFULLY \n\n";
						int var;
					back:cout << "\t\t\t\tPRESS 0 TO BACK TO THE MAIN PAGE OR 1 TO UNDO THE CHANGES" << endl;
						cin >> var;
						if (var == 0)
						{
							cout << "\t\t\t\t\t\t\t\t\t\t\t\tEVENTS SCHEDULER\n";
							cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
							goto label;
						}
						else if (var == 1)
						{
							user.undo_and_type();
							cout << "\t\t\t\tUNDO OPERATION IS DONE AND EVENTS ARE BACK TO THE DONE EVENTS" << endl;
							goto label;
						}

						else {
							cout << "\t\t\t\tINVALID CHOICE TRY AGAIN" << endl;
							goto back;
						}
					}
					else
					{
						cout << "\t\t\t\tNO DONE EVENTS TO CLEAR" << endl;
						goto pp2;
					}
				}
				else if (del == 0) {
					system("cls");
					cout << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t\t\tEVENTS SCHEDULER\n";
					cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
					goto label;
				}
				else {
					goto pp2;
				}
				break;
			}

		}
		//exit choice
	case 6:
		cout << "\t\t\t\t\t\t\t\t\t\t\t-: THANKS FOR USING OUR APPLICATION :-\n\n";
		break;

	default:
		cout << "\t\t\t\tTHIS CHOICE IS INVALID\n";
		goto cho;
	}
}

int main() {
	menu();
}