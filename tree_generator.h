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

        explicit Node(T data) : data(data) {
            // get a unique id.
            this->id = getUUID();
            // initialize the requirements.
            this->out = 0;
            this->depth = -1;
        }
    };

    template<typename N>
    class Tree {

        // root of tree
        Node<N> *head;

        // all the node paths that are avaiable.
        vector<int> available_node_paths;
        
        int curr_power{};
        int next_power{};
        
        // upper_bound on the paths.
        int max_power{};

        // number of nodes in tree.
        int total_nodes{};

        // requirements
        // just add more constraints...
        int max_depth{};
        int max_out{};

        static const int INF = 1e9;

    public:
        Tree() {
            // initialize head with null.
            this->head = nullptr;

            // initialize the variables.
            this->total_nodes = 0;

            // for default constructor, default values.
            this->max_out = 5; 
            this->max_depth = 10;
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

            this->next_power = max_out;
            this->curr_power = 0;
            this->max_power = pow(this->max_out, this->max_depth - 1);
        }

        // function to add data as node in tree
        // returns true if node is added, else false.
        bool addNode(N data) {
            // add more node paths.
            addPaths();
            
            auto *current_node = new Node<N>(data);

            current_node->children.resize(max_out, nullptr);

            // if head is null, make current_node as head.
            if(head == nullptr) {
                head = current_node;

                // make depth 1.
                head->depth = 1;

                // increase total_nodes.
                this->total_nodes++;

                // node is added.
                return true;
            }

            if(available_node_paths.empty()) {
                return false;
            }
            
            Node<N> *parent = head;
            
            // get any avaiable path
            int toChoose = getRandInRange(0, available_node_paths.size() - 1);
            swap(available_node_paths[toChoose], available_node_paths.back());
            toChoose = available_node_paths.back();
            available_node_paths.pop_back();
            
            // convert into b base.
            string inBase;
            while(toChoose > 0) {
                inBase += char((toChoose % max_out) + '0');
                toChoose /= max_out;
            }
            reverse(inBase.begin(), inBase.end());
            
            // move head pointer to the path and add it to the appropriate place.
            int n = inBase.size();
            for(int i = 0; i < n; i++) {
                if(i == n - 1) {
                    parent->children[inBase[i] - '0'] = current_node;
                } else {
                    parent = parent->children[inBase[i] - '0'];
                }
            }

            // increment out degree.
            parent->out++;
            
            // set the depth of current node.
            current_node->depth = parent->depth + 1;
            
            // node added.
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
                        if(child == nullptr)
                            continue;
                        edges.push_back({current_node, child});

                        q.push(child);
                    }
                }
            }

            return edges;
        }

    private:

        void addPaths() {

            if(!available_node_paths.empty())
                return;

            while(curr_power < next_power && available_node_paths.size() < 10) {
                available_node_paths.push_back(curr_power++);
            }

            if(next_power < max_power - 1 && curr_power == next_power) {
                next_power *= max_out;
            }

        }
    };
}

#endif