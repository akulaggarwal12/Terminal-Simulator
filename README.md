# IC Project: System-Integrated Terminal Emulator

This repository contains the source code for **IC Project**, a professional-grade terminal emulator developed in C++ using the Raylib framework. The project focuses on bridging graphical user interfaces with low-level system command execution.

---

## Technical Overview

IC Project is designed to provide a stable, responsive command-line environment. It utilizes a virtual layout system to handle text rendering and command processing, ensuring that system-level operations are handled safely and efficiently.

### Key Functional Components

* **System Command Integration**: The core of the project involves functions linked directly to system commands. This includes the implementation of specialized commands like `/xgh` and others handled through the `aether` namespace.
* **Virtual Rendering Engine**: Implements a two-pass rendering logic. The first pass calculates the vertical bounds (`maxy`) of the terminal content, while the second pass renders the text. This prevents visual jitter during autoscrolling.
* **Command Logic**:
    * **Tab Completion**: A robust algorithm that identifies the longest common prefix for command and file suggestions.
    * **Input Management**: Full support for mid-string editing, cursor movement, and command history retrieval.
    * **Dynamic Layout**: Real-time adjustment of text wrapping and element positioning based on window dimensions.

---

## Prerequisites

To build and run this project, the following dependencies must be installed on your system:

* **C++ Compiler**: GCC (MinGW for Windows) or Clang, supporting C++17 or higher.
* **Raylib**: Version 4.0 or later.
* **Make** (Optional): For automated builds.

---

## Compilation and Build Instructions

The project requires linking the Raylib library and including all relevant source modules. Use the following commands based on your operating system.

### Using GCC (Linux/macOS)
```bash
g++ main.cpp -o ic_project -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

### Using MinGW (Windows)
```bash
g++ main.cpp -o ic_project.exe -lraylib -lgdi32 -lwinmm
```

### Build Parameters
| Flag | Description |
| :--- | :--- |
| `-lraylib` | Links the Raylib static/dynamic library. |
| `-o` | Defines the output executable name. |

---

## Usage and Commands

Once the executable is launched, the terminal accepts standard input. 

1.  **System Commands**: Enter commands directly into the prompt.
2.  **Special Commands**: Commands prefixed with `/` (such as `/xgh`) interface with the `aether` internal functions, made for linux, ubuntu distribution.
3.  **Navigation**:
    * **UP/DOWN**: Cycle through command history.
    * **LEFT/RIGHT**: Move the cursor within the current line for editing.
    * **TAB**: Trigger the autocompletion engine.
    * **F11**: Toggle fullscreen mode.

---

## Custom Wallpaper

We have built our custom wallpaper for the project as a symbol of our team, make sure the image is saved as "Image.png" and in the same parent file as the main.cpp.

---
