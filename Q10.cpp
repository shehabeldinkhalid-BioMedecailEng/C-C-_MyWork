#include <iostream>
using namespace std;

int main() {
    int numbers[] = {5, 30, 2, 8, 20, 70, 30};
    int min = numbers[0];
    int max = numbers[0];
    for (int i = 1; i <(sizeof(numbers)/sizeof(numbers[0])); i++) {
        if (numbers[i] < min)
            min = numbers[i];
        if (numbers[i] > max)
            max = numbers[i];
    }

    cout << "Lowest number: " << min << endl;
    cout << "Largest number: " << max << endl;
}