#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;


struct Node {
    int totalCount = 0;
    string value;
    Node* left;
    Node* right;

    ~Node();
    void clear(Node* head);
    Node* copy(Node* other);
    string& largest();
    string print();
    int numNodes(Node* node);
    string* lookup(int n);
    bool contains (string value);
    bool isLeaf ();
    Node* remove(string value);
};

#endif
