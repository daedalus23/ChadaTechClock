// Author: Jamie Wendle

#include <windows.h>
#include <iostream>
#include <iomanip>
#include <tuple>
#include <thread>
#include <map>
#include <sstream>

#include "Gui.h"
#include "Clock.h"


// Define a constructor for the Gui class
Gui::Gui(Clock& clockInstance, std::atomic<bool>& exitFlag) : clock(clockInstance), exitFlag(exitFlag) {
    // Define the initial menu items
    menuMap = {
        {"1", {"Add one hour.", [this]() { clock.AddOneHour(); }}},
        {"2", {"Add one minute.", [this]() { clock.AddOneMinute(); }}},
        {"3", {"Add one second.", [this]() { clock.AddOneSecond(); }}},
        {"4", {"Resync time.", [this]() { clock.ResyncTime(); }}}
    };

    // Calculate the index for the exit item
    std::ostringstream oss;
    oss << menuMap.size() + 1;
    USER_EXIT_INPUT = oss.str();

    // Add the exit item to the menu
    menuMap[USER_EXIT_INPUT] = { "Exit Program.", [this]() { /* Exit flag */ }};
}

// Define a function to move the cursor to a specific location on the screen
void Gui::Gotoxy(int x, int y) {
    COORD coord{};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

std::string Gui::CreateStringLength(size_t n, char c) {
    // Create a string of length n, filled with character c
    return std::string(n, c);
}

void Gui::ClearLine(int line) {
    Gotoxy(0, line);
    printf("\33[2K\r"); // Clear the line
}

void Gui::ClearScreen() {
	system("cls");
}

void Gui::PrintMenu() {
    int line = MENU_START_LINE;

    ClearLine(line); // Optional: Clear the line before printing
    Gotoxy(0, line++);
    std::cout << std::setfill(' ') << std::setw(4) << ' ' << CreateStringLength(MENU_BOARD_WIDTH, BOARD_ELEMENT);

    for (const auto& option : menuMap) {
        int optionTextLength = option.first.length() + 2 + option.second.first.length();
        int padding = MENU_OPTION_WIDTH - optionTextLength;

        ClearLine(line); // Optional: Clear the line before printing
        Gotoxy(0, line++);
        std::cout << std::setw(4) << ' ' << BOARD_ELEMENT << ' ' << option.first << ": " << option.second.first
            << std::setfill(' ') << std::setw(padding) << BOARD_ELEMENT;
    }

    ClearLine(line); // Optional: Clear the line before printing
    Gotoxy(0, line++);
    std::cout << std::setw(4) << ' ' << CreateStringLength(MENU_BOARD_WIDTH, BOARD_ELEMENT);
}

void Gui::HandleInput() {
    Gotoxy(0, INPUT_LINE);
    ClearLine(INPUT_LINE);
    std::cout << CHOICE_MSG;
    std::cin >> userInput;

    Gotoxy(0, ACTION_MESSAGE_LINE);
    ClearLine(ACTION_MESSAGE_LINE);

    if (menuMap.find(userInput) != menuMap.end()) {
        menuMap[userInput].second();
        std::cout << "Last command: " << menuMap[userInput].first;
    }
    else {
        std::cout << INVALID_MSG;
    }

    // Exit condition
    if (userInput == USER_EXIT_INPUT) {
        exitFlag.store(true);
        this->Gotoxy(0, ACTION_MESSAGE_LINE);
        std::cout << EXIT_MSG;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Give time to read message
    }
}

// Define a function to print a line of clocks
void Gui::PrintClock(const std::tuple<std::tuple<std::string, std::string>, std::tuple<std::string, std::string>> clocks) {
    // Unpack both clocks
    std::tuple<std::string, std::string> clock12 = std::get<0>(clocks);
    std::tuple<std::string, std::string> clock24 = std::get<1>(clocks);

    std::string title12 = std::get<0>(clock12);
    std::string time12 = std::get<1>(clock12);
    std::string title24 = std::get<0>(clock24);
    std::string time24 = std::get<1>(clock24);

    // Calculate positions
    int clock24StartX = START_X + CLOCK_GAP; // Adjust as needed for spacing between clocks

    // Print the clock titles and times side by side
    // Print header
    Gotoxy(START_X, START_Y);
    std::cout << std::setfill(BOARD_ELEMENT) << std::setw(CLOCK_BOARD_WIDTH) << BOARD_ELEMENT << '\t';
    Gotoxy(clock24StartX, START_Y);
    std::cout << std::setfill(BOARD_ELEMENT) << std::setw(CLOCK_BOARD_WIDTH) << BOARD_ELEMENT;

    // Print titles
    // 12-hour clock
    Gotoxy(START_X, START_Y + 1);
    std::cout << BOARD_ELEMENT << '\t' << title12 << '\t' << " " << BOARD_ELEMENT << '\t';
    // 24-hour clock
    Gotoxy(clock24StartX, START_Y + 1);
    std::cout << BOARD_ELEMENT << '\t' << title24 << '\t' << " " << BOARD_ELEMENT;

    // Print times
    // 12-hour clock
    Gotoxy(START_X, START_Y + 2);
    std::cout << BOARD_ELEMENT << '\t' << " " << time12 << '\t' << " " << BOARD_ELEMENT << '\t';
    // 24-hour clock
    Gotoxy(clock24StartX, START_Y + 2);
    std::cout << BOARD_ELEMENT << '\t' << "   " << time24 << '\t' << " " << BOARD_ELEMENT;

    // Print footer
    Gotoxy(START_X, START_Y + 3);
    std::cout << std::setfill(BOARD_ELEMENT) << std::setw(CLOCK_BOARD_WIDTH) << BOARD_ELEMENT << '\t';
    Gotoxy(clock24StartX, START_Y + 3);
    std::cout << std::setfill(BOARD_ELEMENT) << std::setw(CLOCK_BOARD_WIDTH) << BOARD_ELEMENT;

    // Move the cursor to the next line
    Gotoxy(INPUT_LINE_LENGTH, START_Y + INPUT_LINE);
}

// Define a function to print the main menu
bool Gui::Run() {
    ClearScreen();
    // Displaying each menu option
    PrintMenu();

    // Handling user input
    do {
        HandleInput();
    } while (!exitFlag.load());

    return exitFlag.load();
}
