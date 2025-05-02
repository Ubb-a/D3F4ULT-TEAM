//
// Created by Abdelrhman on 4/29/2025.
//

#ifndef ROOM_SE_H
#define ROOM_SE_H

#include <bits/stdc++.h>

using namespace std;

// Trash type definition
struct Trash {
    string name;        // Trash name
    string symbol;      // Console symbol for the trash
    int cleanTime;      // Time required to clean (seconds)
    string cleanCommand; // Command required to clean
};

// Function to display loading bar
void showLoadingBar(int percentage);

// Function to clear screen (works on Windows and Unix)
void clearScreen();

// Function to initialize trash types
vector<Trash> initializeTrashTypes();

// Function to start and run the trash cleaning game
// By default, will generate a random number of trash items between 1 and 20
void runTrashGame(int trashesToGenerate = 20);

#endif //ROOM_SE_H