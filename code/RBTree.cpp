#include "RBTree.h"

///////////////
///////////////   N O D E   O B J E C T   
///////////////
///////////////

Node::Node() {

}

Node::~Node() {
    
}

///////////////
///////////////   R E D - B L A C K    T R E E   O B J E C T   
///////////////
///////////////

RBTree::RBTree() {
    treeRoot = nullptr;
}

RBTree::~RBTree() {

}

// Creates new node with given key value, 'keyVal'. 
// Color is RED and pointers are nullptr.
shared_ptr<Node> RBTree::InitNode(int keyVal) {
    shared_ptr<Node> newNode(new Node);

    newNode->key    = keyVal;
    newNode->color  = RED;
    newNode->parent = nullptr;
    newNode->left   = nullptr;
    newNode->right  = nullptr;

    return newNode;
}

//////////////
//////////////    R E D - B L A C K    T R E E   O B J E C T    
//////////////    B I N A R Y   S E A R C H    T R E E   F U N C T I O N S           
//////////////

// Creates new node with given key value, 'keyVal',
// and inserts this node into RBTree according to binary search tree invariants.
void RBTree::BSTInsertKey(int keyVal) {
    shared_ptr<Node> newNode;

    newNode = InitNode(keyVal);

    return BSTInsertNode(newNode);
}

// Inserts node into RBTree according to binary search tree invariants.
void RBTree::BSTInsertNode(shared_ptr<Node> node) {    
    // If 'node' is first node in tree...
    if (treeRoot == nullptr) {
        treeRoot = node;
        return;
    }

    // If 'node' is not first node in tree...
    else {
        shared_ptr<Node> parent;
        shared_ptr<Node> cursorNode;

        parent       = nullptr;
        cursorNode   = treeRoot;

        // Find insertion location.
        while (cursorNode != nullptr) {
            if (node->key < cursorNode->key) {
                parent     = cursorNode;
                cursorNode = parent->left;
            }
            else {
                parent     = cursorNode;
                cursorNode = parent->right;
            }
        }

        // If node is already in tree, return without modifying tree.
        if (node->key == parent->key) {
            return;
        }

        // If node is not already in tree, insert node into appropriate location.
        if (node->key < parent->key) {
            node->parent = parent;
            parent->left = node;
        }
        if (node->key > parent->key) {
            node->parent  = parent;
            parent->right = node;
        }
    }
}

// Returns pointer to node with key equal to 'keyVal' or nullptr if no such node exists.
shared_ptr<Node> RBTree::BSTSearchKey(int keyVal) {
    shared_ptr<Node> cursorNode;

    // Starting at tree's root, search for node with matching key value.
    cursorNode = treeRoot;
    while (cursorNode != nullptr) {
        if (keyVal == cursorNode->key) {
            return cursorNode;
        }

        else if (keyVal < cursorNode->key) {
            cursorNode = cursorNode->left;
        }

        else {
            cursorNode = cursorNode->right;
        }
    }

    // Return nullptr if node is not found.
    return nullptr;
}

// Locates node containing given key, 'keyVal', and removes
// this node, maintaining binary search tree invariants. If no
// node exists with key, 'keyVal', no alterations are made to tree.
void RBTree::BSTRemoveKey(int keyVal) {
    shared_ptr<Node> parent;
    shared_ptr<Node> cursorNode;
    shared_ptr<Node> successor;
    int successorKey;

    parent  = nullptr;
    cursorNode = treeRoot;
    while (cursorNode != nullptr) {            // Search for node
        
        // NODE FOUND
        if (cursorNode->key == keyVal) { 
            // CASE 1
            // Node has no children
            if (cursorNode->left == nullptr && cursorNode->right == nullptr) {
                if (parent == nullptr) {    // Node is root
                    treeRoot = nullptr;
                }
                else if (parent->left == cursorNode) {
                    parent->left = nullptr;
                }
                else {
                    parent->right = nullptr;
                }
            }
            // CASE 2
            // Node has left child only
            else if (cursorNode->right == nullptr) {
                if (parent == nullptr) {    // Node is root
                    treeRoot = cursorNode->left;
                }
                else if (parent->left == cursorNode) {
                    parent->left = cursorNode->left;
                }
                else {
                    parent->right = cursorNode->left;
                }
            }
            // CASE 3
            // Node has right child only
            else if (cursorNode->left == nullptr) {
                if (parent == nullptr) {    // Node is root
                    treeRoot = cursorNode->right;
                }
                else if (parent->left == cursorNode) {
                    parent->left = cursorNode->right;
                }
                else {
                    parent->right = cursorNode->right;
                }
            }
            // CASE 4
            // Node has two children
            else {
                successor = cursorNode->right;
                while (successor->left != nullptr) {
                    successor = successor->left;
                }
                successorKey = successor->key;
                BSTRemoveKey(successor->key);
                cursorNode->key = successorKey;
            }

            return;     // Node found and removed.
        }

        // NODE NOT FOUND; SEARCH RIGHT
        else if (cursorNode->key < keyVal) { 
            parent  = cursorNode;
            cursorNode = cursorNode->right;
        }
        
        // NODE NOT FOUND; SEARCH LEFT
        else {                            
            parent  = cursorNode;
            cursorNode = cursorNode->left;  
        }
    }
    
    return; // Node not in tree.
}

