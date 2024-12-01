#pragma once
#include <string>
#include <iostream>

using namespace std;

class CarData {
public:
    string model;
    string manufacturer;
    int year;
    int horsepower;
    string color;
    int startingPrice;

    // Default constructor
    CarData() : model(""), manufacturer(""), year(0), horsepower(0), color(""), startingPrice(0) {}

    // Parameterized constructor
    CarData(string model, string manufacturer, int year, int horsepower, string color, double startingPrice)
        : model(model), manufacturer(manufacturer), year(year), horsepower(horsepower), color(color), startingPrice(startingPrice) {}

    // Getters
    string getModel() const { return model; }
    string getManufacturer() const { return manufacturer; }
    int getYear() const { return year; }
    int getHorsepower() const { return horsepower; }
    string getColor() const { return color; }
    int getStartingPrice() const { return startingPrice; }

    // Comparison operator for set
    bool operator<(const CarData& other) const;

    // Output stream operator
    friend ostream& operator<<(ostream& os, const CarData& data);
};

// Comparison operator for set
bool CarData::operator<(const CarData& other) const {
    return model < other.model; // inside set compare based on model
}

// Output stream operator
ostream& operator<<(ostream& os, const CarData& data) {
    os << "Model: " << data.model << ", Manufacturer: " << data.manufacturer
        << ", Year: " << data.year << ", Horsepower: " << data.horsepower
        << ", Color: " << data.color << ", Starting Price: " << " $" << data.startingPrice;
    return os;
}


