#ifndef TREE_GEN
#define TREE_GEN

#include <vector>
#include <random>
#include <ctime>
#include <queue>
#include <chrono>
using namespace std;
using namespace chrono;

namespace tree_gen {
    
    mt19937 gen(time(0));
    uniform_int_distribution<long long> distr(0, 1e18);
    
    int getRandInRange(long long min, long long max) {
        if(min == 0 && max == 0) {
            return 0;
        }
        return min + (distr(gen) % (max - min + 1));
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

    public:
        explicit Node(T data) : data(data) {
            
            // generate a unique id.
            long long current_time = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
            this->id = current_time + getRandInRange(1e16, 1e17 - 1);

            // initialize the requirements.
            this->out = 0;
            this->depth = -1;
            this->child_addable = true;
        }
        
        // getter for id.
        long long getId() {
            return this->id;
        }

        // getter for out degree
        int getOutDegree() {
            return this->out;
        }

        // increment out degree of current node
        void incrementOutDegree() {
            this->out++;
        }

        // getter for depth of current node.
        int getDepth() {
            return this->depth;
        }

        // setter for depth of current node.
        void setDepth(int depth) {
            this->depth = depth;
        }

        // getter for addableChildren bool
        bool canAddChildren() {
            return child_addable;
        }

        // setter for addableChildren bool
        void setchild_addable(bool status) {
            this->child_addable = status;
        }

        // add child.
        void addChild(Node<T> *child) {
            children.push_back(child);
        }

        // getter for children
        vector<Node *> getChildren() {
            return this->children;
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

        // for generating random numbers
        
        
        static const int INF = 1e9;

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
                head->setDepth(1);

                // increase total_nodes.
                this->total_nodes++;

                // node is added.
                return true;
            }

            // probability of adding current_node at any parent.
            int probab = total_nodes - non_addable - head->canAddChildren();

            // utility function to add node.
            return addNodeUtil(current_node, head, probab);
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

                    for (auto child : current_node->getChildren()) {
                        edges.push_back({current_node, child});

                        q.push(child);
                    }
                }
            }

            return edges;
        }

    private:


        bool addNodeUtil(Node<N> *current_node, Node<N> *parent, int &probab) {

            // check if we could add current element as child of parent node.
            if(parent->canAddChildren() && isAddable(parent, probab)) {

                // add child to parent.
                parent->addChild(current_node);

                // increase out degree of parent node.
                parent->incrementOutDegree();

                // set depth of curret node.
                current_node->setDepth(parent->getDepth() + 1);

                // increment the total nodes count.
                total_nodes++;

                // check of addability of parent and current node.
                if(!canAddMore(parent)) {
                    non_addable++;
                    parent->setchild_addable(false);
                }

                if(!canAddMore(current_node)) {
                    non_addable++;
                    current_node->setchild_addable(false);
                }

                // node is added.
                return true;
            }

            // traverse down the path to check for other places.
            if(parent->getDepth() + 1 <= max_depth) {

                for(auto child : parent->getChildren()) {
                    // update the probability
                    probab -= child->canAddChildren();

                    // check children of parent node.
                    if(addNodeUtil(current_node, child, probab)) {
                        return true;
                    }
                }
            }

            // couldn't add in current subtree.
            return false;
        }

        // function to check if we could add more child to current node.
        // apply extra constraints as needed!!
        bool canAddMore(Node<N> *current_node) {

            // depth check
            if(current_node->getDepth() == max_depth)
                return false;

            // out degree check
            if(current_node->getOutDegree() == max_out)
                return false;

            return true;
        }

        // function to check if we could add child to current node.
        // apply extra constraints as needed!!
        bool isAddable(Node<N> *parent, int probab) {

            // depth check
            if(parent->getDepth() + 1 > max_depth) {
                return false;
            }

            // max out degree check
            if(parent->getOutDegree() + 1 > max_out) {
                return false;
            }

            // randomness
            return getRandInRange(0, probab) == 0;
        }
    };
}

#endif
