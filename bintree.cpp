/* 
 * Author: Chelsea Ip
 * File:   bintree.cpp
 * Assignment: CSS343 Lab 2
 * Date: 04/17/2019
 *
 * Poly.h contains all the declarations including proper constructor and
 * destructor functions, overload common operators(+,-,*,=,+=,-=,*=,==,!=),
 * accessors,and mutators.
 */

#include <iostream>
#include "bintree.h"

// --------------------- Default Constructor -----------------------------------------
// Constructs an empty binary search tree
// 
BinTree::BinTree() 
{
    this->root = NULL;
}

// --------------------- Copy Constructor -----------------------------------------
// Helper function for overloaded operator <<
// 
BinTree::BinTree(const BinTree & other) 	
{
    this->root = NULL;
    *this = other;
}

// --------------------- Destructor -----------------------------------------
// Helper function for overloaded operator <<
// 
BinTree::~BinTree()//destructor (deletes all nodes in the tree)
{
    this->makeEmpty();
}

// --------------------- isEmpty() -----------------------------------------
// Helper function for overloaded operator <<
// 
bool BinTree::isEmpty() const //returns true if tree is empty else false
{
    if(this->root == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// --------------------- makeEmpty() -----------------------------------------
// Calls the deleteTree function
// 
void BinTree::makeEmpty()
{
    deleteTree(root); 
}

// --------------------- deleteTree() -----------------------------------------
// Helper function for overloaded operator <<
// 
void BinTree::deleteTree(Node*& treePtr)
{
    if(treePtr!= NULL)
    {
        deleteTree(treePtr->left);//delete left subtree
        deleteTree(treePtr->right);//delete right subtree
        delete treePtr->data;//delete main node 
        treePtr = NULL;
        delete treePtr;
        treePtr = NULL;
    }
}

// --------------------- getHeight() -----------------------------------------
// function to find the height of a given node
// 
 int BinTree::getHeight (const NodeData & goal) const
 {
     return heightHelper(goal, this->root);
 }
 
// --------------------- heightHelper() -----------------------------------------
// function to find the height of a given node
//  
 int BinTree::heightHelper(const NodeData & goal, Node *curr) const
 { 
     if(curr == NULL) //basically u recursively call getHeight, but if u cannot find then 
     {
         return 0;
     }
     else if(*curr->data == goal)//if goal is root data
     {
         return foundGoal(curr);
     }
     else
     {
         int left = heightHelper(goal, curr->left);//find a normal node in the left or right subtree
         int right = heightHelper(goal, curr->right);
         
         return max(left, right);
     }
     
 }
  
// --------------------- heightHelper() -----------------------------------------
// function to find the height of a given node
// 
 int BinTree::foundGoal(Node* curr) const
 {
     if(curr == NULL)
     {
         return 0;
     }
     else
     {
          return 1 + max(foundGoal(curr->left), foundGoal(curr->right));
     }
 }

// --------------------- insert -----------------------------------------
// Inserts a node to the tree. Input is the thing you want to insert.
// From Carol Zander
bool BinTree::insert(NodeData *input)
{
   Node* ptr = new Node;    // exception is thrown if memory is not allocated
   ptr->data = input; //Link to current NodeData
   input = NULL; //Disconnect
   ptr->left = ptr->right = NULL;
   if (isEmpty()) 
   {
      root = ptr; //Empty, set as root
   }
   else 
   {
      Node* current = root;
      bool check = false;

      // if data is less than current data, insert in left subtree,
      // otherwise insert in right subtree
      while (!check) 
      {
         if (*ptr->data == *current->data)      //Duplicate found, discard.
         {	
            delete ptr; //Handle duplicate properly
            ptr = NULL;
            return false;
         }
         else if (*ptr->data < *current->data) 
         {
            if (current->left == NULL) // at leaf, insert left
            {            
               current->left = ptr;
               check = true;
            }
            else
               current = current->left;               // one step left
         }
         else 
         {
            if (current->right == NULL)               //a leaf
            {            
               current->right = ptr;
               check = true;
            }
            else
               current = current->right;              // keep checking until you find a null
         }
      }
   }
   return true;
}

// --------------------- retrieve() -----------------------------------------
//  retrieve function to get NodeData* of a given object in the tree
//  via pass by reference parameter and to report whether the object is found
//  (true or false)
//  toGet is the input the user wants to find
bool BinTree::retrieve(const NodeData & keyValue, NodeData*& received) const
{
    retrieveHelper(root, keyValue, received);
    if(received!= NULL)//if u can't find the node 
    {
        return true;
    }
    else
    {
        return false;
    }
}

// --------------------- retrieve() -----------------------------------------
//  retrieve function to get NodeData* of a given object in the tree
//  via pass by reference parameter and to report whether the object is found
//  (true or false)
bool BinTree::retrieveHelper(Node* curr, const NodeData& keyValue, NodeData *&received) const
{
    if(curr == NULL)//if not found
    {
        received = NULL;
        return false;
    }
    if(*curr->data == keyValue) //if key value is found
    {
        received = curr->data;
        return true;
    }
    else if(*curr->data > keyValue)//if root is greater than key
    {
        retrieveHelper(curr->left, keyValue, received);
    }
    else if(*curr->data < keyValue)//if root data is smaller than key
    {
        retrieveHelper(curr->right, keyValue, received);
    }
    else
    {
        return false;
    }
                
}

// --------------------- bstreeToArray -----------------------------------------
//  Should be empty
//
void BinTree::bstreeToArray(NodeData *array[])
{
    //cout << "Enter bstreeToArray " << endl;
    bstreeToArrayHelper(this->root, array);
    //cout << array << endl;
    this->makeEmpty();
}

// --------------------- bstreeToArrayHelper -----------------------------------------
//  Left, middle then array
//
int BinTree::bstreeToArrayHelper(Node *curr, NodeData *array[])
{
    //cout << "Enter bstreeToArrayHelper" << endl;
    if(curr == NULL)//if binary tree is null 
    {
        return 0;
    }
    int left = bstreeToArrayHelper(curr->left, array);//recursively stores left value in the array
    
    NodeData *temp;
    temp = curr->data; //root data is the mid that's why it comes after left
    curr->data = NULL;
    *(array + left) = temp; //sets temp as the middle
    temp = NULL;
    
    int right = bstreeToArrayHelper(curr->right, array+left+1);
    
    return left + right + 1;
}


// --------------------- arrayToBSTree -----------------------------------------
//  Assign right copy of the binary search tree to the left one
//
 void BinTree::arrayToBSTree (NodeData* array[])
 {
     this->makeEmpty();//leaves tree empty
     int high = 0;
     for(int i = 0; i < 100; i++)//statically allocate array for 100 NULL elements
     {
         if(array[i] != NULL)
         {
             high++;//sets the new highest
         }
         else
         {
             array[i] = NULL;
         }
     }
      arrayToBSTreeHelper(root, array, 0, high-1);
 }

 // --------------------- arrayToBSTreeHelper -----------------------------------------
//  Assign right copy of the binary search tree to the left one
//
 void BinTree::arrayToBSTreeHelper(Node* curr, NodeData* array[], int start, int end)
 {
     if(start > end)//if value at starting index is greater than the end
     {
         curr = NULL;
     }
     else
     {
         int mid = (start + end)/2; //root
         NodeData *temp;
         temp = array[mid];//sets pointer to point to mid of array
         array[mid] = NULL;
         
         insert(temp);//constructs binary tree with each node data inserted
         arrayToBSTreeHelper(curr, array, start, mid-1); //left side
         arrayToBSTreeHelper(curr, array, mid+1, end);//right side
     }
 }
// --------------------- Operator= -----------------------------------------
//  Assign right copy of the binary search tree to the left one
//
BinTree& BinTree::operator=(const BinTree & other)
{
    if(*this != other)
    {
        deleteTree(root);//delete the left tree
        copyTree(other.root, this->root);//copy right tree over
    }
    return *this;
}

// --------------------- copyTree -----------------------------------------
//  Assign right copy of the binary search tree to the left one
//
void BinTree::copyTree(Node *rightTree, Node *&leftTree)
{
    if(rightTree != NULL)
    {
        leftTree = new Node; //make a new node for the left tree
        NodeData *temp = new NodeData(*rightTree->data); //oh this just copies the root data
        leftTree->data = temp;
        //copy from left and right subtree
        copyTree(rightTree->left, leftTree->left);
        copyTree(rightTree->right, leftTree->right);
    }
    else
    {
        leftTree = NULL; //copies the empty tree
    }
}


// --------------------- Operator== -----------------------------------------
//  Compares if tree is identical or not
// 
bool BinTree::operator==(const BinTree & other) const
{
    if(this->root && other.root == NULL)
    {
        return true;
    }
    else
    {
        return equalHelper(this->root, other.root);
    }
}

// --------------------- insertionHelper -----------------------------------------
// Inserts a node to the tree
// 
bool BinTree::equalHelper(Node *leftNode, Node *rightNode) const
{
    if((leftNode != NULL && rightNode != NULL) &&
            (*leftNode->data == *rightNode->data))
    {
        return true;
    }
    if(leftNode == NULL || rightNode == NULL)
    {
        return false;
    }
    return ((*leftNode->data == *rightNode->data)&&
            equalHelper(leftNode->left, rightNode->left)
            && equalHelper(leftNode->right, rightNode->right));
}

// --------------------- Operator!= -----------------------------------------
// Helper function for overloaded operator <<
// 
bool BinTree::operator!=(const BinTree & other) const
{
    return!(*this == other);
}

// --------------------- inorderHelper  -----------------------------------------
// Helper function for overloaded operator <<
// 
void BinTree::inorderHelper(Node* curr) const
{
    if(curr!= NULL)
    {
        inorderHelper(curr->left);
        cout << *curr->data << " ";
        inorderHelper(curr->right);
    }
}

// --------------------- Operator << -----------------------------------------
// Writes the nodes of this tree in a sorted order, calls the inorder function
// 
ostream& operator<<(ostream& output, const BinTree& bst)
{
    bst.inorderHelper(bst.root); 
    output << endl;
    return output;
}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
	sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}