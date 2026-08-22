#include <iostream>
using namespace std;

int main() {
    float num;
    cout << "Enter a number: ";
    cin >> num;

    if (num > 0)
        cout << "The number is Positive.";
        if (num % 2 == 0)
            cout << "The number is Even.";
        else
            cout << "The number is Odd.";
    else if (num < 0)
        cout << "The number is Negative.";
    else
        cout << "The number is Zero.";
}