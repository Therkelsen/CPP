
#include <mutex>
#include <chrono>
#include <thread>
#include <iomanip>
#include <functional>
#include "database.h"
#include "cargenerator.h"

using namespace std;
mutex mtx;

CarGenerator cg;

// Metode som tilføjer biler til databasen
void addCars(int amount) {
  mtx.lock();

  Database db;
  // Laver en vector som indeholder biler, efter generation af generateCar() metoden
  std::cout << "Generating " << amount << " cars starting from regNr " << db.extractHighestRegNr() << std::endl;
  std::vector<std::vector<std::string>> cars = cg.generateCar(amount, db.extractHighestRegNr());

  // Indsætter dataen i databasen
  for (int i = 0; i < cars.size(); i++) {
      db.insertData(QString::fromStdString(cars.at(i).at(0)), QString::fromStdString(cars.at(i).at(1)), stoi(cars.at(i).at(2)));
      //std::cout << "regnr: " << cars.at(i).at(0);
      //std::cout << " | model: " << std::setw(19) << std::left << cars.at(i).at(1) << " | aargang: " << cars.at(i).at(2);
  }
  mtx.unlock();
}

int main() {
  // Tiden hvor koden startede gemmes
  std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
  
  // Klargør databasen ved at "rense" den
  Database db;
  db.clearTable();
  db.createTable();
  db.createIndex();

  int amountToCreate = 5000;
  int threads = 4;

  // Laver fire threads til at generere biler
  std::thread t1(addCars, amountToCreate);
  std::thread t2(addCars, amountToCreate);
  std::thread t3(addCars, amountToCreate);
  std::thread t4(addCars, amountToCreate);

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  //db.openDatabase();
  //db.extractData();
  //db.disconnect();

  // Tiden efter koden har kørt gemmes for at regne kørselstiden ud
  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end - start;

  std::cout << "Code took " << duration.count()/1000.0 << " seconds to generate and extract " << amountToCreate*threads << " cars" << std::endl;

  //db.clearDatabase();

  return 0;
}

