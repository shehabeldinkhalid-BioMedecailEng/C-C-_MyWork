#pragma once
#include <string>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

// -------------------- CONSTANTS --------------------
const int O_NEG_LIMIT = 5;

// -------------------- STRUCTS --------------------
struct BloodUnit {
    int id;
    string type;
    string expiration;
};

struct Hospital {
    string name;
    int oNegCount = 0;
};

struct AllocationLog {
    string hospital;
    string requested;
    string allocated;
    int unitID;
    string reason;
};

// -------------------- COMPARATOR --------------------
struct CompareByExpiration {
    bool operator()(const BloodUnit& a, const BloodUnit& b) {
        return a.expiration > b.expiration; // earliest expiration first
    }
};

// -------------------- GLOBAL DATA --------------------
map<string, priority_queue<BloodUnit, vector<BloodUnit>, CompareByExpiration>> inventory;
map<string, Hospital> hospitals;
vector<AllocationLog> logs;
int unitCounter = 1;

// -------------------- VALID BLOOD TYPES --------------------
vector<string> validTypes = {
    "A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"
};

// -------------------- VALIDATION --------------------
bool isValidBloodType(string type)
{
    return find(validTypes.begin(), validTypes.end(), type) != validTypes.end();
}

// -------------------- COMPATIBILITY --------------------
vector<string> getCompatible(string type)
{
    if (type == "O-")  return { "O-" };
    if (type == "O+")  return { "O+", "O-" };
    if (type == "A-")  return { "A-", "O-" };
    if (type == "A+")  return { "A+", "A-", "O+", "O-" };
    if (type == "B-")  return { "B-", "O-" };
    if (type == "B+")  return { "B+", "B-", "O+", "O-" };
    if (type == "AB-") return { "AB-", "A-", "B-", "O-" };
    if (type == "AB+") return { "AB+", "AB-", "A+", "A-", "B+", "B-", "O+", "O-" };
    return {};
}

// -------------------- ADD BLOOD --------------------
string addBlood(string type, string expiration)
{
    if (!isValidBloodType(type))
        return "Invalid blood type";

    BloodUnit b;
    b.id = unitCounter++;
    b.type = type;
    b.expiration = expiration;

    inventory[type].push(b);

    return "Blood unit added successfully";
}

// -------------------- REQUEST BLOOD --------------------
string requestBlood(string hospitalName, string reqType)
{
    if (!isValidBloodType(reqType))
        return "Invalid blood type requested";

    if (hospitals.find(hospitalName) == hospitals.end())
        hospitals[hospitalName] = Hospital{ hospitalName };

    Hospital& h = hospitals[hospitalName];
    vector<string> compatible = getCompatible(reqType);

    for (string type : compatible)
    {
        if (!inventory[type].empty())
        {
            if (type == "O-" && h.oNegCount >= O_NEG_LIMIT)
                return "O- limit reached for this hospital";

            BloodUnit unit = inventory[type].top();
            inventory[type].pop();

            if (type == "O-")
                h.oNegCount++;

            logs.push_back({
                hospitalName,
                reqType,
                type,
                unit.id,
                (type == reqType ? "Exact Match" : "Compatible Substitute (FIFO by Expiration)")
                });

            return "Allocated Unit ID " + to_string(unit.id) +
                " (" + type + "), Exp: " + unit.expiration;
        }
    }

    return "No compatible blood available";
}

// -------------------- INVENTORY DATA --------------------
vector<pair<string, int>> getInventoryData()
{
    vector<pair<string, int>> result;

    for (auto& p : inventory)
        result.push_back({ p.first, (int)p.second.size() });

    return result;
}

// -------------------- LOG DATA --------------------
vector<AllocationLog> getLogs()
{
    return logs;
}
