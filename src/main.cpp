#include "models.h"
#include "file_manager.h"
#include "auth.h"
#include "flights.h"
#include "planes.h"
#include "search.h"
#include "booking.h"

//----------------------------------------------------Main

int main() {
    Admin admin = { "admin", "1234" };

    Plane* planes = nullptr;
    int planeCount = 0;

    Flight* flights = new Flight[MIN_FLIGHTS];
    int flightCount = 0;

    Booking* bookings = new Booking[MIN_FLIGHTS];
    int bookingCount = 0;

    Passenger passengers[50];
    int passengerCount = 0;

    loadPlanes(planes, planeCount);
    loadFlights(flights, flightCount, planes, planeCount);
    loadBookings(bookings, bookingCount);
    loadPassengers(passengers, passengerCount);

    int choice;
    do {
        system("cls");
        cout << "\n========= Flight Management System =========\n";
        cout << "1. Admin Login\n";
        cout << "2. Passenger Login\n";
        cout << "0. Exit\n";
        cout << "===========================================\n";
        cout << "Choose from-->(1,2,0) :";
        cin >> choice;

        if (choice == 1) {
            if (loginAdmin(admin)) {
                int adminChoice;
                do {
                    system("cls");
                    cout << "\n========= Admin Dashboard =========\n";
                    cout << "1. Display All Planes\n";
                    cout << "2. Add New Plane\n";
                    cout << "3. Update Plane Info\n";
                    cout << "4. Display Flights\n";
                    cout << "5. Search\n";
                    cout << "6. Add Flight\n";
                    cout << "7. Display Bookings\n";
                    cout << "8. Edit Flight\n";
                    cout << "0. Logout\n";
                    cout << "===================================\n";
                    cout << "Choose from-->(1,2,3,4,5,6,7,8,0) :";
                    cin >> adminChoice;

                    switch (adminChoice) {
                    case 1: displayAllPlanes(planes, planeCount); system("pause"); break;
                    case 2: planes = addPlane(planes, planeCount); system("pause"); break;
                    case 3: updatePlane(planes, planeCount); system("pause"); break;
                    case 4: displayFlights(flights, flightCount, planes, planeCount); system("pause"); break;
                    case 5: adminSearch(flights, flightCount, planes, planeCount); system("pause"); break;
                    case 6: addFlight(flights, flightCount, planes, planeCount); system("pause"); break;
                    case 7: displayBookings(bookings, bookingCount); system("pause"); break;
                    case 8: editFlight(flights, flightCount, planes, planeCount); system("pause"); break;
                    case 0: cout << "Logging out...\n"; break;
                    default: cout << "Invalid choice!\n"; system("pause"); break;
                    }
                } while (adminChoice != 0);
            }
        }
        else if (choice == 2) {
            int authChoice;
            cout << "\n1. Login\n2. Sign Up\nEnter choice: ";
            cin >> authChoice;

            Passenger* p = nullptr;
            if (authChoice == 1) {
                p = loginPassenger(passengers, passengerCount);
            }
            else if (authChoice == 2) {
                p = signUp(passengers, passengerCount);
            }

            if (p == nullptr) {
                system("pause");
            }
            else {
                int userChoice;
                do {
                    system("cls");
                    cout << "\n======= Passenger Menu =========\n";
                    cout << "1. Search Flights\n";
                    cout << "2. Display Flights\n";
                    cout << "3. Book Seat\n";
                    cout << "0. Logout\n";
                    cout << "================================\n";
                    cout << "Choose from-->(1,2,3,0) :";
                    cin >> userChoice;

                    switch (userChoice) {
                    case 1: userSearch(flights, flightCount, planes, planeCount); system("pause"); break;
                    case 2: displayFlights(flights, flightCount, planes, planeCount); system("pause"); break;
                    case 3: {
                        string flightNum;
                        cout << "Enter Flight Number: ";
                        cin >> flightNum;

                        int index = -1;
                        for (int i = 0; i < flightCount; i++) {
                            if (flights[i].flightNumber == flightNum) {
                                index = i;
                                break;
                            }
                        }

                        if (index == -1) {
                            cout << "Flight not found!\n";
                            system("pause");
                            break;
                        }

                        Plane plane;
                        bool planeFound = false;
                        for (int j = 0; j < planeCount; j++) {
                            if (planes[j].code == flights[index].planeCode) {
                                plane = planes[j];
                                planeFound = true;
                                break;
                            }
                        }

                        if (!planeFound) {
                            cout << "Plane not found!\n";
                            system("pause");
                            break;
                        }

                        displaySeats(flights[index], plane);

                        int row;
                        char seatLetter;
                        cout << "Enter Row Number: ";
                        cin >> row;
                        cout << "Enter Seat Letter: ";
                        cin >> seatLetter;

                        if (bookSeat(flights[index], plane, row, seatLetter)) {
                            bookings[bookingCount].bookingID = bookingCount + 1;
                            bookings[bookingCount].passengerName = p->name;
                            bookings[bookingCount].flightNumber = flightNum;
                            bookings[bookingCount].row = row;
                            bookings[bookingCount].seat = seatLetter;
                            bookings[bookingCount].passport = p->passport;
                            bookingCount++;
                        }
                        system("pause");
                        break;
                    }
                    case 0: cout << "Logging out...\n"; break;
                    default: cout << "Invalid choice!\n"; system("pause"); break;
                    }
                } while (userChoice != 0);
            }
        }

    } while (choice != 0);

    savePlanes(planes, planeCount);
    saveFlights(flights, flightCount, planes, planeCount);
    saveBookings(bookings, bookingCount);
    savePassengers(passengers, passengerCount);

    delete[] flights;
    delete[] bookings;
    delete[] planes;

    cout << "System closed. Data saved.\n";
    return 0;
}