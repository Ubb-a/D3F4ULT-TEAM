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

bool DatabaseConnection::checkLogin(const string& email, const string& password,
                                  string& name, string& id, string& phone)
{
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnectionHandle, &sqlStatementHandle))
        return false;

    string query = "SELECT [Name], [Guest ID], [Phone Number] FROM Guestes WHERE [Email] = '" + email + "' AND [Password] = '" + password + "'";

    if (SQL_SUCCESS != SQLExecDirect(sqlStatementHandle, (SQLCHAR*)query.c_str(), SQL_NTS))
    {
        showError();
        return false;
    }

    SQLCHAR nameBuffer[256] = {0};
    SQLCHAR idBuffer[256] = {0};
    SQLCHAR phoneBuffer[256] = {0};
    SQLLEN nameLen = 0, idLen = 0, phoneLen = 0;

    // ربط الأعمدة بالمتغيرات
    SQLBindCol(sqlStatementHandle, 1, SQL_C_CHAR, nameBuffer, sizeof(nameBuffer), &nameLen);
    SQLBindCol(sqlStatementHandle, 2, SQL_C_CHAR, idBuffer, sizeof(idBuffer), &idLen);
    SQLBindCol(sqlStatementHandle, 3, SQL_C_CHAR, phoneBuffer, sizeof(phoneBuffer), &phoneLen);

    // التحقق مما إذا كان هناك نتائج
    if (SQL_SUCCESS == SQLFetch(sqlStatementHandle))
    {
        // تحويل البيانات إلى سلاسل نصية
        name = string((char*)nameBuffer);
        id = string((char*)idBuffer);
        phone = string((char*)phoneBuffer);

        // إزالة الأحرف NULL في نهاية السلسلة
        name = name.c_str();
        id = id.c_str();
        phone = phone.c_str();


        return true;
    }

    return false;
}