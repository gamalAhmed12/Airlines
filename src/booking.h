#pragma once
#include "models.h"

//----------------------------------------------------Tickets Booking

char getSeatLetter(int index) {
    return 'A' + index;
}

void initializeSeats(Flight& flight, const Plane& plane) {
    int seatsPerRow = plane.seats.length();
    for (int i = 0; i < plane.rows; i++) {
        for (int j = 0; j < seatsPerRow; j++) {
            flight.seats[i][j] = 'O';
        }
    }
}

void displaySeats(const Flight& flight, const Plane& plane) {
    int seatsPerRow = plane.seats.length();
    cout << "\nSEAT MAP :  (O = Available) , (X = Unavailable)\n";
    for (int i = 0; i < plane.rows; i++) {
        cout << "Row " << i + 1 << ": ";
        for (int j = 0; j < seatsPerRow; j++) {
            char seatLetter = getSeatLetter(j);
            if (flight.seats[i][j] == 'X')
                cout << seatLetter << "(X)  ";
            else
                cout << seatLetter << "(O)  ";
        }
        cout << endl;
    }
}

bool bookSeat(Flight& flight, const Plane& plane, int row, char seatLetter) {
    int seatIndex = seatLetter - 'A';
    int seatsPerRow = plane.seats.length();

    if (row < 1 || row > plane.rows || seatIndex < 0 || seatIndex >= seatsPerRow) {
        cout << "Invalid seat!\n";
        return false;
    }

    if (flight.seats[row - 1][seatIndex] == 'X') {
        cout << "Seat already booked!\n";
        return false;
    }

    flight.seats[row - 1][seatIndex] = 'X';
    cout << "Seat booked successfully!\n";
    return true;
}

void displayBookings(Booking bookings[], int bookingCount) {
    cout << "\n--- Passengers Bookings ---\n";
    if (bookingCount == 0) {
        cout << "No bookings found.\n";
        return;
    }

    for (int i = 0; i < bookingCount; i++) {
        cout << i + 1 << ". Booking ID: " << bookings[i].bookingID
            << " | Passenger: " << bookings[i].passengerName
            << " | Flight: " << bookings[i].flightNumber
            << " | Row: " << bookings[i].row
            << " | Seat: " << bookings[i].seat
            << " | Passport: " << bookings[i].passport << endl;
    }
}