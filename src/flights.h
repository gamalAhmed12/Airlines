#pragma once
#include "models.h"

// ----------------------------------------------------- Admin Dashboard-Part_A

void displayFlights(Flight flights[], int flightCount, Plane planes[], int planeCount) {
    cout << "\n--- Flights Information ---\n";
    if (flightCount == 0) {
        cout << "No flights available.\n";
        return;
    }
    for (int i = 0; i < flightCount; i++) {
        string planeModel = flights[i].planeCode;
        for (int p = 0; p < planeCount; p++) {
            if (planes[p].code == flights[i].planeCode) {
                planeModel = planes[p].model;
                break;
            }
        }

        cout << i + 1 << ". Flight " << flights[i].flightNumber
            << " From: (" << flights[i].departureCity << ')'
            << " | To: (" << flights[i].arrivalCity << ')'
            << " | Date: (" << flights[i].date << ')'
            << " | Departure: (" << flights[i].departureTime << ')'
            << " | Arrival: (" << flights[i].arrivalTime << ')'
            << " | Dep-Airport: (" << flights[i].departureAirport << ')'
            << " | Arr-Airport: (" << flights[i].arrivalAirport << ')'
            << " | ArrivalDate: (" << flights[i].arrivalDate << ')'
            << " | Plane: (" << planeModel << ')' << endl;
    }
}

void addFlight(Flight flights[], int& flightCount, Plane planes[], int planeCount) {
    Flight f;
    cout << "Enter Flight Number: ";
    cin >> f.flightNumber;
    cin.ignore();
    cout << "Enter Departure City: ";
    getline(cin, f.departureCity);
    cout << "Enter Arrival City: ";
    getline(cin, f.arrivalCity);
    cout << "Enter Date (YYYY-MM-DD): ";
    cin >> f.date;
    cout << "Enter Departure Time (HH:MM): ";
    cin >> f.departureTime;
    cout << "Enter Arrival Time (HH:MM): ";
    cin >> f.arrivalTime;
    cin.ignore();
    cout << "Enter Dep-Airport: ";
    getline(cin, f.departureAirport);
    cout << "Enter Arr-Airport: ";
    getline(cin, f.arrivalAirport);
    cout << "Enter Arrival Date (YYYY-MM-DD): ";
    cin >> f.arrivalDate;

    cout << "Available Planes:\n";
    for (int p = 0; p < planeCount; p++)
        cout << "  " << planes[p].model << " (Code: " << planes[p].code << ")\n";

    cout << "Enter Plane Code: ";
    cin >> f.planeCode;

    int rows = 0, seatsPerRow = 0;
    for (int p = 0; p < planeCount; p++) {
        if (planes[p].code == f.planeCode) {
            rows = planes[p].rows;
            seatsPerRow = planes[p].seats.length();
            break;
        }
    }

    if (rows == 0) {
        cout << "Plane code not found! Flight not added.\n";
        return;
    }

    ofstream seatFile("data/" + f.flightNumber + "_seats.txt");
    for (int r = 0; r < rows; r++) {
        for (int s = 0; s < seatsPerRow; s++) {
            seatFile << 'O';
        }
        seatFile << endl;
    }
    seatFile.close();

    flights[flightCount] = f;
    flightCount++;

    cout << "Flight added successfully!\n";
}

void editFlight(Flight flights[], int flightCount, Plane planes[], int planeCount) {
    if (flightCount == 0) {
        cout << "No flights to edit.\n";
        return;
    }

    displayFlights(flights, flightCount, planes, planeCount);

    cout << "Enter flight number to edit: ";
    int index;
    cin >> index;

    if (index <= 0 || index > flightCount) {
        cout << "Invalid selection.\n";
        return;
    }

    Flight& f = flights[index - 1];
    cin.ignore();
    cout << "Enter new Departure City: ";
    getline(cin, f.departureCity);
    cout << "Enter new Arrival City: ";
    getline(cin, f.arrivalCity);
    cout << "Enter new Date (YYYY-MM-DD): ";
    cin >> f.date;
    cout << "Enter new Departure Time (HH:MM): ";
    cin >> f.departureTime;
    cout << "Enter new Arrival Time (HH:MM): ";
    cin >> f.arrivalTime;
    cin.ignore();
    cout << "Enter new Dep-Airport: ";
    getline(cin, f.departureAirport);
    cout << "Enter new Arr-Airport: ";
    getline(cin, f.arrivalAirport);
    cout << "Enter new Arrival Date (YYYY-MM-DD): ";
    cin >> f.arrivalDate;

    cout << "Available Planes:\n";
    for (int p = 0; p < planeCount; p++)
        cout << "  " << planes[p].model << " (Code: " << planes[p].code << ")\n";
    cout << "Enter new Plane Code: ";
    cin >> f.planeCode;

    cout << "Flight updated successfully!\n";
}