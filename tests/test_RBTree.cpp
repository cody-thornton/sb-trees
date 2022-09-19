#include <gtest/gtest.h>
#include "../code/RBTree.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime> 
#include <cmath>

using namespace std;

class test_RBTree : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
	}
    
	// this function runs before every TEST_F function
	void SetUp() override {
    }

	// this function runs after every TEST_F function
	void TearDown() override {
	}
};

// Helper Functions Declarations
void AssignNodeAttributes(
    shared_ptr<Node> node,
    int keyVal, string color, 
    shared_ptr<Node> parentPtr, shared_ptr<Node> leftPtr, shared_ptr<Node> rightPtr);
shared_ptr<Node> GetThreeNodeTree();
shared_ptr<Node> GetUnbalancedLeftBracket();
shared_ptr<Node> GetUnbalancedRightBracket();
shared_ptr<Node> GetSevenNodeTree();
shared_ptr<Node> GetTwelveNodeTree();

//////////////////////
//////////////////////
//////////////////////   T E S T   F U N C T I O N S
////////////////////// 
//////////////////////

TEST_F(test_RBTree, TestInitNode) {
    RBTree testingTree;
    int testVal;
    shared_ptr<Node> testNode;

    testVal = -5;
    testNode = testingTree.InitNode(testVal);
    ASSERT_EQ(testNode->key, testVal);
    ASSERT_EQ(testNode->color, RED);
    ASSERT_FALSE(testNode->parent);
    ASSERT_FALSE(testNode->left);
    ASSERT_FALSE(testNode->right);
    
    testVal = 0;
    testNode = testingTree.InitNode(testVal);
    ASSERT_EQ(testNode->key, testVal);
    ASSERT_EQ(testNode->color, RED);
    ASSERT_FALSE(testNode->parent);
    ASSERT_FALSE(testNode->left);
    ASSERT_FALSE(testNode->right);

    testVal = 17;
    testNode = testingTree.InitNode(testVal);
    ASSERT_EQ(testNode->key, testVal);
    ASSERT_EQ(testNode->color, RED);
    ASSERT_FALSE(testNode->parent);
    ASSERT_FALSE(testNode->left);
    ASSERT_FALSE(testNode->right);
}

TEST_F(test_RBTree, TestBSTInsertKey) {
    RBTree testingTreeOne;
    RBTree testingTreeTwo;

    // testingTreeOne is empty tree.
    testingTreeOne.treeRoot = nullptr;

    // Insertion of node into testingTreeOne should set tree's treeRoot pointer
    // to this new node.
    testingTreeOne.RBTreeInsertKey(13);
    ASSERT_TRUE(testingTreeOne.treeRoot);
    ASSERT_EQ(testingTreeOne.treeRoot->key, 13);

    // Insertion of additional node with key value smaller than treeRoot's key value
    // should not affect treeRoot and should be inserted to the left of treeRoot. 
    // This new node should be treeRoot's left child and should have treeRoot as its parent. 
    testingTreeOne.RBTreeInsertKey(6);
    ASSERT_TRUE(testingTreeOne.treeRoot);
    ASSERT_EQ(testingTreeOne.treeRoot->key, 13);
    ASSERT_TRUE(testingTreeOne.treeRoot->left);
    ASSERT_EQ(testingTreeOne.treeRoot->left->key, 6);
    ASSERT_EQ(testingTreeOne.treeRoot->left->parent, testingTreeOne.treeRoot);

    // Insertion of additional node with key value larger than treeRoot's key value
    // should not affect treeRoot or treeRoot's existing left child and should be inserted 
    // to the right of treeRoot.
    // This new node should be treeRoot's right child and should have treeRoot as its parent. 
    testingTreeOne.RBTreeInsertKey(20);
    ASSERT_TRUE(testingTreeOne.treeRoot);
    ASSERT_EQ(testingTreeOne.treeRoot->key, 13);
    ASSERT_TRUE(testingTreeOne.treeRoot->left);
    ASSERT_EQ(testingTreeOne.treeRoot->left->key, 6);
    ASSERT_EQ(testingTreeOne.treeRoot->left->parent, testingTreeOne.treeRoot);
    ASSERT_TRUE(testingTreeOne.treeRoot->right);
    ASSERT_EQ(testingTreeOne.treeRoot->right->key, 20);
    ASSERT_EQ(testingTreeOne.treeRoot->right->parent, testingTreeOne.treeRoot);

    // testingTreeTwo is twelve-node tree. 
    testingTreeTwo.treeRoot = GetTwelveNodeTree();

    // Insertion of additional nodes into TwelveNodeTree should
    // be perfomed in accordance with binary search tree invariants and update 
    // relevant child and parent pointers. 
    testingTreeTwo.BSTInsertKey(26);
    ASSERT_TRUE(testingTreeTwo.treeRoot->left->right->right->right);
    ASSERT_EQ(testingTreeTwo.treeRoot->left->right->right->right->key, 26);
    ASSERT_EQ(testingTreeTwo.treeRoot->left->right->right->right->parent, 
        testingTreeTwo.treeRoot->left->right->right);
    testingTreeTwo.BSTInsertKey(44);
    ASSERT_TRUE(testingTreeTwo.treeRoot->right->right->left);
    ASSERT_EQ(testingTreeTwo.treeRoot->right->right->left->key, 44);
    ASSERT_EQ(testingTreeTwo.treeRoot->right->right->left->parent, 
        testingTreeTwo.treeRoot->right->right);
}

