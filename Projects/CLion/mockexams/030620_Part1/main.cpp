#include <iostream>
#include <iomanip>
#include <vector>
#include "Lot.h"

int main() {
    std::cout << "--------------------" << std::endl;
    std::cout << "-- Test Opgave 1a --" << std::endl;
    std::cout << "--------------------" << std::endl;

    std::cout << std::left << std::setw(20) << "Address";
    std::cout << std::right << std::setw(-1) << "Min Price";
    std::cout << std::right << std::setw(6) << "Size" << std::endl;

    Lot lt;
    lt.setAddress("Stendyssen 31");
    lt.setMinimumPrice(979200);
    lt.setSize(720);
    const Lot& l = lt;
    std::cout << std::left << std::setw(20) << l.getAddress() <<
              std::right << std::setw(9) << l.getMinimumPrice() <<
              std::setw(6) << l.getSize() << std::endl;
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "--------------------" << std::endl;
    std::cout << "-- Test Opgave 1b --" << std::endl;
    std::cout << "--------------------" << std::endl;

    std::cout << std::left << std::setw(20) << "Address";
    std::cout << std::right << std::setw(-1) << "Min Price";
    std::cout << std::right << std::setw(6) << "Size" << std::endl;

    std::string lots = "";
    lots += "Stendyssen 1;965430;703\n";
    lots += "Stendyssen 3;992160;736\n";
    lots += "Stendyssen 5;990540;734\n";
    lots += "Stendyssen 7;961380;698\n";
    lots += "Stendyssen 9;909540;634\n";
    lots += "Stendyssen 11;964620;702\n";
    lots += "Stendyssen 13;903060;626\n";
    lots += "Stendyssen 15;978390;719\n";
    lots += "Stendyssen 17;976770;717\n";
    lots += "Stendyssen 19;963000;700\n";
    lots += "Stendyssen 21;981630;723\n";
    lots += "Stendyssen 23;958950;695\n";
    lots += "Stendyssen 25;953280;688\n";
    lots += "Stendyssen 27;933840;664\n";

    std::stringstream ss(lots);
    std::vector<Lot> lotList;
    while (!ss.eof()) {
        std::string line;
        std::getline(ss, line);
        if (line.size() > 1) {
            std::stringstream ssLine(line);
            Lot l;
            ssLine >> l;
            lotList.push_back(l);
        }
    }
    lotList.emplace_back("Stendyssen 29", 907110, 631);
    lt.setAddress("Stendyssen 31");
    lt.setMinimumPrice(979200);
    lt.setSize(720);

    lotList.push_back(lt);
    for (unsigned int i = 0; i < lotList.size(); ++i) {
        const Lot& l = lotList[i];
        std::cout << l << std::endl;
    }

    return 0;
}
