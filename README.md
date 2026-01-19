# OpenGL Graphics Programs (C/C++) – Windows (MSYS2 UCRT64)

This repository contains basic **Computer Graphics programs** implemented using **OpenGL (FreeGLUT)** in **C / C++**.  
 
It is part of the **Computer Graphics course syllabus** and intended for **educational purposes**.  

The programs are intended for **academic learning** and are configured to run on **Windows** using **MSYS2 (UCRT64)** and **Visual Studio Code**.


## System Requirements

- Windows 10 / 11  
- Visual Studio Code  
- MSYS2 (UCRT64)  
- GCC / G++ compiler  
- FreeGLUT (OpenGL Utility Toolkit)


## Required Libraries
**Important**

- `libfreeglut.dll` **MUST be present in the project folder** (C:\msys64\ucrt64\bin\libfreeglut.dll)
- Without this DLL, the program will **compile but will NOT run**
- The DLL should be in the **same folder as the `.exe` file**

> This is required because Windows needs the FreeGLUT runtime DLL at execution time.


## MSYS2 Setup

1. Download and install **MSYS2** from  
    https://www.msys2.org/

2. Install it in the default location:  

3. Open **MSYS2 UCRT64** terminal (this is very important).

4. Install required packages:
    ```bash
    pacman -S mingw-w64-ucrt-x86_64-gcc
    pacman -S mingw-w64-ucrt-x86_64-freeglut

5. Verify Installation:
    gcc --version


### Running the Program in VS Code

1. Open the `.c` or `.cpp` file you want to run.
2. Make sure `libfreeglut.dll` is in the same folder as the `.exe`.
3. Press **F5** in Visual Studio Code.

VS Code will:
- Compile the program using GCC from MSYS2
- Link OpenGL and FreeGLUT libraries
- Run the program
- Open a terminal for input and a graphics window for output

