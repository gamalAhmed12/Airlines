#pragma once
#include "models.h"

//--------------------------------------------------Admin & User

bool loginAdmin(const Admin& admin) {
    string user, pass;
    cout << "\n=== Admin Login ===\n";
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;

    if (user == admin.username && pass == admin.password) {
        cout << "Admin login successful!\n";
        return true;
    }
    else {
        cout << "Invalid admin login!\n";
        return false;
    }
}

Passenger* signUp(Passenger passengers[], int& passengerCount) {
    Passenger p;
    cout << "\n=== Sign Up ===\n";
    cout << "Name: ";
    cin.ignore();
    getline(cin, p.name);
    cout << "Phone: ";
    cin >> p.phone;
    cout << "Email: ";
    cin.ignore();
    getline(cin, p.email);
    cout << "Passport: ";
    cin >> p.passport;
    cout << "Password: ";
    cin >> p.password;
    while (p.password.length() < 8) {
        cout << "Password must be at least 8 characters! Try again: ";
        cin >> p.password;
    }

    passengers[passengerCount] = p;
    passengerCount++;

    cout << "Sign up successful!\n";
    return &passengers[passengerCount - 1];
}

Passenger* loginPassenger(Passenger passengers[], int passengerCount) {
    string passport, password;
    cout << "\n=== Passenger Login ===\n";
    cout << "Passport: ";
    cin >> passport;
    cout << "Password: ";
    cin >> password;

    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i].passport == passport && passengers[i].password == password) {
            cout << "Login successful! Welcome " << passengers[i].name << "\n";
            return &passengers[i];
        }
    }
    cout << "Invalid passport or password!\n";
    return nullptr;
}