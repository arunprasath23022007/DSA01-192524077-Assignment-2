#include <iostream>
#include <string>
#include <vector>

// Alternative Concept: TicketOffice / Bus encapsulation allowing multiple buses
class Bus {
private:
    std::string routeName;
    int capacity;
    int issued;

public:
    Bus(std::string name, int cap) : routeName(std::move(name)), capacity(cap), issued(0) {}

    int issueSeat() {
        if (issued < capacity) {
            return ++issued;
        }
        return 0; // Waiting list
    }

    int getIssued() const { return issued; }
    int getCapacity() const { return capacity; }
    std::string getName() const { return routeName; }
};

class ManagedBusTicket {
private:
    std::string passengerName;
    std::string busName;
    int seat;

public:
    ManagedBusTicket(const std::string& name, Bus& bus)
        : passengerName(name), busName(bus.getName()), seat(bus.issueSeat()) {}

    void print() const {
        std::cout << "[" << busName << "] " << passengerName << ": "
                  << (seat ? "Seat " + std::to_string(seat) : "Waiting") << '\n';
    }
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "Multi-Bus Architecture: Solving Static Member Limits\n";
    std::cout << "====================================================\n";

    Bus busRoute1("Route 101 - City Express", 3);
    Bus busRoute2("Route 202 - Campus Shuttle", 2);

    ManagedBusTicket t1("Arun", busRoute1);
    ManagedBusTicket t2("Bina", busRoute1);
    ManagedBusTicket t3("Cyril", busRoute1);
    ManagedBusTicket t4("Deepa", busRoute1); // waiting for bus 1

    ManagedBusTicket t5("Eashwar", busRoute2);
    ManagedBusTicket t6("Farah", busRoute2);
    ManagedBusTicket t7("Gopal", busRoute2); // waiting for bus 2

    t1.print(); t2.print(); t3.print(); t4.print();
    t5.print(); t6.print(); t7.print();

    std::cout << "Route 101 Issued: " << busRoute1.getIssued() << "/" << busRoute1.getCapacity() << '\n';
    std::cout << "Route 202 Issued: " << busRoute2.getIssued() << "/" << busRoute2.getCapacity() << '\n';

    return 0;
}