TEST_F(test_RBTree, TestBSTInsertNode) {
    shared_ptr<Node> twentythree (new Node);
    shared_ptr<Node> nine (new Node);
    shared_ptr<Node> fortyseven (new Node);

    AssignNodeAttributes(twentythree, 23, BLACK, nullptr, nullptr, nullptr);
    AssignNodeAttributes(nine, 9, RED, nullptr, nullptr, nullptr);
    AssignNodeAttributes(fortyseven, 47, RED, nullptr, nullptr, nullptr);

    // testingTreeOne is an empty tree
    RBTree testingTreeOne;
    testingTreeOne.treeRoot = nullptr;

    // After inserting the node 'twentythree' the root should be 'twentythree'.
    testingTreeOne.BSTInsertNode(twentythree);
    ASSERT_TRUE(testingTreeOne.treeRoot);
    ASSERT_EQ(testingTreeOne.treeRoot, twentythree);

    // Inserting 'nine' should cause 'nine' to be the left child of treeRoot.
    testingTreeOne.BSTInsertNode(nine);
    ASSERT_TRUE(testingTreeOne.treeRoot->left);
    ASSERT_EQ(testingTreeOne.treeRoot->left, nine);

    // Inserting 'fortyseven' should cause 'fortyseven' to be the right child of treeRoot.
    testingTreeOne.BSTInsertNode(fortyseven);
    ASSERT_TRUE(testingTreeOne.treeRoot->right);
    ASSERT_EQ(testingTreeOne.treeRoot->right, fortyseven);

    // testingTreeTwo is a twelve node tree
    RBTree testingTreeTwo;
    testingTreeTwo.treeRoot = GetTwelveNodeTree();

    // Insertion of nodes should place them in tree according to binary search tree invariant.
    testingTreeTwo.BSTInsertNode(nine);
    testingTreeTwo.BSTInsertNode(twentythree);
    testingTreeTwo.BSTInsertNode(fortyseven);
    // 'nine'
    ASSERT_TRUE(testingTreeTwo.treeRoot->left->left->left->right);
    ASSERT_EQ(testingTreeTwo.treeRoot->left->left->left->right, nine);
    // 'twentythree'
    ASSERT_TRUE(testingTreeTwo.treeRoot->left->right->right->left);
    ASSERT_EQ(testingTreeTwo.treeRoot->left->right->right->left, twentythree);
    // 'fortyseven'
    ASSERT_TRUE(testingTreeTwo.treeRoot->right->right->left);
    ASSERT_EQ(testingTreeTwo.treeRoot->right->right->left, fortyseven);
}

TEST_F(test_RBTree, TestBSTSearchKey) {
    RBTree testingTree;
    shared_ptr<Node> node;

    testingTree.treeRoot = GetTwelveNodeTree();
    
    node = testingTree.BSTSearchKey(37);
    ASSERT_EQ(node->key, 37);

    node = testingTree.BSTSearchKey(19);
    ASSERT_EQ(node->key, 19);

    node = testingTree.BSTSearchKey(6);
    ASSERT_EQ(node->key, 6);

    // Node not found; should return nullptr
    node = testingTree.BSTSearchKey(26);
    ASSERT_EQ(node, nullptr);

    // Node not found; should return nullptr
    node = testingTree.BSTSearchKey(51);
    ASSERT_EQ(node, nullptr);
}

TEST_F(test_RBTree, TestBSTRemoveKey) {
    RBTree testingTree;
    
    // Make altered twelve node tree
    testingTree.treeRoot = GetTwelveNodeTree();
    testingTree.treeRoot->left->left->right = nullptr;

    // Altered tree:
    /*
    
                                        (33 : Black)
                                       /           \
                                      /             \
                                     /               \
                                    /                 \
                          (17 : Red)                  (42 : Red)
                          /       \                  /          \
                         /         \                /            \
                        /           \              /              \
             (11 : Black)    (20 : Black)      (37 : Black)      (50 : Black)
            /                /      \                                  \
           /                /        \                                  \
          /                /          \                                  \
      (6:Red)          (19:Red)    (25:Red)                           (53:Red)
                   
    */

    // Remove node with no children
    testingTree.BSTRemoveKey(37);

    // Remove node with no children
    testingTree.BSTRemoveKey(25);

    // Remove node with left child only
    testingTree.BSTRemoveKey(11);
   
    // Remove node with right child only
    testingTree.BSTRemoveKey(50);
   
    // Remove node with two children
    testingTree.BSTRemoveKey(33);

    // Remove node with two children
    testingTree.BSTRemoveKey(17);

    // Altered tree after function calls:
    /*
                    (42 : Red)
                     /     \
                    /       \
                   /         \
                  /           \
            (19 : Red)     (53 : Red)
            /     \                          
           /       \                          
          /         \                          
    (6 : Red)     (20 : Black)                                             
    */
    ASSERT_EQ(testingTree.treeRoot->key, 42);
    ASSERT_EQ(testingTree.treeRoot->left->key, 19);
    ASSERT_EQ(testingTree.treeRoot->right->key, 53);
    ASSERT_EQ(testingTree.treeRoot->left->left->key, 6);
    ASSERT_EQ(testingTree.treeRoot->left->right->key, 20);
}

TEST_F(test_RBTree, TestRBTreeSetChild) {
    shared_ptr<Node> twentythree (new Node);
    shared_ptr<Node> nine (new Node);
    shared_ptr<Node> fortyseven (new Node);

    AssignNodeAttributes(twentythree, 33, BLACK, nullptr, nullptr, nullptr);
    AssignNodeAttributes(nine, 17, RED, nullptr, nullptr, nullptr);
    AssignNodeAttributes(fortyseven, 42, RED, nullptr, nullptr, nullptr);

    RBTree testingTree;
    testingTree.treeRoot = twentythree;
    testingTree.RBTreeSetChild(twentythree, "left", nine);
    testingTree.RBTreeSetChild(twentythree, "right", fortyseven);

    RBTree answerTree;
    answerTree.treeRoot = GetThreeNodeTree();
    
    // testingTree and answerTree's keys should be the same
    ASSERT_EQ(testingTree.treeRoot->key, answerTree.treeRoot->key);
    ASSERT_EQ(testingTree.treeRoot->left->key, answerTree.treeRoot->left->key);
    ASSERT_EQ(testingTree.treeRoot->right->key, answerTree.treeRoot->right->key);

    // testingTree and answerTree's parents should be the same
    ASSERT_EQ(testingTree.treeRoot->left->parent->key, answerTree.treeRoot->left->parent->key);
    ASSERT_EQ(testingTree.treeRoot->right->parent->key, answerTree.treeRoot->right->parent->key);
}

TEST_F(test_RBTree, TestRBTreeReplaceChild) {
    shared_ptr<Node> twentythree (new Node);
    shared_ptr<Node> twenty (new Node);
    shared_ptr<Node> fifty (new Node);
    shared_ptr<Node> nine (new Node);
    shared_ptr<Node> fortyseven (new Node);

    AssignNodeAttributes(twentythree, 33, BLACK, nullptr, twenty, fifty);
    AssignNodeAttributes(twenty, 20, RED, twentythree, nullptr, nullptr);
    AssignNodeAttributes(fifty, 50, RED, twentythree, nullptr, nullptr);
    AssignNodeAttributes(nine, 17, RED, nullptr, nullptr, nullptr);
    AssignNodeAttributes(fortyseven, 42, RED, nullptr, nullptr, nullptr);
    
    RBTree testingTree;
    testingTree.treeRoot = twentythree;
    testingTree.RBTreeReplaceChild(twentythree, twenty, nine);
    testingTree.RBTreeReplaceChild(twentythree, fifty, fortyseven);

    RBTree answerTree;
    answerTree.treeRoot = GetThreeNodeTree();
    
    // testingTree and answerTree's root should be the same value
    ASSERT_EQ(testingTree.treeRoot->key, answerTree.treeRoot->key);

    // testingTree and answerTree's children should be the same values
    ASSERT_EQ(testingTree.treeRoot->left->key, answerTree.treeRoot->left->key);
    ASSERT_EQ(testingTree.treeRoot->right->key, answerTree.treeRoot->right->key);

    // testingTree and answerTree's parents should be the same values
    ASSERT_EQ(testingTree.treeRoot->left->parent->key, answerTree.treeRoot->left->parent->key);
    ASSERT_EQ(testingTree.treeRoot->right->parent->key, answerTree.treeRoot->right->parent->key);
}

