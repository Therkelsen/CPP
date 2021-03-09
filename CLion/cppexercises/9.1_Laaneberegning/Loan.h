//
// Created by Thomas Therkelsen on 04-03-2021.
//

#ifndef INC_9_1_LAANEBEREGNING_LOAN_H
#define INC_9_1_LAANEBEREGNING_LOAN_H

#include <iostream>
#include <cmath>

class Loan {

private:
    double _debt{}, _interestRate{}, _interestPerPayment{};
    int _years{}, _paymentsPerYear{};

public:
    Loan();

    Loan (double debt, int years, int paymentsPerYear, double interestRate);

    // Returns the number of years the loan lasts
    int getYears () const;
    void setYears(int years);

    // Amount of payments per year
    int getPaymentsPerYear() const;
    void setPaymentsPerYear(int paymentsPerYear);

    // Debt
    double getDebt() const;
    void setDebt(double debt);

    double getGrant() const;

    // Interest
    double getInterestRate() const;
    void setInterestRate(double rate);

    // Calculate the total interest of a loan for all the years
    double totalInterest() const;

    // Calculate the total repayment of a loan including the interests,
    double totalPayment() const;

    // Calculate the total net interest of a loan after tax refund
    double totalInterestTaxDeducted (double taxDeductionRate) const;

    // Output the periodical payments with unpaid balance, paid interest and repayment of each payment to stream object ost
    void outputPeriodicalPayments (std::ostream & ost) const;

    double getInterestPerPayment() const;

    int amountOfPayments() const;

    static double bankersRounding(double x) ;
};


#endif //INC_9_1_LAANEBEREGNING_LOAN_H
