#include "objPosBST.h"

#include <iostream>
using namespace std;

objPosBST::objPosBST()
{
    // Constructor (Check Lecture Notes for Implementation, Simple)
    root = nullptr;
}

objPosBST::~objPosBST()
{
    // Destructor
    // Invoke delete tree, then set root to NULL
    deleteTree(root);
    root = nullptr;
}

void objPosBST::deleteTree(const TNode* thisNode)
{
	// Delete all nodes in the tree

    // Question from Class - Which Traversal Order should you use for this method?
    //   WARNING - using the wrong one will result in potential heap error.

    //base case for empty tree
    if (thisNode == nullptr)
    {
        return;
    }

    deleteTree(thisNode->left); //delete left subtree recursively
    deleteTree(thisNode->right); //delete right subtree recursively
    delete thisNode; //delete current node
    
}

// Public Interface, Implemented
void objPosBST::deleteTree()
{
    deleteTree(root); // recursive call on the private helper function
    root = nullptr;
}

bool objPosBST::isEmptyTree() const
{
    // Check if tree is empty
    //  Really simple, think about how.
    if (root == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }

}


bool objPosBST::isLeaf(const objPos &thisPos, const TNode* thisNode) const
{
    // Check if thisPos in a Leaf Node.
    //  Remember, tree nodes are inserted using the Prefix member of objPos

    // Algorithm Suggestion:
    // 1. if the node is NULL, just return false
    if (thisNode == nullptr)
    {
        return false;
    }
    // 2. Otherwise, compare Prefix of the data of the current node
    //    against the Prefix of thisPos
    //      - If not equal, follow the BST search rules
    else if (thisPos.getPF() < thisNode->data.getPF())
    {
        return isLeaf(thisPos, thisNode->left);
    }
    else if (thisPos.getPF() > thisNode->data.getPF())
    {
        return isLeaf(thisPos, thisNode->right);
    }

    //      - If equal, check if the node is a leaf node
    else
    {
        return thisNode->left == nullptr && thisNode->right == nullptr;
    }

    // Remember, leaf nodes do not have children nodes
}

bool objPosBST::isLeaf(const objPos &thisPos) const
{
    return isLeaf(thisPos, root);
}


void objPosBST::printTree(const TNode* thisNode) const  // private recursive
{
    // Print the entire tree content using **In-Order Traversal**

    // print in the format of Prefix + Number
    // e.g.  N30 P25 etc.

    // DO NOT use printObjPos() as it will mess up the game display.
    if (thisNode != nullptr)
    {
        printTree(thisNode->left);
        cout << thisNode->data.getPF() << thisNode->data.getNum() << " ";
        printTree(thisNode->right);
    }
}

void objPosBST::printTree() const  // public interface
{    
    if(root == NULL)
    {
        cout << "[Empty]";
        return;
    }
    printTree(root);
}


int objPosBST::getHeight(const TNode* thisNode) const
{
    // Tree Height Calculation Algorithm 

    // 1. If thisNode is null, height is zero.
    if (thisNode == nullptr)
    {
        return 0;
    }

    // 2. Otherwise, recursively invoke getHeight for the left and right subtree, and save
    //    the returned heights.
    int leftHeight = getHeight(thisNode->left); //height of left subtree
    int rightHeight = getHeight(thisNode->right); //height of right subtree

    // 3. Compare the two returned heights, and return the larger one.
    //The +1 is the current node counting itself before returning its height to its parent
    return max(leftHeight, rightHeight) + 1; // Return max height + 1
}

void objPosBST::printCurrentLevel(const TNode* thisNode, const int level) const
{
    // Recursive Level-Order Tree-Printing Algorithm 
    
    // 1. First check if at leaf node.  If yes, do not print anything
    if (thisNode == nullptr)
    {
        return;
    }

    // 2. Then, check if level is 1.  If yes, print the Prefix field only (specified in manual)
    if (level == 1)
    {
        cout << thisNode->data.getPF() << " "; //no need to serach because it's already at level 1
    }

    // 3. Otherwise, invoke recursively printCurrentLevel for left subtree with one less level, then
    //                                                        right subtree with one less level
    //    "if I'm not at the level, keep on searching into the left and the right subtrees"
    else if (level > 1)
    {
        printCurrentLevel(thisNode->left, level - 1);
        printCurrentLevel(thisNode->right, level - 1);
    }

    // You may add other character formatting features to make the tree more readable.
    // (you will be asked to demo this feature during the lab demo!!)
}

// Public Interface.
void objPosBST::printTreeLevel() const
{
    // Interface to the Recursive Version of Level-Order Tree-Printing Algorithm 

    // 1. Get the height of the tree
    int height = getHeight(root);

    // 2. For each level (bounded by height), invoke the recursive tree-printing algorithm.
    for (int i = 1; i <= height; i++)
    {
        printCurrentLevel(root, i);
        cout << endl; //move to a new line after each tree level.
    }

    // You may add other character formatting features to make the tree more readable.
    // (you will be asked to demo this feature during the lab demo!!)
}

