//
// Created by Thomas Therkelsen on 04-03-2021.
//

#include "Loan.h"
#include <cmath>

Loan::Loan() = default;

Loan::Loan (double debt, int years, int paymentsPerYear, double interestRate) {
    _debt = debt;
    _years = years;
    _paymentsPerYear = paymentsPerYear;
    _interestRate = interestRate;
    _interestPerPayment = interestRate/paymentsPerYear;
};

// Returns the number of years the loan lasts
int Loan::getYears () const {
    return _years;
};

// Amount of payments per year
int Loan::getPaymentsPerYear() const {
    return _paymentsPerYear;
};
void Loan::setPaymentsPerYear(int paymentsPerYear) {
    _paymentsPerYear = paymentsPerYear;
};

// Debt
double Loan::getDebt() const {
    return _debt;
};
void Loan::setDebt(double debt) {
    _debt = debt;
};

// Interest
double Loan::getInterestRate() const {
    return _interestRate;
};
void Loan::setInterestRate(double rate) {
    _interestRate = rate;
};

double Loan::getInterestPerPayment() const {
    return _interestPerPayment;
}

double Loan::getGrant() const{
    return getDebt()*(getInterestPerPayment()/(1-pow(1+getInterestPerPayment(),-(getPaymentsPerYear()*getYears()))));
}

// Calculate the total interest of a loan for all the years
double Loan::totalInterest() const {
    double total {0};
    double tempDebt = getDebt();
    for (int i {0}; i < getYears()*getPaymentsPerYear(); i++) {
        total += tempDebt*getInterestPerPayment();
        //Gæld = Gæld - Afdrag
        //Afdrag = Ydelse - Rente
        //Rente = Gæld * Terminsrente
        //Gæld = Gæld - Ydelse - Gæld * Terminsrente
        tempDebt -= getGrant() - tempDebt * getInterestPerPayment();
    }
    return total;
};

// Calculate the total repayment of a loan including the interests,
double Loan::totalPayment() const {
    return getGrant() * getPaymentsPerYear() * getYears();
};

// Calculate the total net interest of a loan after tax refund
double Loan::totalInterestTaxDeducted (double taxDeductionRate) const {

};

// Output the periodical payments with unpaid balance, paid interest and repayment of each payment to stream object ost
void Loan::outputPeriodicalPayments (std::ostream & ost) const {

};