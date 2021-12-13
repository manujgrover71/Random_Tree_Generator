#include <bits/stdc++.h>

#include "tree_generator.h"
using namespace std;
using namespace tree_gen;
template<> int Node<int>::id_gen = 0;

int main() {

    Tree<int> t; // with default constructor, no limit on out degree and depth.
    for(int i = 1; i <= 30; i++) {
        t.addNode(i);
    }

    Tree<int> t1(3, 5); // with max_out_degree, max_depth
    for(int i = 1; i <= 20; i++) {
        t1.addNode(i);
    }

    for(auto edge : t.getEdges()) {
        cout << edge.first << ' ' << edge.second << '\n';
    }

    cout << '\n';

    for(auto edge : t1.getEdges()) {
        cout << edge.first << ' ' << edge.second << '\n';
    }
}