# Project: Red-Black Tree Implementation

This project was created as my final project in my Data Structures\
course. Class and Semester: CSPB2270 Fall 2020\

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

CMakeLists.txt      : Ignore this file.\
CMakeLists.txt.in   : Ignore this file.\ 
README.md           : Readme file.\
app\                : Application folder.\ 
main.cpp            :     Code demonstrating Red-Black\ 
                            Tree effiency.\
build\              : Build folder to build the project.\ 
                            Executables are here.\   
code\               : All code for Red-Black Tree implementation.\
RBTree.cpp          :     Red-Black Tree (RBTree) class source file\
RBTree.h            :     Red-Black Tree (RBTree) class header file\ 
tests\              : All code for Red-Black Tree test harnesses.\
test_RBTree.cpp     :     Tests and related helper functions source file.\ 

## How to Set Up This Project

This project should work identically to the homeworks. First, download the 
RedBlackTree.zip file uploaded to Moodle. Opening this file should decompress
its contents into the Folder/File RedBlackTree. Open this folder using Visual
Studio Code. Open an Integrated Terminal via the build folder. Press CTRL+SHIFT+B
to compile the code. The build folder should now contain the program's 
executables. Enter the command ./run_tests to verify that all tests pass. 
Enter ./run_app for a demonstration of Red-Black Tree's efficiency compared 
to Binary Search Trees. Source code can be reviewed in the main.cpp, RBTree.h,
RBTree.cpp, and test_RBTree.cpp files. 

## Dependencies
You need **gcc** and **cmake** installed to be able to compile this code.
