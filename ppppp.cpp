#include <iostream>
#include <string>
using namespace std;

// ===== Base Class (Encapsulation) =====
class Person {
protected:
    string name;
    int age;
public:
    Person() {}
    Person(string n, int a) {
        name = n;
        age = a;
    }

    virtual void displayInfo() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }

    int getAge() {
        return age;
    }
};

// ===== Patient Class =====
class Patient : public Person {
private:
    string diagnosis;
    int visits[10];   // fixed-size array
    int numVisits;
    static int patientCount;

public:
    Patient() {}
    Patient(string n, int a, string d, int v) : Person(n, a) {
        diagnosis = d;
        numVisits = v > 10 ? 10 : v; // max 10 visits
        for (int i = 0; i < numVisits; i++) visits[i] = 0;
        patientCount++;
    }

    void addVisit(int index, int value) {
        if (index < numVisits) {
            visits[index] = value;
        }
    }

    float getAverageVisits() {
        int sum = 0;
        for (int i = 0; i < numVisits; i++) {
            sum += visits[i];
        }
        return (numVisits > 0) ? (float)sum / numVisits : 0;
    }

    // Prefix & Postfix example
    void ageOperations() {
        cout << "Age before ++: " << age << endl;
        cout << "Postfix age++: " << age++ << endl;
        cout << "Now age = " << age << endl;
        cout << "Prefix ++age: " << ++age << endl;
    }

    void displayInfo() override {
        cout << "Patient Name: " << name
            << ", Age: " << age
            << ", Diagnosis: " << diagnosis
            << ", Avg Visits: " << getAverageVisits() << endl;
    }

    static int getPatientCount() {
        return patientCount;
    }
};
int Patient::patientCount = 0;

// ===== Inheritance Example =====
class EmergencyPatient : public Patient {
private:
    int severityLevel;
public:
    EmergencyPatient() {}
    EmergencyPatient(string n, int a, string d, int v, int s)
        : Patient(n, a, d, v), severityLevel(s) {
    }

    void displayInfo() override {
        Patient::displayInfo();
        cout << "Severity Level: " << severityLevel << endl;
    }
};

// ===== MAIN FUNCTION =====
int main() {
    const int MAX_PATIENTS = 20;
    Patient patients[MAX_PATIENTS];
    EmergencyPatient emergencies[MAX_PATIENTS];
    int normalCount = 0, emergencyCount = 0;

    int choice;

    do {
        cout << "\n--- Hospital Menu ---\n";
        cout << "1. Add Patient\n2. Add Emergency Patient\n3. Show All Patients\n4. Average Age\n5. Exit\n";
        cin >> choice;

        if (choice == 1 && normalCount < MAX_PATIENTS) {
            string name, diag;
            int age, visits;
            cout << "Enter name, age, diagnosis, number of visits: ";
            cin >> name >> age >> diag >> visits;

            patients[normalCount] = Patient(name, age, diag, visits);

            for (int j = 0; j < visits && j < 10; j++) {
                int v;
                cout << "Enter visit " << j + 1 << ": ";
                cin >> v;
                patients[normalCount].addVisit(j, v);
            }

            patients[normalCount].ageOperations();
            normalCount++;
        }
        else if (choice == 2 && emergencyCount < MAX_PATIENTS) {
            string name, diag;
            int age, visits, severity;
            cout << "Enter name, age, diagnosis, number of visits, severity(1-10): ";
            cin >> name >> age >> diag >> visits >> severity;

            emergencies[emergencyCount] = EmergencyPatient(name, age, diag, visits, severity);

            for (int j = 0; j < visits && j < 10; j++) {
                int v;
                cout << "Enter visit " << j + 1 << ": ";
                cin >> v;
                emergencies[emergencyCount].addVisit(j, v);
            }

            emergencies[emergencyCount].ageOperations();
            emergencyCount++;
        }
        else if (choice == 3) {
            cout << "\n--- Patient List ---\n";
            for (int j = 0; j < normalCount; j++) {
                patients[j].displayInfo();
            }
            for (int j = 0; j < emergencyCount; j++) {
                emergencies[j].displayInfo();
            }
            cout << "Total Patients: " << Patient::getPatientCount() << endl;
        }
        else if (choice == 4) {
            int totalAge = 0, totalCount = normalCount + emergencyCount;
            for (int j = 0; j < normalCount; j++) totalAge += patients[j].getAge();
            for (int j = 0; j < emergencyCount; j++) totalAge += emergencies[j].getAge();

            if (totalCount > 0)
                cout << "Average Age of Patients: " << (float)totalAge / totalCount << endl;
        }

    } while (choice != 5);

    return 0;
}