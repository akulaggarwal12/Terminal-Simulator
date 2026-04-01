# Aether - File Explorer Simulator

## About The Project
Aether is a visual, Terminal Simulator built entirely in C/C++. Utilizing the Raylib library for rendering, this project provides a graphical user interface (GUI) to navigate and interact with file directories. It simulates a virtual terminal environment where users can type commands to do various different tasks that are generally used for files or directories in real-time.

## Features
* **Graphical Interface:** Built completely from scratch using Raylib.
* **Interactive Window:** Typing and modifying will be real time interaction.
* **Path Tracking:** A live-updating address bar displaying the current directory path.
* **Custom Assets:** Custom Background Wallpaper is attached which adjusts itself with fullscreen mode.
* **Pure C/C++ Backend:** Efficient file and directory handling using standard C++ libraries.

## Built With
* [C++](https://cplusplus.com/) - Core application logic and backend.
* [Raylib](https://www.raylib.com/) - Rendering, window management, and input detection.

## Getting Started

### Prerequisites
To compile and run this project, you will need:
* A C++ compiler (GCC, Clang, or MSVC)
* [Raylib](https://github.com/raysan5/raylib) installed and configured on your system.
* [CMake / Make] (Optional: specify your build system here)

### Installation & Compilation
1. Clone the repository:  
   ```bash
   git clone https://github.com/akulaggarwal12/Terminal-Simulator.git
   ```


2. Compiling the Project:
Depending on your operating system and setup, choose the compilation method that works best for you.


**Option A: Terminal Compilation (Linux)**

Ensure you have Raylib installed system-wide, then run:
```bash
g++ main.cpp -o terminal -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```


**Option B: Terminal Compilation (Windows via MinGW)**

Assuming you have the Raylib `include` and `lib` folders set up in your compiler path or project directory:
```bash
g++ main.cpp -o terminal.exe -O2 -Wall -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
```


**Option C: Terminal Compilation (macOS)**

Using Clang with Raylib installed via Homebrew (`brew install raylib`):
```bash
clang++ main.cpp -o terminal -std=c++17 -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
```



3. Run the Application
Once compiled successfully, execute the generated file from your terminal to launch the simulator.


**On Linux or macOS:**
```bash
./terminal
```

**On Windows:**
```cmd
terminal.exe
```
