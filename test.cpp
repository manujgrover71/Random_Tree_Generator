#include <bits/stdc++.h>

#include "tree_generator.h"
using namespace std;
using namespace tree_gen;

class RandNumbers {
    int rand1;
    int rand2;
    
public:
    RandNumbers(int rand1, int rand2) : rand1(rand1), rand2(rand2) {}
};

int main() {

    // default constructor.
    Tree<RandNumbers> t(3, 3);
    
    // adding class to tree.
    for(int i = 0; i < 50; i++) {
        t.addNode(RandNumbers(rand() % 100, rand() % 100));
    }

    // taking the edges.
    auto edges = t.getEdges();
    
    set<long long> st;
    
    for(auto edge : edges) {
        auto *parent = edge.first;
        auto *child = edge.second;
        
        long long parentId = parent->getId();
        long long childId = child->getId();
        
        int parentDepth = parent->getDepth();
        int childDepth = child->getDepth();
        
        cout << parentId << ' ' << childId << '\n';
    }
}