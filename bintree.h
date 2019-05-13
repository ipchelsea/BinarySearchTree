/* 
 * File:   bintree.h
 * Assignment: CSS343 Lab 2
 * Date: 04/17/2019
 * Author: Chelsea Ip
 *
 * Poly.h contains all the declarations including proper constructor and
 * destructor functions, overload common operators(+,-,*,=,+=,-=,*=,==,!=),
 * accessors,and mutators.
 */

#include "nodedata.h"
using namespace std;

class BinTree 
{		
    // you add class/method comments and assumptions
    friend ostream& operator<<(ostream& output, const BinTree&);
    
public:
    
        //constructors
	BinTree();
	BinTree(const BinTree &);	
	~BinTree();
        
        int getHeight (const NodeData &) const;
	bool isEmpty() const;		
	void makeEmpty();						
        bool insert(NodeData*);
	bool retrieve(const NodeData &, NodeData* &) const;
        
        void arrayToBSTree (NodeData* []); //Builds balanced binary tree from a sorted array of NodeData*
        void bstreeToArray(NodeData* []);//Built an array of Node Data by from a BST tree
        void displaySideways() const;	
        
        //Overload operators
        BinTree& operator=(const BinTree &);
	bool operator==(const BinTree &) const;
	bool operator!=(const BinTree &) const;

        
private:
	struct Node 
        {
		NodeData* data;						//pointer to the actual data stored
		Node* left;							// left subtree pointer
		Node* right;						// right subtree pointer
	};
        
	Node* root;								// root of the tree

        
// utility functions
int  heightHelper(const NodeData & goal, Node *curr) const;
bool retrieveHelper(Node* curr, const NodeData& keyValue, NodeData *&received) const;
void arrayToBSTreeHelper(Node* curr, NodeData* array[], int start, int end);
int  bstreeToArrayHelper(Node *curr, NodeData* array[]);
int  foundGoal(Node* curr) const;
void copyTree(Node *rightTree, Node *&leftTree);
void inorderHelper(Node*) const;
bool equalHelper(Node *leftNode, Node *rightNode) const;
void sideways(Node*, int) const;	 
void deleteTree(Node*& treePtr);// provided below, helper for displaySideways()

};

