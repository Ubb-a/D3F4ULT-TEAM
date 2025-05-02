#include "func.h"
#include <bits/stdc++.h>
#include "database.h"
#include "Design.h"
#include "Room_se.h"

using namespace std;
DatabaseConnection db;

string dbPath = "C:\\Users\\Abdelrhman\\Desktop\\project\\D3F4ULT.accdb";

void price() {

}

void booking1(const string& guestId) {
    if (db.connect(dbPath)) {
        string checkin, checkout;
        int day, roomnumber;
        
        cout << "                                                     Enter Check-in Date (MM-DD-YYYY): ";
        cin >> checkin;
        cout << "                                                     Enter Check-out Date (MM-DD-YYYY): ";
        cin >> checkout;
        cout << "                                                     Number of days you will stay: ";
        cin >> day;
        cout << "                                                     Enter Room Number (1 - 30): ";
        cin >> roomnumber;
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
+ price + "', '" + checkin + "', '" + checkout + "', '" + room_number + "', '" + guestId + "')";



        if (db.executeQuery(q)) {
            cout << "                                                     Data inserted successfully!" << endl;
        } else {
            cout << "                                                     Error inserting data!" << endl;
        }
    } else {
        cout << "                                                     Failed to connect to the database!" << endl;
    }
}

void IT ( const string& name,string &pos) {
    system("cls");
    int choice;
    while (true) {
        admin();
        cout << "                                                                        Welcome, " << name << "!" << endl;
        cout << "                                                     Your position, " << pos << "!" << endl;
        adminmenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            system("cls");
            posliset();
            system("pause");
        }
        else if (choice == 2) {
            system("cls");
            if (db.connect(dbPath)) {
                string name, pos, email, password,id;
                cout << "                                                     Enter id: ";
                getline(cin, id);
                cout << "                                                     Enter Name: ";
                getline(cin, name);
                cout << "                                                     Enter position: ";
                getline(cin, pos);
                cout << "                                                     Enter Email: ";
                getline(cin, email);
                cout << "                                                     Enter Password: ";
                getline(cin, password);



                string query = "INSERT INTO Employees ([Personal ID], [Position], [Name], [Email], [Password]) VALUES ('"
                + id +"', '"+ pos + "', '" + name + "', '" + email + "', '" + password + "')";
                if (db.executeQuery(query)) {
                    cout << "                                                     Data inserted successfully!" << endl;
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

void room_select() {
    while (true) {
        system("cls");
        room_service();
        room_num();
        int choice;

        cin >> choice;

        if (choice == 0) {
            return;
        }
        else if (1 <= choice && choice <= 30) {
            runTrashGame(20);

            cout << endl<<"                                                     Room " << choice << " service completed!" << endl;
            system("pause");
        }
        else {
            cout << "                                                     Invalid room number! Please choose a number between 1 and 29." << endl;
            system("pause");
        }
    }
}

void ech(DatabaseConnection& db , const string& dbPath) {
    int c ;
    while (true) {
        system("cls");
        employee();
        emenu();
        cin >> c ;
        cin.ignore();

        if ( c == 1) {
            if (db.connect(dbPath)) {
                string email, password;
                cout << "                                                     Enter Email: ";
                getline(cin, email);
                cout << "                                                     Enter Password: ";
                getline(cin, password);

                string userName ,pos;
                if (db.Login(email, password, userName, pos)) {
                    cout << "                                                     Login successful!" << endl;
                    system("cls");

                    if (pos == "CIO" || pos == "CEO" || pos == "HR") {
                        IT(userName , pos);
                        system("pause");
                    }
                    else if (pos == "Room Service") {

                        room_select();
                        // runTrashGame(20);
                    }
                    else{


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



