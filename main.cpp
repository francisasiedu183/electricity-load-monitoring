#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

const string APPLIANCES_FILE = "appliances.txt";
const string BILLING_FILE    = "billing_summary.txt";
const int MAX_APPLIANCES     = 100;

struct Appliance {
    string name;
    double watts;
    double hours;
};

// Clears bad input + removes leftover characters
void flushInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Reads an integer safely
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

// Reads a double safely
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

// Shows menu
void showMenu() {
    cout << "\n1. Register appliance\n";
    cout << "2. View appliances\n";
    cout << "3. Search appliance\n";
    cout << "4. Billing\n";
    cout << "5. Save to file\n";
    cout << "6. Exit\n";
}

int main() {
    cout << "Electrical Load Monitoring & Billing System\n";
    cout << "Loaded appliances: 0\n"; // file loading comes later

    while (true) {
        showMenu();
        int choice = getInt("Choose (1-6): ");

        if (choice == 1) {
            cout << "[Part 1] Register appliance (coming in Part 3)\n";
        }
        else if (choice == 2) {
            cout << "[Part 1] View appliances (coming in Part 4)\n";
        }
        else if (choice == 3) {
            cout << "[Part 1] Search appliance (coming in Part 5)\n";
        }
        else if (choice == 4) {
            cout << "[Part 1] Billing (coming in Part 8)\n";
        }
        else if (choice == 5) {
            cout << "[Part 1] Save to file (coming in Part 6)\n";
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