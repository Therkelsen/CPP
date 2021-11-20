#ifndef CARGENERATOR_H
#define CARGENERATOR_H
#include <iostream>
#include <utility>
#include <random>
#include <vector>
#include <string>

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
  std::uniform_int_distribution<int> rand;
};

#endif // CARGENERATOR_H
