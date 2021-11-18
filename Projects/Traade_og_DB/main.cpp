
#include "database.h"
#include <iostream>
#include <vector>

using namespace std;

vector<std::string> generateRegNum(int amount){
  vector<std::string> regNums;

  for (int i = 0; i < amount; i++) {

    int letterIterator1 = 0;
    int letterIterator2 = 0;
    int numberIterator = 10000;

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

    }

    char x = 'a' + letterIterator1;
    char y = 'a' + letterIterator2;
    std::string z = ""; z.push_back(x); z.push_back(y);
    std::cout << "i: " << i << std::endl;

    if((i > 0 && 1 == 2)) {
    std::cout << "Wrong combination, skipping" << std::endl;
    } else {
      std::cout << "x: " << x << "\n" << "y: " << y << "\n" << "z: " << z << "\n" << "numIt: " << numberIterator << "\n" << std::endl;
      regNums.push_back("");
      numberIterator++;
    }

  }
  return regNums;
}

int main() {

  /*
  Database db;

  db.extractData();
  std::cout << "\nDB: Table contains " << db.countEntries() << " entries" << std::endl;

  db.insertData("QF37218", "Tesla", 2020);
  db.insertData("HG85461", "Ferrari", 1980);
  db.insertData("JR54352", "Ford", 1990);

  db.extractData();
  std::cout << "\nDB: Table contains " << db.countEntries() << " entries" << std::endl;

  db.clearDatabase();
  db.extractData();
  std::cout << "\nDB: Table contains " << db.countEntries() << " entries" << std::endl;
  */

  generateRegNum(1000);

  /*
  char x = 'a' + 25;
  std::cout << x << std::endl;
  */
  return 0;
}

