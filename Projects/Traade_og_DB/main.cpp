
#include <mutex>
#include <thread>
#include <iomanip>
#include "database.h"
#include "cargenerator.h"

using namespace std;
mutex m;

int main() {
  int amountToGenerate = 100;

  Database db;
  CarGenerator cg;

  thread t1();

  db.extractData();
  std::cout << "\nDB: Table contains " << db.countEntries() << " entries" << std::endl;
  std::vector<std::vector<std::string>> cars = cg.generateCar(amountToGenerate, db.extractHighestRegNr());

  for (int i = 0; i < cars.size(); i++) {
      db.insertData(QString::fromStdString(cars.at(i).at(0)), QString::fromStdString(cars.at(i).at(1)), stoi(cars.at(i).at(2)));
      std::cout << "regnr: " << cars.at(i).at(0);
      std::cout << " | model: " << std::setw(19) << std::left << cars.at(i).at(1) << " | aargang: " << cars.at(i).at(2) << std::endl;
  }

  db.extractData();
  std::cout << "\nDB: Table contains " << db.countEntries() << " entries" << std::endl;


  //db.clearDatabase();
  return 0;
}

