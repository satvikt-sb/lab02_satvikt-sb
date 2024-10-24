// intbst.cpp
// Implements class IntBST
// Satvik Talchuru, October 21, 2024

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() : root(nullptr) { 

}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
    root = nullptr;
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n != nullptr) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if (root == nullptr) {
        root = new Node(value);
        return true;
    } else {
        return insert(value, root);
    }
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n->info) {
        return false;
    } else if (value < n->info) {
        if (n->left == nullptr) {
            n->left = new Node(value);
            return true;
        } else {
            return insert(value, n->left);
        }
    } else {
        if (n->right == nullptr) {
            n->right = new Node(value);
            return true;
        } else {
            return insert(value, n->right);
        }
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n != nullptr) {
        cout << n->info << " "; 
        printPreOrder(n->left);
        printPreOrder(n->right);
    } // IMPLEMENT HERE
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}

void IntBST::printInOrder(Node *n) const {
    if (n != nullptr) {
        printInOrder(n->left);
        cout << n->info << " ";
        printInOrder(n->right);
    }
    // IMPLEMENT HERE
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if (n != nullptr) {
        printPostOrder(n->left);
        printPostOrder(n->right);
        cout << n->info << " ";
    }
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if (n == nullptr) {
        return 0; 
    }
    return n->info + sum(n->left) + sum(n->right);  
}

// return count of values
int IntBST::count() const {
    return count(root); // REPLACE THIS NON-SOLUTION
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if (n == nullptr) {
        return 0; 
    }
    return 1 + count(n->left) + count(n->right); 
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if (n == nullptr) {
        return nullptr;  
    }
    else if (n->info == value) {
        return n; 
    } else if (n->info > value) {
        return getNodeFor(value, n->left); 
    } else {
        return getNodeFor(value, n->right); 
    }
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    if (getNodeFor(value, root) == nullptr) {
        return false;
    }
    return true;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* current = getNodeFor(value, root);

    if (current == nullptr) {
        return nullptr;  
    }

    //
    else if (current->left != nullptr) {
        current = current->left;

        while (current->right != nullptr) {
            current = current->right;  
        }
        return current;
    }
    else {
        Node* parent = root;
        Node* predecessor = nullptr;
        while (parent != nullptr) {
            if (value > parent->info) {
                predecessor = parent;
                parent = parent->right;
            } else {
                parent = parent->left;
            }
        }
        return predecessor;
    }
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node* pred = getPredecessorNode(value);

    if (pred == nullptr) {
        return 0;
    } else {
        return pred->info;
    }
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* current = getNodeFor(value, root);

    if (current == nullptr) {
        return nullptr; 
    }
    else if (current->right != nullptr){
        current = current->right;

        while (current->left != nullptr) {
            current = current->left;  
        }
        return current;
    }
    else {
        Node* parent = root;
        Node* successor = nullptr;
        while (parent != nullptr) {
            if (value < parent->info) {
                successor = parent;  
                parent = parent->left;
            } else {
                parent = parent->right;
            }
        }
    return successor;
    }
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node* succ = getSuccessorNode(value);

    if (succ == nullptr) {
        return 0;
    } else {
        return succ->info;
    }
}

////remove is hardest implementation; save for last
// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    if (contains(value) == false){
        return false;
    }

    Node* remove = getNodeFor(value,root);

    //no children, leaf node
    if ( (remove->left == nullptr) && (remove->right == nullptr) ){
        if (remove->parent == nullptr){
            delete remove;
            root = nullptr;
        }
        else{ 
            if(remove->parent->right == remove){
                remove->parent->right = nullptr;
            }
            else {
                remove->parent->left = nullptr;
            }
            delete remove;
        }
    }
    //one child
    else if ((remove->left == nullptr) || (remove->right == nullptr)){
        Node* child = new Node;

        if (remove->right == nullptr){
            child = remove->left;
        }
        else {
            child = remove->right;
        }

        if(remove->parent == nullptr){
            root = child;
            root->parent = nullptr;
        }
        else {
            if (remove->parent->right == remove){
                remove->parent->right = child;
            }
            else {
                remove->parent->left = child;
            }
            child->parent = remove->parent;
        }
        delete remove;
    }
    else {//work on implementing 2 children case
        return true;
    }
}
    

