#include "func.h"
#include <bits/stdc++.h>
#include "database.h"
#include "Design.h"
#include "Room_se.h"
#include "qrcodegen.hpp"

using namespace std;

DatabaseConnection db;
string dbPath = "C:\\Users\\Abdelrhman\\Desktop\\project\\D3F4ULT.accdb";

void printQRCode(const string &text) {
    system("cls");
    qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(text.c_str(), qrcodegen::QrCode::Ecc::MEDIUM);

    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            cout << (qr.getModule(x, y) ? "██" : "  ");
        }
        cout << endl;
    }

    system("pause");
}

bool isValidEmail(const string& email) {

    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(email, pattern);
}


void booking1(const string& guestId) {
    if (db.connect(dbPath)) {
        string checkin, checkout;
        int day, roomnumber;
                cout << "                                                     Enter Room Number (1 - 30): ";
        cin >> roomnumber;
        cout << "                                                     Enter Check-in Date (MM-DD-YYYY): ";
        cin >> checkin;
        cout << "                                                     Enter Check-out Date (MM-DD-YYYY): ";
        cin >> checkout;
        cout << "                                                     Number of days you will stay: ";
        cin >> day;

        if (db.isRoomBooked(roomnumber, checkin, checkout)) {
            cout << "                                                     The room is already booked for this date!" << endl;

            return;
        }


        int calculate = 0;

        if (roomnumber >= 1 && roomnumber <= 10) {
            calculate = day * 120;
        }
        else if (roomnumber >= 11 && roomnumber <= 18) {
            calculate = day * 200;
        }
        else if (roomnumber >= 19 && roomnumber <= 23) {
            calculate = day * 400;
        }
        else if (roomnumber >= 24 && roomnumber <= 25) {
            calculate = day * 300;
        }
        else if (roomnumber >= 26 && roomnumber <= 27) {
            calculate = day * 70;
        }
        else if (roomnumber >= 28 && roomnumber <= 30) {
            calculate = day * 1500;
        }

        string price = to_string(calculate);
        string room_number = to_string(roomnumber);
        

        string q = "INSERT INTO Booking ([Price],[Check in], [Check out], [Room Number], [Guest ID]) VALUES ('"
+ price + "', #" + checkin + "#, #" + checkout + "#, " + room_number + ", '" + guestId + "')";


        if (db.executeQuery(q)) {
            cout << "                                                     Data inserted successfully!" << endl;
        } else {
            cout << "                                                     Error inserting data!" << endl;
        }
    }
    else {
        cout << "                                                     Failed to connect to the database!" << endl;
    }
}

void IT(const string& name, string &pos) {
    int choice;
    while (true) {
        system("cls");
        admin();
        cout << "                                                                        Welcome, " << name << "!" << endl;
        cout << "                                                     Your position, " << pos << "!" << endl;
        adminmenu();
        cin >> choice;
        cin.ignore();

        if (choice == 0) {
            system("cls");
            return;
        }
        else if (choice == 1) {
            system("cls");
            posliset();
            system("pause");
        }
        else if (choice == 2) {
            system("cls");
            if (db.connect(dbPath)) {
                string name, pos, email, password, id;

                do {
                    cout << "                                                     Enter ID (must be 14 digits): ";
                    getline(cin, id);

                    if (id.length() != 14 || !all_of(id.begin(), id.end(), ::isdigit)) {
                        cout << "                                                     Error: ID must be exactly 14 digits. Please try again." << endl;
                    }
                } while (id.length() != 14 || !all_of(id.begin(), id.end(), ::isdigit));

                cout << "                                                     Enter Name: ";
                getline(cin, name);
                cout << "                                                     Enter position: ";
                getline(cin, pos);

                do {
                    cout << "                                                     Enter Email (example@domain.com): ";
                    getline(cin, email);

                    if (!isValidEmail(email)) {
                        cout << "                                                     Error: Invalid email format. Please try again." << endl;
                    }
                } while (!isValidEmail(email));

                cout << "                                                     Enter Password: ";
                getline(cin, password);

                string query = "INSERT INTO Employees ([Personal ID], [Position], [Name], [Email], [Password]) VALUES ('"
                + id +"', '"+ pos + "', '" + name + "', '" + email + "', '" + password + "')";
                if (db.executeQuery(query)) {
                    cout << "                                                     Data inserted successfully!" << endl;
                    system("pause");
                } else {
                    cout << "                                                     Error inserting data!" << endl;
                    system("pause");
                }
            }
        }
    }
}

