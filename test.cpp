#include "Set.h"
#include <iostream>
using namespace std;

int main() {
    Set set;
    set.insert("d");
    set.insert("b");
    set.insert("e");
    set.insert("a");
    set.insert("c");
    set.insert("f");
    set.insert("g");
    set.print();
    cout << "count: " << set.count() << endl;

    set.remove("d");
    set.print();
    //cout <<str;
    //cout << set.lookup(4)<<endl;
    //cout << set.lookup(4) << endl;

  return 0;
}
