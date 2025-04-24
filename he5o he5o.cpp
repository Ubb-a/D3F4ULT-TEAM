/*
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
 */




/*
// ... existing code ...


void first_menu(DatabaseConnection& db, const string& dbPath)
{
    int choice;
    while (true)
    {
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            if (db.connect(dbPath))
            {
                string name, phoneNumber, email, password;
                cout << "Enter name: ";
                getline(cin, name);
                cout << "Enter phone number: ";
                getline(cin, phoneNumber);
                cout << "Enter email: ";
                getline(cin, email);
                cout << "Enter password: ";
                getline(cin, password);

                string query = "INSERT INTO Guestes ([Phone Number], [Name], [Email], [Password]) VALUES ('"
                    + phoneNumber + "', '" + name + "', '" + email + "', '" + password + "')";
                if (db.executeQuery(query)) {
                    cout << "Data inserted successfully!" << endl;
                } else {
                    cout << "Error inserting data!" << endl;
                }
            } else {
                cout << "Failed to connect to the database!" << endl;
            }
        }

        if (choice == 2)
        {
            if (db.connect(dbPath))
            {
                string email, password;
                cout << "Enter email: ";
                getline(cin, email);
                cout << "Enter password: ";
                getline(cin, password);

                SQLHANDLE stmtHandle;
                string query = "SELECT * FROM Guestes WHERE [Email] = '" + email + "' AND [Password] = '" + password + "'";

                if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_STMT, db.sqlConnectionHandle, &stmtHandle) &&
                    SQL_SUCCESS == SQLExecDirect(stmtHandle, (SQLCHAR*)query.c_str(), SQL_NTS)) {

                    if (SQLFetch(stmtHandle) == SQL_SUCCESS) {
                        cout << "Login successful!" << endl;
                    } else {
                        cout << "Invalid email or password!" << endl;
                    }
                    SQLFreeHandle(SQL_HANDLE_STMT, stmtHandle);
                } else {
                    cout << "Error executing login query!" << endl;
                }
            } else {
                cout << "Failed to connect to the database!" << endl;
            }
        }
    }
}
// ... existing code ...
 */