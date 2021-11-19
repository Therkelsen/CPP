
#include "database.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int letterIterator1 = 0;
int letterIterator2 = 0;
int numberIterator = 10000;

vector<std::string> generateRegNum(int amount){
  vector<std::string> regNums;
  for (int i = 0; i < amount; i++) {

    std::string letters = "";
    std::string numbers = "";
    if (numberIterator > 99999) {
      letterIterator2++;
      numberIterator = 10000;
    }
    if (letterIterator2 > 25) {
      letterIterator2 = 0;
      letterIterator1++;
    }
    if (letterIterator1 > 25) {
      return regNums;
    }

    char x = 'a' + letterIterator1;
    char y = 'a' + letterIterator2;
    std::string z = ""; z.push_back(x); z.push_back(y); z = z + std::to_string(numberIterator);
    std::cout << "i: " << i << std::endl;


    regNums.push_back(z);
    //std::cout << "Regnr: " << z << "\n" << std::endl;
    std::cout << "Regnr: " << regNums.at(i) << "\n" << std::endl;
    numberIterator++;
  }
  return regNums;
}

int main() {

  generateRegNum(100000);

  /*Database db;

  db.extractData();
  std::cout << "DB: Table contains " << db.countEntries() << " entries" << std::endl;

  db.insertData("QF37218", "Tesla", 2020);
  db.insertData("HG85461", "Ferrari", 1980);
  db.insertData("JR54352", "Ford", 1990);

  db.extractData();
  std::cout << "DB: Table contains " << db.countEntries() << " entries" << std::endl;

  db.clearDatabase();
  db.extractData();
  std::cout << "DB: Table contains " << db.countEntries() << " entries" << std::endl;*/

  return 0;
}

