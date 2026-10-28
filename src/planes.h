#pragma once
#include "models.h"

// -----------------------------------------------------Admin Dashboard-Part_b

void displayAllPlanes(Plane* planes, int planeCount) {
    cout << "\n--- Current Planes Information ---\n";
    if (planeCount == 0) {
        cout << "No planes available.\n";
        return;
    }
    for (int i = 0; i < planeCount; i++) {
        cout << i + 1 << ". " << planes[i].model << " (" << planes[i].code
            << ")" << " | Rows " << planes[i].rows << " | Seats: (" << planes[i].seats << ')' << endl;
    }
}

Plane* addPlane(Plane* planes, int& planeCount) {
    Plane* newPlanes = new Plane[planeCount + 1];

    for (int i = 0; i < planeCount; i++) {
        newPlanes[i] = planes[i];
    }

    delete[] planes;

    cout << "Enter Model: ";
    cin >> newPlanes[planeCount].model;
    cout << "Enter Code: ";
    cin >> newPlanes[planeCount].code;
    cout << "Enter Number of Rows: ";
    cin >> newPlanes[planeCount].rows;
    cout << "Enter Seat Letters (example : ABCDEF): ";
    cin >> newPlanes[planeCount].seats;

    planeCount++;

    cout << "Plane added successfully!\n";
    return newPlanes;
}

void updatePlane(Plane* planes, int planeCount) {
    if (planeCount == 0) {
        cout << "No planes to update.\n";
        return;
    }

    for (int i = 0; i < planeCount; i++) {
        cout << i + 1 << ". " << planes[i].model << " (" << planes[i].code << ")\n";
    }

    cout << "Enter plane number to edit: ";
    int index;
    cin >> index;

    if (index <= 0 || index > planeCount) {
        cout << "Invalid selection.\n";
        return;
    }

    Plane& p = planes[index - 1];
    cout << "Enter new Model: ";
    cin >> p.model;
    cout << "Enter new Code: ";
    cin >> p.code;
    cout << "Enter new Rows: ";
    cin >> p.rows;
    cout << "Enter new Seat Letters: ";
    cin >> p.seats;

    cout << "Plane updated successfully!\n";
}