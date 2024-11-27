#pragma once
#include <string>
using namespace std;

class CarData {

public:
	string model;
	string manufacturer;
	int year;
	int horsepower;
	string color;
	double startingPrice;

	CarData(string model, string manufacturer, int year, int horsepower, string color, double startingPrice) :
		model(model), manufacturer(manufacturer), year(year), horsepower(horsepower), color(color), startingPrice(startingPrice) {}


	// Getters
	string getModel() const {
		return model;
	}

	string getManufacturer() const {
		return manufacturer;
	}

	int getYear() const {
		return year;
	}

	int getHorsepower() const {
		return horsepower;
	}

	string getColor() const {
		return color;
	}

	double getStartingPrice() const {
		return startingPrice;
	}
};
