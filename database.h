//
// Created by Abdelrhman on 4/24/2023.
//

#ifndef DATABASE_H
#define DATABASE_H

#pragma once
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <string>

class DatabaseConnection
{
private:
    SQLHANDLE sqlEnvHandle;
    SQLHANDLE sqlConnectionHandle;
    SQLHANDLE sqlStatementHandle;
    SQLRETURN retCode;

    void showError(); // إضافة دالة لعرض أخطاء SQL

public:
    DatabaseConnection();
    bool connect(const std::string &dbPath);
    bool executeQuery(const std::string &query);
    ~DatabaseConnection();
    bool checkLogin(const std::string& email, const std::string& password,
               std::string& name, std::string& id, std::string& phone);
};


#endif //DATABASE_H