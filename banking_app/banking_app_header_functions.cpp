#include <iostream>
#include <cmath>
#include <string>

#include "FinancialInformation2"        // couldn't use .h notation because it kept coming up as unrecognized

/*-----------------------------------------
 setter functions defined 
 ------------------------------------------*/

void FinancialInformation::SetInitialBalance(double t_initialBalance) {
    m_initialBalance = t_initialBalance;
}
void FinancialInformation::SetAnnualInterest(double t_annualInterest) {
    m_annualInterest = t_annualInterest;
}
void FinancialInformation::SetMonthlyDepositAmount(double t_monthlyDeposit){
    m_monthlyDeposit = t_monthlyDeposit;
}
void FinancialInformation::SetNumYears(int t_numYears){
    m_numYears = t_numYears;
}

/*-----------------------------------------
 default build tasks 
 ------------------------------------------*/

void FinancialInformation::SetInitialBalance() {
    m_initialBalance = 0.0;
}
void FinancialInformation::SetMonthlyDepositAmount() {
    m_monthlyDeposit = 0.0;
}
void FinancialInformation::SetAnnualInterest() {
    m_annualInterest = 0.0;
}
void FinancialInformation::SetNumYears() {
    m_numYears = 0;
}

/*-----------------------------------------
 getter fucntions 
 ------------------------------------------*/

double FinancialInformation::GetInitialBalance() {
    return m_initialBalance;
}
double FinancialInformation::GetAnnualInterest() {
    return m_annualInterest;
}
double FinancialInformation::GetMonthlyDepositAmount() {
    return m_monthlyDeposit;
}
int FinancialInformation::GetNumYears() {
    return m_numYears;
}

/*-----------------------------------------
 arithmetic fucntions 
 ------------------------------------------*/

// common variables for function set
double t_yearEndBalance = 0;
double t_annualInterestEarned = 0;

// year end balance calculated accounting for deposits and interest
double FinancialInformation::CalcYearEndBalance(double t_yearEndBalance, double t_monthlyDeposit, double t_annualInterest) {
    for (int i = 0; i < 12; i++) {
        t_yearEndBalance += t_monthlyDeposit;
        t_yearEndBalance += t_yearEndBalance * ((t_annualInterest / 100) / 12);
    }

    return t_yearEndBalance;
}
// total interest earned calculated - included a counter variable for proper math
double FinancialInformation::CalcAnnualInterestEarned(double t_yearEndBalance, double t_monthlyDeposit, double annualInterest, int counter) {
    t_annualInterestEarned = t_yearEndBalance - m_initialBalance - ((t_monthlyDeposit * 12) * counter);
    return t_annualInterestEarned;
}
