#include <iostream>
using namespace std;

int main() {
    float marks;
    cout << "Enter student's marks: ";
    cin >> marks;

    switch (marks < 0 || marks > 100) {
        case true:
            cout << "Invalid marks entered. Please enter marks between 0 and 100." << endl;
            continue;;
        case false:
            break;
    }
    if (marks >= 90)
        cout << "Grade: A";
    else if (marks >= 80)
        cout << "Grade: B";
    else if (marks >= 70)
        cout << "Grade: C";
    else if (marks >= 60)
        cout << "Grade: D";
    else
        cout << "Grade: F";
}