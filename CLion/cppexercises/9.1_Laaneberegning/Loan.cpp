//
// Created by Thomas Therkelsen on 04-03-2021.
//

#include "Loan.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>

Loan::Loan() = default;

Loan::Loan (double debt, int years, int paymentsPerYear, double interestRate) {
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

void Loan::setYears(int years) {
    _years = years;
}

// Amount of payments per year
int Loan::getPaymentsPerYear() const {
    return _paymentsPerYear;
}
void Loan::setPaymentsPerYear(int paymentsPerYear) {
    _paymentsPerYear = paymentsPerYear;
}

// Debt
double Loan::getDebt() const {
    return _debt;
}
void Loan::setDebt(double debt) {
    _debt = debt;
}

// Interest
double Loan::getInterestRate() const {
    return _interestRate;
}
void Loan::setInterestRate(double rate) {
    _interestRate = rate;
}

double Loan::getInterestPerPayment() const {
    return _interestPerPayment;
}

int Loan::totalPayments() const {
    return getYears()*getPaymentsPerYear();
}

double Loan::getGrant() const{
    return getDebt()*(getInterestPerPayment()/(1-pow(1+getInterestPerPayment(),-(totalPayments()))));
}

// Calculate the total interest of a loan for all the years
double Loan::totalInterest() const {
    double total {0};
    double tempDebt = getDebt();
    for (unsigned int i {0}; i < totalPayments(); i++) {
        total += tempDebt*getInterestPerPayment();
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
    return getGrant() * totalPayments();
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
    double interest [totalPayments()];
    double payment  [totalPayments()];
    double debt     [totalPayments()];

    *(interest + 0) = getDebt() * getInterestPerPayment();
    *(payment + 0)  = getGrant() - *(interest + 0);
    *(debt + 0)     = getDebt();

    ost << "Termin" << std::setw(19) << "Ydelse" << std::setw(20) << "Rente" << std::setw(20);
    ost << "Afdrag" << std::setw(20) << "Restg\x91ld" << std::endl;

    for (unsigned int i {1}; i <= totalPayments(); i++) {
        *(interest + i) = *(debt + i - 1) * getInterestPerPayment();
        *(payment + i)  = getGrant() - *(interest + i);
        *(debt + i)     = *(debt + i - 1) - *(payment + i);
        ost << std::fixed << std::setprecision(2) << std::setw(6) << i << " ";
        ost << std::setw(14) << bankersRounding(getGrant()) << " DKK ";
        ost << std::setw(15) << bankersRounding(*(interest + i)) << " DKK ";
        ost << std::setw(15) << bankersRounding(*(payment + i))  << " DKK ";
        ost << std::setw(15) << std::abs(bankersRounding(*(debt + i))) << " DKK ";
        ost << std::endl;
    }
}

double Loan::bankersRounding(double x) const {
    std::string xString = std::to_string(x);
    char delim = '.';
    char secondDigit = xString.at(xString.find(delim) + 2);
    char thirdDigit = xString.at(xString.find(delim) + 3);

    if ((((int)thirdDigit == 5 && (int)secondDigit % 2 != 0) || (int)thirdDigit > 5) && x > 0.1) {
        xString.erase((xString.find(delim) + 3), xString.length()*10);
        x = std::stod(xString);
        return x += 0.01;
    } else {
        xString.erase((xString.find(delim) + 3), xString.length()*10);
        return std::stod(xString);
    }
}
