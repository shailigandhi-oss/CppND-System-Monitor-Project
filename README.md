# C++ System Monitor

A Linux system monitor application built with C++ that displays real-time system information similar to `htop`. This project is part of the Udacity C++ Nanodegree Program.

## Screenshots

### System Monitor in Action
![System Monitor](images/monitor.png)

### Starting Monitor
![Starting Monitor](images/starting_monitor.png)

## Overview

This system monitor displays:
- System information (OS, Kernel version, CPU, Memory, Uptime)
- CPU utilization
- Memory usage
- Running processes with their CPU/Memory usage, uptime, and command
- Real-time updates using ncurses display

## Dependencies

- **cmake** >= 2.6
  - All OSes: [click here for installation instructions](https://cmake.org/install/)
- **make** >= 4.1 (Linux)
  - Linux: `sudo apt-get install build-essential`
- **gcc/g++** >= 5.4
  - Linux: `sudo apt-get install build-essential`
- **ncurses**
  - Linux: `sudo apt-get install libncurses5-dev libncursesw5-dev`

## Build Instructions

1. Clone this repository
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Alternative: Use the Makefile directly: `make build`

## Run Instructions

1. After building, run the executable:
   ```bash
   ./build/monitor
   ```
   Or using the Makefile:
   ```bash
   make run
   ```

## Project Structure

```
.
├── include/              # Header files
│   ├── format.h         # Time formatting utilities
│   ├── linux_parser.h   # Linux system parsing functions
│   ├── ncurses_display.h # Display interface
│   ├── process.h        # Process class
│   ├── processor.h      # Processor class
│   └── system.h         # System class
├── src/                 # Source files
│   ├── format.cpp
│   ├── linux_parser.cpp
│   ├── main.cpp
│   ├── ncurses_display.cpp
│   ├── process.cpp
│   ├── processor.cpp
│   └── system.cpp
├── CMakeLists.txt       # CMake configuration
├── Makefile             # Build automation
└── README.md
```

## Key Components

- **System**: Main class that aggregates system information
- **Processor**: Handles CPU utilization calculations
- **Process**: Represents individual processes with their metrics
- **LinuxParser**: Parses `/proc` filesystem for system information
- **NCursesDisplay**: Provides terminal-based UI using ncurses
- **Format**: Utility functions for formatting time and other data

## Implementation Notes

- Uses C++17 standard
- Reads from Linux `/proc` filesystem for system information
- Compiles with `-Wall -Wextra` flags for strict error checking
- Real-time display updates using ncurses library

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

Copyright (c) 2019 Udacity
