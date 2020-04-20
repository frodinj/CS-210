//============================================================================
// Name        : TheZoo.cpp
// Author      : Jon Frodin
// Version     : 4.1.2020
// Copyright   : Bowser the Turtle Studios (c) 2020
// Description : Zoo RFID app for module 7 project three
//============================================================================

#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>
#include <string>
#include <jni.h>
using namespace std;
#include "Animal.h"
#include <vector>

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}

// cross-function variables
char menuChoice;
vector<Animal*> AnimalList;     // create array for storage
Oviparous* oviparousItemPtr = nullptr;  // create a pointer for oviparous and mammal
Mammal* mammalItemPtr = nullptr;
string t_subType;
string t_numEggs;
string t_type;
string t_name;
string t_nursingStatus;
string t_trackingNum;
int t_trackingNum1;
char t_nursingStatusChar;
int t_numEggsInt;
int t_nursingStatusInt;
string oviSearch = "Oviparous";
string oviSearch2 = "oviparous";
string fileOutput;


/*This large function adds an animal to the vector at the end of the list. The function validates all inputs.
First it makes sure that the tracking number is the proper length and then it checks to confirm whether it is already
in use. Then it adds the name, type, subtype, and egg count or nursing status to the vector. It decides whether the animal
is an oviparous class or a mammal class.*/
void AddAnimal() {
    string tempString;
    int resizeInt;
    char menuChar;
    int result = 0;
    string iterationTrackingNum;
    cout << "Adding an Animal" << endl;
    // try/catch block to handle errors on inputs
    try {
        cout << "Please Enter a Valid Tracking Number (6 digits): " << endl;
        cin >> t_trackingNum;
        // confirms the tracking number is 6 digits
        if (t_trackingNum.size() != 6) {
            throw invalid_argument("Tracking Number Entered is not 6 digits. Please try again");
        }
        // confirms tracking number is new
        for (int j = 0; j < AnimalList.size(); j++) {
            iterationTrackingNum = AnimalList.at(j)->GetTrackNum();
            if (iterationTrackingNum == t_trackingNum) {
                throw invalid_argument("Tracking Number is already in use. Cannot allow duplicate. Please try again.");
            }
        }
        cout << "Please Enter a Name for the Animal: " << endl;
        cin >> t_name;
        // confirms name is not more than 15 characters per specification sheet
        if (t_name.size() > 15) {
            throw invalid_argument("Name Entered is too long, maximum length is 15 characters. Please try again");
        }
        // resizing to fit formatting guidelines and decoder function
        if (t_name.size() < 15) {
            resizeInt = 15 - t_name.size();
            for (int i = 0; i < resizeInt; i++) {
                t_name = t_name + " ";
            }
        }
        cout << "Please Enter Animal Type (Oviparous or Mammal): " << endl;
        cin >> t_type;
        for (int i = 0; i < 1; i++) {
            t_type.at(i)= toupper(t_type.at(i));           // allows user to enter 'oviparous' or 'mammal' but converts it (works on visual studio but not eclipse
        }
        // confirms type is either oviparous or mammal
        if (t_type != "Oviparous" && t_type != "Mammal") {
            throw invalid_argument("Invalid type entered. Must be 'Oviparous' or 'Mammal'");
        }
        // resizing to fit formatting guidelines
        if (t_type.size() < 15) {
            resizeInt = 15 - t_type.size();
            for (int i = 0; i < resizeInt; i++) {
                t_type = t_type + " ";
            }
        }
        cout << "Please Enter Animal Sub-Type (Bat, Whale, etc.): " << endl;
        cin >> t_subType;
        // confirms sub-type is not more than 15 characters per specification sheet
        if (t_subType.size() > 15) {
            throw invalid_argument("Sub-Type is too long, maximum length is 15 characters. Please try again");
        }
        // converts sub-type first character to uppercase if not already done for vector
        for (int i = 0; i < 1; i++) {
            t_subType.at(i) = toupper(t_subType.at(i));
        }
        // resizing to fit formatting guidelines
        if (t_subType.size() < 15) {
            resizeInt = 15 - t_subType.size();
            for (int i = 0; i < resizeInt; i++) {
                t_subType = t_subType + " ";
            }
        }
        cout << "Please Enter the Number of Eggs for the Animal (if Mammal, enter 0): " << endl;
        // obtain char to convert to str to move to int
        cin >> tempString;
        // confirms positive or 0 entered
        for (int i = 0; i < tempString.size(); i++) {
            if (isalpha(tempString.at(i))){
            throw invalid_argument("Must Enter a number, not a character or string. Please try again");
            }
        }
        // convert to num eggs for storage
        // confirming no negative numbers
        t_numEggsInt = atoi(tempString.c_str());
        if (t_numEggsInt < 0) {
            cout << "Error: number of eggs cannot be negative. Please try again. For zero eggs, enter '0'." << endl;
        }
        else {
            t_numEggs = tempString;
        }
        cout << t_numEggs << endl;      // testing line - remove from final version
        cout << "Is the animal nursing? ('1' for yes or '0' for no)" << endl << "If oviparous animal, enter '0'" << endl;
        cin >> tempString;
        // testing for errors and converting to t_nursingStatus
        for (int i = 0; i < tempString.size(); i++) {
            if (isalpha(tempString.at(i))){
            throw invalid_argument("Must Enter a number, not a character or string. Please try again");
            }
        }
        t_nursingStatusInt = atoi(tempString.c_str());
        if (t_nursingStatusInt != 0 && t_nursingStatusInt != 1) {
            cout << "Error: Nursing status must be either '1' or '0'. Please enter '1' for yes or '0' for no." << endl;
        }
        // after confirmation - assign nursing status to the value from input
        else {
            t_nursingStatus = tempString;
        }
        cout << t_nursingStatus << endl;        // testing line - remove from final version
        cout << "Are you sure you want to save this animal? ('Y' for yes): " << endl;
        cin >> menuChar;
        if (menuChar == 'Y' || menuChar == 'y') {
            if (t_subType == "Oviparous") {
                oviparousItemPtr = new Oviparous(t_trackingNum, t_name, t_type, t_subType, t_numEggs);
                AnimalList.push_back(oviparousItemPtr);
            }
            else {
                mammalItemPtr = new Mammal(t_trackingNum, t_name, t_type, t_subType, t_nursingStatus);
                AnimalList.push_back(mammalItemPtr);
            }
            // loop to verify animal was added
            for (int j = 0; j < AnimalList.size(); j++) {
                iterationTrackingNum = AnimalList.at(j)->GetTrackNum();
                if (t_trackingNum == iterationTrackingNum) {
                    result += 1;
                }
            }
            // notifying user of successful add or failed add
            if (result > 0) {
                cout << "Animal has been added successfully!" << endl;
            }
            else {
                cout << "Error encountered, please try again" << endl;
            }
        }
        // if user does not enter Y to confirm
        else {
            cout << "Animal will not be added." << endl;
        }
    }
    catch(invalid_argument& excpt) {
        cout << "Error: " << excpt.what() << endl;
    }
    catch(runtime_error& excpt) {
        cout << "Error: " << excpt.what() << endl;
    }
}

