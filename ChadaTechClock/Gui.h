// Author: Jamie Wendle

#pragma once

#include <tuple>
#include <string>
#include "Clock.h"
#include <functional>
#include <map>
#include <sstream>


class Gui
{
    private:
        std::string userInput;
        std::atomic<bool>& exitFlag;
        std::ostringstream oss;

        std::string EXIT_MSG = "Exiting program, goodbye...";
        std::string CHOICE_MSG = "Enter your choice: ";
        std::string INVALID_MSG = "Invalid input, please try again.";
        std::string USER_EXIT_INPUT;

        std::map <std::string, std::pair<std::string, std::function<void()>>> menuMap;

        static const char BOARD_ELEMENT = '*';

        static const int MENU_START_LINE = 5;
        static const int MENU_OPTION_WIDTH = 22;
        static const int MENU_BOARD_WIDTH = 24;
        static const int MENU_PADDING = 20;

        static const int CLOCK_GAP = 40;
        static const int CLOCK_BOARD_WIDTH = 26;

        static const int INPUT_LINE = 13;
        static const int INPUT_LINE_LENGTH = 19;
        static const int ACTION_MESSAGE_LINE = 14;
        
        static const int START_X = 0;
        static const int START_Y = 0;

    public:
        Gui(Clock& clockInstance, std::atomic<bool>& exitFlag);
        Clock& clock;
        void PrintMenu();
        void HandleInput();
        void Gotoxy(int x, int y);
        void PrintClock(const std::tuple<std::tuple<std::string, std::string>, std::tuple<std::string, std::string>> clocks);
        bool Run();
        void ClearLine(int line);
        void ClearScreen();
        std::string CreateStringLength(size_t n, char c);
};
