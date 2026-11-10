#include <iostream>
#include <string>

class BusTicket {
    static int issued; // shared by all BusTicket objects
    static const int CAPACITY = 3;
    int seat;
    std::string name;

public:
    explicit BusTicket(const std::string& n) : seat(0), name(n)
    {
        // TODO 1: If fewer than CAPACITY tickets have been issued, increase issued and
        // give this ticket the next seat number; otherwise leave seat as 0 (waiting list)
        if (issued < CAPACITY) {
            seat = ++issued;
        } else {
            seat = 0;
        }
    }

    static int count()
    {
        // TODO 2: Return the number of seats issued so far
        return issued;
    }

    void print() const
    {
        std::cout << name << ": "
                  << (seat ? "Seat " + std::to_string(seat) : std::string("Waiting"))
                  << '\n';
    }
};

int BusTicket::issued = 0; // definition of the static data member

void issueBatch(const std::string& batchName) {
    std::cout << "\n--- Function issueBatch called for: " << batchName << " ---\n";
    BusTicket batch[4] = {BusTicket(batchName + "_1"), BusTicket(batchName + "_2"),
                          BusTicket(batchName + "_3"), BusTicket(batchName + "_4")};
    for (const auto& t : batch) t.print();
    std::cout << "Issued total so far: " << BusTicket::count() << '\n';
}

int main()
{
    std::cout << "--- Standard Run (Expected Output Check) ---\n";
    BusTicket trip[4] = {BusTicket("Asha"), BusTicket("Bala"),
                         BusTicket("Chitra"), BusTicket("Dev")};
    for (const BusTicket& t : trip) t.print();
    std::cout << "Issued: " << BusTicket::count() << '\n';

    std::cout << "\n--- Calling ticket creation inside a function twice ---\n";
    std::cout << "Notice: Because CAPACITY is 3 and 3 seats are already issued,\n";
    std::cout << "all tickets created in subsequent calls get waiting list (seat 0)!\n";
    issueBatch("TripB_Batch1");
    issueBatch("TripB_Batch2");

    return 0;
}
