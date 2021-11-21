
#include <mutex>
#include <chrono>
#include <thread>
#include <iomanip>
#include <functional>
#include "database.h"
#include "cargenerator.h"

using namespace std;
mutex m;

CarGenerator cg;

void addCars(int amount) {
  m.lock();

  Database db;

  std::vector<std::vector<std::string>> cars = cg.generateCar(amount, db.extractHighestRegNr());
  std::cout << "Generating " << amount << " cars starting from regNr " << db.extractHighestRegNr() << std::endl;

  for (int i = 0; i < cars.size(); i++) {
      db.insertData(QString::fromStdString(cars.at(i).at(0)), QString::fromStdString(cars.at(i).at(1)), stoi(cars.at(i).at(2)));
      //std::cout << "regnr: " << cars.at(i).at(0);
      //std::cout << " | model: " << std::setw(19) << std::left << cars.at(i).at(1) << " | aargang: " << cars.at(i).at(2);
  }
  db.disconnect();
  m.unlock();
}

void extractCars(){
  Database db;
  std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
  db.extractData();
  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end - start;
  std::cout << "\nExtraction without indexing took " << duration.count()/1000.0 << " seconds" << std::endl;
}

int main() {
  std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
  Database db;
  db.clearDatabase();
  db.createTable();
  db.countRows();

  int amountToCreate = 5;
  std::thread t1(addCars, amountToCreate);
  std::thread t2(addCars, amountToCreate);
  std::thread t3(addCars, amountToCreate);
  std::thread t4(addCars, amountToCreate);

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end - start;

  std::cout << "Generation and instertion of " << amountToCreate << " cars took " << duration.count()/1000.0 << " seconds" << std::endl;;
  std::cout << "That's " << duration.count()/1000.0/amountToCreate << " seconds pr. car" << std::endl;

  extractCars();

  //db.clearDatabase();

  return 0;
}

