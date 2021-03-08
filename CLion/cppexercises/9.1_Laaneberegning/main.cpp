#include <iostream>
#include "Loan.h"
#include <iomanip>

using namespace std;

int main() {

    double taxDeductionRate, debt, interestRate;
    int years, paymentsPerYear;

    cout << "Velkommen til l\x86neberegner beregner 3000 bum bum maskinen" << endl;
    cout << "Start lige med, at indtaste dit l\x86ns hovedstol" << endl;
    cin >> debt;

    cout << "Skriv s\x86 renten p\x86 l\x86net" << endl;
    cin >> interestRate;
    if (interestRate > 1) {
        interestRate /= 100;
    }

    cout << "S\x86 skal jeg vide l\x9B" << "betiden p\x86 dit l\x86n, i \x86r" << endl;
    cin >> years;

    cout << "Jeg skal ogs\x86 have antal terminer pr. \x86r, p\x86 dit l\x86n" << endl;
    cin >> paymentsPerYear;

    cout << "Til sidst indtaster du din kommunale skattefradragssats"    << endl;
    cin  >> taxDeductionRate;

    Loan l1(debt, years, paymentsPerYear, interestRate);

    l1.outputPeriodicalPayments(std::cout);
    cout << "\nSum af rentefradag: " << l1.totalInterestTaxDeducted(taxDeductionRate) << " DKK";

    return 0;
}
