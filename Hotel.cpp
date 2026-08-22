// Hotal Project.cpp 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <limits> // <-- Added for numeric_limits
#include <conio.h> // For getch()
#include <cstdlib> // For exit()
using namespace std;

int counter = 0;
void cheackcoiunter() {
    if (counter == 3) {
        cout << "Too many failed attempts. Exiting...\n";
        exit(0);
    }
};
bool isValidCppName(const std::string& name) {
    // The regex pattern:
    // ^      - Start of the string
    // [a-zA-Z_] - Matches the first character (letter or underscore)
    // [a-zA-Z0-9_]* - Matches zero or more subsequent characters (letters, digits, or underscores)
    // $      - End of the string
    const std::regex pattern("^[a-zA-Z_][a-zA-Z0-9_]*$");

    // std::regex_match checks if the entire string matches the pattern
    return std::regex_match(name, pattern);
}
string getHiddenPasswordWindows() {
    string password;
    char ch;
    cout << "Enter password: ";

    // Use getch() to read character without echoing it to the console
    while ((ch = _getch()) != '\r') { // '\r' is the carriage return (Enter key)
        if (ch == '\b') { // Handle backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // Erase the character and the asterisk
            }
        }
        else {
            password += ch;
            cout << "*"; // Print an asterisk
        }
    }
    cout << endl; // Move to the next line after Enter is pressed
    return password;
}
bool isValidEmail(const string& email) {
    const regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return regex_match(email, pattern);
}
bool isValidPhoneNumber(const string& phoneNumber) {
    const regex pattern(R"(^(\+|00)?[0-9\s\-\(\)\.]{7,32}$)");
    return regex_match(phoneNumber, pattern);
}
bool isValidID(const string& id) {
    const regex pattern(R"(^[0-9]{14}$)");
    return regex_match(id, pattern);
}

// ================= Base Class =================
class Person {
protected:
    string name = "";
    string id = "";
public:
    void setData(string n, string i) {
        name = n;
        id = i;
    }
    string getName() { return name; }
    string getID() { return id; }
};
// ================= Customer =================
class Customer : public Person {
private:
    string phone = "", email = "";

public:
    void input() {
        int age = 0;
        bool valid = false;

        // Name Validation (ADDED)
        while (true) {
            cout << "Enter Name: ";
            cin >> name;
            if (!isValidCppName(name))
                cout << "Invalid Name Try again\n";
            else { cout << "OK Done\n"; break; }
        }
        // ID Validation
        while (true) {
            cout << "Enter ID: ";
            cin >> id;
            valid = isValidID(id);
            if (!valid) cout << "invalid ID Try again" << endl;
            else { cout << "OK Done" << endl; break; }
        }

        // Age Validation
        cout << "Enter Age: ";
        while (!(cin >> age)) {
            cout << "Invalid input. Please try again with an integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "OK Done" << endl;

        // Phone Validation
        while (true) {
            cout << "Enter Phone: ";
            cin >> phone;
            valid = isValidPhoneNumber(phone);
            if (!valid) cout << "invalid PhoneNumber Try again" << endl;
            else { cout << "OK Done" << endl; break; }
        }

        // Email Validation
        while (true) {
            cout << "Enter Email: ";
            cin >> email;
            valid = isValidEmail(email);
            if (!valid) cout << "invalid Email Try again" << endl;
            else { cout << "OK Done" << endl; break; }
        }
    }

    void display() {
        cout << "Name: " << name
            << " | ID: " << id
            << " | Phone: " << phone
            << " | Email: " << email << endl;
    }
};
// ================= Employee =================
class Employee : public Person {
private:
    string position = "";
    double salary = 0;

public:
    void input() {
        bool valid = false;
        //  Name Validation (ADDED)
        while (true) {
            cout << "Enter Name: ";
            cin >> name;
            if (!isValidCppName(name))
                cout << "Invalid Name Try again\n";
            else { cout << "OK Done\n"; break; }
        }

        // ID Validation
        while (true) {
            cout << "Enter ID: ";
            cin >> id;
            valid = isValidID(id);
            if (!valid) cout << "invalid ID Try again" << endl;
            else { cout << "OK Done" << endl; break; }
        }
        while (true) {
            cout << "Enter Position: ";
            cin >> position;
            if (!isValidCppName(name))
                cout << "Invalid Name Try again\n";
            else { cout << "OK Done\n"; break; }
        }

        // Salary Validation
        cout << "Enter Salary: ";
        while (!(cin >> salary) || salary < 0) {
            cout << "Invalid salary. Please enter a valid number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "OK Done" << endl;
    }

    void display() {
        cout << "Employee: " << name
            << " | ID: " << id
            << " | Position: " << position
            << " | Salary: " << salary << endl;
    }
};
// ================= Manger ====================
class Manager {
private:
    string username = "admin";
    string password = "1234";
public:
    bool login() {
        string u, p;
        cout << "Username: "; cin >> u;
        p = getHiddenPasswordWindows();
        return (u == username && p == password);
    }
};
// ================= Room =================
class Room {
private:
    int number;
    int beds;
    int capacity;
    double price;
    bool available;

public:
    Room(int n = 0, int b = 0, int c = 0, double p = 0, bool a = true) {
        number = n; beds = b; capacity = c; price = p; available = a;
    }

