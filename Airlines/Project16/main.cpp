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

        string seatsFile = flights[i].flightNumber + "_seats.txt";
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

        string seatsFile = flights[flightCount].flightNumber + "_seats.txt";
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

    ofstream seatFile(f.flightNumber + "_seats.txt");
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