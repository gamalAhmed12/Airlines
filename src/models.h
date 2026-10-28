#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <cstdlib>
using namespace std;

const int MIN_PLANES = 25;
const int MIN_FLIGHTS = 50;
const int ROWS = 50;
const int SEATS = 6;

//-----------------------------------------Data Architect

struct Plane {
    string model{};
    string code{};
    int rows{};
    string seats{};
};

struct Flight {
    string flightNumber{};
    string departureCity{};
    string arrivalCity{};
    string date{};
    string departureTime{};
    string arrivalTime{};
    string departureAirport{};
    string arrivalAirport{};
    string arrivalDate{};
    string planeCode{};
    string seatsFile{};
    char seats[ROWS][SEATS]{};
};

struct Booking {
    int bookingID{};
    string passengerName{};
    string flightNumber{};
    int row{};
    char seat{};
    string passport{};
};

struct Admin {
    string username{};
    string password{};
};

struct Passenger {
    string name{};
    string phone{};
    string email{};
    string passport{};
    string password{};
};