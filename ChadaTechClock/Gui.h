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
        Clock& clock;
        std::string userInput;
        int returnLine;
        std::atomic<bool> exitFlag;
        std::ostringstream oss;

        std::string EXIT_MSG;
        std::string CHOICE_MSG;
        std::string INVALID_MSG;
        std::string USER_EXIT_INPUT;

        std::map <std::string, std::pair<std::string, std::function<void()>>> menuMap;

        static const int MENU_START_LINE = 5;
        static const int CLOCK_GAP = 40;
        static const int INPUT_LINE = 13;
        static const int INPUT_LINE_LENGTH = 19;
        static const int ACTION_MESSAGE_LINE = 14;
        static const int BOARD_WIDTH = 26;
        static const int START_X = 0;
        static const int START_Y = 0;

    public:
       
        Gui(Clock& clockInstance);
        void PrintMenu();
        void HandleInput();
        void Gotoxy(int x, int y);
        void PrintClock(const std::tuple<std::tuple<std::string, std::string>, std::tuple<std::string, std::string>> clocks);
        bool Run();
        void ClearLine(int line);
        void ClearScreen();
};
