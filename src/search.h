#pragma once
#include "models.h"

//----------------------------------------------------------Search 

void userSearch(Flight flights[], int count, Plane planes[], int planeCount) {
    string keyword;
    int choice;
    cout << "\n--- Flight Search ---" << endl;
    cout << "1. Search by Departure City\n";
    cout << "2. Search by Arrival City\n";
    cout << "3. Search by Date\n";
    cout << "Enter choice: ";
    cin >> choice;
    cout << "Enter keyword: ";
    cin >> keyword;

    cout << "\nSearch result:" << endl;
    bool found = false;
    for (int i = 0; i < count; i++) {
        if ((choice == 1 && flights[i].departureCity == keyword) ||
            (choice == 2 && flights[i].arrivalCity == keyword) ||
            (choice == 3 && flights[i].date == keyword)) {

            string planeModel = flights[i].planeCode;
            for (int p = 0; p < planeCount; p++) {
                if (planes[p].code == flights[i].planeCode) {
                    planeModel = planes[p].model;
                    break;
                }
            }

            cout << "Flight Number: " << flights[i].flightNumber
                << " From: (" << flights[i].departureCity << ')'
                << " | To: (" << flights[i].arrivalCity << ')'
                << " | Date: (" << flights[i].date << ')'
                << " | Plane: (" << planeModel << ')' << endl;
            found = true;
        }
    }
    if (!found) cout << "No matching flights found" << endl;
}

void adminSearch(Flight flights[], int flightCount, Plane planes[], int planeCount) {
    int choice;
    cout << "\n--- Search ---\n";
    cout << "1. Search Planes\n";
    cout << "2. Search Flights\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        string keyword;
        cout << "Enter Aircraft model/code: ";
        cin >> keyword;
        bool found = false;
        for (int i = 0; i < planeCount; i++) {
            if (planes[i].model.find(keyword) != string::npos ||
                planes[i].code.find(keyword) != string::npos) {
                cout << "Aircraft Model: " << planes[i].model
                    << " Code: " << planes[i].code
                    << " Rows: " << planes[i].rows
                    << " Seats: " << planes[i].seats << endl;
                found = true;
            }
        }
        if (!found) cout << "No matching aircraft found\n";
    }
    else if (choice == 2) {
        userSearch(flights, flightCount, planes, planeCount);
    }
}