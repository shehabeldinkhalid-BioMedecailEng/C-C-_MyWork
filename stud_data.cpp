#include <iostream>
using namespace std;

int main() {
    int studentID, studentAge;
    string studentName, studentSec;

    cout << "Enter Student ID: ";
    cin >> studentID;
    cout << "Enter Student Age: ";
    cin >> studentAge;
    cout << "Enter Student Name: ";
    cin >> studentName;
    cout << "Enter Student Section: ";
    cin >> studentSec;

    cout << "\n--- Student Details ---\n";
    cout << "ID: " << studentID << endl;
    cout << "Age: " << studentAge << endl;
    cout << "Name: " << studentName << endl;
    cout << "Section: " << studentSec << endl;
}