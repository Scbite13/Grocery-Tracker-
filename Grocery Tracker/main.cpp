/*
Sabrina Bitecofer
April 16, 2025
Project Three: Grocery Tracker
*/
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>

// create class
class GroceryTracker {
private:
    std::map<std::string, int> itemFrequency;

public:
    // Load data from input file 
    void LoadData(const std::string& filename) {
        std::ifstream file(filename);
        std::string item;

        if (!file) {
            std::cerr << "Error: Unable to open input file.\n";
            return;
        }

        while (file >> item) {
            ++itemFrequency[item];
        }

        file.close();
        WriteBackupFile("frequency.dat");
    }

    // Menu option 1: Get item frequency
    int GetItemFrequency(const std::string& item) {
        if (itemFrequency.find(item) != itemFrequency.end()) {
            return itemFrequency[item];
        }
        return 0;
    }

    // Menu option 2: Print Frequency
    void PrintAllFrequencies() {
        for (const auto& pair : itemFrequency) {
            std::cout << pair.first << " " << pair.second << "\n";
        }
    }

    // Menu option 3: Print Histograph
    void PrintHistogram() {
        for (const auto& pair : itemFrequency) {
            std::cout << std::setw(12) << std::left << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                std::cout << "*";
            }
            std::cout << "\n";
        }
    }

    // Write the backup file
    void WriteBackupFile(const std::string& filename) {
        std::ofstream outFile(filename);
        for (const auto& pair : itemFrequency) {
            outFile << pair.first << " " << pair.second << "\n";
        }
        outFile.close();
    }
};

int main() {
    GroceryTracker tracker;
    tracker.LoadData("CS210_Project_Three_Input_File.txt");

    int choice;
    std::string itemName;

    do {
        std::cout << "\n=== Corner Grocer Menu ===\n";
        std::cout << "1. Search for item frequency\n";
        std::cout << "2. Print all item frequencies\n";
        std::cout << "3. Print histogram\n";
        std::cout << "4. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter item name: ";
            std::cin >> itemName;
            std::cout << itemName << " was purchased "
                << tracker.GetItemFrequency(itemName) << " times.\n";
            break;
        case 2:
            tracker.PrintAllFrequencies();
            break;
        case 3:
            tracker.PrintHistogram();
            break;
        case 4:
            std::cout << "Exiting program. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
