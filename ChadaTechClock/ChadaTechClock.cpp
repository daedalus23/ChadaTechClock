// Author: Jamie Wendle

#include <windows.h> 
#include <iostream>
#include <iomanip>
#include <thread>
#include <tuple>
#include "Clock.h"  // Include the header file for the Clock class
#include "Gui.h"    // Include the header file for the Gui class



int main() {
    Clock clock;
    std::atomic<bool> exitFlag = false;
    Gui app{ clock, exitFlag };

    // Create a thread to handle clock updates and display
    std::thread clockThread([&clock, &app, &exitFlag]() {
        while (!exitFlag.load()) {
            auto clocks = clock.GetTime();
            app.PrintClock(clocks);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        });

    // Run the application's GUI event loop
    app.Run();

    // Signal the clock thread to stop and wait for it to finish
    exitFlag.store(true);
    if (clockThread.joinable()) {
        clockThread.join();
    }

    return 0;
}
