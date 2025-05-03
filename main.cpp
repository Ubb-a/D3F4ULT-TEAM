#include <bits/stdc++.h>
#include "func.h"
#include "database.h"
#include "Design.h"
#include "Room_se.h"

using namespace std;

int main() {
    DatabaseConnection db;
    string dbPath = "C:\\Users\\Abdelrhman\\Desktop\\project\\D3F4ULT.accdb";

    int choice;
    SetConsoleOutputCP(CP_UTF8);
    while (true) {
        system("cls");
        hlogo();
        menu1();
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            gch(db, dbPath);

        }
        else if (choice == 2) {
            ech(db, dbPath);

        }
        else if (choice == 0) {
            cout << "                                                     Exiting program. Goodbye!" << endl;
            break;
        }
        else if (choice == 3) {
            printQRCode("https://f.top4top.io/p_3410wcz891.png");
        }
        else {
            cout << "                                                     Invalid choice! Please try again." << endl;
            system("pause");
        }
    }

    return 0;
}