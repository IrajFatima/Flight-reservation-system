#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Seat {
    int seatNumber;
    bool isBooked;

    Seat(int num) : seatNumber(num), isBooked(false) {}
};

struct Flight {
    string flightNumber;
    string destination;
    string departureTime;
    vector<Seat> seats;

    Flight(string fn, string dest, string dt, int seatCount) 
        : flightNumber(fn), destination(dest), departureTime(dt) {
        for (int i = 1; i <= seatCount; ++i) {
            seats.push_back(Seat(i));
        }
    }
};

struct Reservation {
    string passengerName;
    string flightNumber;
    int seatNumber;

    Reservation(string pname, string fnum, int snum) 
        : passengerName(pname), flightNumber(fnum), seatNumber(snum) {}

    bool operator==(const Reservation& other) const {
        return passengerName == other.passengerName &&
               flightNumber == other.flightNumber &&
               seatNumber == other.seatNumber;
    }
};

vector<Flight> flights;
vector<Reservation> reservations;

void addFlight() {
    string flightNumber, destination, departureTime;
    int seatCount;
    cout << "Enter flight number: ";
    cin >> flightNumber;
    cout << "Enter destination: ";
    cin >> destination;
    cout << "Enter departure time: ";
    cin >> departureTime;
    cout << "Enter number of seats: ";
    cin >> seatCount;
    flights.push_back(Flight(flightNumber, destination, departureTime, seatCount));
    cin.ignore(); // Clear the input buffer
}

void bookSeat() {
    string passengerName, flightNumber;
    int seatNumber;
    cout << "Enter passenger name: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, passengerName);
    cout << "Enter flight number: ";
    getline(cin, flightNumber);
    cout << "Enter seat number: ";
    cin >> seatNumber;
    for (auto &flight : flights) {
        if (flight.flightNumber == flightNumber) {
            if (seatNumber > 0 && seatNumber <= flight.seats.size() && !flight.seats[seatNumber-1].isBooked) {
                flight.seats[seatNumber-1].isBooked = true;
                reservations.push_back(Reservation(passengerName, flightNumber, seatNumber));
                cout << "<----Seat has been reserved successfully---->" << endl;
                return;
            }
            cout << "<---Seat number invalid or already booked--->" << endl;
            return;
        }
    }
    cout << "<---Flight not found--->" << endl;
}

void cancelBooking() {
    string passengerName, flightNumber;
    cout << "Enter flight number: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, flightNumber);
    cout << "Enter passenger name: ";
    getline(cin, passengerName);
    for (auto &res : reservations) {
        if (res.passengerName == passengerName && res.flightNumber == flightNumber) {
            for (auto &flight : flights) {
                if (flightNumber == flight.flightNumber) {
                    flight.seats[res.seatNumber-1].isBooked = false;
                    reservations.erase(remove(reservations.begin(), reservations.end(), res), reservations.end());
                    cout << "<----Reservation has been cancelled successfully---->" << endl;
                    return;
                }
            }
        }
    }
    cout << "Booking not found" << endl;
}

void viewReservations() {
    for (const auto &res : reservations) {
        cout << "Passenger name: " << res.passengerName 
             << ", Flight number: " << res.flightNumber 
             << ", Seat: " << res.seatNumber << endl;
    }
}

void flightStatus() {
    string flightNumber;
    cout << "Enter flight number: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, flightNumber);
    for (const auto &flight : flights) {
        if (flight.flightNumber == flightNumber) {
            cout << "Flight number: " << flight.flightNumber 
                 << ", Departure time: " << flight.departureTime << endl;
            for (const auto &seat : flight.seats) {
                cout << "Seat " << seat.seatNumber << ": " << (seat.isBooked ? "Booked" : "Available") << "\n";
            }
            return;
        }
    }
    cout << "Flight not found" << endl;
}

int main() {
    int choice;
    while (true) {
        cout << "1. Add Flight\n2. Book Seat\n3. Cancel Booking\n4. View Reservations\n5. Flight Status\n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: 
                addFlight();
                break;
            case 2: 
                bookSeat(); 
                break;
            case 3: 
                cancelBooking(); 
                break;
            case 4: 
                viewReservations(); 
                break;
            case 5: 
                flightStatus();
                break;
            case 6: 
                return 0;
            default: 
                cout << "Invalid choice.\n";
        }
    }
    return 0;
}
