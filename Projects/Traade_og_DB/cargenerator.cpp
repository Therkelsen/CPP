#include "cargenerator.h"

CarGenerator::CarGenerator()
  :rand()
{}

// Here I'm using a vector vector string, to spite someone online who told me to use a struct =)
std::vector<std::vector<std::string>> CarGenerator::generateCar(int amount, std::string currHighestRegNr = "") {
  std::vector<std::vector<std::string>> cars;
  std::vector<std::string> car;

  srand((unsigned int)time(NULL));

  if (currHighestRegNr.length() != 7) {
    letterIterator1 = 0;
    letterIterator2 = 0;
    numberIterator = 10000;
  } else {
    char x = currHighestRegNr[0];
    char y = currHighestRegNr[1];
    int z = stoi(currHighestRegNr.substr(2,6)) + 1;
    letterIterator1 = int(x) - 65;
    letterIterator2 = int(y) - 65;
    numberIterator = z;
  }

  year = 0;
  regNum = "";
  model = "";
  // Since size of the vectors is known, all allocation is done at once to speed up the code

  for (int i = 0; i < amount; i++) {
    car.clear();
    car.reserve(3);
    if (numberIterator > 99999) {
      letterIterator2++;
      numberIterator = 10000;
    }
    if (letterIterator2 > 90) {
      letterIterator2 = 0;
      letterIterator1++;
    }
    if (letterIterator1 > 90) {
      return cars;
    }

    // Utilize ascii values to increment letters
    x = 'A' + letterIterator1;
    y = 'A' + letterIterator2;
    // Insert license plate number in a string, to be appended onto the vector
    regNum = ""; regNum.push_back(x); regNum.push_back(y); regNum = regNum + std::to_string(numberIterator);

    // Here I use emplace_back in place of push_back, as it's faster
    // (This, along with the pre-emptive allocation saves about 60% process time)
    int j = 1 + (rand() % 8);

    switch (j) {
      case 1:
        model = "Tesla Cybertruck";
        year = 2022;
        break;
      case 2:
        model = "Ferrari Testarossa";
        year = rand() % ((1996 - 1984) + 1) + 1984;
        break;
      case 3:
        model = "Lada Riva";
        year = rand() % ((2015 - 1979) + 1) + 1979;
        break;
      case 4:
        model = "Fiat Multipla";
        year = rand() % ((2013 - 1998) + 1) + 1998;
        break;
      case 5:
        model = "Ellert";
        year = rand() % ((2018 - 1987) + 1) + 1987;
      case 6:
        model = "Nissan Skyline R34";
        year = rand() % ((2002 - 1999) + 1) + 1999;
      case 7:
        model = "Ford Model T";
        year = rand() % ((1927- 1908) + 1) + 1908;
      case 8:
        model = "Lotus Esprit";
        year = rand() % ((2004- 1976) + 1) + 1976;
      default:
        break;
    }

    car.emplace_back(regNum);
    car.emplace_back(model);
    car.emplace_back(std::to_string(year));
    cars.emplace_back(car);

    /*std::cout << "Regnr: " << cars.at(i).at(0) << std::endl;
    std::cout << "Model: " << cars.at(i).at(1) << std::endl;
    std::cout << "Aargang: " << cars.at(i).at(2) <<  "\n" << std::endl;*/
    numberIterator++;
  }
  return cars;
}