    void input() {
        while (true) {
            cout << "Enter Room Number: ";
            cin >> number;
            if (number <= 0) cout << "invalid Room Number Try again" << endl;
            else { cout << "OK Done" << endl; break; }
        }

        cout << "Enter Beds: ";
        while (!(cin >> beds) || beds <= 0) {
            cout << "Invalid beds number. Try again: ";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "OK Done" << endl;

        cout << "Enter Capacity: ";
        while (!(cin >> capacity) || capacity <= 0) {
            cout << "Invalid capacity. Try again: ";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "OK Done" << endl;

        cout << "Enter Price: ";
        while (!(cin >> price) || price < 0) {
            cout << "Invalid price. Try again: ";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "OK Done" << endl;

        while (true) {
            int choice;
            cout << "Is Available? (1 = Yes, 0 = No): ";
            cin >> choice;
            if (choice == 1) { available = true; cout << "OK Done" << endl; break; }
            else if (choice == 0) { available = false; cout << "OK Done" << endl; break; }
            else cout << "Invalid choice Try again" << endl;
        }
    }

    void display() {
        cout << "Room " << number
            << " | Price: " << price
            << " | Available: " << (available ? "Yes" : "No") << endl;
    }
    double getPrice() { return price; }
    bool isAvailable() { return available; }
    void book() { available = false; }
};
// ================= Hall =================
class Hall {
private:
    int id = 0;
    string name = "";
    int capacity = 0;
    string occasion = "";

public:
    void input() {
        while (true) {
            cout << "Hall ID: "; cin >> id;
            if (id <= 0) cout << "invalid ID Try again" << endl;
            else { cout << "OK Done" << endl; break; }
        }

        // Name Validation (ADDED)
        while (true) {
            cout << "Enter Name: ";
            cin >> name;
            if (!isValidCppName(name))
                cout << "Invalid Name Try again\n";
            else { cout << "OK Done\n"; break; }
        }

        cout << "Capacity: ";
        while (!(cin >> capacity) || capacity <= 0) {
            cout << "Invalid capacity. Try again: ";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "OK Done" << endl;

        cout << "Occasion: "; cin >> occasion;
    }

    void display() {
        cout << "Hall " << name << " | Capacity: " << capacity << endl;
    }
};
// ===================== Restaurant =====================
class Restaurant {
private:
    string menu[100];  // array of food names
public:
    void addMenuItem() {
        string item;
        cout << "Enter food item to add: ";
        cin.ignore(); // flush leftover newline
        getline(cin, item);

        if (item.empty()) {
            cout << "Item cannot be empty.\n";
            return;
        }

        for (int i = 0; i < 100; i++) {
            if (menu[i].empty()) {
                menu[i] = item;
                cout << "Item added: " << item << endl;
                return;
            }
        }
        cout << "Menu full! Cannot add more items.\n";
    }


    void displayMenu() const {
        cout << "\n--- Restaurant Menu ---\n";
        bool emptyMenu = true;
        for (int i = 0; i < 100; i++) {
            if (!menu[i].empty()) {
                cout << i + 1 << ". " << menu[i] << endl;
                emptyMenu = false;
            }
        }
        if (emptyMenu) cout << "Menu is empty.\n";
        cout << "----------------------\n";
    }

    void saveMenu() const {
        ofstream file("menu.txt");
        for (int i = 0; i < 100; i++) {
            if (!menu[i].empty()) file << menu[i] << "\n";
        }
    }

    void loadMenu() {
        ifstream file("menu.txt");
        if (!file.is_open()) return;
        string line;
        int i = 0;
        while (getline(file, line) && i < 100) {
            if (!line.empty()) menu[i++] = line;
        }
    }
};
// ================= Reservation =================
class Reservation {
private:
    string customerName = "";
    int roomNumber = 0;
    int days = 0;
    double total = 0.0;
public:
    void makeReservation(string name, int room, int d, double price) {
        customerName = name;
        roomNumber = room;
        days = d;
        total = days * price;
    }
    double getFullPrice() const { return total; }
    void display() const {
        cout << "Reservation for " << customerName
            << " | Room: " << roomNumber
            << " | Days: " << days
            << " | Total: " << total << endl;
    }
};

int choice = 0;
bool allowed = false;
// ================= Global Variables =================
vector<Customer> customers;
vector<Employee> employees;
vector<Room> rooms = {
    Room(1,2,2,100,true),
    Room(2,3,3,150,true),
    Room(3,1,1,80,true),
    Room(4,2,2,120,true)
};
Restaurant rest;
vector<Reservation> reservations;

// ===== Manger Functions =====
void removeEmployee(vector<Employee>& employees) {
    if (employees.empty()) {
        cout << "No employees to remove.\n";
        return;
    }

    for (int i = 0; i < employees.size(); i++) {
        cout << "Employee Number ==> " << i + 1 << ":\n";
        employees[i].display();
        cout << "-----------------------------\n";
    }

    int num;
    cout << "Enter The Number of employee: ";

    while (!(cin >> num)) {
        cout << "Invalid input. Enter integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (num < 1 || num > employees.size()) {
        cout << "Invalid employee number.\n";
        return;
    }

    employees.erase(employees.begin() + (num - 1));
    cout << "Employee removed successfully.\n";
}
void addEmployee(vector<Employee>& employees) {
    Employee e;
    e.input();
    employees.push_back(e);
    cout << "Employee added successfully.\n";
}
void manageRestaurant(Restaurant rest) {
    int choice;

    while (true) {
        cout << "\n--- Restaurant Menu ---\n";
        cout << "1. View Menu\n";
        cout << "2. Add Item\n";
        cout << "3. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
            rest.displayMenu();
        else if (choice == 2) {
            rest.addMenuItem();
            rest.saveMenu();
        }
        else if (choice == 3)
            break;
        else
            cout << "Invalid choice.\n";
    }
}
void showAllData(vector<Customer> customers, vector<Employee> employees, vector<Room> rooms) {
    cout << "\n========== ALL SYSTEM DATA ==========\n";

    cout << "\n--- Customers ---\n";
    if (customers.empty()) cout << "No customers.\n";
    else {
        for (int i = 0; i < customers.size(); i++) {
            customers[i].display();
        }
    }

    cout << "\n--- Employees ---\n";
    if (employees.empty()) cout << "No employees.\n";
    else {
        for (int i = 0; i < employees.size(); i++) {
            employees[i].display();
        }
    }

    cout << "\n--- Rooms ---\n";
    if (rooms.empty()) cout << "No rooms.\n";
    else {
        for (int i = 0; i < rooms.size(); i++) {
            rooms[i].display();
        }
    }

    cout << "\n=====================================\n";
}
void showReservations(vector<Reservation> reservations) {
    if (reservations.empty()) {
        cout << "No reservations found.\n";
        return;
    }

    for (int i = 0; i < reservations.size(); i++) {
        reservations[i].display();
    }
}
void foodMenuManagement(Restaurant rest) {
    int choice;
    do {
        cout << "\n--- Food Menu Management ---\n";
        cout << "1. Add Food Item\n";
        cout << "2. View Menu\n";
        cout << "3. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
        case 1:
            rest.addMenuItem();
            rest.saveMenu();
            break;
        case 2:
            rest.displayMenu();
            break;
        case 3:
            cout << "Returning...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 3);
}
void bookRoom(vector<Room>& rooms, vector<Reservation>& reservations) {
    cout << "Available Rooms:\n";

    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i].isAvailable())
            rooms[i].display();
    }

    string customerName;
    int roomChoice, days;

    cout << "Enter Customer Name: ";
    cin.ignore();
    getline(cin, customerName);

    cout << "Enter Room Number: ";
    cin >> roomChoice;

    cout << "Enter Days: ";
    cin >> days;

    if (roomChoice < 1 || roomChoice > rooms.size()) {
        cout << "Invalid room.\n";
        return;
    }

    if (!rooms[roomChoice - 1].isAvailable()) {
        cout << "Room not available.\n";
        return;
    }

    rooms[roomChoice - 1].book();

    double price = rooms[roomChoice - 1].getPrice(); // ✅ FIX

    Reservation r;
    r.makeReservation(customerName, roomChoice, days, price);

    reservations.push_back(r);

    cout << "Reservation saved!\n";
}

void Manger()
{
    int counter = 0;

    // ===== LOGIN SYSTEM =====
    while (true) {
        Manager manger;
        allowed = manger.login();

        if (allowed) {
            counter = 0;
            break;
        }
        else {
            counter++;
            cheackcoiunter();
            cout << "Wrong username or password. Try again.\n";
        }
    }

    // ===== MAIN MENU =====
    while (allowed) {
        cout << "\n===== Manager Menu =====\n";
        cout << "1. Add Employee\n";
        cout << "2. Remove Employee\n";
        cout << "3. Book Room\n";
        cout << "4. Manage Restaurant\n";
        cout << "5. Show All Data\n";
        cout << "6. Show Reservations\n";
        cout << "7. Food Menu Management\n";
        cout << "8. Exit\n";
        cout << "Choose: ";
        cin >> choice;
        while (!cin) {
            cout << "Invalid input. Enter number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> choice;
        }
        if (choice < 1 || choice > 8) {
            cout << "Invalid choice. Try again.\n";
            continue;
        }
        char ans;
        cout << "Confirm choice? (Y/N): ";
        cin >> ans;
        while (ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N') {
            cout << "Invalid input. Enter Y or N: ";
            cin >> ans;
        }
        if (ans == 'n' || ans == 'N') continue;
        switch (choice) {
        case 1:
            addEmployee(employees);
            break;

        case 2:
            removeEmployee(employees);
            break;

        case 3:
            bookRoom(rooms, reservations);
            break;

        case 4:
            manageRestaurant(rest);
            break;

        case 5:
            showAllData(customers, employees, rooms);
            break;

        case 6:
            showReservations(reservations);
            break;

        case 7:
            foodMenuManagement(rest);
            break;

        case 8:
            cout << "Goodbye Manager!\n";
            exit(0);
            return;
        }
    }
}

// ================= EMPLOYEE and Customer FEATURES ================
void viewReservations(vector<Reservation>& reservations) {
    if (reservations.empty()) {
        cout << "No reservations found.\n";
        return;
    }

    for (int i = 0; i < reservations.size(); i++) {
        cout << i + 1 << ". ";
        reservations[i].display();
    }
}
void cancelReservation(vector<Reservation>& reservations) {
    if (reservations.empty()) {
        cout << "No reservations to cancel.\n";
        return;
    }

    viewReservations(reservations);

    int choice;
    cout << "Enter reservation number to cancel: ";
    cin >> choice;

    if (choice < 1 || choice > reservations.size()) {
        cout << "Invalid choice.\n";
        return;
    }

    reservations.erase(reservations.begin() + (choice - 1));
    cout << "Reservation cancelled successfully.\n";
}
void showSchedule() {
    cout << "\n--- Daily Schedule ---\n";
    cout << "Breakfast: 7 AM - 11 AM\n";
    cout << "Lunch: 3 PM - 7 PM\n";
    cout << "Dinner: 9 PM - 12 AM\n";
}
void cleanRoom(vector<Room>& rooms) {
    int roomNumber;
    cout << "Enter room number to clean: ";
    cin >> roomNumber;
    if (roomNumber < 1 || roomNumber > rooms.size()) {
        cout << "Invalid room number.\n";
        return;
    }
    cout << "Room " << roomNumber << " cleaned successfully.\n";
}
void extendReservation(vector<Reservation>& reservations) {
    if (reservations.empty()) {
        cout << "No reservations found.\n";
        return;
    }

    viewReservations(reservations);

    int choice;
    cout << "Choose reservation: ";
    cin >> choice;

    if (choice < 1 || choice > reservations.size()) {
        cout << "Invalid choice.\n";
        return;
    }

    int extraDays;
    cout << "Enter extra days: ";
    cin >> extraDays;

    char approval;
    cout << "Manager approval (Y/N): ";
    cin >> approval;

    if (approval == 'Y' || approval == 'y') {
        cout << "Reservation extended successfully.\n";
        // (You can modify total if you want)
    }
    else {
        cout << "Request rejected.\n";
    }
}
void checkoutRoom(vector<Room>& rooms) {
    int roomNumber;
    cout << "Enter room number: ";
    cin >> roomNumber;

    if (roomNumber < 1 || roomNumber > rooms.size()) {
        cout << "Invalid room.\n";
        return;
    }

    int payment;
    cout << "Payment Method (1 = Cash, 2 = Visa): ";
    cin >> payment;

    if (payment == 1)
        cout << "Paid with Cash.\n";
    else if (payment == 2)
        cout << "Paid with Visa.\n";
    else
        cout << "Invalid payment method.\n";

    cout << "Checkout completed.\n";
}
void requestDayOff() {
    char approval;
    cout << "Requesting a day off...\n";
    cout << "Manager approval (Y/N): ";
    cin >> approval;

    if (approval == 'Y' || approval == 'y')
        cout << "Day off approved.\n";
    else
        cout << "Request rejected.\n";
}

void employee(vector<Reservation>& reservations, vector<Room>& rooms) {
    int choice;
    cout << "\n===== Employee Menu =====\n";
    cout << "1. View Reservations\n";
    cout << "2. Cancel Reservation\n";
    cout << "3. Show Schedule\n";
    cout << "4. Clean Room\n";
    cout << "5. Extend Reservation\n";
    cout << "6. Checkout Room\n";
    cout << "7. Request Day Off\n";
    cout << "8. Exit\n";
    cout << "Choose: ";
    cin >> choice;
    while (!(cin >> choice)) {
        cout << "Invalid input. Please try again with an integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    while (true) {
        if (choice < 1 || choice > 8) {
            cout << "Invalid choice. Please try again." << endl;
            cin >> choice;
            continue;
        }
        char ans;
        cout << "Confirm choice? (Y/N): ";
        cin >> ans;
        while (ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N') {
            cout << "that '" << ans << "' Not specfic Please Follow instructions";
            cin >> ans;
        }
        if (ans == 'n' || ans == 'N') {
            cout << "Please choose again: ";
            cout << "\n===== Employee Menu =====\n";
            cout << "1. View Reservations\n";
            cout << "2. Cancel Reservation\n";
            cout << "3. Show Schedule\n";
            cout << "4. Clean Room\n";
            cout << "5. Extend Reservation\n";
            cout << "6. Checkout Room\n";
            cout << "7. Request Day Off\n";
            cout << "8. Exit\n";
            cout << "Choose: ";
            cin >> choice;
            continue;
        }
        break;
    }
    switch (choice) {
    case 1: viewReservations(reservations); break;
    case 2: cancelReservation(reservations); break;
    case 3: showSchedule(); break;
    case 4: cleanRoom(rooms); break;
    case 5: extendReservation(reservations); break;
    case 6: checkoutRoom(rooms); break;
    case 7: requestDayOff(); break;
    case 8: cout << "Returning...\n"; break;
    default: cout << "Invalid choice.\n";
    }
}

void customer() {
    int choice;
    cout << "\n===== CUSTOMER MENU =====\n";
    cout << "1. View Rooms\n";
    cout << "2. Book Room\n";
    cout << "3. View Menu\n";
    cout << "4. Order Food\n";
    cout << "5. Exit\n";
    cin >> choice;
    while (!(cin >> choice)) {
        cout << "Invalid input. Please try again with an integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    while (true) {
        if (choice < 1 || choice > 5) {
            cout << "Invalid choice. Please try again." << endl;
            cin >> choice;
            continue;
        }
        char ans;
        cout << "Confirm choice? (Y/N): ";
        cin >> ans;
        while (ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N') {
            cout << "that '" << ans << "' Not specfic Please Follow instructions";
            cin >> ans;
        }
        if (ans == 'n' || ans == 'N') {
            cout << "Please choose again: ";
            cout << "1. View Rooms\n";
            cout << "2. Book Room\n";
            cout << "3. View Menu\n";
            cout << "4. Order Food\n";
            cout << "5. Exit\n";
            cin >> choice;
            continue;
        }
        break;
    }
    switch (choice) {
    case 1: {
        for (auto& r : rooms)
            r.display();
        break;
    }

    case 2: {
        string name;
        int roomNum, days;
        while (true) {
            cout << "Enter Name: ";
            cin >> name;
            if (!isValidCppName(name))
                cout << "Invalid Name Try again\n";
            else break;
        }
        while (true) {
            cout << "Enter Room Number: ";
            cin >> roomNum;
            if (roomNum < 1 || roomNum > rooms.size()) {
                cout << "Invalid room Try again\n";
                continue;
            }
            if (!rooms[roomNum - 1].isAvailable()) {
                cout << "Room already booked\n";
                continue;
            }
            break;
        }
        while (true) {
            cout << "Enter Days: ";
            cin >> days;

            if (days <= 0)
                cout << "Invalid days Try again\n";
            else break;
        }
        rooms[roomNum - 1].book();

        Reservation r;
        r.makeReservation(name, roomNum, days, rooms[roomNum - 1].getPrice());

        reservations.push_back(r);

        cout << "Reservation Done!\n";
        break;
    }

    case 3: {
        rest.displayMenu();
        break;
    }

    case 4: {
        rest.displayMenu();
        int food;
        cout << "Choose food: ";
        cin >> food;
        cout << "Order saved successfully\n";
        break;
    }

    default:
        cout << "Invalid choice\n";
    }
}
//---------------- Save And Load Functions ---------------------------
void saveCustomers() {
    ofstream file("customers.txt");
    for (auto& c : customers) {
        file << c.getName() << " " << c.getID() << endl;
    }
}
void loadCustomers() {
    ifstream file("customers.txt");
    string name, id;

    while (file >> name >> id) {
        Customer c;
        c.setData(name, id);
        customers.push_back(c);
    }
}
void saveReservations() {
    ofstream file("reservations.txt");

    for (auto& r : reservations) {
        file << r.getFullPrice() << endl; // simplified
    }
}
void loadReservations() {
    ifstream file("reservations.txt");
    double total;

    while (file >> total) {
        Reservation r;
        // minimal load (you can expand later)
        reservations.push_back(r);
    }
}
void saveRooms() {
    ofstream file("rooms.txt");

    for (auto& r : rooms) {
        file << r.getPrice() << " " << r.isAvailable() << endl;
    }
}
void loadRooms() {
    ifstream file("rooms.txt");

    double price;
    bool available;
    int i = 0;

    while (file >> price >> available && i < rooms.size()) {
        rooms[i] = Room(i + 1, 1, 1, price, available);
        i++;
    }
}


// ================= Main =================
int main()
{
    loadCustomers();
    loadReservations();
    loadRooms();
    rest.loadMenu();

    while (true)
    {
        int Num;
        cout << "1. Manger\n2.Employee\n3. Customer" << endl;
        cout << "WHO Are You? " << endl;

        cin >> Num;
        while (!cin) {
            cout << "Invalid input. Please try again with an integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> Num;
        }

        while (true) {
            if (Num < 1 || Num > 3) {
                cout << "Invalid choice. Please try again." << endl;
                cout << "1. Manger\n2.Employee\n3. Customer" << endl;
                cin >> Num;
                continue;
            }
            char ans;
            cout << "Confirm choice? (Y/N): ";
            cin >> ans;

            if (ans == 'y' || ans == 'Y')
                break;
        }

        switch (Num)
        {
        case 1:
            Manger();
            break;
        case 2:
            employee(reservations, rooms);
            break;
        case 3:
            customer();
            break;
        default:
            break;
        }
    }

    saveCustomers();
    saveReservations();
    saveRooms();
    rest.saveMenu();
}