// Tests that RBTreeRotateLeft works with non-null rightLeftChild.
TEST_F(test_RBTree, TestRBTreeRotateLeft) {
    RBTree testingTree;
    testingTree.treeRoot = GetSevenNodeTree();

    testingTree.RBTreeRotateLeft(testingTree.treeRoot);
    
    ASSERT_EQ(testingTree.treeRoot->key, 42);
    ASSERT_EQ(testingTree.treeRoot->left->key, 33);
    ASSERT_EQ(testingTree.treeRoot->left->left->key, 17);
    ASSERT_EQ(testingTree.treeRoot->left->right->key, 37);
}

// Tests that RBTreeRotateRight works with non-null leftRightChild.
TEST_F(test_RBTree, TestRBTreeRotateRight) {
    RBTree testingTree;
    testingTree.treeRoot = GetSevenNodeTree();

    testingTree.RBTreeRotateRight(testingTree.treeRoot); 

    ASSERT_EQ(testingTree.treeRoot->key, 17);
    ASSERT_EQ(testingTree.treeRoot->right->key, 33);
    ASSERT_EQ(testingTree.treeRoot->right->right->key, 42);
    ASSERT_EQ(testingTree.treeRoot->right->left->key, 20);
}

TEST_F(test_RBTree, TestRBTreeRotateLeftandRight) {
    // This test will seek to transform a GetUnbalancedLeftBracket() tree and
    // a GetUnbalancedRightBracket() tree into a GetThreeNodeTree() by means of 
    // left and right rotations.
    RBTree answerTree;
    answerTree.treeRoot = GetThreeNodeTree();
    
    RBTree testingTreeOne;
    testingTreeOne.treeRoot = GetUnbalancedLeftBracket();
    // The following Left-Right Rotation should transofrm testingTreeOne into answerTree.
    // (Although testingTreeOne's node colors are not correct).
    testingTreeOne.RBTreeRotateLeft(testingTreeOne.treeRoot->left);
    testingTreeOne.RBTreeRotateRight(testingTreeOne.treeRoot);

    RBTree testingTreeTwo;
    testingTreeTwo.treeRoot = GetUnbalancedRightBracket();
    // The following Right-Left Rotation should transofrm testingTreeTwo into answerTree.
    // (Although testingTreeTwo's node colors do not follow Red-Black Tree invariants).
    testingTreeTwo.RBTreeRotateRight(testingTreeTwo.treeRoot->right);
    testingTreeTwo.RBTreeRotateLeft(testingTreeTwo.treeRoot);

    // Test testingTreeOne
    // testingTreeOne and answerTree's root should be the same value
    ASSERT_EQ(testingTreeOne.treeRoot->key, answerTree.treeRoot->key);

    // testingTreeOne and answerTree's children should be the same values
    ASSERT_EQ(testingTreeOne.treeRoot->left->key, answerTree.treeRoot->left->key);
    ASSERT_EQ(testingTreeOne.treeRoot->right->key, answerTree.treeRoot->right->key);

    // testingTreeOne and answerTree's parents should be the same values
    ASSERT_EQ(testingTreeOne.treeRoot->left->parent->key, answerTree.treeRoot->left->parent->key);
    ASSERT_EQ(testingTreeOne.treeRoot->right->parent->key, answerTree.treeRoot->right->parent->key);

    // Test testingTreeTwo
    // testingTreeTwo and answerTree's root should be the same values
    ASSERT_EQ(testingTreeTwo.treeRoot->key, answerTree.treeRoot->key);

    // testingTreeTwo and answerTree's children should be the same values
    ASSERT_EQ(testingTreeTwo.treeRoot->left->key, answerTree.treeRoot->left->key);
    ASSERT_EQ(testingTreeTwo.treeRoot->right->key, answerTree.treeRoot->right->key);

    // testingTreeTwo and answerTree's parents should be the same values
    ASSERT_EQ(testingTreeTwo.treeRoot->left->parent->key, answerTree.treeRoot->left->parent->key);
    ASSERT_EQ(testingTreeTwo.treeRoot->right->parent->key, answerTree.treeRoot->right->parent->key);
}

TEST_F(test_RBTree, TestRBTreeGetGrandparent) {
    shared_ptr<Node> grandparent;
    shared_ptr<Node> nullGrandparent;

    RBTree testingTree;
    testingTree.treeRoot = GetUnbalancedLeftBracket();

    grandparent     = testingTree.RBTreeGetGrandparent(testingTree.treeRoot->left->right);
    nullGrandparent = testingTree.RBTreeGetGrandparent(testingTree.treeRoot->left);

    // testingTreeTwo and answerTree's parents should be the same values
    ASSERT_EQ(grandparent->key, 42);
    ASSERT_EQ(nullGrandparent, nullptr);
}

TEST_F(test_RBTree, TestRBTreeGetUncle) {
    shared_ptr<Node> leftUncle;
    shared_ptr<Node> rightUncle;
    shared_ptr<Node> nullUncle;

    RBTree testingTreeOne;
    testingTreeOne.treeRoot = GetSevenNodeTree();

    // node has left uncle
    leftUncle = testingTreeOne.RBTreeGetUncle(testingTreeOne.treeRoot->right->left);
    ASSERT_EQ(leftUncle->key, 17);

    // node has right uncle
    rightUncle = testingTreeOne.RBTreeGetUncle(testingTreeOne.treeRoot->left->right);
    ASSERT_EQ(rightUncle->key, 42);

    // node has null parent so uncle is null
    nullUncle = testingTreeOne.RBTreeGetUncle(testingTreeOne.treeRoot);
    ASSERT_EQ(nullUncle, nullptr);

    // node has null grandparent so uncle is null
    nullUncle = testingTreeOne.RBTreeGetUncle(testingTreeOne.treeRoot);
    ASSERT_EQ(nullUncle, nullptr);

    // node has no left uncle so uncle is null
    RBTree testingTreeTwo;
    testingTreeTwo.treeRoot = GetUnbalancedRightBracket();
    nullUncle = testingTreeTwo.RBTreeGetUncle(testingTreeTwo.treeRoot->right->left);
    ASSERT_EQ(nullUncle, nullptr);

    // node has no right uncle so uncle is null
    RBTree testingTreeThree;
    testingTreeThree.treeRoot = GetUnbalancedLeftBracket();
    nullUncle = testingTreeThree.RBTreeGetUncle(testingTreeThree.treeRoot->left->right);
    ASSERT_EQ(nullUncle, nullptr);
}

