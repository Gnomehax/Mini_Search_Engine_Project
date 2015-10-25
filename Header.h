#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <sstream>

using namespace std;


class Node {
    string document;
    Node* left;
    Node* right;
public:
	Node();
	void setDocument(string doc);
	void setLeft(Node* left);
    void setRight(Node* right);
	string getDocument();
    Node* getLeft() { 
		return left; 
	};
    Node* getRight() { 
		return right; 
	};
};

class BSTree {
     Node* root;
public:
     BSTree();
     ~BSTree();     
     void insertNode(string doc);
	 bool search(string doc, Node *root);
     void inOrder(Node* node);
	 Node* Root() {
		 return root;
	 };
private:
     void insertNode(string doc, Node* leaf);
     void deleteNode(Node* leaf);
};

/*******************************************************
*   Deafult constructor for Node class                 *
*   contains default document string "" meaning it is  *
*   not contained in the document list.                *
*                                                      * 
********************************************************/

Node::Node() {
	document = "";
	left = NULL;
	right = NULL;
}

//set Document
void Node::setDocument(string doc) {
	document = doc;
}
//set Left node
void Node::setLeft(Node *left) {
	this->left = left;
}
//set Right node
void Node::setRight(Node *right) {
	this->right = right;
}
//get Document
string Node::getDocument() {
	return document;
}

//constructor and destructor for BSTree Class
BSTree::BSTree() {
     root = NULL;
}
BSTree::~BSTree() {
     deleteNode(root);
}

//delete the tree is called from the deconstructor
void BSTree::deleteNode(Node* leaf)
{
    if (leaf != NULL)
    {
       deleteNode(leaf->getLeft());
	   deleteNode(leaf->getRight());
       delete leaf;
    }
}

//add node to the tree
void BSTree::insertNode(string doc) {
     //If nothing is stored in the root node add to the root, else add to the children
     if (root == NULL) {
        Node* n = new Node();
        n->setDocument(doc);
        root = n;
     }
     else {
       insertNode(doc, root);
     }
}

//called by the public insertNode function used to add the children to the tree
void BSTree::insertNode(string doc, Node* leaf) {
    if (doc <= leaf->getDocument()) {
       if (leaf->getLeft() != NULL)
          insertNode(doc, leaf->getLeft());
       else {
          Node* n = new Node();
          n->setDocument(doc);
          leaf->setLeft(n);
       }
    }
    else {
       if (leaf->getRight() != NULL)
		   insertNode(doc, leaf->getRight());
       else {
          Node* n = new Node();
          n->setDocument(doc);
          leaf->setRight(n);
       }
    }
}
//Print the tree inOrder
void BSTree::inOrder(Node* node) {
    if (node) {
       inOrder(node->getLeft());
       cout << node->getDocument() << endl;
       inOrder(node->getRight());
    }
}
//search to see if the document is contained in the Tree
bool BSTree::search(string doc, Node *root) {

	if (root == NULL) {
		return false;
	}
	else if (doc == root->getDocument()) {
		return true;
	}

	return search(doc, root->getLeft()) || search(doc, root->getRight());
}
