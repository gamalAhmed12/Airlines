#pragma once
#include "models.h"

//------------------------------------------------File Management

void savePassengers(Passenger passengers[], int passengerCount) {
    ofstream file("data/passengers.txt");
    for (int i = 0; i < passengerCount; i++) {
        file << passengers[i].passport << "\n"
            << passengers[i].password << "\n"
            << passengers[i].name << "\n"
            << passengers[i].phone << "\n"
            << passengers[i].email << "\n";
    }
    file.close();
}

void loadPassengers(Passenger passengers[], int& passengerCount) {
    ifstream file("data/passengers.txt");
    passengerCount = 0;
    string temp;
    while (getline(file, temp)) {
        if (temp.empty()) continue;
        passengers[passengerCount].passport = temp;
        getline(file, passengers[passengerCount].password);
        getline(file, passengers[passengerCount].name);
        getline(file, passengers[passengerCount].phone);
        getline(file, passengers[passengerCount].email);
        passengerCount++;
    }
    file.close();
}

void savePlanes(Plane planes[], int planeCount) {
    ofstream file("data/planes.txt");
    for (int i = 0; i < planeCount; i++) {
        file << planes[i].model << " "
            << planes[i].code << " "
            << planes[i].rows << " "
            << planes[i].seats << endl;
    }
    file.close();
}

void loadPlanes(Plane*& planes, int& planeCount) {
    ifstream file("data/planes.txt");
    planeCount = 0;
    if (!file.is_open()) return;

    planes = new Plane[MIN_PLANES];
    while (file >> planes[planeCount].model
        >> planes[planeCount].code
        >> planes[planeCount].rows
        >> planes[planeCount].seats) {
        planeCount++;
    }
    file.close();
}

void saveFlights(Flight flights[], int flightCount, Plane planes[], int planeCount) {
    ofstream file("data/flights.txt");
    for (int i = 0; i < flightCount; i++) {
        file << flights[i].flightNumber << " "
            << flights[i].departureCity << " "
            << flights[i].arrivalCity << " "
            << flights[i].date << " "
            << flights[i].departureTime << " "
            << flights[i].arrivalTime << " "
            << flights[i].departureAirport << " "
            << flights[i].arrivalAirport << " "
            << flights[i].arrivalDate << " "
            << flights[i].planeCode << endl;

        string seatsFile = "data/" + flights[i].flightNumber + "_seats.txt";
        ofstream seatFile(seatsFile);
        int rows = 0, seatsPerRow = 0;
        for (int p = 0; p < planeCount; p++) {
            if (planes[p].code == flights[i].planeCode) {
                rows = planes[p].rows;
                seatsPerRow = planes[p].seats.length();
                break;
            }
        }
        for (int r = 0; r < rows; r++) {
            for (int s = 0; s < seatsPerRow; s++) {
                seatFile << flights[i].seats[r][s];
            }
            seatFile << endl;
        }
        seatFile.close();
    }
    file.close();
}

void loadFlights(Flight flights[], int& flightCount, Plane planes[], int planeCount) {
    ifstream file("data/flights.txt");
    flightCount = 0;
    while (file >> flights[flightCount].flightNumber
        >> flights[flightCount].departureCity
        >> flights[flightCount].arrivalCity
        >> flights[flightCount].date
        >> flights[flightCount].departureTime
        >> flights[flightCount].arrivalTime
        >> flights[flightCount].departureAirport
        >> flights[flightCount].arrivalAirport
        >> flights[flightCount].arrivalDate
        >> flights[flightCount].planeCode) {

        int rows = 0, seatsPerRow = 0;
        for (int p = 0; p < planeCount; p++) {
            if (planes[p].code == flights[flightCount].planeCode) {
                rows = planes[p].rows;
                seatsPerRow = planes[p].seats.length();
                break;
            }
        }

        string seatsFile = "data/" + flights[flightCount].flightNumber + "_seats.txt";
        ifstream seatFile(seatsFile);
        for (int r = 0; r < rows; r++) {
            string seatLine;
            seatFile >> seatLine;
            for (int s = 0; s < seatsPerRow && s < (int)seatLine.size(); s++) {
                flights[flightCount].seats[r][s] = seatLine[s];
            }
        }
        seatFile.close();
        flightCount++;
    }
    file.close();
}

void saveBookings(Booking bookings[], int bookingCount) {
    ofstream file("data/bookings.txt");
    for (int i = 0; i < bookingCount; i++) {
        file << bookings[i].bookingID << "\n"
            << bookings[i].passengerName << "\n"
            << bookings[i].flightNumber << "\n"
            << bookings[i].row << "\n"
            << bookings[i].seat << "\n"
            << bookings[i].passport << "\n";
    }
    file.close();
}

void loadBookings(Booking bookings[], int& bookingCount) {
    ifstream file("data/bookings.txt");
    bookingCount = 0;
    string temp;
    while (getline(file, temp)) {
        if (temp.empty()) continue;
        bookings[bookingCount].bookingID = stoi(temp);
        getline(file, bookings[bookingCount].passengerName);
        getline(file, bookings[bookingCount].flightNumber);
        getline(file, temp); bookings[bookingCount].row = stoi(temp);
        getline(file, temp); bookings[bookingCount].seat = temp[0];
        getline(file, bookings[bookingCount].passport);
        bookingCount++;
    }
    file.close();
}