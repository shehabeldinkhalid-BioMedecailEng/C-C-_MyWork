#include <iostream>
using namespace std;

int main() {
    int sum = 0;
    for (int i = 0; i <= 20; i++) {
        sum += i;
    }
    cout << "Sum of numbers from 0 to 20 is: " << sum;
}