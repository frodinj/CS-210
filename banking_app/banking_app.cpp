//============================================================================
// Name        : banking_app.cpp
// Author      : Jon Frodin
// Version     : 4.1.2020
// Copyright   : Bowser the Turtle Studios (c) 2020
// Description : banking application for module 5 project two
//============================================================================

#include <iostream>
using namespace std;
#include <iomanip>      // included for setprecision() function
#include <vector>       // included just in case
#include <string>       // included just in case
#include "FinancialInformation2"    // couldn't use .h notation because the build kept failing
#include "banking_app_header_functions.cpp"     // had to include this explicitly despite it not being in zybooks b/c the build showwed lnk2019 errors without this statement

// variables to use across functions
double balance;
double depositMonthly;
double annualInterest;
int yearTotal;
double yearEndBalance;
double annualInterestEarned;

// main menu display for entering variables
void DisplayMainMenu() {
    cout << "**********************************" << endl;
    cout << "********** Data Input ************" << endl;
    cout << "Initial Investment Amount: " << endl;
    cout << "Monthly Deposit Amount: " << endl;
    cout << "Annual Interest: " << endl;
    cout << "Number of Years: " << endl;
    cout << "**********************************" << endl;
}

// display for yes and no monthly deposit amounts
void FinancialBreakdownDisplays(FinancialInformation value1, double balance, double depositMonthly, double annualInterest, int yearTotal) {
    // variables for function
    int currYear;
    double monthEndBalance;
    double depositAmount;
    double monthTotal;
    double monthlyInterestAccrued;
    double closingBalance;
    // loop with calculations and display
    if (depositMonthly > 0.0) {
        // basic top display
        cout << "\tBalance and Interest With Additional Monthly Deposits\t" << endl;
        cout << "==============================================================" << endl;
        cout << "   Year\t  Year End Balance\t  Year End Earned Interest\t" << endl;
        cout << "--------------------------------------------------------------" << endl;
        cout << setprecision(2) << fixed;
        for (int i = 0; i < yearTotal; i++) {
            currYear = i + 1;       // update current year count
            // run functions to get yearly balance and interest earned
            yearEndBalance = value1.CalcYearEndBalance(balance, depositMonthly, annualInterest);
            annualInterestEarned = value1.CalcAnnualInterestEarned(yearEndBalance, depositMonthly, annualInterest, currYear);
            if (currYear == 1) {        // formatting
                cout << "  " << currYear << "   \t   $" << yearEndBalance << "   \t\t\t$" << annualInterestEarned << endl;
            }
            else {                      // formatting
                cout << "  " << currYear << "   \t   $" << yearEndBalance << "   \t\t\t$" << annualInterestEarned << endl;
            }
            balance = yearEndBalance;   // updating variable for loop
        }
        // bottom for clarity
        cout << "--------------------------------------------------------------" << endl;
    }
    // for without additional monthly deposits
    else {
        // basic top display
        cout << "   Balance and Interest Without Additional Monthly Deposits   " << endl;
        cout << "==============================================================" << endl;
        cout << "   Year\t  Year End Balance\t  Year End Earned Interest\t" << endl;
        cout << "--------------------------------------------------------------" << endl;
        cout << setprecision(2) << fixed;
        for (int i = 0; i < yearTotal; i++) {
            currYear = i + 1;       // update current year count
            // run functions to get yearly balance and interest earned
            yearEndBalance = value1.CalcYearEndBalance(balance, depositMonthly, annualInterest);
            annualInterestEarned = value1.CalcAnnualInterestEarned(yearEndBalance, depositMonthly, annualInterest, currYear);
            if (currYear == 1) {        // formatting
                cout << "  " << currYear << "   \t   $" << yearEndBalance << "\t\t\t\t$" << annualInterestEarned << endl;
            }
            else {                      // formatting
                cout << "  " << currYear << "   \t   $" << yearEndBalance << "\t\t\t\t$" << annualInterestEarned << endl;
            }
            balance = yearEndBalance;   // updating variable for loop
        }
        // bottom to make things more clear with multiple inputs
        cout << "--------------------------------------------------------------" << endl;
    }
}

// main program body
int main() {
    char menuInput = 'y';       // variable to continue or not
    while (menuInput == 'y' || menuInput == 'Y'){
        // creation of an item for class to adjust
        FinancialInformation value1;
        DisplayMainMenu();
        // fetch inputs and assignment functions
        try {
            cin >> balance;
            if (balance < 0) {
                throw runtime_error("Invalid Initial Depost");
            }
            cin >> depositMonthly;
            if (depositMonthly < 0) {
                throw runtime_error("Invalid Monthly Deposit Amount");
            }
            cin >> annualInterest;
            if (annualInterest < 0) {
                throw runtime_error("Invalid Annual Interest Rate");
            }
            cin >> yearTotal;
            if (yearTotal < 0) {
                throw runtime_error("Invalid Number of Years");
            }

        }
        catch (runtime_error& excpt) {
            cout << excpt.what() << endl;
            cout << "Cannot Compute Data." << endl;
        }


        system("pause");
        // used a try/catch block to weed out negative numbers
        value1.SetInitialBalance(balance);
        value1.SetMonthlyDepositAmount(depositMonthly);
        value1.SetAnnualInterest(annualInterest);
        value1.SetNumYears(yearTotal);
        cin.ignore();   // reset input

        // displaying the financial breakdwon which runs functions to calculate interest and totals
        FinancialBreakdownDisplays(value1, balance, depositMonthly, annualInterest, yearTotal);
        // to press any key to continue
        system("pause");

        // made this section to give user the option to try multiple scenarios without restarting the program
        cout << "Would you like to enter another scenario?" << endl;
        cout << "Enter 'y' for yes, or 'q' to end program." << endl;
        cin >> menuInput;   // does work as long as either of the keys are pressed
        cin.ignore();   // reset input
    }
    if (menuInput == 'q' || menuInput == 'Q') {
        cout << "Program Finished." << endl;
    }

    return 0;   // end statement
}

