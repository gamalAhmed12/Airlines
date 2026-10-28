# Airlines Management System

A command-line flight reservation and fleet management system written in C++ using Structured Programming concepts. The application uses a modular header architecture and flat-file storage to handle flight scheduling, aircraft configurations, and passenger seat bookings.

## Features

- **Flight Management:** Add, update, and list aircraft models, codes, row capacities, and seat layouts.
- **Flight Scheduling:** Create and modify flight records, link flights to specific aircraft codes, and initialize seat maps.
- **Reservation System:** Interactive 2D seat map display (`O` for available, `X` for occupied) with validation for row and seat boundaries.
- **Search & Filtering:** Query aircraft by model/code or search flights by departure city, destination, or date.
- **Role-Based Access:** Separate workflows for administrators and passengers, including passenger registration and login via passport credentials.
- **File Persistence:** Reads from and writes to local text files on startup and exit to preserve state across sessions.

## Project Structure

```text
Airlines/
├── data/
│   ├── bookings.txt        # Reservation records
│   ├── flights.txt         # Scheduled flights metadata
│   ├── passengers.txt      # Registered passenger accounts
│   ├── planes.txt          # Aircraft fleet specifications
│   └── *_seats.txt         # Per-flight seat availability matrices
├── src/
│   ├── models.h            # Data structures and global constants
│   ├── file_manager.h      # File I/O serialization routines
│   ├── auth.h              # Admin and passenger authentication
│   ├── flights.h           # Flight CRUD operations
│   ├── planes.h            # Aircraft CRUD operations
│   ├── search.h            # Search and filtering functions
│   ├── booking.h           # Seat map rendering and booking logic
│   └── main.cpp            # Entry point and menu loop
└── README.md
