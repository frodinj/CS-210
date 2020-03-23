/*
 ============================================================================
 Name        : Dual_Clock.cpp
 Author      : Jon Frodin
 Version     : 3.16.2020
 Copyright   : Bowser the Turtle Studios
 Description : Dual Clock Application in C++,
 ============================================================================
 */

#include <iostream>
using namespace std;
#include <string>
#include <chrono>

// variables used for many modules
// separated out variables to allow for independent updating
// had trouble updating w/ single variables for hr min second
int hours12 = 8; // initialized time variables to a number for testing
int hours24 = 8;
int minutes12 = 58;
int minutes24 = 58;
int seconds12 = 4; 
int seconds24 = 4;
string amPm = "AM";
string currentTime12;
string currentHours12;
string currentHours24;
string currentMinutes12;
string currentMinutes24;
string currentSeconds12;
string currentSeconds24;
string currentTime24;


void displayClocks() {       // displays the clock - separated to call on each repeat
    // This first section is the primary display
	cout << "**************************\t**************************" << endl;
	cout << "*      12-Hour Clock     *\t*      24-Hour Clock     *" << endl;
	cout << "*\t" << currentTime12 << " \t *\t*\t " << currentTime24 <<"\t *" << endl;
	cout << "**************************\t**************************" << endl;
	system("pause");		// SOURCE: https://stackoverflow.com/questions/21257544/c-wait-for-user-input
}

// handling 12-hr clock
string Clock12 () {
	// first set of blocks to handle over-values and AM/PM switch
	if (hours12 > 12) {	
		hours12 = 1;
	}
	if (hours12 == 12) {
		if (amPm == "AM") {
			amPm = "PM";
		}
		else if (amPm == "PM") {
			amPm = "AM";
		}
	}
	if (minutes12 > 59) {
		minutes12 = 0;
		hours12 += 1;
	}
	if (seconds12 > 59) {
		seconds12 = 0;
		minutes12 += 1;
	}
	// section now that numbers are handled to convert time to display
	currentHours12 = (hours12 < 10) ? "0" + to_string(hours12) : to_string(hours12);
	currentMinutes12 = (minutes12 < 10) ? "0" + to_string(minutes12) : to_string(minutes12);
	currentSeconds12 = (seconds12 < 10) ? "0" + to_string(seconds12) : to_string(seconds12);

	// outputting full time string
	currentTime12 = currentHours12 + ":" + currentMinutes12 + ":" + currentSeconds12 + " " + amPm;
	return currentTime12;		// output statement

}
// handling 24-hr clock
string Clock24() {
	// rollover for minutes and seconds
	if (minutes24 > 59) {
		minutes24 = 0;
		hours24 += 1;
	}
	if (seconds24 > 59) {
		seconds24 = 0;
		minutes24 += 1;
	}
	// formatting for hours on 24-hr clock
	if (hours24 < 10) {
		currentHours24 = "0" + to_string(hours24);
	}
	if (hours24 > 23) {
		hours24 = 0;
		currentHours24 = "0" + to_string(hours24);
	}
	if (hours24 >= 10 && hours24 <= 23) {
		currentHours24 = to_string(hours24);
	}
	// formatting for minutes and seconds
	currentMinutes24 = (minutes24 < 10) ? "0" + to_string(minutes24) : to_string(minutes24);
	currentSeconds24 = (seconds24 < 10) ? "0" + to_string(seconds24) : to_string(seconds24);

	currentTime24 = currentHours24 + ":" + currentMinutes24 + ":" + currentSeconds24;
	return currentTime24;
}

// this block of 6 functions handles the functions for the menu other than option 4
int addHour12() {
	hours12 += 1;		// adding 1 hour to 12-clock
	Clock12();		// updating 12-hr clock
	return hours12;	// returning variable
}
int addMinute12() {
	minutes12 += 1;	// adding 1 minute to both clocks
	Clock12();		// updating 12-hr clock
	return minutes12;	// returning variable
}
int addSecond12() {
	seconds12 += 1;	// adding 1 second
	Clock12();		// updating 12-hr clock
	return seconds12; // returning variable
}
int addHour24() {
	hours24 += 1;	// adding 1 hour
	Clock24();		// updating 24-hr clock
	return hours24;	// return variable
}
int addMinute24() {
	minutes24 += 1;	// adding 1 minute
	Clock24();		// updating 24-hr clock
	return minutes24; // returning variable
}
int addSecond24() {
	seconds24 += 1;	// adding 1 seconds
	Clock24();		// updating 24-hr clock
	return seconds24; // returning variable
}
/* attempted to use this block to keep the seconds constantly ticking
but I could not get it to work at this time
void incrementSeconds() {
	_sleep(1);			// waits 1 second
	addSecond12();		// adds second to 12-hr
	addSecond24(); 		// adds second to 24-hr
}*/

// menu loop and variable 

void displayMenu(){         // display menu code
	int menuSelect = 0;
    while(menuSelect != 4){
	    cout << endl << endl;
	    cout << "**************************" << endl;
	    cout << "* 1 - Add One Hour       *" << endl;
	    cout << "* 2 - Add One Minute     *" << endl;
	    cout << "* 3 - Add One Second     *" << endl;
	    cout << "* 4 - Exit Program       *" << endl;
	    cout << "**************************" << endl;

	    // switch case for menu operation
	    // used switch case to simply handle menu navigation
	    cin >> menuSelect;
	    switch (menuSelect) {
		    case 1:
			    cout << "Adding One Hour" << endl;
				addHour12(); 
				addHour24();
                displayClocks();
                break;
		    case 2:
			    cout << "Adding One Minute" << endl;
				addMinute12();
				addMinute24();
                displayClocks();
                break;
		    case 3:
			    cout << "Adding One Second" << endl;
				addSecond12();
				addSecond24();
                displayClocks();
                break;
		    case 4:
			    cout << "Exiting Program" << endl;
			    break;
        }
    }
}

// main function as simple as possible
int main(void) {		// main function opener
	_sleep(1);			// delays opening 1 second - SOURCE: https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program
	Clock12();			// populate clock 12
	Clock24();			// populate clock 24
    displayClocks();	// initiate display 
    displayMenu();		// open up menu
	return 0;		// return statement at the end
}