TEST_F(test_RBTree, TestRBTreeBalance) {
    RBTree testingTree;

    // TEST CASE 1
    // If 'node' is tree's root, it should turn black.
    shared_ptr<Node> thirteen (new Node);
    AssignNodeAttributes(thirteen, 13, RED, nullptr, nullptr, nullptr);
    testingTree.treeRoot = thirteen;
    testingTree.RBTreeBalance(thirteen);
    ASSERT_EQ(thirteen->color, BLACK);

    // TEST CASE 2
    // If 'node' has black parent, return without alterations.
    testingTree.treeRoot = GetThreeNodeTree();
    /*
            (33 : Black)
             /        \
       (17 : Red)   (42 : Red)
    */
    testingTree.RBTreeBalance(testingTree.treeRoot->left);
    testingTree.RBTreeBalance(testingTree.treeRoot->right);
    ASSERT_EQ(testingTree.treeRoot->left->key, 17);
    ASSERT_EQ(testingTree.treeRoot->left->color, RED);
    ASSERT_EQ(testingTree.treeRoot->right->key, 42);
    ASSERT_EQ(testingTree.treeRoot->right->color, RED);

    // TEST CASE 3
    // If 'node' has red uncle ("Red Uncle Case").
    // Create altered, unbalanced twelve node tree.
    testingTree.treeRoot = GetTwelveNodeTree();
    testingTree.treeRoot->left->color = BLACK;
    testingTree.treeRoot->left->left->color = RED;
    testingTree.treeRoot->left->right->color = RED;
    /*
                                        (33 : Black)
                                       /           \
                                      /             \
                                     /               \
                                    /                 \
                         (17 : BLACK)                (42 : Red)
                          /       \                  /          \
                         /         \                /            \
                        /           \              /              \
            (11  :  RED)     (20  :  RED)      (37 : Black)      (50 : Black)
            /    \            /    \                                    \
           /      \          /      \                                    \
          /        \        /        \                                    \
      (6:Red) (13:Red)  (19:Red) (25:Red)                               (53:Red)               
    */
    // Calling RBTreeBalance on node 6 should activate "Red Uncle Case" and rebalance
    // tree.
    testingTree.RBTreeBalance(testingTree.treeRoot->left->left->left);
    ASSERT_EQ(testingTree.treeRoot->left->color, RED);
    ASSERT_EQ(testingTree.treeRoot->left->left->color, BLACK);
    ASSERT_EQ(testingTree.treeRoot->left->right->color, BLACK);

    // TEST CASE 4
    // If node has no uncle (or uncle is black) and "left bracket case"...
    testingTree.treeRoot = GetUnbalancedLeftBracket();
    /*
      (42 : Black)        
       /                               
    (17 : Red)       ->        (33 : Black) 
       \                         /      \
      (33 : Red)          (17 : Red)   (42 : Red)
    */
    testingTree.RBTreeBalance(testingTree.treeRoot->left->right);
    ASSERT_EQ(testingTree.treeRoot->key, 33);
    ASSERT_EQ(testingTree.treeRoot->color, BLACK);
    ASSERT_EQ(testingTree.treeRoot->left->key, 17);
    ASSERT_EQ(testingTree.treeRoot->left->color, RED);
    ASSERT_EQ(testingTree.treeRoot->right->key, 42);
    ASSERT_EQ(testingTree.treeRoot->right->color, RED);

    // TEST CASE 5
    // If node has no uncle (or uncle is black) and "right bracket case"... 
    testingTree.treeRoot = GetUnbalancedRightBracket();
    /*
    (17 : Black)              
        \                          
      (42 : Red)        ->        (33 : Black) 
        /                           /      \
    (33 : Red)               (17 : Red)   (42 : Red)
    */
    testingTree.RBTreeBalance(testingTree.treeRoot->right->left);
    ASSERT_EQ(testingTree.treeRoot->key, 33);
    ASSERT_EQ(testingTree.treeRoot->color, BLACK);
    ASSERT_EQ(testingTree.treeRoot->left->key, 17);
    ASSERT_EQ(testingTree.treeRoot->left->color, RED);
    ASSERT_EQ(testingTree.treeRoot->right->key, 42);
    ASSERT_EQ(testingTree.treeRoot->right->color, RED);
}

TEST_F(test_RBTree, TestRBTreeInsertKey) {
    RBTree testingTree;

    // Inserted sorted, ascending values.
    testingTree.RBTreeInsertKey(11);
    testingTree.RBTreeInsertKey(22);
    testingTree.RBTreeInsertKey(33);
    testingTree.RBTreeInsertKey(44);
    testingTree.RBTreeInsertKey(55);
    testingTree.RBTreeInsertKey(66);
    testingTree.RBTreeInsertKey(77);
    testingTree.RBTreeInsertKey(88);

    // Check tree root.
    ASSERT_EQ(testingTree.treeRoot->key, 44);
    ASSERT_EQ(testingTree.treeRoot->color, BLACK);
    
    // Check tree root's left subtree.
    ASSERT_EQ(testingTree.treeRoot->left->key, 22);
    ASSERT_EQ(testingTree.treeRoot->left->color, RED);
    ASSERT_EQ(testingTree.treeRoot->left->left->key, 11);
    ASSERT_EQ(testingTree.treeRoot->left->left->color, BLACK);
    ASSERT_EQ(testingTree.treeRoot->left->right->key, 33);
    ASSERT_EQ(testingTree.treeRoot->left->right->color, BLACK);

    // Check tree root's right subtree.
    ASSERT_EQ(testingTree.treeRoot->right->key, 66);
    ASSERT_EQ(testingTree.treeRoot->right->color, RED);
    ASSERT_EQ(testingTree.treeRoot->right->left->key, 55);
    ASSERT_EQ(testingTree.treeRoot->right->left->color, BLACK);
    ASSERT_EQ(testingTree.treeRoot->right->right->key, 77);
    ASSERT_EQ(testingTree.treeRoot->right->right->color, BLACK);
    ASSERT_EQ(testingTree.treeRoot->right->right->right->key, 88);
    ASSERT_EQ(testingTree.treeRoot->right->right->right->color, RED);
}

