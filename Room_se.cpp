#include <bits/stdc++.h>
#include "Room_se.h"
#include "Design.h"

using namespace std;

void showLoadingBar(int percentage) {
    const int barWidth = 50;

    cout << "                                      [";
    int pos = barWidth * percentage / 100;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) cout << "=";
        else if (i == pos) cout << ">";
        else cout << " ";
    }
    cout << "] " << percentage << "%\r";
    cout.flush();
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Function to initialize trash types
vector<Trash> initializeTrashTypes() {
    vector<Trash> trashTypes = {
        {"Plastic Bottle", "🍶", 2, "recycle"},
        {"Metal Can", "🥫", 2, "metal"},
        {"Paper", "📄", 1, "paper"},
        {"Fruit Peels", "🍌", 1, "compost"},
        {"Glass Bottle", "🍾", 3, "glass"}
    };

    return trashTypes;
}

void room_service_g(int trashesToGenerate) {
    if (trashesToGenerate == 20) {
        srand(static_cast<unsigned int>(time(nullptr)));
        trashesToGenerate = rand() % 20 + 1;
    }
    srand(static_cast<unsigned int>(time(nullptr)));

    vector<Trash> trashTypes = initializeTrashTypes();

    vector<Trash> allTrash;

    for (int i = 0; i < trashesToGenerate; i++) {
        allTrash.push_back(trashTypes[rand() % trashTypes.size()]);
    }

    map<string, int> trashCleaned;
    for (const auto& trash : trashTypes) {
        trashCleaned[trash.cleanCommand] = 0;
    }

    int trashesRemaining = trashesToGenerate;

    clearScreen();

    room_service();
    cout << "                                        You need to clean trash using the appropriate commands." << endl;
    cout << "                                        Available commands: recycle, metal, paper, compost, glass" << endl;
    cout << "                                                   Press Enter to start...";
    cin.get();

    bool gameRunning = true;

    while (gameRunning && trashesRemaining > 0) {
        // Clear screen and redraw the game state for each new round
        clearScreen();
        room_service();

        // Display game information
        cout << "                                                   Trash Remaining: " << trashesRemaining << "/" << trashesToGenerate << endl;
        cout << "                                 Trash Cleaned: ";
        for (const auto& item : trashCleaned) {
            cout << item.first << ":" << item.second << " ";
        }
        cout << endl << endl;

        // Display all trash
        cout << "                                                   Current Trash:" << endl;
        for (size_t i = 0; i < allTrash.size(); ++i) {
            cout << "                                                   " << i+1 << ". " << allTrash[i].name << " " << allTrash[i].symbol << endl;
        }

        // Get user command
        cout << "\n                                         Enter cleaning command (or exit to quit): ";
        string command;
        cin >> command;

        if (command == "exit") {
            gameRunning = false;
            continue;
        }

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Check if command is valid
        bool validCommand = false;
        vector<size_t> matchingTrashIndices;

        for (size_t i = 0; i < allTrash.size(); ++i) {
            if (allTrash[i].cleanCommand == command) {
                matchingTrashIndices.push_back(i);
                validCommand = true;
            }
        }

        if (validCommand && !matchingTrashIndices.empty()) {
            // If there are multiple matching trash items, clean the first one
            size_t trashIndex = matchingTrashIndices[0];
            Trash trashToBeCleaned = allTrash[trashIndex];

            cout << "                                                   Cleaning " << trashToBeCleaned.name << " " << trashToBeCleaned.symbol << "..." << endl;

            for (int progress = 0; progress <= 100; progress += 5) {
                showLoadingBar(progress);
                this_thread::sleep_for(chrono::milliseconds(trashToBeCleaned.cleanTime * 50));
            }

            // Update
            trashCleaned[command]++;
            trashesRemaining--;

            allTrash.erase(allTrash.begin() + trashIndex);

            this_thread::sleep_for(chrono::milliseconds(1000));

        } else {
            cout << "Invalid command! No matching trash found." << endl;
            cout << "Valid commands are: recycle, metal, paper, compost, glass" << endl;

            // Brief pause to read the error message
            this_thread::sleep_for(chrono::seconds(2));
        }
    }
}