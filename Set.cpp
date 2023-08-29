#include "Set.h"
#include <stdexcept>
#include <string>
using namespace std;

Set::Set() {
    mRoot = new Node();
    mRoot->value = "";
    mRoot->left = NULL;
    mRoot->right = NULL;
}

Set::Set(const Set& other) {
    if (other.mRoot == NULL) {
        mRoot = new Node();
        mRoot->value = "";
        mRoot->left = NULL;
        mRoot->right = NULL;
    }

    if (other.mRoot != NULL) {
        mRoot = mRoot->copy(other.mRoot);
        mRoot->totalCount = other.mRoot->totalCount;

    }
}

Set::Set(Set&& other){
    if (other.mRoot == NULL) {
        mRoot = new Node();
        mRoot->value = "";
        mRoot->left = NULL;
        mRoot->right = NULL;
    }

    if (other.mRoot != NULL) {
        mRoot = mRoot->copy(other.mRoot);
    }
    other.clear();
}

Set::~Set() {
    if (mRoot != NULL) mRoot->clear(mRoot);
}

size_t Set::clear() {
    if (mRoot == NULL || mRoot->value == "") return 0;
    int num = 0;
    num += mRoot->totalCount;
    mRoot->clear(mRoot);
    mRoot = NULL;
    return num;
}

bool Set::contains(const std::string& value) const {
    if (mRoot->value == "") return false;
    return mRoot->contains(value);
}

size_t Set::count() const {
    if (mRoot == NULL) return 0;
    return mRoot->totalCount;
}

size_t Set::insert(const std::string& value) {
    bool added = false;
    if (mRoot->value == "") {
        mRoot->value = value;
        added = true;
    }
    Node* current = mRoot;
    while (!added) {
        if (value == current->value) break;
        if (value < current->value) {
            if (current->left == NULL) {
                current->left = new Node();
                current->left->value = value;
                added = true;
            } else {
                current = current->left;
            }
        }

        else if (value > current->value) {
            if (current->right == NULL) {
                current->right = new Node();
                current->right->value = value;
                added = true;
            } else {
                current = current->right;
            }
        }
    }
    if (added){
        mRoot->totalCount++;
        return 1;
    }
    else return 0;
}

const std::string& Set::lookup(size_t n) const {
    if (mRoot->value == "" || n >= count()) throw out_of_range("Index out of range");

    if (n + 1 == count()) {
        //return the last value
        return mRoot->largest();
    }

    return *mRoot->lookup(n);
}

void Set::print() const {
    if(mRoot == NULL) cout << "-" << endl;
    else {
        if (mRoot->value == "") cout << "-";
        cout << mRoot->print() << endl;
    }
}

size_t Set::remove(const std::string& value) {
    if (mRoot->value == "" || mRoot == NULL) return 0;
    if (!contains(value)) return 0;
    else {
        if (mRoot->value == value && mRoot->left == NULL && mRoot->right == NULL) {
            mRoot->value = "";
        }
        else mRoot->remove(value);
        mRoot->totalCount--;
        return 1;
    }
}