TEST_F(test_RBTree, TestRBTreeInsertNode) {
    RBTree testingTree;

    shared_ptr<Node> eightyeight (new Node);
    shared_ptr<Node> seventyseven (new Node);
    shared_ptr<Node> sixtysix (new Node);
    shared_ptr<Node> fiftyfive (new Node);
    shared_ptr<Node> fortyfour (new Node);
    shared_ptr<Node> thirtythree (new Node);
    shared_ptr<Node> twentytwo (new Node);
    shared_ptr<Node> eleven (new Node);

    AssignNodeAttributes(eightyeight, 88, RED, nullptr, nullptr, nullptr);
    AssignNodeAttributes(seventyseven, 77, RED, nullptr, nullptr, nullptr);
    AssignNodeAttributes(sixtysix, 66, RED, nullptr, nullptr, nullptr);
    AssignNodeAttributes(fiftyfive, 55, RED, nullptr, nullptr, nullptr);
    AssignNodeAttributes(fortyfour, 44, RED, nullptr, nullptr, nullptr);
    AssignNodeAttributes(thirtythree, 33, RED, nullptr, nullptr, nullptr);
    AssignNodeAttributes(twentytwo, 22, RED, nullptr, nullptr, nullptr);
    AssignNodeAttributes(eleven, 11, RED, nullptr, nullptr, nullptr);

    // Insert nodes with sorted, descending values.
    testingTree.RBTreeInsertNode(eightyeight);
    testingTree.RBTreeInsertNode(seventyseven);
    testingTree.RBTreeInsertNode(sixtysix);
    testingTree.RBTreeInsertNode(fiftyfive);
    testingTree.RBTreeInsertNode(fortyfour);
    testingTree.RBTreeInsertNode(thirtythree);
    testingTree.RBTreeInsertNode(twentytwo);
    testingTree.RBTreeInsertNode(eleven);

    // Check tree root.
    ASSERT_EQ(testingTree.treeRoot->key, 55);
    ASSERT_EQ(testingTree.treeRoot->color, BLACK);
    
    // Check tree root's left subtree.
    ASSERT_EQ(testingTree.treeRoot->left->key, 33);
    ASSERT_EQ(testingTree.treeRoot->left->color, RED);
    ASSERT_EQ(testingTree.treeRoot->left->left->key, 22);
    ASSERT_EQ(testingTree.treeRoot->left->left->color, BLACK);
    ASSERT_EQ(testingTree.treeRoot->left->right->key, 44);
    ASSERT_EQ(testingTree.treeRoot->left->right->color, BLACK);
    ASSERT_EQ(testingTree.treeRoot->left->left->left->key, 11);
    ASSERT_EQ(testingTree.treeRoot->left->left->left->color, RED);

    // Check tree root's right subtree.
    ASSERT_EQ(testingTree.treeRoot->right->key, 77);
    ASSERT_EQ(testingTree.treeRoot->right->color, RED);
    ASSERT_EQ(testingTree.treeRoot->right->left->key, 66);
    ASSERT_EQ(testingTree.treeRoot->right->left->color, BLACK);
    ASSERT_EQ(testingTree.treeRoot->right->right->key, 88);
    ASSERT_EQ(testingTree.treeRoot->right->right->color, BLACK);
}

/*
TEST_F(test_RBTree, TestRBTreeRemoveKey) {
    // TO DO.
}

TEST_F(test_RBTree, TestRBTreeRemoveNode) {
    // TO DO.
}
*/

TEST_F(test_RBTree, TestRBTreeGetPredecessor) {
    shared_ptr<Node> testPredecessor;

    RBTree testingTree;
    testingTree.treeRoot = GetTwelveNodeTree();

    testPredecessor = testingTree.RBTreeGetPredecessor(testingTree.treeRoot);
    ASSERT_EQ(testPredecessor->key, 25);

    testPredecessor = testingTree.RBTreeGetPredecessor(testingTree.treeRoot->left);
    ASSERT_EQ(testPredecessor->key, 13);

    testPredecessor = testingTree.RBTreeGetPredecessor(testingTree.treeRoot->right);
    ASSERT_EQ(testPredecessor->key, 37);
}

TEST_F(test_RBTree, TestRBTreeGetSibling) {
    shared_ptr<Node> testSibling;

    RBTree testingTree;
    testingTree.treeRoot = GetTwelveNodeTree();

    testSibling = testingTree.RBTreeGetSibling(testingTree.treeRoot->left);
    ASSERT_EQ(testSibling->key, 42);

    testSibling = testingTree.RBTreeGetSibling(testingTree.treeRoot->right);
    ASSERT_EQ(testSibling->key, 17);

    testSibling = testingTree.RBTreeGetSibling(testingTree.treeRoot->left->left);
    ASSERT_EQ(testSibling->key, 20);

    testSibling = testingTree.RBTreeGetSibling(testingTree.treeRoot->right->right->right);
    ASSERT_EQ(testSibling, nullptr);
}

TEST_F(test_RBTree, TestRBTreeIsNonNullAndRed) {
    bool testBool;

    RBTree testingTree;
    testingTree.treeRoot = GetTwelveNodeTree();

    // Node is null.
    testBool = testingTree.RBTreeIsNonNullAndRed(testingTree.treeRoot->right->left->left);
    ASSERT_FALSE(testBool);

    // Root is non-null but black.
    testBool = testingTree.RBTreeIsNonNullAndRed(testingTree.treeRoot);
    ASSERT_FALSE(testBool);

    // Node is non-null and red.
    testBool = testingTree.RBTreeIsNonNullAndRed(testingTree.treeRoot->right);
    ASSERT_TRUE(testBool);

    // Node is non-null and red.
    testBool = testingTree.RBTreeIsNonNullAndRed(testingTree.treeRoot->left);
    ASSERT_TRUE(testBool);
}

