
#include <mutex>
#include <thread>
#include <iomanip>
#include "database.h"
#include "cargenerator.h"

using namespace std;
mutex m;

int main() {

  Database db;
  CarGenerator cg;

  //thread t1(db.insertData(););
  cg.generateCar(1000000);

  /*
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

