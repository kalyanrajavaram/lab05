#include "Student.h"
#include <sstream>
#include <string>


Student::Student(int perm, std::string lastName, std::string firstAndMiddleNames) 
    : perm(perm), lastName(lastName), firstAndMiddleNames(firstAndMiddleNames) {
}

// Constructor that initializes a `Student` object from a CSV string, e.g., "1234567,Smith,Mary Kay"
Student::Student(std::string csvString) {
    std::istringstream iss(csvString);

    std::string permAsString;
    getline(iss, permAsString, ',');
    this->perm = std::stoi(permAsString);  // Convert `perm` from string to int

    getline(iss, this->lastName, ',');
    getline(iss, this->firstAndMiddleNames, '\n');
}


int Student::getPerm() const { 
    return perm;
}


std::string Student::getLastName() const { 
    return lastName;
}


std::string Student::getFirstAndMiddleNames() const {
    return firstAndMiddleNames;
}


std::string Student::getFullName() const { 
    return firstAndMiddleNames + " " + lastName;
}


std::string Student::toString() const { 
    std::ostringstream oss;
    oss << "[" 
        << this->getPerm() << ","
        << this->getLastName() << ","
        << this->getFirstAndMiddleNames() << "]";
    return oss.str();
} 
