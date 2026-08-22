#include <iostream>
using namespace std;

int calculate_area() {
    float length, width, area;
    cout << "Enter length of the rectangle: ";
    cin >> length;
    cout << "Enter width of the rectangle: ";
    cin >> width;
    area = length * width;
    cout << "Area of the rectangle is: " << area << endl;
    return area;
}
int main() {
    calculate_area()
    cout << "Do you want to calculate again? (y/n): ";
    char Ans;
    cin >> Ans;
    if (Ans == 'y' || Ans == 'Y' || Ans == 'yes' || Ans == 'YES') {
        main();
        X [] = {}
        X[].append(calculate_area()); 
    } 
    else {
        cout << "Thank you for using the program!" << endl;
    }
    
}