#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Vehicle {
protected:
    string vehicle_id;
    string make;
    string model;
    int year;
    bool isRented;
    double dailyRentalRate;

public:
    Vehicle(string id, string making, string v_model, int m_year, double rent)
        : vehicle_id(id), make(making), model(v_model), year(m_year), isRented(false), dailyRentalRate(rent) {}

    virtual ~Vehicle() {} // Destructor

    // Getter functions
    string getVehicleId() const { return vehicle_id; }
    bool getIsRented() const { return isRented; }

    virtual double calRentalCost(int days) const = 0;

    virtual void display_vehicle() const {
        cout << "Vehicle ID: " << vehicle_id << endl;
        cout << "Manufacturer: " << make << endl;
        cout << "Model: " << model << endl;
        cout << "Year: " << year << endl;
        cout << "Daily Rental Rate: $" << dailyRentalRate << endl;
        cout << "Is Rented: " << (isRented ? "Yes" : "No") << endl;
    }

    void rentVehicle() { isRented = true; }
    void returnVehicle() { isRented = false; }
};

// Derived class: Car
class Car : public Vehicle {
    int numberOfDoors;
    string fuelType;

public:
    Car(string id, string making, string v_model, int m_year, double rent, int doors, string fuel)
        : Vehicle(id, making, v_model, m_year, rent), numberOfDoors(doors), fuelType(fuel) {}

    double calRentalCost(int days) const override {
        return dailyRentalRate * days;
    }

    void display_vehicle() const override {
        Vehicle::display_vehicle();
        cout << "Number of Doors: " << numberOfDoors << endl;
        cout << "Fuel Type: " << fuelType << endl;
    }
};

// Derived class: Motorcycle
class Motorcycle : public Vehicle {
    string engineType;
    bool hasSidecar;

public:
    Motorcycle(string id, string making, string v_model, int m_year, double rent, string eng, bool sidecar)
        : Vehicle(id, making, v_model, m_year, rent), engineType(eng), hasSidecar(sidecar) {}

    double calRentalCost(int days) const override {
        return dailyRentalRate * days + (hasSidecar ? 20 * days : 0);
    }

    void display_vehicle() const override {
        Vehicle::display_vehicle();
        cout << "Engine Type: " << engineType << endl;
        cout << "Has Sidecar: " << (hasSidecar ? "Yes" : "No") << endl;
    }
};

// Derived class: Truck
class Truck : public Vehicle {
    double cargoCapacity;
    int numberOfAxles;

public:
    Truck(string id, string making, string v_model, int m_year, double rent, double capacity, int axles)
        : Vehicle(id, making, v_model, m_year, rent), cargoCapacity(capacity), numberOfAxles(axles) {}

    double calRentalCost(int days) const override {
        return dailyRentalRate * days + (cargoCapacity * 10 * days);
    }

    void display_vehicle() const override {
        Vehicle::display_vehicle();
        cout << "Cargo Capacity: " << cargoCapacity << " cubic meters" << endl;
        cout << "Number of Axles: " << numberOfAxles << endl;
    }
};

// Rental System Class
class RentalSystem {
    vector<Vehicle*> vehicles;

public:
    ~RentalSystem() {
        for (auto vehicle : vehicles) {
            delete vehicle; // Free dynamically allocated memory
        }
    }

    void addVehicle(Vehicle* vehicle) {
        vehicles.push_back(vehicle);
    }

    void displayAvailableVehicles() const {
        cout << "\nAvailable Vehicles:\n";
        for (const auto& vehicle : vehicles) {
            if (!vehicle->getIsRented()) {
                vehicle->display_vehicle();
                cout << "------------------------\n";
            }
        }
    }

    Vehicle* findVehicle(string vehicleID) {
        for (auto& vehicle : vehicles) {
            if (vehicle->getVehicleId() == vehicleID) {
                return vehicle;
            }
        }
        return nullptr;
    }

    void rentVehicle(string vehicleID, int days) {
        Vehicle* vehicle = findVehicle(vehicleID);
        if (!vehicle) {
            cout << "Vehicle not found!\n";
            return;
        }
        if (vehicle->getIsRented()) {
            cout << "Vehicle is already rented!\n";
            return;
        }

        vehicle->rentVehicle();
        cout << "Rental Cost: $" << vehicle->calRentalCost(days) << endl;
    }

    void returnVehicle(string vehicleID) {
        Vehicle* vehicle = findVehicle(vehicleID);
        if (!vehicle) {
            cout << "Vehicle not found!\n";
            return;
        }
        if (!vehicle->getIsRented()) {
            cout << "Vehicle is not currently rented!\n";
            return;
        }

        vehicle->returnVehicle();
        cout << "Vehicle returned successfully!\n";
    }
};

// Main function with menu
int main() {
    RentalSystem rentalSystem;

    // Adding sample vehicles
    rentalSystem.addVehicle(new Car("CAR123", "Toyota", "Camry", 2022, 50, 4, "Petrol"));
    rentalSystem.addVehicle(new Motorcycle("BIKE456", "Honda", "CBR500", 2021, 30, "Inline-4", true));
    rentalSystem.addVehicle(new Truck("TRUCK789", "Ford", "F-150", 2023, 80, 15, 2));

    int choice;
    do {
        cout << "\nVehicle Rental System Menu:\n";
        cout << "1. Display Available Vehicles\n";
        cout << "2. Rent a Vehicle\n";
        cout << "3. Return a Vehicle\n";
        cout << "4. Find Vehicle and Display Details\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string vehicleID;
        int days;

        switch (choice) {
            case 1:
                rentalSystem.displayAvailableVehicles();
                break;
            case 2:
                cout << "Enter Vehicle ID: ";
                cin >> vehicleID;
                cout << "Enter number of days: ";
                cin >> days;
                rentalSystem.rentVehicle(vehicleID, days);
                break;
            case 3:
                cout << "Enter Vehicle ID: ";
                cin >> vehicleID;
                rentalSystem.returnVehicle(vehicleID);
                break;
            case 4:
                cout << "Enter Vehicle ID: ";
                cin >> vehicleID;
                if (Vehicle* v = rentalSystem.findVehicle(vehicleID)) {
                    v->display_vehicle();
                } else {
                    cout << "Vehicle not found!\n";
                }
                break;
            case 5:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