/*This section for RemoveAnimal() asks a user to input a 6-digit tracking number. The method then searches the vector
for that number. If it is found, it asks the user to confirm deletion. If the user confirms deletion, the animal is removed
from the AnimalList vector along with its contents.*/
void RemoveAnimal() {
    // variables needed for functions
    string removeTrackNum;
    int result = 0;
    char removeConfirm;
    string animalTrackNum;
    int deleteAniamlPosition;
    string resizeName;
    // overall loop for process with error handling
	try {
        cout << "Enter Tracking Number to Remove" << endl;
        cin >> removeTrackNum;
        if (removeTrackNum.length() < 6) {      // confirms the number is valid
            throw invalid_argument("Invalid Tracking Number Entered");      // exception to keep program going and not waste space
        }
        // loop to find the animal in the vector
        for (int i = 0; i < AnimalList.size(); i++) {
            animalTrackNum = AnimalList.at(i)->GetTrackNum();       // fetch tracking num from each animal for comparison
            if (removeTrackNum == animalTrackNum) {
                result += 1;                                        // determining variable for matches to be used below
            }
        }
        // handling for a confirmed and accurate tracking number
        if (result > 0) {
            for (int i = 0; i < AnimalList.size(); i++) {
                animalTrackNum = AnimalList.at(i)->GetTrackNum();
                // find tracking number again to run confirmation
                if (removeTrackNum == animalTrackNum) {
                    // once found - ask user to confirm deletion - listed animal tracking number for verification
                    cout << "Are you sure you want to delete the animal with tracking number: "
                    << AnimalList.at(i)->GetTrackNum() << "? (Press 'Y' to confirm)" << endl;
                    cin >> removeConfirm;       // obtain confirmation from user
                    deleteAniamlPosition = i;
                    if (removeConfirm == 'y' || removeConfirm == 'Y') {
                        // delete animal
                        AnimalList.erase(AnimalList.begin() + deleteAniamlPosition);        //SOURCE: https://stackoverflow.com/questions/875103/how-do-i-erase-an-element-from-stdvector-by-index
                    }
                    else {
                        cout << "Animal at Tracking Number: " << AnimalList.at(i)->GetTrackNum() << " has not been removed." << endl;
                    }
                }
            }
            // final loop to confirm deletion was successful
            result = 0;             // reset result for counting
            for (int i = 0; i < AnimalList.size(); i++) {
                animalTrackNum = AnimalList.at(i)->GetTrackNum();
                if (removeTrackNum == animalTrackNum) {
                    result += 1;            // to confirm whether or not variable was deleted from vector
                }
            }
            // output confirmation of deletion
            if (result < 1) {
                cout << "Animal successfully deleted." << endl;
            }
            else {
                cout << "An error was encountered, please try again." << endl;
            }
        }
        // handling for a valid (proper length) but not found tracking number
        else {
            cout << "The tracking number you entered is not on the list, please try again." << endl;
        }
    }
    // error handling for a tracking number entered fewer than 6 digits
    catch(invalid_argument& excpt) {
        cout << "Exception Found: " << excpt.what() << endl;
    }
}

