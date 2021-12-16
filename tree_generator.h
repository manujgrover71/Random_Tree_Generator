#ifndef TREE_GEN
#define TREE_GEN

#include <vector>
#include <random>
#include <ctime>
#include <queue>
#include <stdexcept>
#include <chrono>
using namespace std;
using namespace chrono;

namespace tree_gen {
    
    mt19937 gen(time(0));
    uniform_int_distribution<long long> distr(0, 1e18);
    
    const long long current_time = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
    
    int getRandInRange(long long min, long long max) {
        if(min == 0 && max == 0) {
            return 0;
        }
        return min + (distr(gen) % (max - min + 1));
    }

    long long getUUID() {
        return current_time + getRandInRange(1e16, 1e17 - 1);
    }

    template<typename T>
    struct Node {
        // unique id for current node.
        long long id{};
        // data for current node.
        T data;
        // list of children of current node.
        vector<Node *> children;

        // current out degree
        int out{};

        // current depth
        int depth{};

        // boolean to represent if mode childen could be added.
        bool child_addable{};

        explicit Node(T data) : data(data) {
            // get a unique id.
            this->id = getUUID();

            // initialize the requirements.
            this->out = 0;
            this->depth = -1;
            this->child_addable = true;
        }
    };

    template<typename N>
    class Tree {

        // root of tree
        Node<N> *head;

        //  number of nodes which can not have more children.
        int non_addable{};

        // number of nodes in tree.
        int total_nodes{};

        // requirements
        // just add more constraints...
        int max_depth{};
        int max_out{};
        
        static const int INF = 1e9;
        
        // list to store all nodes which can have more children.
        vector<Node<N> *> valid_parents;

    public:
        Tree() {
            // initialize head with null.
            this->head = nullptr;

            // initialize the variables.
            this->non_addable = 0;
            this->total_nodes = 0;

            // for default constructor
            this->max_out = INF;
            this->max_depth = INF;            
        }


        explicit Tree(int max_out_degree, int max_depth) : Tree() {
        
            if(max_depth < 1) {
                throw runtime_error("Max Depth should be greater than 1");
            }
            
            if(max_out_degree < 0) {
                throw runtime_error("Max out degree should be positive");
            }
        
            this->max_out = max_out_degree;
            this->max_depth = max_depth;
            
        }

        // function to add data as node in tree
        // returns true if node is added, else false.
        bool addNode(N data) {
            // create Node class with given data.
            auto *current_node = new Node<N>(data);

            // if head is null, make current_node as head.
            if(head == nullptr) {
                head = current_node;

                // make depth 1.
                head->depth = 1;

                // increase total_nodes.
                this->total_nodes++;
                
                // if head can have more children, add to valid_parents list.
                if(canAddMore(head)) {
                    valid_parents.push_back(head);
                }
            
                // node is added.
                return true;
            }
            
            // if no parent is there, we cannot add new child.
            if(valid_parents.empty()) {
                return false;
            }
            
            // take a random parent.
            int toChoose = getRandInRange(0, (int)valid_parents.size() - 1);
            
            // move that parent to last of list, so that removing can be done in O(1) if required.
            swap(valid_parents[toChoose], valid_parents.back());
            
            // take the parent.
            Node<N> *parent = valid_parents.back();
            
            // increase the out degree.
            parent->out++;
            
            // add current node as child of parent.
            parent->children.push_back(current_node);
            
            // set the depth of child to parent_depth + 1.
            current_node->depth = parent->depth + 1;
            
            // if the parent cannot have more children, remove it from the list.
            if(!canAddMore(parent)) {
                valid_parents.pop_back();
                parent->child_addable = false;
            }
            
            // if current node can have children, add it to the list.
            if(canAddMore(current_node)) {
                valid_parents.push_back(current_node);
            } else {
                current_node->child_addable = false;
            }
            
            // increase the total_nodes count.
            this->total_nodes++;
            
            // new node has been added.
            return true;
        }

        // function to return edges in form of ids of node.
        vector<pair<Node<N> *, Node<N> *>> getEdges() {
            vector<pair<Node<N> *, Node<N> *>> edges;

            queue<Node<N> *> q;
            if (head != nullptr)
                q.push(head);

            while (q.size()) {
                int sz = q.size();

                for (int i = 0; i < sz; i++) {
                    auto current_node = q.front();
                    q.pop();

                    for (auto child : current_node->children) {
                        edges.push_back({current_node, child});

                        q.push(child);
                    }
                }
            }

            return edges;
        }

    private:

        // function to check if we could add more child to current node.
        // apply extra constraints as needed!!
        bool canAddMore(Node<N> *current_node) {

            // depth check
            if(current_node->depth == max_depth)
                return false;

            // out degree check
            if(current_node->out == max_out)
                return false;

            return true;
        }
    };
}

#endif
