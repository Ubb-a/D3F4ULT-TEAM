#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <string>
#include "Design.h"
#include "database.h"
#include "func.h"
#include "Room_se.h"

using namespace std;


void first_menu()
{
    hlogo();
    menu1();
    int choice;
    while (true)
    {
        cin >> choice;
        cin.ignore();
        if (choice == 1)
        {
            DatabaseConnection db;
            string dbPath = "C:\\Users\\Abdelrhman\\Desktop\\project\\D3F4ULT.accdb";
            gch(db, dbPath);

        }

        if (choice == 2)
        {
            DatabaseConnection db;
            string dbPath = "C:\\Users\\Abdelrhman\\Desktop\\project\\D3F4ULT.accdb";

           ech(db, dbPath);
        }

    }
}


int main()
{
    SetConsoleOutputCP(CP_UTF8);


    first_menu();


    return 0;
}