///////////////
///////////////   R E D - B L A C K    T R E E   O B J E C T 
///////////////          R E D - B L A C K   T R E E  
///////////////     I N S E R T I O N   F U N C T I O N S 
///////////////

// Sets 'parent' node's left or right child (determined by 'whichChild') to 'child'.
bool RBTree::RBTreeSetChild(
    shared_ptr<Node> parent, string whichChild, shared_ptr<Node> child) {

    if (whichChild != "left" && whichChild != "right") {
        return false;
    }

    if (whichChild == "left") {
        parent->left = child;
    }

    else {
        parent->right = child;
    }

    if (child != nullptr) {
        child->parent = parent;
    }

    return true;
}

// Given 'parent' node and one of this node's current children 'currentChild', 
// this function replaces 'currentChild' with given node, 'newChild' updating 
// all pointers appropriately.
bool RBTree::RBTreeReplaceChild(
    shared_ptr<Node> parent, shared_ptr<Node> currentChild, shared_ptr<Node> newChild) {

    if (parent->left == currentChild) {
        return RBTreeSetChild(parent, "left", newChild);
    }

    else if (parent->right == currentChild) {
        return RBTreeSetChild(parent, "right", newChild);
    }

    // Return false if parent is nullptr.
    return false;
}

// Shifts node downward and to the left with node->right becoming node's new parent
// and node becoming this parent's left child. In the process, what was formerly
// node->right->left becomes node's new right child. 
void RBTree::RBTreeRotateLeft(shared_ptr<Node> node) {
    shared_ptr<Node> rightLeftChild = node->right->left;

    if (node->parent != nullptr) {
        RBTreeReplaceChild(node->parent, node, node->right);
    }

    else {
        treeRoot         = node->right;
        treeRoot->parent = nullptr;
    }

    RBTreeSetChild(node->right, "left", node);
    RBTreeSetChild(node, "right", rightLeftChild);
}

// Shifts node downward and to the right with node->left becoming node's new parent
// and node becoming this parent's right child. In the process, what was formerly
// node->left->right becomes node's new left child. 
void RBTree::RBTreeRotateRight(shared_ptr<Node> node) {
    shared_ptr<Node> leftRightChild = node->left->right;

    if (node->parent != nullptr) {
        RBTreeReplaceChild(node->parent, node, node->left);
    }

    else {
        treeRoot         = node->left;
        treeRoot->parent = nullptr;
    }

    RBTreeSetChild(node->left, "right", node);
    RBTreeSetChild(node, "left", leftRightChild); 
}

// Returns pointer to node's grandparent or nullptr if no grandparent exists.
shared_ptr<Node> RBTree::RBTreeGetGrandparent(shared_ptr<Node> node) {
    if (node->parent == nullptr) {
        return nullptr;
    }

    else {
        return node->parent->parent;
    }
}

// Returns node's uncle or nullptr if no uncle exists. 
shared_ptr<Node> RBTree::RBTreeGetUncle(shared_ptr<Node> node) {
    shared_ptr<Node> grandparent;

    grandparent = nullptr;

    if (node->parent != nullptr) {
        grandparent = node->parent->parent;
    }

    if (grandparent == nullptr) {
        return nullptr;
    }

    if (grandparent->left == node->parent) {
        return grandparent->right;
    }

    else {
        return grandparent->left;
    }
}

