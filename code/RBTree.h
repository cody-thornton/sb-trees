#ifndef RBTREE_H__
#define RBTREE_H__

#include <iostream>
#include <string>
#include <queue>

using namespace std;

#define BLACK "Black"
#define RED "Red"

class Node {
public:
    Node();
    ~Node();
    
    int key;
    string color;
    shared_ptr<Node> parent;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
};

class NodeQueue {
    NodeQueue();
    ~NodeQueue();

    vector<Node> queue;
};

class RBTree {
public:
    RBTree();
    ~RBTree();
    shared_ptr<Node> treeRoot;
    
    // General Functions
    shared_ptr<Node> InitNode(int keyVal);

    // Binary Search Tree Functions
    // (Node color is ignored in these functions).
    void BSTInsertKey(int key);
    void BSTInsertNode(shared_ptr<Node> newNode);
    shared_ptr<Node> BSTSearchKey(int keyVal);
    void BSTRemoveKey(int keyVal);

    // Red-Black Tree Insertion Functions
    bool RBTreeSetChild(
        shared_ptr<Node> parent, string whichChild, shared_ptr<Node> child);
    bool RBTreeReplaceChild(
        shared_ptr<Node> parent, shared_ptr<Node> currentChild, shared_ptr<Node> newChild);
    void RBTreeRotateLeft(shared_ptr<Node> node);
    void RBTreeRotateRight(shared_ptr<Node> node);
    shared_ptr<Node> RBTreeGetGrandparent(shared_ptr<Node> node);
    shared_ptr<Node> RBTreeGetUncle(shared_ptr<Node> node);
    void RBTreeBalance(shared_ptr<Node> node);
    void RBTreeInsertKey(int keyVal);
    void RBTreeInsertNode(shared_ptr<Node> node);

    // Red-Black Tree Removal Functions
    void RBTreeRemoveKey(int keyVal);
    void RBTreeRemoveNode(shared_ptr<Node> node);
    shared_ptr<Node> RBTreeGetPredecessor(shared_ptr<Node> node);
    shared_ptr<Node> RBTreeGetSibling(shared_ptr<Node> node);
    bool RBTreeIsNonNullAndRed(shared_ptr<Node> node);
    bool RBTreeIsNullOrBlack(shared_ptr<Node> node);
    bool RBTreeAreBothChildrenBlack(shared_ptr<Node> node);
    void RBTreePrepareForRemoval(shared_ptr<Node> node);
    bool RBTreeTryCase1(shared_ptr<Node> node);
    bool RBTreeTryCase2(shared_ptr<Node> node, shared_ptr<Node> sibling);
    bool RBTreeTryCase3(shared_ptr<Node> node, shared_ptr<Node> sibling);
    bool RBTreeTryCase4(shared_ptr<Node> node, shared_ptr<Node> sibling);
    bool RBTreeTryCase5(shared_ptr<Node> node, shared_ptr<Node> sibling);
    bool RBTreeTryCase6(shared_ptr<Node> node, shared_ptr<Node> sibling);

    // Miscellaneous Functions
    int GetTreeHeight(shared_ptr<Node> node);
    void Print();
    void PrintTree();
};

#endif // RBTREE_H__