/*This function decodes a line of text from an imported file in the LoadDataFromFile() function
It can be used in other areas so long as the input is the same file or a file formatted in the same manner
and so long as the output of said file is one line of string*/
void DecodeLine(string input) {
    // function to segregate variables obtained in LoadDataFromFile()
	if (input.at(5) != '0' && input.at(5) != '1' && input.at(5) != '2' && input.at(5) != '3' && input.at(5) != '4' && input.at(5) != '5' && input.at(5) != '6' && input.at(5) != '7' && input.at(5) != '8' && input.at(5) != '9') {
		input.insert(0, "0");
	}
    t_trackingNum = input.substr(0, 6);        // obtain tracking num - keep as string to maintain leading zeroes
    t_name = input.substr(6, 15);              // obtain name using 15-char fixed length
    t_type = input.substr(21, 15);             // obtain type using 15-char fixed length
    t_subType = input.substr(36, 15);          // obtain sub-type using 15-char fixed length
    t_numEggs = input.substr(51, 1);            // obtain number of eggs
    t_nursingStatus = input.substr(52, 1);      //obtain nursing status
}

/* This load from file function fetches data from an external file in a specific format per the notes in sec 3.b
of the specifications document. The decoder must have characters in that format to work properly*/
void LoadDataFromFile() {
    string input;
    int found = 0;          // used for finding oviparous or mammal
    ifstream inFS; // use file stream
    inFS.open("zoodata.txt");  // opening java file for data retrieval
    if (!inFS.is_open()) {          // error handling for file stream
        cout << "Could not open File. Try again." << endl;
    }
    // loop to read file
    while (!inFS.eof()) {
    	inFS.ignore();
        getline(inFS, input);   // gets full line from file at a time
        // loop to generate animal items and populate the <Animal*> vector
        for (int i = 0; i < 1; i++) {
            DecodeLine(input);      // decodes the line to fetch the variables
            if (t_type == "Oviparous      "){		// determines whether animal is oviparous or mammal - replace the "/54" when java file is imported
                oviparousItemPtr = new Oviparous(t_trackingNum, t_name, t_type, t_subType, t_numEggs);  // uses pointer to create new oviparous animal
                AnimalList.push_back(oviparousItemPtr);     // adds item to the end of the list
            }
            // handling for mammal subclass following the oviparous search
            else {
                mammalItemPtr = new Mammal(t_trackingNum, t_name, t_type, t_subType, t_nursingStatus);
                AnimalList.push_back(mammalItemPtr);
            }
        }
    }
    inFS.close();       // close file for populating table
    cout << "File closed." << endl;     // verification that file is closed
    cout << "Load Complete." << endl;    // message per instructions
}