// Helper function for RBTreeInsert().
// After inserting a node, 'node', into a Red-Black Tree, this function
// makes appropriate adjustments in position and color to 'node' and its
// neighboring nodes to restore all Red-Black Tree invariants. 
void RBTree::RBTreeBalance(shared_ptr<Node> node) {
    // Tree needs no alterations if node is root or node's parent is black.
    if (node->parent == nullptr) {
        node->color = BLACK;
        return;
    }
    if (node->parent->color == BLACK) {
        return;
    }

    // Tree will require alterations if node's parent is red...
    shared_ptr<Node> parent;
    shared_ptr<Node> grandparent;
    shared_ptr<Node> uncle;
    parent      = node->parent;
    grandparent = RBTreeGetGrandparent(node);
    uncle       = RBTreeGetUncle(node);
    
    // "Red Uncle Case"
    // If red uncle exists, parent and uncle turn black and grandparent turns red.
    // Recursive call is made to RBTreeBalance on grandparent.
    if (uncle != nullptr && uncle->color == RED) {
        parent->color = uncle->color = BLACK;
        grandparent->color           = RED;
        RBTreeBalance(grandparent);
        return;
    }

    // "Bracket Cases"
    // If Left Bracket Case, make Left Straight Case
    /*
         * grandparent                  * grandparent
       /                               /
      * parent            ->          * parent (formerly node)
       \                             /
         * node                     * node (formerly parent)
    */
    if (node == parent->right && parent == grandparent->left) {
        RBTreeRotateLeft(parent);
        node   = parent;
        parent = node->parent;
    }
    // If Right Bracket Case, make Right Straight Case
    /*
        * grandparent              * grandparent
         \                          \
          * parent        ->         * parent (formerly node)
         /                            \
        * node                         * node (formerly parent)
    */
    else if (node == parent->left && parent == grandparent->right) {
        RBTreeRotateRight(parent);
        node   = parent;
        parent = node->parent;
    }

    parent->color      = BLACK;
    grandparent->color = RED;
    
    // "Straight Cases"
    // Left Straight Case
    /*
            * grandparent            
           /                         
          * parent        ->                 * parent
         /                                  / \
        * node                        node *   * "grandparent"
    */ 
    if (node == parent->left) {
        RBTreeRotateRight(grandparent);
    }
    // Right Straight Case
    /*
        * grandparent              
         \                          
          * parent        ->                 * parent
           \                                / \
            * node           "grandparent" *   * node
    */ 
    else {
        RBTreeRotateLeft(grandparent);
    }
}

// Creates new node with given new key value 'keyVal'
// and inserts this node into Red-Black Tree by calling RBTreeInsertNode
void RBTree::RBTreeInsertKey(int keyVal) {
    shared_ptr<Node> newNode = InitNode(keyVal);

    RBTreeInsertNode(newNode);
}

// Helper function for RBTreeInsertKey.
// Inserts node into Red-Black Tree and ensures Red-Black Tree invariants
// are maintained after insertion via call to RBTreeBalance(). 
void RBTree::RBTreeInsertNode(shared_ptr<Node> node) {
    BSTInsertNode(node);
    node->color = RED;
    RBTreeBalance(node);
}

///////////////
///////////////   R E D - B L A C K    T R E E   O B J E C T 
///////////////          R E D - B L A C K   T R E E 
///////////////        R E M O V A L  F U N C T I O N S
///////////////

void RBTree::RBTreeRemoveKey(int keyVal) {
    shared_ptr<Node> node;

    node = BSTSearchKey(keyVal);
    if (node != nullptr) {
        RBTreeRemoveNode(node);
    }
}

void RBTree::RBTreeRemoveNode(shared_ptr<Node> node) {
    shared_ptr<Node> predecessorNode;
    int predecessorKey;

    // If node has two children...
    if (node->left != nullptr && node->right != nullptr) {
        predecessorNode = RBTreeGetPredecessor(node);
        predecessorKey  = predecessorNode->key;
        RBTreeRemoveNode(predecessorNode);
        node->key = predecessorKey;
        return;
    }

    if (node->color == BLACK) {
        RBTreePrepareForRemoval(node);
    }

    BSTRemoveKey(node->key);
}

shared_ptr<Node> RBTree::RBTreeGetPredecessor(shared_ptr<Node> node) {
    shared_ptr<Node> nodePredecessor;

    if (node == nullptr || node->left == nullptr) {
        return nullptr;
    }

    nodePredecessor = node->left;
    while (nodePredecessor->right != nullptr) {
        nodePredecessor = nodePredecessor->right;
    }

    return nodePredecessor;
}

shared_ptr<Node> RBTree::RBTreeGetSibling(shared_ptr<Node> node) {
    if (node->parent != nullptr) {
        if (node == node->parent->left) {
            return node->parent->right;
        }
        return node->parent->left;
    }

    return nullptr;
}

