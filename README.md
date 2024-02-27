# Simulation of Light Dip Detector

## Project Description
The primary objective of this application is to simulate the operation of an LED Light Dip Detector. The application consists of two main components: the Server and the Client side.The primary objective of this application is to simulate the operation of an LED Light Dip Detector. There are two part of the application which are Server and Client side

### Server

The Server is written in C and serves as the core component of the application. It is responsible for controlling the hardware and detecting light dips. 
Key features of the Server include:
- Dip Detection:
  - A "Dip" occurs when the light level drops below a threshold value, specifically 0.1V below the current average light level.
  - Detection of a "Dip" requires a voltage difference of 0.1V or more from the current average light level.
  - To prevent incorrect re-triggering due to noise, a hysteresis of 0.03V is applied, ensuring that another "Dip" cannot be detected until the light level returns above the threshold.
- Display Functionality:
  - The application displays the number of dips detected within a 1-second sampling batch.
  - The display utilizes 14-segment digits and is presented on the BeagleBone, a single-board computer developed by Texas Instruments, featuring an ARM-based microprocessor.
- Communication Interface:
  - The simulator allows communication with client devices via UDP messaging.
  - Clients can retrieve information such as the number of dips detected, historical sampling data, and the sampling batch size from the previous second.

The Server is a multi-threaded application designed to efficiently handle various tasks associated with light detection and display on the BeagleBone platform. It comprises several major threads, each responsible for specific functionalities:

- Shutdown Thread: Manages the orderly shutdown of the program once all other threads have completed their operations, and re-capture all resources.
- UDP Server Thread: Facilitates communication with clients, allowing them to retrieve data from the Light Dip Detector.
- LED Light Thread: Controls the flashing frequency of an LED light using Pulse Width Modulation (PWM) on the BeagleBone. The flashing frequency is adjusted based on the voltage value read from a potentiometer (POT).
- Digital Digit Display Thread: Handles the operation of displaying the number of light dips detected on the BeagleBone.
- Sampling:
  - Producer Sample Thread: Reads sampling data from the light sensor.
  - Consumer Sample Thread: Calculates the average exponential smoothing average voltage and detects the number of light dip events within a sampling batch.
  - Analyze Sample Thread: Analyzes statistical time periods, including the average time between events, the minimum/maximum time between events, and the total count of events.

This application aims to provide comprehensive functionality for monitoring and analyzing light data, facilitating communication with external clients, and controlling LED output based on sensor readings.

### Client

The client was written in Python which is a Graphical User Interface application which allow user to retrieve data from server and stop the server remotely
Key functionality of clients:
- Sending Message: This component manages communication between the client and server. It allows users to send commands to the server, including commands such as "help", "?", "length", "count", and "history".
- Listening Thread: A dedicated thread constantly listens for responses from the server. It retrieves data from the server and stores it for subsequent plotting and visualization.
- Data Visualization: The client application displays both raw data received from the server and visualizes this data on a graph, providing users with a comprehensive view of the information.

## General File Sturcture

- `hal/`: Contains all low-level hardware abstraction layer (HAL) modules
- `app/`: Contains all application-specific code. Broken into modules and a main file
- `build/`: Generated by CMake; stores all temporary build files (may be deleted to clean)

```
 .
  ├── app
  │   ├── include
  │   │   └── <file_name>.h
  │   ├── src
  │   │   ├── <file_name>.c
  │   │   └── main.c
  │   └── CMakeLists.txt           # Sub CMake file, just for app/
  ├── client_gui
  │   ├── client_gui.py
  ├── hal
  │   ├── include
  │   │   └── hal
  │   │       └── <hardware_filename>.h
  │   ├── src
  │   │   └── <hardware_filename>.c
  │   └── CMakeLists.txt           # Sub CMake file, just for hal/
  ├── CMakeLists.txt               # Main CMake file for the project
  └── README.md
```  

Note: This application is just to help you get started! It also has a bug in its computation (just for fun!)

## Usage

- Install CMake: `sudo apt update` and `sudo apt install cmake`
- When you first open the project, click the "Build" button in the status bar for CMake to generate the `build\` folder and recreate the makefiles.
  - When you edit and save a CMakeLists.txt file, VS Code will automatically update this folder.
- When you add a new file (.h or .c) to the project, you'll need to rerun CMake's build
  (Either click "Build" or resave `/CMakeLists.txt` to trigger VS Code re-running CMake)
- Cross-compile using VS Code's CMake addon:
  - The "kit" defines which compilers and tools will be run.
  - Change the kit via the menu: Help > Show All Commands, type "CMake: Select a kit".
    - Kit "GCC 10.2.1 arm-linux-gnueabi" builds for target.
    - Kit "Unspecified" builds for host (using default `gcc`).
  - Most CMake options for the project can be found in VS Code's CMake view (very left-hand side).
- Build the project using Ctrl+Shift+B, or by the menu: Terminal > Run Build Task...
  - If you try to build but get an error about "build is not a directory", the re-run CMake's build as mentioned above.

## Address Sanitizer

- The address sanitizer built into gcc/clang is very good at catching memory access errors.
- Enable it by uncomment the `fsanitize=address` lines in the root CMakeFile.txt.
- For this to run on the BeagleBone, you must run:
  `sudo apt install libasan6`
  - Without this installed, you'll get an error:   
    "error while loading shared libraries: libasan.so.6: cannot open shared object file: No such file or directory"

## Manually Running CMake

To manually run CMake from the command line use:

```shell
  # Regenerate build/ folder and makefiles:
  rm -rf build/         # Wipes temporary build folder
  cmake -S . -B build   # Generate makefiles in build\

  # Build (compile & link) the project
  cmake --build build
```
