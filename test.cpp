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
        cout << t.addNode(RandNumbers(rand() % 100, rand() % 100)) << '\n';
    }

    // taking the edges.
    auto edges = t.getEdges();
    
    for(auto edge : edges) {
        auto *parent = edge.first;
        auto *child = edge.second;
        
        long long parentId = parent->id;
        long long childId = child->id;
        
        int parentDepth = parent->depth;
        int childDepth = child->depth;
        
        cout << parentId << ' ' << childId << '\n';
    }
}