#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// Files (same names as yours)
const string APPLIANCES_FILE = "appliances.txt";
const string BILLING_FILE    = "billing_summary.txt";

// Limits
const int MAX_APPLIANCES = 100;

struct Appliance {
    string name;
    double watts;
    double hours;
};

// ---------- small helpers ----------
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
        if (cin >> v) {
            flushInput();
            return v;
        }
        cout << "Invalid number. Try again.\n";
        flushInput();
    }
}

double getDouble(const string& prompt) {
    double v;
    while (true) {
        cout << prompt;
        if (cin >> v) {
            flushInput();
            return v;
        }
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

// ---------- calculations ----------
double calcKwhPerDay(const Appliance& a) {
    return (a.watts / 1000.0) * a.hours;
}

double calcTotalKwhPerDay(const Appliance list[], int count) {
    double sum = 0.0;
    for (int i = 0; i < count; i++) sum += calcKwhPerDay(list[i]);
    return sum;
}

// ---------- file handling ----------
void saveApplianceFile(const Appliance list[], int count) {
    ofstream out(APPLIANCES_FILE.c_str());
    if (!out.is_open()) {
        cout << "Error writing " << APPLIANCES_FILE << "\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        out << list[i].name << "|" << list[i].watts << "|" << list[i].hours << "\n";
    }
    out.close();
}

void loadApplianceFile(Appliance list[], int& count) {
    count = 0;
    ifstream in(APPLIANCES_FILE.c_str());
    if (!in.is_open()) return;

    string line;
    while (getline(in, line)) {
        line = trimText(line);
        if (line.empty()) continue;

        int p1 = (int)line.find('|');
        int p2 = (p1 == -1) ? -1 : (int)line.find('|', p1 + 1);
        if (p1 == -1 || p2 == -1) continue;

        string name = trimText(line.substr(0, p1));
        string wStr = trimText(line.substr(p1 + 1, p2 - p1 - 1));
        string hStr = trimText(line.substr(p2 + 1));

        if (name.empty()) continue;

        double w = 0.0, h = 0.0;
        try {
            w = stod(wStr);
            h = stod(hStr);
        } catch (...) {
            continue;
        }

        if (w <= 0 || h < 0 || h > 24) continue;

        if (count < MAX_APPLIANCES) {
            list[count].name = name;
            list[count].watts = w;
            list[count].hours = h;
            count++;
        }
    }
    in.close();
}

void appendBillingSummary(double tariff, int count,
                          double dayKwh, double dayCost,
                          double monthKwh, double monthCost) {
    ofstream out(BILLING_FILE.c_str(), ios::app);
    if (!out.is_open()) {
        cout << "Error appending " << BILLING_FILE << "\n";
        return;
    }

    out << "================ BILLING SUMMARY ================\n";
    out << fixed << setprecision(2);
    out << "Tariff: " << tariff << " per kWh\n";
    out << "Appliances count: " << count << "\n";
    out << "Total daily energy: " << dayKwh << " kWh\n";
    out << "Total daily cost:  " << dayCost << "\n";
    out << "Estimated 30-day energy: " << monthKwh << " kWh\n";
    out << "Estimated 30-day cost:  " << monthCost << "\n";
    out << "=================================================\n\n";

    out.close();
}

// ---------- features ----------
void showMenu() {
    cout << "\n1. Register appliance\n";
    cout << "2. View appliances\n";
    cout << "3. Search appliance\n";
    cout << "4. Billing\n";
    cout << "5. Save to file\n";
    cout << "6. Exit\n";
}

void registerAppliance(Appliance list[], int& count) {
    if (count >= MAX_APPLIANCES) {
        cout << "Limit reached.\n";
        return;
    }

    Appliance a;
    a.name = getNonEmptyLine("Name: ");

    do { a.watts = getDouble("Watts (>0): "); } while (a.watts <= 0);
    do { a.hours = getDouble("Hours/day (0-24): "); } while (a.hours < 0 || a.hours > 24);

    list[count] = a;
    count++;

    saveApplianceFile(list, count);
    cout << "Saved.\n";
}

void viewAppliances(const Appliance list[], int count) {
    if (count == 0) {
        cout << "No appliances.\n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << left << setw(4) << "#"
         << setw(25) << "Name"
         << setw(10) << "Watts"
         << setw(10) << "Hours"
         << setw(10) << "kWh/day"
         << "\n";

    for (int i = 0; i < count; i++) {
        cout << left << setw(4) << (i + 1)
             << setw(25) << list[i].name
             << setw(10) << list[i].watts
             << setw(10) << list[i].hours
             << setw(10) << calcKwhPerDay(list[i])
             << "\n";
    }
}

void searchAppliance(const Appliance list[], int count) {
    if (count == 0) {
        cout << "No appliances.\n";
        return;
    }

    string q = toLowerText(getNonEmptyLine("Search name: "));
    bool found = false;

    cout << fixed << setprecision(2);
    for (int i = 0; i < count; i++) {
        string nm = toLowerText(list[i].name);
        if (nm.find(q) != string::npos) {
            cout << "- " << list[i].name
                 << " | " << list[i].watts << " W"
                 << " | " << list[i].hours << " hrs"
                 << " | " << calcKwhPerDay(list[i]) << " kWh/day\n";
            found = true;
        }
    }

    if (!found) cout << "No match.\n";
}

void doBilling(const Appliance list[], int count) {
    if (count == 0) {
        cout << "No appliances. Add some first.\n";
        return;
    }

    double tariff;
    do { tariff = getDouble("Tariff per kWh (>0): "); } while (tariff <= 0);

    double dayKwh = calcTotalKwhPerDay(list, count);
    double dayCost = dayKwh * tariff;
    double monthKwh = dayKwh * 30.0;
    double monthCost = dayCost * 30.0;

    cout << fixed << setprecision(2);
    cout << "\nTariff: " << tariff << " per kWh\n";
    cout << "Daily energy: " << dayKwh << " kWh\n";
    cout << "Daily cost:   " << dayCost << "\n";
    cout << "30-day energy: " << monthKwh << " kWh\n";
    cout << "30-day cost:   " << monthCost << "\n";

    cout << "Save summary to billing_summary.txt? (y/n): ";
    char ch;
    cin >> ch;
    flushInput();

    if (ch == 'y' || ch == 'Y') {
        appendBillingSummary(tariff, count, dayKwh, dayCost, monthKwh, monthCost);
        cout << "Billing summary saved.\n";
    } else {
        cout << "Not saved.\n";
    }
}

// ---------- main ----------
int main() {
    Appliance appliances[MAX_APPLIANCES];
    int count = 0;

    loadApplianceFile(appliances, count);

    cout << "Electrical Load Monitoring & Billing System\n";
    cout << "Loaded appliances: " << count << "\n";

    while (true) {
        showMenu();
        int choice = getInt("Choose (1-6): ");

        if (choice == 1) {
            registerAppliance(appliances, count);
        } else if (choice == 2) {
            viewAppliances(appliances, count);
        } else if (choice == 3) {
            searchAppliance(appliances, count);
        } else if (choice == 4) {
            doBilling(appliances, count);
        } else if (choice == 5) {
            saveApplianceFile(appliances, count);
            cout << "Saved to " << APPLIANCES_FILE << ".\n";
        } else if (choice == 6) {
            saveApplianceFile(appliances, count);
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}