bool RBTree::RBTreeIsNonNullAndRed(shared_ptr<Node> node) {
    if (node == nullptr) {
        return false;
    }

    return(node->color == RED);
}

bool RBTree::RBTreeIsNullOrBlack(shared_ptr<Node> node) {
    if (node == nullptr) {
        return true;
    }

    return (node->color == BLACK);
}

bool RBTree::RBTreeAreBothChildrenBlack(shared_ptr<Node> node) {
    if (node->left != nullptr && node->left->color == RED) {
        return false;
    }

    if (node->right != nullptr && node->right->color == RED) {
        return false;
    }

    return true;
}

void RBTree::RBTreePrepareForRemoval(shared_ptr<Node> node) {
    if (RBTreeTryCase1(node)) {
        return;
    }

    shared_ptr<Node> sibling;
    sibling = RBTreeGetSibling(node);
    if (RBTreeTryCase2(node, sibling)) {
        sibling = RBTreeGetSibling(node);
    }

    if (RBTreeTryCase3(node, sibling)) {
        return;
    }

    if (RBTreeTryCase4(node, sibling)) {
        return;
    }

    if (RBTreeTryCase5(node, sibling)) {
        sibling = RBTreeGetSibling(node);
    }

    if (RBTreeTryCase6(node, sibling)) {
        sibling = RBTreeGetSibling(node);
    }

    sibling->color      = node->parent->color;
    node->parent->color = BLACK;
    if (node == node->parent->left) {
        sibling->right->color = BLACK;
        RBTreeRotateLeft(node->parent);
    }
    else {
        sibling->left->color = BLACK;
        RBTreeRotateRight(node->parent);
    }
}

// Return true if node is red or node's parent is null, false otherwise.
bool RBTree::RBTreeTryCase1(shared_ptr<Node> node) {
    if (node->color == RED || node->parent == nullptr) {
        return true;
    }

    else {
        return false;
    }
}

bool RBTree::RBTreeTryCase2(shared_ptr<Node> node, shared_ptr<Node> sibling) {
    if (sibling->color == RED) {
        node->parent->color = RED;
        sibling->color      = BLACK;
        if (node == node->parent->left) {
            RBTreeRotateLeft(node->parent);
        }
        else {
            RBTreeRotateRight(node->parent);
        }
        return true;
    }
    
    return false;
}

bool RBTree::RBTreeTryCase3(shared_ptr<Node> node, shared_ptr<Node> sibling) {
    if (node->parent->color == BLACK &&
        RBTreeAreBothChildrenBlack(sibling)) {
    
        node->parent->color = BLACK;
        sibling->color      = RED;
        return true;
    }
    
    return false;
}

bool RBTree::RBTreeTryCase4(shared_ptr<Node> node, shared_ptr<Node> sibling) {
    if (node->parent->color == RED &&
        RBTreeAreBothChildrenBlack(sibling)) {
        
        node->parent->color = BLACK;
        sibling->color      = RED;
        return true;
    }
    
    return false;
}

bool RBTree::RBTreeTryCase5(shared_ptr<Node> node, shared_ptr<Node> sibling) {
    if (RBTreeIsNonNullAndRed(sibling->left) &&
        RBTreeIsNullOrBlack(sibling->right)  &&
        node == node->parent->left) {
        
        sibling->color       = RED;
        sibling->left->color = BLACK;
        RBTreeRotateRight(sibling);
        return true;
    }
    
    return false;
}

bool RBTree::RBTreeTryCase6(shared_ptr<Node> node, shared_ptr<Node> sibling) {
    if (RBTreeIsNullOrBlack(sibling->left)    &&
        RBTreeIsNonNullAndRed(sibling->right) &&
        node == node->parent->right) {
        
        sibling->color        = RED;
        sibling->right->color = BLACK;
        RBTreeRotateLeft(sibling);
        return true;
    }
    
    return false;
}

///////////////
///////////////   R E D - B L A C K    T R E E   O B J E C T 
///////////////          M I S C .   F U N C T I O N S
///////////////

