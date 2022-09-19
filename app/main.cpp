#include <iostream>
#include "../code/RBTree.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime> 
#include <cmath>

using namespace std;

int main(){
    RBTree myTree;
    myTree.RBTreeInsertKey(13);
    myTree.RBTreeInsertKey(45);
    myTree.RBTreeInsertKey(24);
    myTree.RBTreeInsertKey(67);
    myTree.RBTreeInsertKey(34);
    myTree.RBTreeInsertKey(50);

    myTree.PrintTree();

    /*
    int numTrees;
    int numValues;
    int maxValue;
    int logNumValues;
    vector<int> integerValues;
    RBTree redBlackTree;
    RBTree binarySearchTree;
    float redBlackHeights;
    float binarySearchHeights;
    float avgRedBlackHeight;
    float avgBinarySearchHeight;

    numTrees            = 100;
    numValues           = 256;
    maxValue            = 10000;
    logNumValues        = log2(numValues);
    redBlackHeights     = 0.0;
    binarySearchHeights = 0.0;

    for (int i = 0; i < numTrees; i++) {        
        // Populate the vector 'integerValues' with a number (equal to numValues) of random integers.
        srand(time(0));  // Unique seed
        for (int i = 0; i < numValues; i++) {
            integerValues.push_back(rand() % maxValue);
        }
        
        // Build a Red-Black Tree and a Binary Search Tree with these values.
        for (int i = 0; i < integerValues.size(); i++) {
            redBlackTree.RBTreeInsertKey(integerValues.at(i));
            binarySearchTree.BSTInsertKey(integerValues.at(i));
        }

        // Determine height of resulting Red-Black Tree and Binary Search Trees.
        redBlackHeights += redBlackTree.GetTreeHeight(redBlackTree.treeRoot);
        binarySearchHeights += binarySearchTree.GetTreeHeight(binarySearchTree.treeRoot);

        // Clear Red-Black Tree and Binary Search Trees of values.
        redBlackTree.treeRoot     = nullptr;
        binarySearchTree.treeRoot = nullptr;
    }

    // Calculate average heights.
    avgRedBlackHeight     = redBlackHeights / numTrees;
    avgBinarySearchHeight = binarySearchHeights / numTrees;

    // Print report of results.
    cout << endl;
    cout << "Built " << numTrees << " trees each of Red-Black Trees and Binary Search Trees." << endl;
    cout << "Each tree contained ";
    cout << numValues;
    cout << " random integers between 1 and ";
    cout << maxValue << ".";
    cout << endl;
    cout << endl;
    cout << "Ideal O(log2) Height would be         : " << logNumValues << endl;
    cout << "Average Red-Black Tree Height was     : " << avgRedBlackHeight << endl;
    cout << "Average Binary Search Tree Height was : " << avgBinarySearchHeight << endl;
    cout << endl;
    cout << endl;
    */

    return 0;
}