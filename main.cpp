#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <fstream>

using namespace std;

const string APPLIANCES_FILE = "appliances.txt";
const string BILLING_FILE    = "billing_summary.txt";
const int MAX_APPLIANCES     = 100;

struct Appliance {
    string name;
    double watts;
    double hours;
};

void flushInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string trimText(const string& s) {
    int start = 0;
    int end = (int)s.size() - 1;

    while (start <= end && (s[start] == ' ' || s[start] == '\t' || s[start] == '\r' || s[start] == '\n')) start++;
    while (end >= start && (s[end] == ' ' || s[end] == '\t' || s[end] == '\r' || s[end] == '\n')) end--;

    if (start > end) return "";
    return s.substr(start, end - start + 1);
}

string toLowerText(string s) {
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') s[i] = char(s[i] - 'A' + 'a');
    }
    return s;
}

int getInt(const string& prompt) {
    int v;
    while (true) {
        cout << prompt;
        if (cin >> v) { flushInput(); return v; }
        cout << "Invalid number. Try again.\n";
        flushInput();
    }
}

double getDouble(const string& prompt) {
    double v;
    while (true) {
        cout << prompt;
        if (cin >> v) { flushInput(); return v; }
        cout << "Invalid number. Try again.\n";
        flushInput();
    }
}

string getNonEmptyLine(const string& prompt) {
    while (true) {
        cout << prompt;
        string s;
        getline(cin, s);
        s = trimText(s);
        if (!s.empty()) return s;
        cout << "Input must not be empty.\n";
    }
}

void showMenu() {
    cout << "\n1. Register appliance\n";
    cout << "2. View appliances\n";
    cout << "3. Search appliance\n";
    cout << "4. Billing\n";
    cout << "5. Save to file\n";
    cout << "6. Exit\n";
}

double kwhPerDay(const Appliance& a) {
    return (a.watts / 1000.0) * a.hours;
}

double totalKwhPerDay(const Appliance arr[], int count) {
    double total = 0.0;
    for (int i = 0; i < count; i++) total += kwhPerDay(arr[i]);
    return total;
}

void registerAppliance(Appliance arr[], int& count) {
    if (count >= MAX_APPLIANCES) {
        cout << "Limit reached.\n";
        return;
    }

    Appliance a;
    a.name = getNonEmptyLine("Name: ");
    do { a.watts = getDouble("Watts (>0): "); } while (a.watts <= 0);
    do { a.hours = getDouble("Hours/day (0-24): "); } while (a.hours < 0 || a.hours > 24);

    arr[count] = a;
    count++;

    cout << "Appliance registered (in memory).\n";
}

void viewAppliances(const Appliance arr[], int count) {
    if (count == 0) {
        cout << "No appliances.\n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << left << setw(4)  << "#"
         << setw(25) << "Name"
         << setw(10) << "Watts"
         << setw(10) << "Hours"
         << setw(10) << "kWh/day"
         << "\n";

    for (int i = 0; i < count; i++) {
        cout << left << setw(4)  << (i + 1)
             << setw(25) << arr[i].name
             << setw(10) << arr[i].watts
             << setw(10) << arr[i].hours
             << setw(10) << kwhPerDay(arr[i])
             << "\n";
    }
}

void searchAppliances(const Appliance arr[], int count) {
    if (count == 0) {
        cout << "No appliances.\n";
        return;
    }

    string q = toLowerText(getNonEmptyLine("Search name: "));
    bool found = false;

    cout << fixed << setprecision(2);
    for (int i = 0; i < count; i++) {
        string nm = toLowerText(arr[i].name);
        if (nm.find(q) != string::npos) {
            cout << "- " << arr[i].name
                 << " | " << arr[i].watts << " W"
                 << " | " << arr[i].hours << " hrs"
                 << " | " << kwhPerDay(arr[i]) << " kWh/day\n";
            found = true;
        }
    }

    if (!found) cout << "No match.\n";
}

// -------- Part 6 addition --------
void saveAppliancesToFile(const Appliance arr[], int count) {
    ofstream out(APPLIANCES_FILE.c_str());
    if (!out.is_open()) {
        cout << "Error writing " << APPLIANCES_FILE << "\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        out << arr[i].name << "|" << arr[i].watts << "|" << arr[i].hours << "\n";
    }

    out.close();
    cout << "Saved to " << APPLIANCES_FILE << ".\n";
}
// --------------------------------

int main() {
    Appliance appliances[MAX_APPLIANCES];
    int count = 0;

    cout << "Electrical Load Monitoring & Billing System\n";
    cout << "Loaded appliances: " << count << "\n";

    while (true) {
        showMenu();
        int choice = getInt("Choose (1-6): ");

        if (choice == 1) {
            registerAppliance(appliances, count);
        }
        else if (choice == 2) {
            viewAppliances(appliances, count);
        }
        else if (choice == 3) {
            searchAppliances(appliances, count);
        }
        else if (choice == 4) {
            cout << "[Part 6] Billing (coming in Part 8)\n";
        }
        else if (choice == 5) {
            saveAppliancesToFile(appliances, count);
        }
        else if (choice == 6) {
            cout << "Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