void gch(DatabaseConnection& db, const string& dbPath) {
    int ch;
    while (true) {
        system("cls");
        guest();
        gmenu();
        cin >> ch;
        cin.ignore();

        if (ch == 0) {
            system("cls");
            return;
        }
        else if (ch == 1) {
            if (db.connect(dbPath)) {
                string email, password;
                cout << "                                                     Enter Email: ";
                getline(cin, email);
                cout << "                                                     Enter Password: ";
                getline(cin, password);

                string userName, userId, userPhone;
                if (db.checkLogin(email, password, userName, userId, userPhone)) {
                    cout << "                                                     Login successful!" << endl;
                    system("cls");

                    booking();
                    cout << endl;
                    cout << "                                                     Welcome, " << userName << "!" << endl;

                    cout << "                                                     Your ID: " << userId << endl;

                    if (userId.empty()) {
                        cout << "                                                     Error: User ID is empty!" << endl;
                        system("pause");
                        continue;
                    }

                    booking1(userId);
                    system("pause");
                } else {
                    cout << "                                                     Invalid email or password! Please try again." << endl;
                    system("pause");
                }
            }
        }
        else if (ch == 2) {
            if (db.connect(dbPath)) {
                string name, phoneNumber, email, password, id;

                do {
                    cout << "                                                     Enter ID (must be 14 digits): ";
                    getline(cin, id);

                    if (id.length() != 14 || !all_of(id.begin(), id.end(), ::isdigit)) {
                        cout << "                                                     Error: ID must be exactly 14 digits. Please try again." << endl;
                    }
                } while (id.length() != 14 || !all_of(id.begin(), id.end(), ::isdigit));

                cout << "                                                     Enter Name: ";

                getline(cin, name);

                do {
                    cout << "                                                     Enter Phone Number (must be 11 digits): ";
                    getline(cin, phoneNumber);

                    if (phoneNumber.length() != 11 || !all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit)) {
                        cout << "                                                     Error: Number must be exactly 11 digits. Please try again." << endl;
                    }
                } while (phoneNumber.length() != 11 || !all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit));

                do {
                    cout << "                                                     Enter Email (example@domain.com): ";
                    getline(cin, email);

                    if (!isValidEmail(email)) {
                        cout << "                                                     Error: Invalid email format. Please try again." << endl;
                    }
                } while (!isValidEmail(email));

                cout << "                                                     Enter Password: ";
                getline(cin, password);

                string query = "INSERT INTO Guestes ([Guest ID], [Phone Number], [Name], [Email], [Password]) VALUES ('"
                + id +"', '"+ phoneNumber + "', '" + name + "', '" + email + "', '" + password + "')";
                if (db.executeQuery(query)) {
                    cout << "                                                     Data inserted successfully!" << endl;
                    system("pause");
                } else {
                    cout << "                                                     Error inserting data!" << endl;
                    system("pause");
                }
            } else {
                cout << "                                                     Failed to connect to the database!" << endl;
                system("pause");
            }
        }
    }
}

void room_select() {
    while (true) {
        system("cls");
        room_service();
        room_num();
        int choice;

        cin >> choice;

        if (choice == 0) {
            system("cls");
            return;
        }
        else if (1 <= choice && choice <= 30) {
            room_service_g(20);

            cout << endl<<"                                                     Room " << choice << " service completed!" << endl;
            system("pause");
        }
        else {
            cout << "                                                     Invalid room number! Please choose a number between 1 and 30" << endl;
            system("pause");
        }
    }
}

void ech(DatabaseConnection& db, const string& dbPath) {
    int c;
    while (true) {
        system("cls");
        employee();
        emenu();
        cin >> c;
        cin.ignore();

        if (c == 0) {
            system("cls");
            return;
        }
        else if (c == 1) {
            if (db.connect(dbPath)) {
                string email, password;
                cout << "                                                     Enter Email: ";
                getline(cin, email);
                cout << "                                                     Enter Password: ";
                getline(cin, password);

                string userName, pos;
                if (db.Login(email, password, userName, pos)) {
                    cout << "                                                     Login successful!" << endl;
                    system("cls");

                    if (pos == "CIO" || pos == "CEO" || pos == "HR") {
                        IT(userName, pos);
                        system("cls");
                        employee();
                        emenu();
                    }
                    else if (pos == "Room Service") {
                        room_select();
                        system("cls");
                        employee();
                        emenu();
                    }
                    else {
                        cout << endl;
                        system("pause");
                    }
                } else {
                    cout << "                                                     Invalid email or password! Please try again." << endl;
                    system("pause");
                }
            }
        }
    }
}