#include<iostream>
#include<string>
using namespace std;

int const TOTAL_SEATS = 30;

int Bookticket(int* arr) {
    for (int i = 0; i < TOTAL_SEATS; i++) {
        if (arr[i] == 0) {
            arr[i] = 1;
            cout << "Booked seat number: " << i + 1 << '\n';
            return i + 1;
        }
    }

    cout << "No seat available.\n";
    return 0;
}

struct node {
    int seatNumber;
    string name;
    int age;
    string gender;
    node* next;
};

void InsertPassenger(node*& start, int seat, string name,
                     int age, string gender) {
    node* newnode = new node;

    newnode->seatNumber = seat;
    newnode->name = name;
    newnode->age = age;
    newnode->gender = gender;
    newnode->next = nullptr;


    if (start == nullptr) {
        start = newnode;
        return;
    }

    node* ptr = start;

    while (ptr->next != nullptr) {
        ptr = ptr->next;
    }

    
    ptr->next = newnode;
}

void DisplayPassengers(node* start) {

    if(start == nullptr){
        cout<<"No passenger is booked yet.";
        return;
    }

    node* ptr = start;

    while (ptr != nullptr) {
        cout << "Seat: " <<ptr->seatNumber << endl;
        cout << "Name: " << ptr->name << endl;
        cout << "Age: " << ptr->age << endl;
        cout << "Gender: " << ptr->gender << endl;
        cout << "------------------" << endl;

        ptr = ptr->next;
    }
}

void ViewTrainStatus( int* seats) {
    cout << "\nTrain Seat Status\n";
    for (int i = 0; i < TOTAL_SEATS; i++) {
        cout << i + 1 << ":";
        if (seats[i] == 0) {
            cout << "Available ";
        } else {
            cout << "Booked ";
        }    
    }
}


void CancelTicket(int* seats, node*& start) {
    int seat;
    cout << "Enter seat number to cancel (1-" << TOTAL_SEATS << "): ";
    cin >> seat;

    if (seat < 1 || seat > TOTAL_SEATS) {
        cout << "Invalid seat number.\n";
        return;
    }

    if (seats[seat - 1] == 0) {
        cout << "That seat is already available.\n";
        return;
    }

    node* current = start;
    node* previous = nullptr;

    while (current != nullptr && current->seatNumber != seat) {
        previous = current;
        current = current->next;
    }

    
    if (current == nullptr) {
        cout << "Passenger record not found; seat status was not changed.\n";
        return;
    }

    if (previous == nullptr) {
        start = current->next;       
    } else {
        previous->next = current->next;
    }

    delete current;
    seats[seat - 1] = 0;
    cout << "Ticket for seat " << seat << " cancelled successfully.\n";
}


int main() {
     int seats[TOTAL_SEATS] = {0};

    node* start = nullptr;
    int choice = 0;

    do {
        cout << "\n------- Railway Reservation System -------\n"
             << "1. Book Ticket\n"
             << "2. Cancel Ticket\n"
             << "3. View Train Status\n"
             << "4. View Passenger List\n"
             << "5. Exit\n"
             << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Exiting safely.\n";
            break;
        }

        switch (choice) {
            case 1: {
                int seat = Bookticket(seats);
                if (seat != 0) {
                    string name, gender;
                    int age;

                    cout << "Enter passenger name: ";
                    getline(cin >>ws, name);

                    cout << "Enter age: ";
                    if (!(cin >> age) || age < 0) {
                        cout << "Invalid age. Booking cancelled.\n";
                        seats[seat - 1] = 0;
                        break;
                    }

                    cout << "Enter gender: ";
                    cin >> gender;

                    InsertPassenger(start, seat, name, age, gender);
                    cout << "Passenger details saved successfully.\n";
                }
                break;
            }

            case 2:
                CancelTicket(seats, start);
                break;

            case 3:
                ViewTrainStatus(seats);
                break;

            case 4:
                DisplayPassengers(start);
                break;

            case 5:
                cout << "Thank you for using the Railway Reservation System.\n";
                break;

            default:
                cout << "Invalid choice. Please select 1-5.\n";
        }
    }
        while(choice != 5);
}
