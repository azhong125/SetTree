#include "Node.h"


Node::~Node() {
    delete left;
    delete right;
}

void Node::clear(Node* head) {
    if (head->left != NULL) {
        clear(head->left);
        head->left = NULL;
    }
    if (head->right != NULL) {
        clear(head->right);
        head->right = NULL;
    }
    delete head;
}

Node* Node::copy(Node* other) {
    if (other != NULL) {
        Node *newNode = new Node();
        newNode->value = other->value;
        newNode->left = copy(other->left);
        newNode->right = copy(other->right);
        return newNode;
    } else {
        return NULL;
    }
}

string& Node::largest() {
    Node* temp = this;
    while(temp->right != NULL) {
        temp = temp->right;
    }
    string* str = &temp->value;
    return *str;
}
string Node::print() {
    if(left == NULL && right == NULL) return value;

    if (left != NULL || right != NULL) {
        if (left == NULL) return "(- " + value + " " + right->print() + ")";
        if (right == NULL) return "(" + left->print() + " " + value + " -)";
        return "(" + left->print() + " " + value + " " + right->print() + ")";
    }
    return NULL;
}

int Node::numNodes(Node* node) {
    if (node == NULL) return 0;
    else return 1 + numNodes(node->left) + numNodes(node->right);
}

string* Node::lookup(int n) {
    string* str = &value;
    if (numNodes(left) == n ) {
        *str = value;
        return str;
    }

    if (numNodes(this) - numNodes(right) == n) {
        if (right->left != NULL) {
            Node* ptr = right->left;
            while (ptr->left != NULL) {
                ptr = ptr->left;
            }
            *str = ptr->value;
            return str;
        }
        *str = right->value;
        return str;
    }
    if(numNodes(this) - numNodes(right) < n) {
        return right->lookup(n - numNodes(this) + numNodes(right));
    } else {
        if (left != NULL) {
            return left->lookup(n);
        }
    }
    return str;
}

bool Node::contains (string value) {
    if (this->value == value) return true;
    if (left != NULL) {
        if(left->contains(value)) return true;
    }
    if (right != NULL) {
        if(right->contains(value)) return true;
    }
    return false;
}

bool Node::isLeaf () {
    return left == NULL && right == NULL;
}
Node* Node::remove(string value) {
    if (this->value == value) {
        if (right != NULL && left != NULL) {
            // Gets the largest, but smaller than value
            int count = 0;
            Node *ptr = left;
            Node *parent = this;
            Node* prev = left;
            // cout << parent->value << endl;
            while (ptr->right != NULL) {
                ptr = ptr->right;
                if (count == 1) {
                    //  parent = parent->left;
                    prev = prev->right;
                }
                else if (count > 1) {
                    //   parent = parent->right;
                    prev = prev->right;
                }
                count++;
            }
            parent->value = ptr->value;
            delete ptr;
            prev->right = NULL;
            return NULL;

        }
            // Handle case where one of left or right is NULL
        else if (right == NULL) {
            //replace with left child
            Node* ptr = left;
            Node* parent = this;
            parent->value = ptr->value;
            parent->left = ptr->left;
            parent->right = ptr->right;

            while(ptr->left != NULL) {
                parent = parent->left;
                ptr = ptr->left;
                parent->value = ptr->value;
                parent->left = ptr->left;
                parent->right = ptr->right;
            }
            ptr = ptr->left;
            delete ptr;
        }
        else if (left == NULL) {
            //replace with right child
            Node* ptr = right;
            Node* parent = this;

            while(ptr->right != NULL) {
                parent->value = ptr->value;
                parent->left = ptr->left;
                parent->right = ptr->right;
                parent = parent->right;
                ptr = ptr->right;
            }
            ptr = ptr->right;
            delete ptr;
        }
    }
    if (this->value > value) {
        if (left != NULL) {
            if (left->value == value && left->isLeaf()) {
                delete left;
                left = NULL;
            }
            else {
                // recursively call remove to left child
                left->remove(value);
            }
        }
    }
    else if (this->value < value) {
        if (right != NULL) {
            if (right->value == value && right->isLeaf()) {
                delete right;
                right = NULL;
            }
            else {
                // recursively call remove to right child
                right->remove(value);
            }
        }
    }
    return NULL;
}


/*
void Node::remove(string value){
    if ((left != NULL && left->value == value) || (right != NULL && right->value == value)) {
        Node* toDelete = this;
        int count = 0;
        if (left->value == value) {
            toDelete = left;
        }
        else {
            toDelete = right;
            count = 1;
        }
        //if leaf
        if (toDelete->left == NULL && toDelete->right == NULL) {
            delete toDelete;
            if (count == 0) {
                left = NULL;
                return;
            } else {
                right = NULL;
                return;
            }
        }

            //if one child
        else if (toDelete->left == NULL && toDelete->right != NULL) {
            Node* ptr = right;
            Node* parent = this;
            Node* next = right->right;

            while(next != NULL) {
                ptr = ptr->right;
                parent = parent->right;
                next = next->right;
            }

            parent->right = next;
            delete ptr;
            return;
        }
        else if (toDelete->left != NULL && toDelete->right == NULL) {
            Node* ptr = left;
            Node* parent = this;
            Node* next = left->left;

            while(next != NULL) {
                ptr = ptr->left;
                parent = parent->left;
                next = next->left;
            }
            parent->left = next;
            delete ptr;
            return;
        }
            //if two children
        else if(toDelete->left != NULL && toDelete->right != NULL) {
            Node* ptr = left;
            if (left->right == NULL) {
                this->value = ptr->value;
                this->left = NULL;
                delete ptr;
                return;
            }
            Node* next = left->right;
            while (next->right != NULL) {
                next = next->right;
                ptr = ptr->right;
            }
            ptr->value = next->value;
            ptr->right = NULL;
            delete next;
            return;
        }
    } else {
        if (this->value < value) {
            right->remove(value);
        } else if (this->value > value) {
            left->remove(value);
        }
    }

}
void Node::removeParent(string value) {
    if (left == NULL && right == NULL) {
        value = "";
    } else if (left != NULL && right == NULL) {
        Node* ptr = left;
        Node* next = left->right;
        while (next->right != NULL) {
            next = next->right;
            ptr = ptr->right;
        }
        ptr->value = next->value;
        ptr->right = NULL;
        delete next;
    } else if(left == NULL && right != NULL) {
        Node* ptr = right;
        Node* parent = this;
        Node* next = right->right;
        while(next != NULL) {
            ptr = ptr->right;
            parent = parent->right;
            next = next->right;
        }
        parent->right = next;
        delete ptr;
    } else {
        Node* ptr = left;
        if (left->right == NULL) {
            this->value = ptr->value;
            this->left = NULL;
            delete ptr;
        } else {
            Node* next = left->right;
            while (next->right != NULL) {
                next = next->right;
                ptr = ptr->right;
            }
            this->value = next->value;
            ptr->right = NULL;
            delete next;
        }
    }*/