bool objPosBST::isInTree(const objPos& thisPos, const TNode* thisNode) const
{
    // Check if thisPos in in the tree.
    //  Remember, tree nodes are inserted using the Prefix member of objPos

    // Algorithm Suggestion:
    // 1. if the node is NULL, just return false
    if (thisNode == nullptr)
    {
        return false;
    }
    // 2. Otherwise, compare Prefix of the data of the current node
    //    against the Prefix of thisPos
    //      - If not equal, follow the BST search rules
    else if (thisPos.getPF() < thisNode->data.getPF()) //search left
    {
        return isInTree(thisPos, thisNode->left);
    }
    else if (thisPos.getPF() > thisNode->data.getPF()) //search right
    {
        return isInTree(thisPos, thisNode->right);
    }

    //      - If equal, return true
    else
    {
        return true;
    }

}

// Public Interface, Implemented
bool objPosBST::isInTree(const objPos &thisPos) const
{
    return isInTree(thisPos, root); // recursive call on the private helper function
}

// insert OR update!!
void objPosBST::insert(const objPos &thisPos, TNode* &thisNode)
{
    // Insert objPos as a Node into the BST

    // Check Lecture Notes for general implementation
    //  Hint: Algorithm similar to isInTree.

    // 1. if the node is NULL, create new node
    if (thisNode == nullptr)
    {
        thisNode = new TNode(thisPos);
        return;
    }
    // 2. Otherwise, compare Prefix of the data of the current node
    //    against the Prefix of thisPos
    //      - If not equal, follow the BST search rules
    else if (thisPos.getPF() < thisNode->data.getPF()) //search left
    {
        insert(thisPos, thisNode->left);
    }
    else if (thisPos.getPF() > thisNode->data.getPF()) //search right
    {
        insert(thisPos, thisNode->right);
    }

    // Modification: 
    //   If the node is already in the tree (i.e. Prefix match found)
    //   Add the number member of thisPos to the number member of the objPos data at the node
    //   (DO NOT JUST IGNORE.  ADD NUMBERS!!)
    else
    {
        thisNode->data.setNum(thisNode->data.getNum() + thisPos.getNum());
    }
}

// Public Interface, Implemented
void objPosBST::insert(const objPos &thisPos)
{
    insert(thisPos, root); // recursive call on the private helper function
}


const TNode* objPosBST::findMin(const TNode* thisNode) const
{
	// Find the node with the smallest prefix in the subtree from thisNode
    // Used as part of remove() algorithm
    // Check Lecture Notes for implementation
    if (thisNode == nullptr){ //empty tree
        return nullptr;
    }
    while  (thisNode ->left != nullptr) //keep searching left
    {
        thisNode = thisNode->left;
    }
    return thisNode;

}


void objPosBST::remove(const objPos &thisPos, TNode* &thisNode)
{
	// Remove the node with matching prefix of thisPos from the subtree thisNode

    // *IMPORTANT* Check Lecture Notes for general implementation
    //  Remember the three removal case scenarios

    //if the subtree is empty, the node is not in the tree
    if (thisNode == nullptr) 
    {
        return;
    }

    if (thisPos.getPF() < thisNode->data.getPF()) //search left if prefix of thisPos is less than subtree thisNode prefix
    {
        remove(thisPos, thisNode->left);
    }
    else if (thisPos.getPF() > thisNode->data.getPF()) //search right if prefix of thisPos is more than subtree thisNode prefix
    {
        remove(thisPos, thisNode->right);
    }

    //matching node was found
    else 
    {
        // Case 3 - Delete the node with 2 children
    //   You can use either methods (check lecture notes)
        if (thisNode->left != nullptr && thisNode->right != nullptr) //deleting node with 2 children
        {
            thisNode->data = findMin(thisNode->right)->data; //replace thisNode data with the data of the node with smallest prefix of the right subtree
            remove(thisNode->data, thisNode->right); //then remove node with smallest prefix of right subtree
        }

        // Case 1 and 2 both can be handled with one algorithm (Lecture Notes)
        //node has no childnre or one child
        else
        {
            TNode* oldNode = thisNode;

            //connect the parent to the node's existing child
            //if there is no left child, use the right child
            thisNode = (thisNode->left != nullptr) ? thisNode->left : thisNode->right;
            delete oldNode;
        }
    }

}

// Public Interface, Implemented
void objPosBST::remove(const objPos &thisPos)
{
    remove(thisPos, root); // recursive call on the private helper function
}

bool objPosBST::findGreater(const int numThreshold, const TNode* thisNode) const
{
    // Determine whether any nodes in the tree has the NUMBER field of objPos data member greater than numThreshold

    // WARNING - this one is not as straightforward.

    // Algorithm Suggestion
    //  1. If tree empty, just return false
    if (thisNode == nullptr) 
    {
        return false;
    }
    //  2. Recursively check if the any number on the LEFT subtree is greater than numThreshold
    if (findGreater(numThreshold, thisNode->left)) 
    {
        return true;
    }
    //  3. Recursively check if the any number on the RIGHT subtree is greater than numThreshold
    else if (findGreater(numThreshold, thisNode->right))
    {
        return true;
    }
    //  4. Then, check if the number field of the objPos data in the current node is greater than numThreshold
    else if (thisNode->data.getNum() > numThreshold)
    {
        return true;
    }
    //  5. If any of the results from item 2, 3, and 4 is TRUE, return true.
    //     Otherwise, return false.
    else
    {
        return false;
    }

    // HINT:  If you do this right, the algorithm is less than 10 lines.
}

bool objPosBST::findGreater(const int numThreshold) const
{
    return findGreater(numThreshold, root);
}
