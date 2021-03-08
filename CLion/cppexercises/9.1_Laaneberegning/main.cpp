#include <iostream>
#include "Loan.h"
#include <iomanip>

using namespace std;

int main() {

    double taxDeductionRate;

    Loan l1(1000000, 15, 4, 0.03);

    cout << "Please enter your municipality tax deduction rate in decimal: "    << endl;
    cin  >> taxDeductionRate;
    l1.outputPeriodicalPayments(std::cout);
    /*
    cout << fixed << setprecision(2);
    cout << "Grant:            "                << l1.getGrant()                                    << " DKK"   << endl;
    cout << "Years:            "                << l1.getYears()                                                << endl;
    cout << "Payments/year:    "                << l1.getPaymentsPerYear()                                      << endl;
    cout << "Interest rate:    "                << l1.getInterestRate()                             << " %"     << endl;
    cout << "Debt:             "                << l1.getDebt()                                     << " DKK"   << endl;
    cout << "Interest/payment: "                << l1.getInterestPerPayment()                       << " %"     << endl;
    cout << "Total interest:   "                << l1.totalInterest()                               << " DKK"   << endl;
    cout << "Total payment:    "                << l1.totalPayment()                                << " DKK"   << endl;
    cout << "Total interested tax deducted: "   << l1.totalInterestTaxDeducted(taxDeductionRate)                << endl;*/

    return 0;
}
