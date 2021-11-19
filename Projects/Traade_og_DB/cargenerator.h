#ifndef CARGENERATOR_H
#define CARGENERATOR_H
#include <iostream>
#include <utility>
#include <vector>
#include <string>

class CarGenerator {
public:
  CarGenerator();
  std::vector<std::vector<std::string>> generateCar(int amount);
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