TEST_F(test_RBTree, TestRBTreeIsNullOrBlack) {
    bool testBool;

    RBTree testingTree;
    testingTree.treeRoot = GetTwelveNodeTree();

    // Node is red.
    testBool = testingTree.RBTreeIsNullOrBlack(testingTree.treeRoot->right);
    ASSERT_FALSE(testBool);

    // Node is black.
    testBool = testingTree.RBTreeIsNullOrBlack(testingTree.treeRoot->right->left);
    ASSERT_TRUE(testBool);

    // Node is null.
    testBool = testingTree.RBTreeIsNullOrBlack(testingTree.treeRoot->right->left->left);
    ASSERT_TRUE(testBool);
}

TEST_F(test_RBTree, TestRBTreeAreBothChildrenBlack) {
    bool testBool;

    RBTree testingTree;
    testingTree.treeRoot = GetTwelveNodeTree();

    // Two non-null black children.
    testBool = testingTree.RBTreeAreBothChildrenBlack(testingTree.treeRoot->left);
    ASSERT_TRUE(testBool);

    // Two null black children.
    testBool = testingTree.RBTreeAreBothChildrenBlack(testingTree.treeRoot->right->left);
    ASSERT_TRUE(testBool);

    // Two red children.
    testBool = testingTree.RBTreeAreBothChildrenBlack(testingTree.treeRoot->left->right);
    ASSERT_FALSE(testBool);

    // One red child + one (null) black child.
    testBool = testingTree.RBTreeAreBothChildrenBlack(testingTree.treeRoot->right->right);
    ASSERT_FALSE(testBool);
}

TEST_F(test_RBTree, TestRBTreePrepareForRemoval) {
    // To do.
}

TEST_F(test_RBTree, TestRBTreeTryCase1) {
    bool testBool;

    RBTree testingTree;
    testingTree.treeRoot = GetTwelveNodeTree();

    // Node is red; should be true.
    testBool = testingTree.RBTreeTryCase1(testingTree.treeRoot->left);
    ASSERT_TRUE(testBool);
    
    // Node is root so parent is null; should be true.
    testBool = testingTree.RBTreeTryCase1(testingTree.treeRoot);
    ASSERT_TRUE(testBool);

    // Node is black and has parent; should be false.
    testBool = testingTree.RBTreeTryCase1(testingTree.treeRoot->right->left); 
    ASSERT_FALSE(testBool);
}

TEST_F(test_RBTree, TestRBTreeTryCase2) {
    bool testBool;

    RBTree testingTreeOne;
    testingTreeOne.treeRoot = GetTwelveNodeTree();

    // Node has black sibling; should be false.
    testBool = testingTreeOne.RBTreeTryCase2(
        testingTreeOne.treeRoot->right->right, testingTreeOne.treeRoot->right->left); 
    ASSERT_FALSE(testBool);

    // (Rotate RIGHT will be called).
    // Node has red sibling; should be true.
    // testingTree should also subsequently be altered such that node's parent is red, 
    // and its sibling is black and RBTreeRotateRight is called on node's parent.
    testBool = testingTreeOne.RBTreeTryCase2(
        testingTreeOne.treeRoot->left->right->right, testingTreeOne.treeRoot->left->right->left);
    ASSERT_TRUE(testBool);
    ASSERT_EQ(testingTreeOne.treeRoot->left->right->color, BLACK);
    ASSERT_EQ(testingTreeOne.treeRoot->left->right->key, 19);
    ASSERT_EQ(testingTreeOne.treeRoot->left->right->right->color, RED);
    ASSERT_EQ(testingTreeOne.treeRoot->left->right->right->key, 20);
    ASSERT_EQ(testingTreeOne.treeRoot->left->right->right->right->color, RED);
    ASSERT_EQ(testingTreeOne.treeRoot->left->right->right->right->key, 25);

    // Get fresh twelve node tree.
    RBTree testingTreeTwo;
    testingTreeTwo.treeRoot = GetTwelveNodeTree();

    // (Rotate LEFT will be called).
    // Node has red sibling; should be true.
    // testingTree should also subsequently be altered such that node's parent is red, 
    // and its sibling is black and RBTreeRotateLeft is called on node's parent.
    testBool = testingTreeTwo.RBTreeTryCase2(
        testingTreeTwo.treeRoot->left->right->left, testingTreeTwo.treeRoot->left->right->right);
    ASSERT_TRUE(testBool);
    ASSERT_EQ(testingTreeTwo.treeRoot->left->right->color, BLACK);
    ASSERT_EQ(testingTreeTwo.treeRoot->left->right->key, 25);
    ASSERT_EQ(testingTreeTwo.treeRoot->left->right->left->color, RED);
    ASSERT_EQ(testingTreeTwo.treeRoot->left->right->left->key, 20);
    ASSERT_EQ(testingTreeTwo.treeRoot->left->right->left->left->color, RED);
    ASSERT_EQ(testingTreeTwo.treeRoot->left->right->left->left->key, 19);
}

TEST_F(test_RBTree, TestRBTreeTryCase3) {
    bool testBool;
    shared_ptr<Node> parent;
    shared_ptr<Node> node;
    shared_ptr<Node> sibling;

    // Create altered SevenNodeTree
    RBTree testingTree;
    testingTree.treeRoot = GetSevenNodeTree();
    testingTree.treeRoot->right->left->color  = BLACK;
    testingTree.treeRoot->right->right->color = BLACK;
    parent  = testingTree.treeRoot;
    node    = testingTree.treeRoot->left;
    sibling = testingTree.treeRoot->right;

    // Altered SevenNodeTree:
    /*
            parent-> (33:Black)
                    /         \
    node-> (17 : Black)        (42 : Black) <-sibling
                               /        \
                        (37 : BLACK)     (50 : BLACK)
    */

   // TryCase3 should return true.
   // 'parent' remains black and 'sibling' turns red.
   testBool = testingTree.RBTreeTryCase3(node, sibling);
   ASSERT_TRUE(testBool);
   ASSERT_TRUE(parent->color == BLACK);
   ASSERT_TRUE(sibling->color == RED);
}

TEST_F(test_RBTree, TestRBTreeTryCase4) {
    bool testBool;
    shared_ptr<Node> parent;
    shared_ptr<Node> node;
    shared_ptr<Node> sibling;

    // Create altered SevenNodeTree
    RBTree testingTree;
    testingTree.treeRoot = GetSevenNodeTree();
    testingTree.treeRoot->color               = RED;
    testingTree.treeRoot->right->left->color  = BLACK;
    testingTree.treeRoot->right->right->color = BLACK;
    parent  = testingTree.treeRoot;
    node    = testingTree.treeRoot->left;
    sibling = testingTree.treeRoot->right;

    // Altered SevenNodeTree:
    /*
            parent-> (33 : RED)
                    /         \
    node-> (17 : Black)        (42 : Black) <-sibling
                               /        \
                        (37 : BLACK)     (50 : BLACK)
    */

   // TryCase4 should return true.
   // 'parent' remains black and 'sibling' turns red.
   testBool = testingTree.RBTreeTryCase4(node, sibling);
   ASSERT_TRUE(testBool);
   ASSERT_TRUE(parent->color == BLACK);
   ASSERT_TRUE(sibling->color == RED);
}

