#include "Random.h"

std::string Random::internalnumberPlateGenerator() {
	int value = 10000 + (rand() % 99999);
	std::string svalue = std::to_string(value);

	int index1 = 0 + (rand() % 26);
	int index2 = 0 + (rand() % 26);
	std::string alfabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	char i1 = alfabet[index1];
	char i2 = alfabet[index2];
	std::string result;
	result.push_back(i1);
	result.push_back(i2);
	result += svalue;
	return result;
}

std::string Random::internalrandomModelGenerator() {
	int index = 1 + (rand() % 5);
	std::string model;

	switch (index) {
	case 1:
		model = "Citroen C1";
		break;
	case 2:
		model = "Suzuki Alto";
		break;
	case 3:
		model = "Fiat Punto";
		break;
	case 4:
		model = "VW Golf 1 GTI";
		break;
	case 5:
		model = "Citroen 2CV";
	default:
		break;
	}

	return model;
}

std::string Random::internalrandomYearGenerator() {
	int index = 1 + (rand() % 5);
	std::string aar;

	switch (index) {
	case 1:
		aar = "1990";
		break;
	case 2:
		aar = "1992";
		break;
	case 3:
		aar = "1985";
		break;
	case 4:
		aar = "1995";
		break;
	case 5:
		aar = "1980";
	default:
		break;
	}

	return aar;
}