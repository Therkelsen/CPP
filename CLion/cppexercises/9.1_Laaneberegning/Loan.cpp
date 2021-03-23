//
// Created by Thomas Therkelsen on 04-03-2021.
//

#include "Loan.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>

Loan::Loan() = default; // Default constructor

Loan::Loan (double debt, int years, int paymentsPerYear, double interestRate) { // Main constructor
    _debt = debt;
    _years = years;
    _paymentsPerYear = paymentsPerYear;
    _interestRate = interestRate;
    _interestPerPayment = interestRate/paymentsPerYear;

}

// Returns the number of years the loan lasts
int Loan::getYears () const {
    return _years;
}

// Sets years
void Loan::setYears(int years) {
    _years = years;
}

// Amount of payments per year
int Loan::getPaymentsPerYear() const {
    return _paymentsPerYear;
}

// Sets payments per year
void Loan::setPaymentsPerYear(int paymentsPerYear) {
    _paymentsPerYear = paymentsPerYear;
}

// Debt
double Loan::getDebt() const {
    return _debt;
}

// Sets debt
void Loan::setDebt(double debt) {
    _debt = debt;
}

// Returns interest
double Loan::getInterestRate() const {
    return _interestRate;
}

// Sets interest
void Loan::setInterestRate(double rate) {
    _interestRate = rate;
}

// Returns interest per payment
double Loan::getInterestPerPayment() const {
    return _interestPerPayment;
}

// Returns total amount of payments
int Loan::amountOfPayments() const {
    return getYears() * getPaymentsPerYear();
}

// Returns the grant
double Loan::getGrant() const {
    return getDebt() * (getInterestPerPayment() / (1 - pow(1 + getInterestPerPayment(), - (amountOfPayments()))));
}

void Loan::setTaxDeductionRate(double taxDeductionRate) {
    _taxDeductionRate = taxDeductionRate;
}

double Loan::getTaxDeductionRate() const {
    return _taxDeductionRate;
}

// Calculate the total interest of a loan for all the years
double Loan::totalInterest() const {
    double total {0};
    double tempDebt = getDebt();
    for (unsigned int i {0}; i < amountOfPayments(); i++) {
        total += tempDebt * getInterestPerPayment();
        //Gæld = Gæld - Afdrag
        //Afdrag = Ydelse - Rente
        //Rente = Gæld * Terminsrente
        //Gæld = Gæld - Ydelse - Gæld * Terminsrente
        tempDebt -= getGrant() - tempDebt * getInterestPerPayment();
    }
    return total;
}

// Calculate the total repayment of a loan including the interests,
double Loan::totalPayment() const {
    return getGrant() * amountOfPayments();
}

// Calculate the total net interest of a loan after tax refund
double Loan::totalInterestTaxDeducted (double taxDeductionRate) const {
    if (taxDeductionRate > 1) {
        return totalInterest() * taxDeductionRate / 100;
    }
    return totalInterest() * taxDeductionRate;
}

// Output the periodical payments with unpaid balance, paid interest and repayment of each payment to stream object ost
void Loan::outputPeriodicalPayments (std::ostream & ost) const {
    double interest [amountOfPayments()];
    double payment  [amountOfPayments()];
    double debt     [amountOfPayments()];

    *(interest + 0) = getDebt() * getInterestPerPayment();
    *(payment + 0)  = getGrant() - *(interest + 0);
    *(debt + 0)     = getDebt();

    ost << "Termin"         << std::setw(19);
    ost << "Ydelse"         << std::setw(20);
    ost << "Rente"          << std::setw(20);
    ost << "Afdrag"         << std::setw(20);
    ost << "Restg\x91ld"    << std::endl;
    ost << std::fixed << std::setprecision(2);

    for (unsigned int i {1}; i <= amountOfPayments(); i++) {
        *(interest + i) = *(debt + i - 1) * getInterestPerPayment();
        *(payment + i)  = getGrant() - *(interest + i);
        *(debt + i)     = *(debt + i - 1) - *(payment + i);
        ost << std::setw(6) << i << " ";
        ost << std::setw(14) << bankersRounding(getGrant())         << " DKK ";
        ost << std::setw(15) << bankersRounding(*(interest + i))    << " DKK ";
        ost << std::setw(15) << bankersRounding(*(payment + i))     << " DKK ";
        ost << std::setw(15) << std::abs(bankersRounding(*(debt + i)))      << " DKK ";
        ost << std::endl;
    }

    ost << "\nSum af rentefradag: " << totalInterestTaxDeducted(bankersRounding(getTaxDeductionRate())) << " DKK";

    /*Another way to solve it, without pointers:
    double periodicalPayments[4][amountOfPayments()];
    double tempDebt = getDebt();
    for (int i {0}; i < amountOfPayments(); i++) {
        periodicalPayments[0][i] = getGrant();
        periodicalPayments[1][i] = (tempDebt * getInterestPerPayment());
        tempDebt -= getGrant() - tempDebt * getInterestPerPayment();
        periodicalPayments[2][i] = getGrant() - periodicalPayments[1][i];
        periodicalPayments[3][i] = tempDebt;
    }
    ost << "Termin" << std::setw(15) << "Ydelse" << std::setw(15) << "Rente" << std::setw(15);
    ost << "Afdrag" << std::setw(15) << "Restg\x91ld" << std::endl;

    for (int i {0}; i < amountOfPayments(); i++) {
        ost << std::fixed << std::setprecision(2) << std::setw(6) << (i + 1) << " ";
        for (int j {0}; j < 4; j++) {
            ost << std::setw(10) << std::abs(periodicalPayments[j][i]) << " DKK ";
        }

*/
}

/*
Uses bankers rounding, to round off a double, explained here:
Bankers Rounding is an algorithm for rounding quantities to integers,
in which numbers which are equidistant from the two nearest integers
are rounded to the nearest even integer. Thus, 0.5 rounds down to 0; 1.5
rounds up to 2. A similar algorithm can be constructed for rounding to other
sets besides the integers (in particular, sets which a constant interval between adjacent members).
Other decimal fractions round as you would expect--0.4 to 0, 0.6 to 1, 1.4 to 1, 1.6 to 2, etc.
Only x.5 numbers get the "special" treatment.
So called because banks supposedly use it for certain computations.
The supposed advantage to bankers rounding is that it is unbiased, and thus produces
better results with various operations that involve rounding.
It should be noted that it is unbiased only in the limit. That is, an average of all errors approaches 0.0.
*/
double Loan::bankersRounding(double x) {
    return nearbyint(x * 100) / 100;

    /*std::string xString = std::to_string(x);
    char delim = '.';
    char secondDigit = xString.at(xString.find(delim) + 2);
    char thirdDigit  = xString.at(xString.find(delim) + 3);

    if ((((int)thirdDigit == 5 && (int)secondDigit % 2 != 0) || (int)thirdDigit > 5) && x > 0.1) {
        xString.erase((xString.find(delim) + 3), xString.length()*10);
        x = std::stod(xString);
        return x += 0.01;
    } else {
        xString.erase((xString.find(delim) + 3), xString.length()*10);
        return std::stod(xString);
    }*/
}