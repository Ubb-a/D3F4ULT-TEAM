#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <string>
#include "database.h"
using namespace std;

DatabaseConnection::DatabaseConnection()
{
    sqlEnvHandle = NULL;
    sqlConnectionHandle = NULL;
    sqlStatementHandle = NULL;
}

bool DatabaseConnection::connect(const string &dbPath)
{
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
        return false;

    if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
        return false;

    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnectionHandle))
        return false;

    string connStr = "Driver={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=" + dbPath + ";";

    switch (SQLDriverConnect(sqlConnectionHandle, NULL,
                             (SQLCHAR *)connStr.c_str(),
                             SQL_NTS,
                             NULL,
                             0,
                             NULL,
                             SQL_DRIVER_NOPROMPT))
    {
    case SQL_SUCCESS:
    case SQL_SUCCESS_WITH_INFO:
        return true;
    case SQL_INVALID_HANDLE:
    case SQL_ERROR:
        return false;
    default:
        return false;
    }
}

bool DatabaseConnection::executeQuery(const string &query)
{
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnectionHandle, &sqlStatementHandle))
        return false;

    if (SQL_SUCCESS != SQLExecDirect(sqlStatementHandle, (SQLCHAR *)query.c_str(), SQL_NTS))
    {
        cout << "ERROR!" << endl;
        showError();
        return false;
    }
    return true;
}

void DatabaseConnection::showError()
{
    SQLCHAR sqlState[1024];
    SQLCHAR message[1024];
    if (SQL_SUCCESS == SQLGetDiagRec(SQL_HANDLE_STMT, sqlStatementHandle, 1, sqlState, NULL, message, 1024, NULL))
        cout << "SQLSTATE: " << sqlState << " - " << message << endl;
}

DatabaseConnection::~DatabaseConnection()
{
    if (sqlStatementHandle)
        SQLFreeHandle(SQL_HANDLE_STMT, sqlStatementHandle);
    if (sqlConnectionHandle) {
        SQLDisconnect(sqlConnectionHandle);
        SQLFreeHandle(SQL_HANDLE_DBC, sqlConnectionHandle);
    }
    if (sqlEnvHandle)
        SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
}