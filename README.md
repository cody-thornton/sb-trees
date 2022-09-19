# Red-Black Tree Implementation and Asymptotic Analysis

This project was created as my final project in my Data Structures
course.

This project has the following folder tree:

├── CMakeLists.txt  
├── CMakeLists.txt.in  
├── README.md  
├── app  
│   └── main.cpp  
├── build  
├── code  
│   ├── RBTree.cpp  
│   └── RBTree.h  
└── tests  
    └── test_RBTree.cpp

CMakeLists.txt      : Ignore this file.<br>
CMakeLists.txt.in   : Ignore this file.<br>
README.md           : Readme file.<br>
app\                : Application folder.<br>
&emsp; main.cpp            :   Code demonstrating Red-Black Tree effiency.<br>
build\              : Build folder to build the project. Executables are here.<br>
code\               : All code for Red-Black Tree implementation.<br>
&emsp; RBTree.cpp          :   Red-Black Tree (RBTree) class source file<br>
&emsp; RBTree.h            :   Red-Black Tree (RBTree) class header file<br>
tests\              : All code for Red-Black Tree test harnesses.<br>
&emsp; test_RBTree.cpp     :    Tests and related helper functions source file.<br>

## How to Set Up This Project

Open this project using Visual Studio Code. Open an Integrated Terminal via the build
folder. Press CTRL+SHIFT+B to compile the code. The build folder should now contain 
the program's executables. Enter the command ./run_tests to verify that all tests pass. 
Enter ./run_app for a demonstration of Red-Black Tree's efficiency compared 
to Binary Search Trees. Source code can be reviewed in the main.cpp, RBTree.h,
RBTree.cpp, and test_RBTree.cpp files. 

## Dependencies
You need **gcc** and **cmake** installed to be able to compile this code.
