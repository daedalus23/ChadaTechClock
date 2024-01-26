// Author: Jamie Wendle

#include <windows.h> 
#include <iostream>
#include <iomanip>
#include <thread>
#include <tuple>
#include "Clock.h"  // Include the header file for the Clock class
#include "Gui.h"    // Include the header file for the Gui class


// This is a test line!

int main() {
    Clock clock;
    Gui gui{clock};
    std::atomic<bool> exitFlag = false;

    // Create a thread to handle clock updates and display
    std::thread clockThread([&clock, &gui, &exitFlag]() {
        while (!exitFlag.load()) {
            auto clocks = clock.GetTime();
            gui.PrintClock(clocks);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        });

    exitFlag = gui.Run();

    // Wait for the clock thread to finish
    if (clockThread.joinable()) {
        clockThread.join();
    }

    return 0;
}