void SaveDataToFile() {
    char saveChar = 'a';
    ofstream outFS;         // variable to output data
    outFS.open("zoodata.txt");
    // verify file is opened
    if (!outFS.is_open()) {
        cout << "Could not open file. Please try again." << endl;
    }
    cout << "Would you like to save your table to file? ('Y' for yes): " << endl;
    cin >> saveChar;
    if (saveChar == 'y' || saveChar == 'Y') {
        // write data to file
        string tempString;
        outFS << "HELLO" << endl;
        for (int i = 0; i < AnimalList.size(); i++) {
            tempString = AnimalList.at(i)->GetTrackNum();
            outFS << tempString;
            tempString = AnimalList.at(i)->GetAnimalName();
            outFS << tempString;
            tempString = AnimalList.at(i)->GetType();
            outFS << tempString;
            tempString = AnimalList.at(i)->GetSubType();
            outFS << tempString;
            tempString = AnimalList.at(i)->GetNumberOfEggs();
            outFS << tempString;
            tempString = AnimalList.at(i)->GetNursingStatus();
            outFS << tempString;

            // end line after each animal
            outFS << endl;
        }
    }
    else {
        cout << "File will not be saved at this time." << endl;
    }
    outFS.close();
    cout << "Save successfully completed!" << endl;
}

/*This function displays the animal data in a table generated by the header functions and internal functions.
each cell is 17 characters widee including the leading "|" character. The cells populate based on the animal
and the function places a call to the PrintItem() function defined in the headers. Since spaces are added to the various
words and digits in the print functions, it is not necessary here. The only thing I don't have this working for is egg
counts that are greater than 9 because it throws off the spacing.*/
void DisplayAnimalData() {
	for (int i = 0; i < 102; i++) {
		cout << "-"; // top line for table and general line format
	}
	cout << endl;
	cout << "| Track #        | Name           | Type           "
			"| Sub-Type       | Eggs           | Nurse         |" << endl;
	for (int i = 0; i < 102; i++) {
		cout << "-"; // after each row
	}
    cout << endl;

    for (int j = 0; j < AnimalList.size(); j++) {
        AnimalList.at(j)->PrintItem();
        for (int k = 0; k < 102; k++) {
            cout << "-";
        }
        cout << endl;
    }
	cout << endl;

}

void DisplayMenu()
{
	cout << "******************************************" << endl;
	cout << "***************MAIN MENU******************" << endl;
	cout << "* 1: Load Animal Data                    *" << endl;
	cout << "* 2: Generate Data                       *" << endl;
	cout << "* 3: Display Animal Data                 *" << endl;
	cout << "* 4: Add Record                          *" << endl;
	cout << "* 5: Delete Record                       *" << endl;
	cout << "* 6: Save Animal Data                    *" << endl;
	cout << "******************************************" << endl;
	cout << "******************************************" << endl;
	cin >> menuChoice;
    /*Selections include all required elements from prompt and an input to store the value
    to be used in other functions and a loop to handle the menu
    until q is pressed to quit most likely
    */
	switch(menuChoice) {
	case '1':
		LoadDataFromFile();
		break;
	case '2':
		GenerateData();
		break;
	case '3':
		DisplayAnimalData();
		break;
	case '4':
		AddAnimal();
		break;
	case '5':
		RemoveAnimal();
		break;
	case '6':
		SaveDataToFile();
		break;
    default:
        cout << "Invalid Entry, Please Try Again.";
        break;
    case 'Q':
    case 'q':
        break;
	}
}


int main()
{
    unsigned int i;     //unsure if needed
    char QuitChar = 'a';    // assigned to 'a' to avoid immediate quit

    do {        // loop for multiple function access
        DisplayMenu();
        cout << "Press any key to continue or 'Q' to quit." << endl;
        cin >> QuitChar;
    } while (QuitChar != 'Q' && QuitChar != 'q');

	return 1;
}
