#include <iostream>
using namespace std;

int main() {
        cout << "Enter your boundary first number: ";
        int bound1;
        cin >> bound1;
        cout << "Enter your boundary first number: ";
        int bound2;
        cin >> bound2;
        cout << "numbers between "<< bound1 <<" and "<< bound2 <<":" << endl;
        cout << "Even numbers between "<< bound1 <<" and "<< bound2 <<":" << endl;
        for (int i = bound1; i <= bound2; i++) 
            if (i % 2 == 0)
                cout << i << " ";
}