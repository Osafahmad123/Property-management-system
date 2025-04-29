#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <limits>
#include <conio.h>
using namespace std;

// Function to clear the screen
void clearScreen() {
    // Use ANSI escape codes to clear the screen
    cout << "\033[2J\033[1;1H";
}

// Node for PropertiesList
template <typename T>
struct Node {
    T data;
    Node* next;
    Node* previous;
    Node(T value) : data(value), next(nullptr), previous(nullptr) {}
};

// PropertiesList implementation using linklist
template <typename T>
class PropertiesList {
private:
    Node<T>* head;
    int size;

public:
    PropertiesList() : head(nullptr), size(0) {}

    void add(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
            newNode->previous = current;
        }
        size++;
    }

    bool remove(int id) {
        if (!head) return false;

        if (head->data.getId() == id) {
            Node<T>* temp = head;
            head = head->next;
            if (head) head->previous = nullptr;
            delete temp;
            size--;
            return true;
        }

        Node<T>* current = head;
        while (current->next) {
            if (current->next->data.getId() == id) {
                Node<T>* temp = current->next;
                current->next = current->next->next;
                if (current->next) current->next->previous = current;
                delete temp;
                size--;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    Node<T>* getHead() {
        return head;
    }
    int getSize() {
        return size;
    }
};

// Users implementation for users using queue
template <typename T>
class Users {
public:
    struct UserNode {
        T data;
        UserNode* rare;
        UserNode(T value) : data(value), rare(nullptr) {}
    };

private:
    UserNode* front;
    UserNode* rear;
    int size;

public:
    Users() : front(nullptr), rear(nullptr), size(0) {}

    void enqueue(T value) {
        UserNode* newNode = new UserNode(value);
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->rare = newNode;
            rear = newNode;
        }
        size++;
    }

    bool dequeue() {
        if (!front) return false;
        UserNode* temp = front;
        front = front->rare;
        if (!front) rear = nullptr;
        delete temp;
        size--;
        return true;
    }

    UserNode* getFront() {
        return front;
    }
    int getSize() {
        return size;
    }
};

// Transactions implementation for transactions using stack
template <typename T>
class Transactions {
public:
    struct TransactionNode {
        T data;
        TransactionNode* rare;
        TransactionNode(T value) : data(value), rare(nullptr) {}
    };

private:
    TransactionNode* top;
    int size;

public:
    Transactions() : top(nullptr), size(0) {}

    void push(T value) {
        TransactionNode* newNode = new TransactionNode(value);
        newNode->rare = top;
        top = newNode;
        size++;
    }

    bool pop() {
        if (!top) return false;
        TransactionNode* temp = top;
        top = top->rare;
        delete temp;
        size--;
        return true;
    }

    TransactionNode* getTop() {
        return top;
    }
    int getSize() {
        return size;
    }
};

// Address class
class Address {
private:
    string street;
    string city;

public:
    Address(const string& s = "", const string& c = "")
        : street(s), city(c) {}

    string getStreet() const {
        return street;
    }
    string getCity() const {
        return city;
    }
    void setStreet(const string& s) {
        street = s;
    }
    void setCity(const string& c) {
        city = c;
    }
};

// Property class
class Property {
private:
    int id;
    string location;
    double price;
    string status;
    Address address;

public:
    Property(int i = 0, const string& loc = "", double p = 0.0,
             const Address& addr = Address())
        : id(i), location(loc), price(p), status("Available"), address(addr) {}

    int getId() const {
        return id;
    }
    string getLocation() const {
        return location;
    }
    double getPrice() const {
        return price;
    }
    string getStatus() const {
        return status;
    }
    Address getAddress() const {
        return address;
    }
    void setStatus(const string& s) {
        status = s;
    }
};

// User class
class User {
private:
    int id;
    string name;
    string role;
    string email;
    string password;

public:
    User(int i = 0, const string& n = "", const string& r = "",
         const string& e = "", const string& p = "")
        : id(i), name(n), role(r), email(e), password(p) {}

    int getId() const {
        return id;
    }
    string getName() const {
        return name;
    }
    string getRole() const {
        return role;
    }
    string getEmail() const {
        return email;
    }
    string getPassword() const {
        return password;
    }
};

class Transaction {
private:
    int id;
    int propertyId;
    int buyerId;
    double amount;
    string date;

public:
    Transaction(int i = 0, int pid = 0, int bid = 0, double a = 0.0)
        : id(i), propertyId(pid), buyerId(bid), amount(a) {
        // Get current date
        time_t now = time(0);
        tm* localTime = localtime(&now);

        // Format YYYY-MM-DD
        char buffer[11];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", localTime);

        date = buffer; // Store the formatted date
    }

    int getId() const {
        return id;
    }
    int getPropertyId() const {
        return propertyId;
    }
    int getBuyerId() const {
        return buyerId;
    }
    double getAmount() const {
        return amount;
    }
    string getDate() const {
        return date;
    }
};

// Property management class
class PropertyManagement {
private:
    PropertiesList<Property> properties;
    Users<User> users;
    Transactions<Transaction> transactions;
    int nextPropertyId;
    int nextUserId;
    int nextTransactionId;
    User* currentUser;

    // Bubble sort for sorting properties by price
    void bubbleSort(Node<Property>* start) {
        if (!start) return;

        bool swapped;
        Node<Property>* ptr1;
        Node<Property>* lptr = nullptr;

        do {
            swapped = false;
            ptr1 = start;

            while (ptr1->next != lptr) {
                if (ptr1->data.getPrice() > ptr1->next->data.getPrice()) {
                    Property temp = ptr1->data;
                    ptr1->data = ptr1->next->data;
                    ptr1->next->data = temp;
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
    }

    // Save users to file
    void saveUsersToFile() {
        ofstream file("users.txt");
        if (file.is_open()) {
            Users<User>::UserNode* current = users.getFront();
            while (current) {
                file << current->data.getId() << " "
                     << current->data.getName() << " "
                     << current->data.getRole() << " "
                     << current->data.getEmail() << " "
                     << current->data.getPassword() << "\n";
                current = current->rare;
            }
            file.close();
        }
    }

    // Load users from file
    void loadUsersFromFile() {
        ifstream file("users.txt");
        if (file.is_open()) {
            int id;
            string name, role, email, password;
            while (file >> id >> name >> role >> email >> password) {
                users.enqueue(User(id, name, role, email, password));
                if (id >= nextUserId) nextUserId = id + 1;
            }
            file.close();
        }
    }

    // Save properties to file
    void savePropertiesToFile() {
        ofstream file("properties.txt");
        if (file.is_open()) {
            Node<Property>* current = properties.getHead();
            while (current) {
                file << current->data.getId() << " "
                     << current->data.getLocation() << " "
                     << current->data.getPrice() << " "
                     << current->data.getStatus() << " "
                     << current->data.getAddress().getStreet() << " "
                     << current->data.getAddress().getCity() << "\n";
                current = current->next;
            }
            file.close();
        }
    }

    // Load properties from file
    void loadPropertiesFromFile() {
        ifstream file("properties.txt");
        if (file.is_open()) {
            int id;
            string location, status, street, city;
            double price;
            while (file >> id >> location >> price >> status >> street >> city) {
                Address addr(street, city);
                Property prop(id, location, price, addr);
                prop.setStatus(status);
                properties.add(prop);
                if (id >= nextPropertyId) nextPropertyId = id + 1;
            }
            file.close();
        }
    }

public:
    PropertyManagement() : nextPropertyId(1), nextUserId(1), nextTransactionId(1), currentUser(nullptr) {
        loadUsersFromFile();
        loadPropertiesFromFile();
    }

    ~PropertyManagement() {
        saveUsersToFile();
        savePropertiesToFile();
    }

    // Login system
    bool login() {
        string email, password;
        cout << "\nEnter email: ";
        cin >> email;
        cout << "Enter password: ";

        // hide password with the help of *
        char ch;
        password = "";
        while ((ch = _getch()) != '\r') {
            if (ch == '\b') { // Handle backspace
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b";
                }
            } else {
                password.push_back(ch);
                cout << '*';
            }
        }
        cout << endl;

        Users<User>::UserNode* current = users.getFront();
        while (current) {
            if (current->data.getEmail() == email && current->data.getPassword() == password) {
                currentUser = &(current->data);
                cout << "\nLogin successful! Welcome, " << currentUser->getName() << ".\n";
                clearScreen();
                return true;
            }
            current = current->rare;
        }
        cout << "\nInvalid email or password.\n";
        clearScreen();
        return false;
    }

    void logout() {
        currentUser = nullptr;
        cout << "\nLogged out successfully.\n";
        clearScreen();
    }

    void addProperty() {
        if (!currentUser || currentUser->getRole() != "Admin") {
            cout << "\nAccess denied! Only admins can add properties.\n";
            return;
        }

        string location, street, city;
        double price;

        cout << "\nEnter property details:\n";
        cout << "Location: ";
        cin.ignore();
        getline(cin, location);
        cout << "Street: ";
        getline(cin, street);
        cout << "City: ";
        getline(cin, city);
        cout << "Price: ";
        cin >> price;

        Address addr(street, city);
        Property prop(nextPropertyId++, location, price, addr);
        properties.add(prop);
        cout << "\nProperty added successfully!\n";
    }

    void displayProperties() {
        Node<Property>* current = properties.getHead();

        if (!current) {
            cout << "\nNo properties available.\n";
            return;
        }

        cout << "\nProperty Listings:\n";
        cout << "ID\tLocation\tPrice\tStatus\tAddress\n";
        cout << "------------------------------------------------\n";

        while (current) {
            Property& prop = current->data;
            cout << prop.getId() << "\t"
                 << prop.getLocation() << "\t"
                 << prop.getPrice() << "\t"
                 << prop.getStatus() << "\t"
                 << prop.getAddress().getStreet() << ", "
                 << prop.getAddress().getCity() << "\n";
            current = current->next;
        }
    }

    void deleteProperty() {
        if (!currentUser || currentUser->getRole() != "Admin") {
            cout << "\nAccess denied! Only admins can delete properties.\n";
            return;
        }

        displayProperties();
        int id;
        cout << "\nEnter property ID to delete: ";
        cin >> id;

        if (properties.remove(id)) {
            cout << "Property deleted successfully!\n";
        } else {
            cout << "Property not found!\n";
        }
    }

    void sortPropertiesByPrice() {
        bubbleSort(properties.getHead());
        cout << "\nProperties sorted by price:\n";
        displayProperties();
    }

    void addUser() {
        string name, role, email, password;
        cout << "\nEnter user details:\n";
        cout << "Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Role (Buyer/Owner/Admin): ";
        getline(cin, role);
        cout << "Email: ";
        getline(cin, email);
        cout << "Password: ";
        getline(cin, password);

        users.enqueue(User(nextUserId++, name, role, email, password));
        cout << "\nUser added successfully!\n";
    }

    void displayUsers() {
        if (!currentUser || currentUser->getRole() != "Admin") {
            cout << "\nAccess denied! Only admins can view users.\n";
            return;
        }

        Users<User>::UserNode* current = users.getFront();

        if (!current) {
            cout << "\nNo users registered.\n";
            return;
        }

        cout << "\nRegistered Users:\n";
        cout << "ID\tName\tRole\tEmail\n";
        cout << "--------------------------------\n";

        while (current) {
            User& user = current->data;
            cout << user.getId() << "\t"
                 << user.getName() << "\t"
                 << user.getRole() << "\t"
                 << user.getEmail() << "\n";
            current = current->rare;
        }
    }

    void createTransaction() {
        if (!currentUser || currentUser->getRole() != "Admin") {
            cout << "\nAccess denied! Only admins can create transactions.\n";
            return;
        }

        displayProperties();
        int propertyId, buyerId;
        cout << "\nEnter property ID: ";
        cin >> propertyId;
        displayUsers();
        cout << "Enter buyer ID: ";
        cin >> buyerId;

        Node<Property>* current = properties.getHead();
        while (current) {
            if (current->data.getId() == propertyId) {
                Transaction trans(nextTransactionId++, propertyId, buyerId,
                                  current->data.getPrice());
                transactions.push(trans);
                current->data.setStatus("Booked");
                cout << "\nTransaction created successfully!\n";
                return;
            }
            current = current->next;
        }
        cout << "Property not found!\n";
    }

    void displayTransactions() {
        if (!currentUser || currentUser->getRole() != "Admin") {
            cout << "\nAccess denied! Only admins can view transactions.\n";
            return;
        }

        Transactions<Transaction>::TransactionNode* current = transactions.getTop();

        if (!current) {
            cout << "\nNo transactions available.\n";
            return;
        }

        cout << "\nTransaction History:\n";
        cout << "ID\tProperty ID\tBuyer ID\tAmount\tDate\n";
        cout << "------------------------------------------------\n";

        while (current) {
            Transaction& trans = current->data;
            cout << trans.getId() << "\t"
                 << trans.getPropertyId() << "\t\t"
                 << trans.getBuyerId() << "\t\t"
                 << trans.getAmount() << "\t"
                 << trans.getDate() << "\n";
            current = current->rare;
        }
    }

    void searchProperties() {
        string location;
        double maxPrice;
        cout << "\nEnter search criteria:\n";
        cout << "Location: ";
        cin.ignore();
        getline(cin, location);
        cout << "Maximum price: ";
        cin >> maxPrice;

        Node<Property>* current = properties.getHead();
        bool found = false;

        cout << "\nSearch Results:\n";
        cout << "ID\tLocation\tPrice\tStatus\n";
        cout << "--------------------------------\n";

        while (current) {
            Property& prop = current->data;
            if (prop.getLocation() == location && prop.getPrice() <= maxPrice) {
                cout << prop.getId() << "\t"
                     << prop.getLocation() << "\t"
                     << prop.getPrice() << "\t"
                     << prop.getStatus() << "\n";
                found = true;
            }
            current = current->next;
        }

        if (!found) {
            cout << "No properties found matching your criteria.\n";
        }
    }

    void displayMenuBasedOnRole() {
        if (!currentUser) {
            cout << "\nPlease login to access the system.\n";
            return;
        }

        string role = currentUser->getRole();
        if (role == "Admin") {
            displayAdminMenu();
        } else if (role == "Owner") {
            displayOwnerMenu();
        } else if (role == "Buyer") {
            displayBuyerMenu();
        }
    }

    void displayAdminMenu() {
        int choice;
        while (true) {
            cout << "\n=== Admin Menu ===\n";
            cout << "1. Add Property\n";
            cout << "2. Display Properties\n";
            cout << "3. Delete Property\n";
            cout << "4. Sort Properties by Price\n";
            cout << "5. Add User\n";
            cout << "6. Display Users\n";
            cout << "7. Create Transaction\n";
            cout << "8. Display Transactions\n";
            cout << "9. Search Properties\n";
            cout << "10. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addProperty();
                    break;
                case 2:
                    displayProperties();
                    break;
                case 3:
                    deleteProperty();
                    break;
                case 4:
                    sortPropertiesByPrice();
                    break;
                case 5:
                    addUser();
                    break;
                case 6:
                    displayUsers();
                    break;
                case 7:
                    createTransaction();
                    break;
                case 8:
                    displayTransactions();
                    break;
                case 9:
                    searchProperties();
                    break;
                case 10:
                    logout();
                    return;
                default:
                    cout << "Invalid choice! Please try again.\n";
            }
        }
    }

    void displayOwnerMenu() {
        int choice;
        while (true) {
            cout << "\n=== Owner Menu ===\n";
            cout << "1. Display Properties\n";
            cout << "2. Search Properties\n";
            cout << "3. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    displayProperties();
                    break;
                case 2:
                    searchProperties();
                    break;
                case 3:
                    logout();
                    return;
                default:
                    cout << "Invalid choice! Please try again.\n";
            }
        }
    }

    void displayBuyerMenu() {
        int choice;
        while (true) {
            cout << "\n=== Buyer Menu ===\n";
            cout << "1. Display Properties\n";
            cout << "2. Search Properties\n";
            cout << "3. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    displayProperties();
                    break;
                case 2:
                    searchProperties();
                    break;
                case 3:
                    logout();
                    return;
                default:
                    cout << "Invalid choice! Please try again.\n";
            }
        }
    }
};

// Main function
int main() {
    PropertyManagement system;
    int choice;

    while (true) {
        cout << "\n=== Property Management System ===\n";
        cout << "1. Login\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (system.login()) {
                    system.displayMenuBasedOnRole();
                }
                break;
            case 2:
                cout << "Thank you for using the system!\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}