#pragma once
#include <chrono>
#include <string>
#include <iostream>
#include <random>
#include <mutex>

// Singleton class
class Random
{
public:
	// Sletter copy constructor og assignment operator
	Random(const Random&) = delete;
	void operator=(const Random&) = delete;

	// Access to the private constructor is hidden in a function
	static Random& get() {
		static Random instance;
		return instance;
	}

	static std::string numberPlateGenerator() { return get().internalnumberPlateGenerator(); }
	static std::string randomModelGenerator() { return get().internalrandomModelGenerator(); }
	static std::string randomYearGenerator() { return get().internalrandomYearGenerator();}

private:
	Random() {}

	std::string internalnumberPlateGenerator();
	std::string internalrandomModelGenerator();
	std::string internalrandomYearGenerator();

	std::mutex _mutex;
};