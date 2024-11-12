#include "Roster.h"
#include <cstdlib>
#include <fstream>
#include <cassert>
#include <sstream>

Roster::Roster() : numStudents(0) {
    // Initialize all pointers in the `students` array to `nullptr`
    for (int i = 0; i < ROSTER_MAX; i++) {
        students[i] = nullptr;
    }
}



void Roster::resetRoster() {
    // Release memory for all allocated students
    while (numStudents > 0) {
        delete students[--numStudents];
        students[numStudents] = nullptr;  // Set to `nullptr` to avoid dangling pointers
    }
}

void Roster::addStudentsFromFile(std::string filename) {
    std::ifstream ifs(filename);
    if (ifs.fail()) {
        std::cerr << "Could not open input file: " << filename << std::endl;
        exit(2);  // Exit with error code if file cannot be opened
    }
    addStudentsFromStream(ifs);
}

void Roster::addStudentsFromStream(std::istream &is) {
    resetRoster();  // Clear existing roster before adding new students

    std::string line;
    getline(is, line);  // Skip header line

    while (getline(is, line)) {
        if (numStudents < ROSTER_MAX) {
            students[numStudents++] = new Student(line);
        }
    }
}

int Roster::getNumStudents() const {
    return numStudents;
}

Student Roster::getStudentAt(int index) const {
    assert(index >= 0 && index < numStudents);  // Ensure index is valid
    return *students[index];  // Dereference pointer to return `Student` object
}

std::string Roster::toString() const {
    std::ostringstream oss;
    oss << "{\n";
    
    for (int i = 0; i < numStudents; i++) {
        oss << students[i]->toString();
        if (i < numStudents - 1) {
            oss << ",\n";  // Add comma and newline for all but the last student
        }
    }
    
    oss << "\n}\n";  // Close the list with a newline and brace
    return oss.str();
}

int Roster::indexOfMaxPermAmongFirstKStudents(int k) const {
    int maxIndex = 0;
    for (int i = 1; i < k; i++) {
        if (students[i]->getPerm() > students[maxIndex]->getPerm()) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

void Roster::sortByPermHelper(int k) {
    int maxIndex = indexOfMaxPermAmongFirstKStudents(k);
    if (maxIndex != k - 1) {
        std::swap(students[maxIndex], students[k - 1]);
    }
}

void Roster::sortByPerm() {
    // Selection sort by `perm` in descending order
    for (int i = numStudents; i > 1; i--) {
        sortByPermHelper(i);
    }
}