TEST_F(test_RBTree, TestRBTreeTryCase5) {
    bool testBool;
    shared_ptr<Node> parent;
    shared_ptr<Node> node;
    shared_ptr<Node> sibling;

    // Create altered SevenNodeTree
    RBTree testingTree;
    testingTree.treeRoot = GetSevenNodeTree();
    testingTree.treeRoot->right->right->color = BLACK;
    parent  = testingTree.treeRoot;
    node    = testingTree.treeRoot->left;
    sibling = testingTree.treeRoot->right;

    // Altered SevenNodeTree:
    /*
            parent-> (33 : Black)
                    /         \
    node-> (17 : Black)        (42 : Black) <-sibling
                               /        \
                        (37 : Red)     (50 : BLACK)
    */

    // TryCase5 should return true.
    // 'sibling' turns red and sibling's left child turns black.
    // Rotate right at sibling.
    testBool = testingTree.RBTreeTryCase5(node, sibling);
    ASSERT_TRUE(testBool);

    // SevenNodeTree after function call should be:
    /*
            parent-> (33 : Black)
                    /         \
    node-> (17 : Black)        (37 : Black)
                                       \
                                     (42 : Red)
                                          \
                                        (50 : Black)
    */
    ASSERT_TRUE(testingTree.treeRoot->right->color == BLACK);
    ASSERT_TRUE(testingTree.treeRoot->right->key   == 37);
    ASSERT_TRUE(testingTree.treeRoot->right->right->color == RED);
    ASSERT_TRUE(testingTree.treeRoot->right->right->key   == 42);
    ASSERT_TRUE(testingTree.treeRoot->right->right->right->color == BLACK);
    ASSERT_TRUE(testingTree.treeRoot->right->right->right->key   == 50);
}

TEST_F(test_RBTree, TestRBTreeTryCase6) {
    bool testBool;
    shared_ptr<Node> parent;
    shared_ptr<Node> node;
    shared_ptr<Node> sibling;

    // Create altered SevenNodeTree
    RBTree testingTree;
    testingTree.treeRoot = GetSevenNodeTree();
    testingTree.treeRoot->left->left->color = BLACK;
    parent  = testingTree.treeRoot;
    node    = testingTree.treeRoot->right;
    sibling = testingTree.treeRoot->left;

    // Altered SevenNodeTree:
    /*
            parent-> (33 : Black)
                    /           \
    sibling-> (17 : Black)     (42 : Black) <-node
               /        \
         (11:BLACK)   (20:Red) 
    */

    // TryCase6 should return true.
    // 'sibling' turns red and sibling's right child turns black.
    // Rotate left at sibling.
    testBool = testingTree.RBTreeTryCase6(node, sibling);
    ASSERT_TRUE(testBool);

    // SevenNodeTree after function call should be:
    /*
                    (33 : Black)
                    /         \
            (20 : Black)     (42 : Black)
                 /
           (17 : Red) 
               /
        (11 : Black)    
    */
    ASSERT_TRUE(testingTree.treeRoot->left->color == BLACK);
    ASSERT_TRUE(testingTree.treeRoot->left->key   == 20);
    ASSERT_TRUE(testingTree.treeRoot->left->left->color == RED);
    ASSERT_TRUE(testingTree.treeRoot->left->left->key   == 17);
    ASSERT_TRUE(testingTree.treeRoot->left->left->left->color == BLACK);
    ASSERT_TRUE(testingTree.treeRoot->left->left->left->key   == 11);
}

TEST_F(test_RBTree, TestGetTreeHeight) {
    int treeHeight;
    
    RBTree testingTree;

    testingTree.treeRoot = GetThreeNodeTree();
    treeHeight = testingTree.GetTreeHeight(testingTree.treeRoot);
    ASSERT_EQ(treeHeight, 1);

    testingTree.treeRoot = GetSevenNodeTree();
    treeHeight = testingTree.GetTreeHeight(testingTree.treeRoot);
    ASSERT_EQ(treeHeight, 2);

    testingTree.treeRoot = GetTwelveNodeTree();
    treeHeight = testingTree.GetTreeHeight(testingTree.treeRoot);
    ASSERT_EQ(treeHeight, 3);

    // Create compound tree structure:
    /*
    topTree
        \ <-(new edge)
         \
        middleTree
         /
        / <-(new edge)
    bottomTree
    */

    RBTree topTree;
    RBTree middleTree;
    RBTree bottomTree;

    topTree.treeRoot    = GetTwelveNodeTree();
    middleTree.treeRoot = GetTwelveNodeTree();
    bottomTree.treeRoot = GetTwelveNodeTree();

    AssignNodeAttributes(topTree.treeRoot->right->right->right, 
        53, RED,
        topTree.treeRoot->right->right,
        nullptr,
        middleTree.treeRoot);
    AssignNodeAttributes(middleTree.treeRoot, 
        33, BLACK,
        topTree.treeRoot->right->right->right,
        middleTree.treeRoot->left,
        middleTree.treeRoot->right);
    AssignNodeAttributes(middleTree.treeRoot->left->left->left, 
        6, RED,
        middleTree.treeRoot->left->left,
        bottomTree.treeRoot,
        nullptr);
    AssignNodeAttributes(bottomTree.treeRoot, 
        33, BLACK,
        middleTree.treeRoot->left->left->left,
        bottomTree.treeRoot->left,
        bottomTree.treeRoot->right);

    // Expected height of new structure is: (height of each tree * 3) + 2 new edges = 11.
    treeHeight = topTree.GetTreeHeight(topTree.treeRoot);
    ASSERT_EQ(treeHeight, 11);
}

////////////////////
////////////////////
////////////////////   H E L P E R   F U N C T I O N S
////////////////////
////////////////////

// Assigns given node, 'node', with given attributes.
void AssignNodeAttributes(
    shared_ptr<Node> node,
    int keyVal, string color, 
    shared_ptr<Node> parentPtr, shared_ptr<Node> leftPtr, shared_ptr<Node> rightPtr) {

    node->key    = keyVal;
    node->color  = color;
    node->parent = parentPtr;
    node->left   = leftPtr;
    node->right  = rightPtr;
}

