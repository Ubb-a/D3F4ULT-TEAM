//
// Created by Abdelrhman on 4/24/2025.
//

#ifndef FUNC_H
#define FUNC_H

#include "database.h"
#include <string>

void gch(DatabaseConnection& db, const std::string& dbPath);
void ech(DatabaseConnection& db, const std::string& dbPath);
void printQRCode(const std::string &text);

#endif //FUNC_H
