# ChadaTech Clock Program README

## Overview
The ChadaTech Clock program is a C++ console application designed to display the current time in both 12-hour and 24-hour formats. It features a simple GUI for user interaction, allowing users to manipulate the clock's time and synchronize it with the system clock. This application demonstrates effective use of C++ classes, multithreading, and GUI handling in a console environment.

## Features
- **Real-Time Clock Update:** Displays the current time, updating every second.
- **User Interaction:** Allows users to add hours, minutes, or seconds to the current time display.
- **Time Format Display:** Shows time in both 12-hour and 24-hour formats side by side.
- **Time Synchronization:** Provides an option to resynchronize the displayed time with the system's current time.

## Dependencies
- Windows API for console window manipulation.
- C++ STL libraries: `<iostream>`, `<iomanip>`, `<thread>`, `<tuple>`, `<map>`, and `<chrono>` for various functionalities including I/O operations, threading, and time handling.

## Compilation and Execution
Ensure you have a C++ compiler that supports C++11 or later. This program is designed for Windows due to its use of the Windows API. Compile the program with a command similar to:

```bash
g++ -o ChadaTechClock ChadaTechClock.cpp Clock.cpp Gui.cpp -std=c++11 -lwsock32
```

##File Structure
ChadaTechClock.cpp: Main program entry point, handling GUI and threading for clock updates.
Clock.cpp: Defines the Clock class responsible for time management and formatting.
Gui.cpp: Defines the Gui class, responsible for user interface and interaction.
Clock.h: Header file for the Clock class.
Gui.h: Header file for the Gui class.

##Program Usage
Upon running, the program displays the current time in both 12-hour and 24-hour formats. The user can interact with the program using the menu options:

Add one hour: Increments the displayed time by one hour.
Add one minute: Increments the displayed time by one minute.
Add one second: Increments the displayed time by one second.
Resync time: Synchronizes the displayed time with the system's current time.
Exit Program: Exits the application.

##Design and Implementation
Class-Based Design: Utilizes classes to encapsulate the logic for clock management (Clock) and user interface (Gui).
Multithreading: Separates the clock's time update logic and the GUI into different threads for real-time updates without blocking user input.
Map-Based Menu System: Uses a std::map to handle menu options and associated actions dynamically.

##Best Practices
In-line Comments: Code is well-documented with in-line comments explaining the functionality of major sections.
Naming Conventions: Adheres to standard naming conventions for variables, functions, and classes for readability.
Error Handling: Includes basic error handling for user input to ensure the program's robustness.

##Future Improvements
Extend compatibility for cross-platform usage.
Enhance the GUI for a more interactive user experience.
Implement additional features such as alarms and timers.