// Returns pointer to root of three-node tree.
shared_ptr<Node> GetThreeNodeTree() {
    /*
            (33 : Black)
             /        \
       (17 : Red)   (42 : Red)
    */
    shared_ptr<Node> threeNodeTreeRoot;
    shared_ptr<Node> twentythree (new Node);
    shared_ptr<Node> nine (new Node);
    shared_ptr<Node> fortyseven (new Node);

    threeNodeTreeRoot = twentythree;

    AssignNodeAttributes(twentythree, 33, BLACK, nullptr, nine, fortyseven);
    AssignNodeAttributes(nine, 17, RED, twentythree, nullptr, nullptr);
    AssignNodeAttributes(fortyseven, 42, RED, twentythree, nullptr, nullptr);

    return threeNodeTreeRoot;
}

// Returns pointer to top of unbalanced three-node structure.
shared_ptr<Node> GetUnbalancedLeftBracket() {
    /*
            (42 : Black)
                /
        (17 : Red) 
                \
            (33 : Red)
    */
    shared_ptr<Node> leftBracketTreeRoot;
    shared_ptr<Node> fortyseven (new Node);
    shared_ptr<Node> nine (new Node);
    shared_ptr<Node> twentythree (new Node);

    leftBracketTreeRoot = fortyseven;

    AssignNodeAttributes(fortyseven, 42, BLACK, nullptr, nine, nullptr);
    AssignNodeAttributes(nine, 17, RED, fortyseven, nullptr, twentythree);
    AssignNodeAttributes(twentythree, 33, RED, nine, nullptr, nullptr);

    return leftBracketTreeRoot;
}

// Returns pointer to top of unbalanced three-node structure.
shared_ptr<Node> GetUnbalancedRightBracket() {
    /*
        (17 : Black)
            \
            (42 : Red)
            /
        (33 : Red)
    */
    shared_ptr<Node> rightBracketTreeRoot;
    shared_ptr<Node> nine (new Node);
    shared_ptr<Node> fortyseven (new Node);
    shared_ptr<Node> twentythree (new Node);

    rightBracketTreeRoot = nine;

    AssignNodeAttributes(nine, 17, BLACK, nullptr, nullptr, fortyseven);
    AssignNodeAttributes(fortyseven, 42, RED, nine, twentythree, nullptr);
    AssignNodeAttributes(twentythree, 33, RED, fortyseven, nullptr, nullptr);

    return rightBracketTreeRoot;
}

// Returns pointer to root of seven-node tree.
shared_ptr<Node> GetSevenNodeTree() {
    /*
                    (33 : Black)
                    /         \
         (17 : Black)         (42 : Black)
            /    \                 /     \
    (11 : Red) (20 : Red)   (37 : Red) (50 : Red)
    */
    shared_ptr<Node> sevenNodeTreeRoot;
    shared_ptr<Node> twentythree (new Node);
    shared_ptr<Node> nine (new Node);
    shared_ptr<Node> fortyseven (new Node);
    shared_ptr<Node> eleven (new Node);
    shared_ptr<Node> twenty (new Node);
    shared_ptr<Node> thirtyseven (new Node);
    shared_ptr<Node> fifty (new Node);

    sevenNodeTreeRoot  = twentythree;

    AssignNodeAttributes(twentythree, 33, BLACK, nullptr, nine, fortyseven);
    AssignNodeAttributes(nine, 17, BLACK, twentythree, eleven, twenty);
    AssignNodeAttributes(fortyseven, 42, BLACK, twentythree, thirtyseven, fifty);
    AssignNodeAttributes(eleven, 11, RED, nine, nullptr, nullptr);
    AssignNodeAttributes(twenty, 20, RED, nine, nullptr, nullptr);
    AssignNodeAttributes(thirtyseven, 37, RED, fortyseven, nullptr, nullptr);
    AssignNodeAttributes(fifty, 50, RED, fortyseven, nullptr, nullptr);

    return sevenNodeTreeRoot;
}

// Returns pointer to root of twelve-node tree.
shared_ptr<Node> GetTwelveNodeTree() {
    /*
                                        (33 : Black)
                                       /           \
                                      /             \
                                     /               \
                                    /                 \
                          (17 : Red)                  (42 : Red)
                          /       \                  /          \
                         /         \                /            \
                        /           \              /              \
             (11 : Black)    (20 : Black)      (37 : Black)      (50 : Black)
            /    \            /    \                                    \
           /      \          /      \                                    \
          /        \        /        \                                    \
      (6:Red) (13:Red)  (19:Red) (25:Red)                               (53:Red)               
    */
    shared_ptr<Node> twelveNodeTreeRoot;
    shared_ptr<Node> twentythree (new Node);
    shared_ptr<Node> nine (new Node);
    shared_ptr<Node> fortyseven (new Node);
    shared_ptr<Node> eleven (new Node);
    shared_ptr<Node> twenty (new Node);
    shared_ptr<Node> thirtyseven (new Node);
    shared_ptr<Node> fifty (new Node);
    shared_ptr<Node> six (new Node);
    shared_ptr<Node> thirteen (new Node);
    shared_ptr<Node> nineteen (new Node);
    shared_ptr<Node> twentyfive (new Node);
    shared_ptr<Node> fiftythree (new Node);

    twelveNodeTreeRoot = twentythree;

    AssignNodeAttributes(twentythree, 33, BLACK, nullptr, nine, fortyseven);
    AssignNodeAttributes(nine, 17, RED, twentythree, eleven, twenty);
    AssignNodeAttributes(fortyseven, 42, RED, twentythree, thirtyseven, fifty);
    AssignNodeAttributes(eleven, 11, BLACK, nine, six, thirteen);
    AssignNodeAttributes(twenty, 20, BLACK, nine, nineteen, twentyfive);
    AssignNodeAttributes(thirtyseven, 37, BLACK, fortyseven, nullptr, nullptr);
    AssignNodeAttributes(fifty, 50, BLACK, fortyseven, nullptr, fiftythree);
    AssignNodeAttributes(six, 6, RED, eleven, nullptr, nullptr);
    AssignNodeAttributes(thirteen, 13, RED, eleven, nullptr, nullptr);
    AssignNodeAttributes(nineteen, 19, RED, twenty, nullptr, nullptr);
    AssignNodeAttributes(twentyfive, 25, RED, twenty, nullptr, nullptr);
    AssignNodeAttributes(fiftythree, 53, RED, fifty, nullptr, nullptr);

    return twelveNodeTreeRoot;
}