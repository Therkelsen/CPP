#ifndef CARGENERATOR_H
#define CARGENERATOR_H
#include <iostream>
#include <QString>
#include <utility>
#include <random>
#include <vector>
#include <string>
#include <ctime>

class CarGenerator {
public:
  CarGenerator();
  std::vector<std::vector<std::string>> generateCar(int amount, std::string currHighestRegNr);
private:
  int letterIterator1;
  int letterIterator2;
  int numberIterator;
  int year;
  char x, y;
  std::string regNum;
  std::string model;
};

#endif // CARGENERATOR_H
