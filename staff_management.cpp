

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Staff {
    string username;
    string password;
    string fullName;
    string role;
};

struct Movie {
    string id;
    string title;
    string genre;
    int    durationMin;
    string rating;
    vector<string> showtimes;
};

struct Booking {
    string code;
    string customerName;
    string movieId;
    string showtime;
    vector<string> seats;
    string status;
};

const string STAFF_FILE    = "staff.txt";
const string MOVIES_FILE   = "movies.txt";
const string BOOKINGS_FILE = "bookings.txt";

vector<Staff>   staffList;
vector<Movie>   movieList;
vector<Booking> bookingList;

Staff currentStaff;

vector<string> splitStr(const string& s, char delim) {
    vector<string> out;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) out.push_back(item);
    return out;
}

string joinStr(const vector<string>& items, char delim) {
    string out;
    for (size_t i = 0; i < items.size(); i++) {
        out += items[i];
        if (i + 1 < items.size()) out += delim;
    }
    return out;
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (cin.eof()) exit(0);
    cin.get();
}

string readLine(const string& prompt) {
    cout << prompt;
    string line;
    if (!getline(cin, line)) { cout << "\nNo more input. Exiting.\n"; exit(0); }
    return line;
}

int readInt(const string& prompt) {
    cout << prompt;
    int val;
    while (!(cin >> val)) {
        if (cin.eof()) { cout << "\nNo more input. Exiting.\n"; exit(0); }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return val;
}

string generateBookingCode() {
    int n = 1000 + rand() % 9000;
    return "CN-" + to_string(n);
}

void seedStaffFile() {
    ofstream f(STAFF_FILE);
    f << "g.lin,pass123,Grace Lin,Box Office\n";
    f << "m.diaz,pass123,Marco Diaz,Floor Supervisor\n";
    f << "o.bello,pass123,Ola Bello,Concessions\n";
}

void seedMoviesFile() {
    ofstream f(MOVIES_FILE);
    f << "m1,Ember Trail,Action/Adventure,118,PG-13,13:00|16:15|19:30|22:00\n";
    f << "m2,The Glass Horizon,Sci-Fi/Drama,132,PG-13,12:30|15:45|20:00\n";
    f << "m3,Nightshift Diner,Comedy,96,PG,14:00|17:20|21:15\n";
    f << "m4,Coral Static,Thriller,104,R,13:45|18:10|21:50\n";
}

void seedBookingsFile() {
    ofstream f(BOOKINGS_FILE);
    f << "CN-7741,Ana Ruiz,m1,19:30,4-2;4-3,confirmed\n";
    f << "CN-7742,Devon Cole,m2,15:45,2-4,pending\n";
    f << "CN-7743,Priya Nair,m3,21:15,5-1;5-2;5-3,checked-in\n";
    f << "CN-7744,Sam Okoye,m4,13:45,1-1,cancelled\n";
}

void loadStaff() {
    ifstream f(STAFF_FILE);
    if (!f.good()) { seedStaffFile(); f.open(STAFF_FILE); }
    staffList.clear();
    string line;
    while (getline(f, line)) {
        if (line.empty()) continue;
        auto p = splitStr(line, ',');
        if (p.size() < 4) continue;
        staffList.push_back({p[0], p[1], p[2], p[3]});
    }
}

void loadMovies() {
    ifstream f(MOVIES_FILE);
    if (!f.good()) { seedMoviesFile(); f.open(MOVIES_FILE); }
    movieList.clear();
    string line;
    while (getline(f, line)) {
        if (line.empty()) continue;
        auto p = splitStr(line, ',');
        if (p.size() < 6) continue;
        Movie m;
        m.id = p[0]; m.title = p[1]; m.genre = p[2];
        m.durationMin = atoi(p[3].c_str()); m.rating = p[4];
        m.showtimes = splitStr(p[5], '|');
        movieList.push_back(m);
    }
}

void loadBookings() {
    ifstream f(BOOKINGS_FILE);
    if (!f.good()) { seedBookingsFile(); f.open(BOOKINGS_FILE); }
    bookingList.clear();
    string line;
    while (getline(f, line)) {
        if (line.empty()) continue;
        auto p = splitStr(line, ',');
        if (p.size() < 6) continue;
        Booking b;
        b.code = p[0]; b.customerName = p[1]; b.movieId = p[2];
        b.showtime = p[3]; b.seats = splitStr(p[4], ';'); b.status = p[5];
        bookingList.push_back(b);
    }
}

void saveBookings() {
    ofstream f(BOOKINGS_FILE, ios::trunc);
    for (auto& b : bookingList) {
        f << b.code << "," << b.customerName << "," << b.movieId << ","
          << b.showtime << "," << joinStr(b.seats, ';') << "," << b.status << "\n";
    }
}

Movie* findMovie(const string& id) {
    for (auto& m : movieList) if (m.id == id) return &m;
    return nullptr;
}

string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

bool login() {
    cout << "\n===================================\n";
    cout << "   CINEMA SYSTEM - STAFF SIGN-IN\n";
    cout << "===================================\n";
    string user = readLine("Username: ");
    string pass = readLine("Password: ");

    for (auto& s : staffList) {
        if (s.username == user && s.password == pass) {
            currentStaff = s;
            return true;
        }
    }
    cout << "\nIncorrect username or password.\n";
    return false;
}

void printBookingRow(const Booking& b) {
    Movie* m = findMovie(b.movieId);
    string title = m ? m->title : b.movieId;
    cout << "  [" << b.code << "] " << b.customerName
         << " - " << title << " @ " << b.showtime
         << " - seats: " << joinStr(b.seats, ',')
         << " - status: " << b.status << "\n";
}

void dashboard() {
    int pending = 0, checked = 0;
    for (auto& b : bookingList) {
        if (b.status == "pending") pending++;
        if (b.status == "checked-in") checked++;
    }
    cout << "\n----- DASHBOARD -----\n";
    cout << "Signed in as: " << currentStaff.fullName << " (" << currentStaff.role << ")\n";
    cout << "Showings today : " << movieList.size() << "\n";
    cout << "Bookings pending : " << pending << "\n";
    cout << "Checked in : " << checked << "\n";
}

void updateStatusMenu(Booking& b) {
    cout << "\nUpdate status for " << b.code << " (current: " << b.status << ")\n";
    cout << "  1. Confirm\n  2. Check in\n  3. Cancel\n  0. Back\n";
    int choice = readInt("Choice: ");
    switch (choice) {
        case 1: b.status = "confirmed"; break;
        case 2: b.status = "checked-in"; break;
        case 3: b.status = "cancelled"; break;
        default: return;
    }
    saveBookings();
    cout << "Status updated to \"" << b.status << "\".\n";
}

void bookingLookup() {
    string q = toLower(readLine("\nSearch by guest name or booking code (blank = show all): "));
    vector<Booking*> matches;
    for (auto& b : bookingList) {
        string hay = toLower(b.customerName + b.code);
        if (q.empty() || hay.find(q) != string::npos) matches.push_back(&b);
    }
    if (matches.empty()) { cout << "No bookings found.\n"; return; }

    cout << "\nResults:\n";
    for (size_t i = 0; i < matches.size(); i++) {
        cout << i + 1 << ". ";
        printBookingRow(*matches[i]);
    }
    int pick = readInt("\nOpen a booking by number (0 to cancel): ");
    if (pick < 1 || pick > (int)matches.size()) return;

    Booking* b = matches[pick - 1];
    Movie* m = findMovie(b->movieId);
    cout << "\n----- BOOKING " << b->code << " -----\n";
    cout << "Guest    : " << b->customerName << "\n";
    cout << "Film     : " << (m ? m->title : b->movieId) << "\n";
    cout << "Showtime : " << b->showtime << "\n";
    cout << "Seats    : " << joinStr(b->seats, ',') << "\n";
    cout << "Status   : " << b->status << "\n";
    updateStatusMenu(*b);
}

void issueWalkInTicket() {
    cout << "\n----- ISSUE WALK-IN TICKET -----\n";
    for (size_t i = 0; i < movieList.size(); i++) {
        cout << i + 1 << ". " << movieList[i].title
             << " (" << movieList[i].genre << ", " << movieList[i].durationMin << " min)\n";
    }
    int mChoice = readInt("Choose a film by number: ");
    if (mChoice < 1 || mChoice > (int)movieList.size()) { cout << "Invalid choice.\n"; return; }
    Movie& m = movieList[mChoice - 1];

    for (size_t i = 0; i < m.showtimes.size(); i++)
        cout << i + 1 << ". " << m.showtimes[i] << "\n";
    int tChoice = readInt("Choose a showtime by number: ");
    if (tChoice < 1 || tChoice > (int)m.showtimes.size()) { cout << "Invalid choice.\n"; return; }
    string time = m.showtimes[tChoice - 1];

    string guest = readLine("Guest name: ");
    string seatsRaw = readLine("Seats (comma separated, e.g. 2-1,2-2): ");
    vector<string> seats = splitStr(seatsRaw, ',');
    for (auto& s : seats) {

        size_t p = s.find_first_not_of(' ');
        if (p != string::npos) s = s.substr(p);
    }

    Booking b;
    b.code = generateBookingCode();
    b.customerName = guest.empty() ? "Walk-in guest" : guest;
    b.movieId = m.id;
    b.showtime = time;
    b.seats = seats;
    b.status = "confirmed";
    bookingList.push_back(b);
    saveBookings();

    cout << "\nTicket issued.\n";
    printBookingRow(b);
}

void viewSchedule() {
    cout << "\n----- TODAY'S SCHEDULE -----\n";
    for (auto& m : movieList) {
        cout << m.title << " (" << m.rating << ", " << m.durationMin << " min)\n";
        cout << "  Showtimes: " << joinStr(m.showtimes, ',') << "\n";
    }
}

void mainMenu() {
    while (true) {
        cout << "\n===================================\n";
        cout << "   CINEMA SYSTEM - STAFF TERMINAL\n";
        cout << "===================================\n";
        cout << "1. Dashboard\n";
        cout << "2. Look up a booking\n";
        cout << "3. Issue a walk-in ticket\n";
        cout << "4. View today's schedule\n";
        cout << "5. Log out\n";
        int choice = readInt("Choose an option: ");

        switch (choice) {
            case 1: dashboard(); pause(); break;
            case 2: bookingLookup(); pause(); break;
            case 3: issueWalkInTicket(); pause(); break;
            case 4: viewSchedule(); pause(); break;
            case 5: return;
            default: cout << "Invalid option.\n";
        }
    }
}

int main() {
    srand((unsigned)time(nullptr));
    loadStaff();
    loadMovies();
    loadBookings();

    cout << "Welcome to the Cinema System staff terminal.\n";
    cout << "(Sample login: g.lin / pass123)\n";

    while (!login()) {
        string retry = readLine("Try again? (y/n): ");
        if (toLower(retry) != "y") return 0;
    }

    cout << "\nLogged in as " << currentStaff.fullName << ".\n";
    mainMenu();

    cout << "\nLogged out. Goodbye.\n";
    return 0;
}