// Return the number of edges between the leaf node that is most distant from 
// the tree's root and the tree's root. 
int RBTree::GetTreeHeight(shared_ptr<Node> node) {
    // BASE CASE
    // Leaf node encountered. 
    // Return 0 because leaf nodes have a height of 0.
    if (node->left == nullptr && node->right == nullptr) {
        return 0;
    }

    // If node has left child only...
    // recursively call GetTreeHeight on left child and add one to account for present node.
    // Return result. 
    else if (node->left != nullptr && node->right == nullptr) {
        return GetTreeHeight(node->left) + 1;
    }

    // If node has right child only...
    // recursively call GetTreeHeight on right child and add one to account for present node.
    // Return result. 
    else if (node->left == nullptr && node->right != nullptr) {
        return GetTreeHeight(node->right) + 1;
    }

    // If node has left and right child...
    // recursively call GetTreeHeight on both children, adding one to account for present node.
    // Return the larger of these two values. 
    else {
        int leftSubtHeight  = GetTreeHeight(node->left) + 1;
        int rightSubtHeight = GetTreeHeight(node->right) + 1;

        if (leftSubtHeight > rightSubtHeight) {
            return leftSubtHeight;
        }

        else {
            return rightSubtHeight;
        }
    }
}

// Print visualization of levels 0-2 of RBTree.
void RBTree::Print() {
    // PRINT LEVEL 0
    cout << "(";
    if (treeRoot) {
        cout << treeRoot->key << " : " << treeRoot->color;
    }
    else {
        cout << "NULL:B";
    }
    cout << ")";
    cout << endl;
    
    // PRINT LEVEL 1
    cout << "(";
    if (treeRoot == nullptr) {
        cout << "NULL:B";
    }
    else if (treeRoot->left) {
        cout << treeRoot->left->key << " : " << treeRoot->left->color;
    }
    else {
        cout << "NULL:B";
    }
    cout << ") (";
    if (treeRoot == nullptr) {
        cout << "NULL:B";
    }
    else if (treeRoot->right) {
        cout << treeRoot->right->key << " : " << treeRoot->right->color;
    }
    else {
        cout << "NULL:B";
    }
    cout << ") ";
    cout << endl;
    
    // PRINT LEVEL 2
    cout << "(";
    // (left side)
    if (treeRoot == nullptr) {
        cout << "NULL:B";
    }
    else if (treeRoot->left == nullptr) {
        cout << "NULL:B";
    }
    else if (treeRoot->left->left) {
        cout << treeRoot->left->left->key << " : " << treeRoot->left->left->color;
    }
    else {
        cout << "NULL:B";
    }
    cout << ") (";
    if (treeRoot == nullptr) {
        cout << "NULL:B";
    }
    else if (treeRoot->left == nullptr) {
        cout << "NULL:B";
    }
    else if (treeRoot->left->right) {
        cout << treeRoot->left->right->key << " : " << treeRoot->left->right->color;
    }
    else {
        cout << "NULL:B";
    }
    // (right side)
    cout << ") (";
    if (treeRoot == nullptr) {
        cout << "NULL:B";
    }
    else if (treeRoot->right == nullptr) {
        cout << "NULL:B";
    }
    else if (treeRoot->right->left) {
        cout << treeRoot->right->left->key << " : " << treeRoot->right->left->color;;
    }
    else {
        cout << "NULL:B";
    }
    cout << ") (";
    if (treeRoot == nullptr) {
        cout << "NULL:B";
    }
    else if (treeRoot->right == nullptr) {
        cout << "NULL:B";
    }
    else if (treeRoot->right->right) {
        cout << treeRoot->right->right->key << " : " << treeRoot->right->right->color;
    }
    else {
        cout << "NULL:B";
    }
    cout << ")";
    cout << endl;
}

void RBTree::PrintTree() {
    queue<shared_ptr<Node>> NodeQueue;
    shared_ptr<Node> nodeToPrint;
    int level;

    level = 0;
    nodeQueue.push(treeRoot);
    for (auto node : NodeQueue) {}
    while (!nodeQueue.empty()) {
        // Print level and 
        nodeToPrint = nodeQueue.front();
        cout << "level: " << level << endl;
        cout << nodeToPrint->key << " ";
        if (nodeToPrint->left) {
            nodeQueue.push(nodeToPrint->left);
        }
        if (nodeToPrint->right) {
            nodeQueue.push(nodeToPrint->right);
        }
        nodeQueue.pop();
        level += 1;
    }
    cout << endl;
}

/*
void levelOrder(node *root) {
    std::queue<node *> q;
    q.push(root);
    while (!q.empty()) {
        root = q.front();
        std::cout << root->data << " ";
        q.pop();
        if (root->left)
            q.push(root->left);
        if (root->right)
            q.push(root->right);
    }
}
*/