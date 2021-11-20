#include "cargenerator.h"

CarGenerator::CarGenerator(){}

// Her bruger jeg en bonderøvs vector vector string, for at trodse en online som sagde jeg skulle bruge en struct =)
std::vector<std::vector<std::string>> CarGenerator::generateCar(int amount, std::string currHighestRegNr = "") {
  std::cout << "CG: Generating " << amount << " cars starting from regNr " << currHighestRegNr << std::endl;
  std::vector<std::vector<std::string>> cars;
  std::vector<std::string> car;

  // Da størrelsen på vektoren kendes, pre-allokeres pladsen for at spare kørselstid
  cars.reserve(amount);

  // Her bruges en uniform_int_distribution da jeg ikke var glad for ko-klokke-distributionen rand() giver
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dis(0, 1);

  // Generatoren seedes med tiden
  gen.seed((unsigned int)time(NULL));

  // Hvis vi har fået et registreringsnummer startes der med nummerpladen ét nummer højere
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
  // Nummerplader mellem AA10000 og ZZ99999 kan genereres her
  // Derudover kan bilen have en af x antal modeller, som alle har deres rigtige produktionsår
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

    // Udnytter ascii værdier for at inkrementere bogstaverne
    x = 'A' + letterIterator1;
    y = 'A' + letterIterator2;
    // Indsætter registreringsnummeret i en stræng, så den kan blive smidt på enden af vektoren
    regNum = ""; regNum.push_back(x); regNum.push_back(y); regNum = regNum + std::to_string(numberIterator);

    decltype(dis.param()) new_range (1, 8);
    dis.param(new_range);
    int j = dis(gen);

    switch (j) {
      case 1: {
        model = "Tesla Cybertruck";
        year = 2022;
        break;
      } case 2: {
        model = "Ferrari Testarossa";
        decltype(dis.param()) new_range (1984, 1996);
        dis.param(new_range);
        year = dis(gen);
        break;
      } case 3: {
        model = "Lada Riva";
        decltype(dis.param()) new_range (1979, 2015);
        dis.param(new_range);
        year = dis(gen);
        break;
      } case 4: {
        model = "Fiat Multipla";
        decltype(dis.param()) new_range (1998, 2013);
        dis.param(new_range);
        year = dis(gen);
        break;
      } case 5: {
        model = "Ellert";
        decltype(dis.param()) new_range (1987, 2018);
        dis.param(new_range);
        year = dis(gen);
        break;
      } case 6: {
        model = "Nissan Skyline R34";
        decltype(dis.param()) new_range (1999, 2002);
        dis.param(new_range);
        year = dis(gen);
      } case 7:  {
        model = "Ford Model T";
        decltype(dis.param()) new_range (1908, 1927);
        dis.param(new_range);
        year = dis(gen);
      } case 8: {
        model = "Lotus Esprit";
        decltype(dis.param()) new_range (1976, 2004);
        dis.param(new_range);
        year = dis(gen);
      } default:
        break;
    }

    // Her bruges emplace_back i stedet for push_back, da det er hurtigere
    // Det, sammen med at pre-allokere sparede mig omkring 60% kørselstid
    car.emplace_back(regNum);
    car.emplace_back(model);
    car.emplace_back(std::to_string(year));
    cars.emplace_back(car);

    numberIterator++;
  }
  return cars;
}
