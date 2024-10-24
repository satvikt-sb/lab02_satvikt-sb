#include "intbst.h"
#include <iostream>
using namespace std;

int main() {
    IntBST tree;

    // Test Insert
    cout << "Inserting values" << endl;
    tree.insert(64);
    tree.insert(8);
    tree.insert(128);
    tree.insert(4);
    tree.insert(32);
    tree.insert(16);
    tree.insert(512);
    tree.insert(256);

    cout << "PreOrder traversal: ";
    tree.printPreOrder();
    cout << endl;

    cout << "InOrder traversal: ";
    tree.printInOrder();
    cout << endl;

    cout << "PostOrder traversal: ";
    tree.printPostOrder();
    cout << endl;

    cout << "Checking for 64: " << (tree.contains(64) ? "Yes" : "No") << endl;  // Yes
    cout << "Checking for 17: " << (tree.contains(17) ? "Yes" : "No") << endl;  // No

    cout << "Predecessor of 64 is: " << tree.getPredecessor(64) << endl;  // 32
    cout << "Predecessor of 4 is: " << tree.getPredecessor(4) << endl;    // 0 
    cout << "Predecessor of 512 is: " << tree.getPredecessor(512) << endl;  // 256

    cout << "Successor of 64 is: " << tree.getSuccessor(64) << endl;      // 128
    cout << "Successor of 4 is: " << tree.getSuccessor(4) << endl;        // 8
    cout << "Successor of 512 is: " << tree.getSuccessor(512) << endl;    // 0 

    cout << "Sum of all nodes: " << tree.sum() << endl;  // 1020
    cout << "Total number of nodes: " << tree.count() << endl;  // 8

}
