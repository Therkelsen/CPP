#include <iostream>
#include "Loan.h"
#include <iomanip>

using namespace std;

int main() {

    Loan l1(1000000, 15, 4, 0.03);

    cout << fixed << setprecision(2);
    cout << "Grant: " << l1.getGrant() << endl;
    cout << "Years: " << l1.getYears() << endl;
    cout << "Payments/year: " << l1.getPaymentsPerYear() << endl;
    cout << "Interest rate: " << l1.getInterestRate() << endl;
    cout << "Debt: " << l1.getDebt() << endl;
    cout << "Interest/payment: " << l1.getInterestPerPayment() << endl;
    cout << "Total interest: " << l1.totalInterest() << endl;

    return 0;
}
