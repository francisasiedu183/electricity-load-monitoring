# Electrical Load Monitoring & Billing System

## Description

This is a simple C++ console program that helps users monitor electrical appliance usage and estimate electricity costs.  
The system allows users to enter appliance details, calculate daily energy consumption, and generate a billing summary.

The program also saves appliance data and billing summaries to text files.

---

## Features

- Add/register appliances
- View all appliances
- Search appliance by name
- Calculate daily electricity usage
- Estimate 30-day electricity cost
- Save data to file
- Load saved data automatically when the program starts

---

## How Energy is Calculated

Energy consumption is calculated using:

kWh per day = (Watts ÷ 1000) × Hours used per day

Electricity cost is calculated as:

Cost = Total kWh × Tariff per kWh

Monthly estimation is based on 30 days.

---

## Files Used

- appliances.txt  
  Stores all appliance records.

- billing_summary.txt  
  Stores saved billing results.

These files are created automatically if they do not exist.

---

## How to Compile and Run

### Using g++ (Command Prompt / Terminal)

g++ main.cpp -o program  
./program

### Using an IDE

1. Create a new C++ project
2. Paste the code into main.cpp
3. Build and run

---

## Menu Options

1. Register appliance
2. View appliances
3. Search appliance
4. Billing
5. Save to file
6. Exit

---

## Example

If you enter:

Appliance: Fan  
Watts: 75  
Hours/day: 8  
Tariff: 0.15

The system will calculate:

Daily energy = 0.6 kWh  
Daily cost = 0.09  
30-day cost = 2.70

---

## Purpose of the Project

This project was created to practice:

- Structures
- Arrays
- File handling
- Input validation
- Basic calculations in C++

---

## License

This project is for educational purposes.
