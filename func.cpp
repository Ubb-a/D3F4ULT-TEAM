#include "func.h"
#include <bits/stdc++.h>
#include "database.h"
#include "Design.h"

using namespace std;
DatabaseConnection db;

string dbPath = "C:\\Users\\Abdelrhman\\Desktop\\project\\D3F4ULT.accdb";

void booking1(const string& guestId) {
    if (db.connect(dbPath)) {
        string checkin, checkout, roomnumber;
        cout << "                                                     Enter Check-in Date (DD-MM-YYYY): ";
        cin >> checkin;
        cout << "                                                     Enter Check-out Date (DD-MM-YYYY): ";
        cin >> checkout;
        cout << "                                                     Enter Room Number: ";
        cin >> roomnumber;

        string q = "INSERT INTO Booking ([Check in], [Check out], [Room Number], [Guest ID]) VALUES ('"
    + checkin + "', '" + checkout + "', '" + roomnumber + "', '" + guestId + "')";





        if (db.executeQuery(q)) {
            cout << "                                                     Data inserted successfully!" << endl;
        } else {
            cout << "                                                     Error inserting data!" << endl;
        }
    } else {
        cout << "                                                     Failed to connect to the database!" << endl;
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

        if (ch == 1) {
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
            if (db.connect(dbPath))
            {
                // Input data from user

                string name, phoneNumber, email, password,id;
                cout << "                                                     Enter ID: ";
                getline(cin, id);
                cout << "                                                     Enter Name: ";
                getline(cin, name);
                cout << "                                                     Enter Phone Number: ";
                getline(cin, phoneNumber);
                cout << "                                                     Enter Email: ";
                getline(cin, email);
                cout << "                                                     Enter Password: ";
                getline(cin, password);



                string query = "INSERT INTO Guestes ([Guest ID], [Phone Number], [Name], [Email], [Password]) VALUES ('"
                + id +"', '"+ phoneNumber + "', '" + name + "', '" + email + "', '" + password + "')";
                if (db.executeQuery(query)) {
                    cout << "                                                     Data inserted successfully!" << endl;
                } else {
                    cout << "                                                     Error inserting data!" << endl;
                }
            } else {
                cout << "                                                     Failed to connect to the database!" << endl;
            }
        }
    }
}

