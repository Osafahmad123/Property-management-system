# Property Management System (C++)

A console-based Property Management System built using C++.  
The program uses Linked List, Queue, and Stack to manage properties, users, and transactions.  
It supports multiple user roles (Admin, Owner, Buyer) with role-based menus and stores data in text files.

---

## Features

### Authentication
- Login system with password masking.
- Role-based access for Admin, Owner, and Buyer.

### Admin
- Add, view, and delete properties.
- Sort properties by price (Bubble Sort).
- Add and view users.
- Create transactions for property bookings.
- Search properties by location and price.

### Owner & Buyer
- View available properties.
- Search properties by location and budget.

---

## Data Structures
| Feature                | Data Structure       |
|------------------------|----------------------|
| Property List          | Doubly Linked List   |
| User List              | Queue                |
| Transaction History    | Stack                |

---

## File Storage
- `users.txt` – stores user information.
- `properties.txt` – stores property listings.

---

## Installation & Usage

### Compile
```bash
g++ main.cpp -o property_management
