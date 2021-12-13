## Random Tree Generator

A generic random tree generator which supports multiple external contraints like max out degree, max heights and so on...

### Steps to get started:
- Required any c++ compiler, one such compiler could be found here [MinGW-w64](https://sourceforge.net/projects/mingw-w64/)

- Clone the project
``` 
git clone https://github.com/manujgrover71/Random_Tree_Generator.git
```
- Create a new cpp file and make sure tree_generator.h file is in the same directory.

- Import the tree generator header file and use the correct namespace.
```cpp
#include "tree_generator.h"
using namespace tree_gen
```
- Initialize the tree node id with 0.
```cpp
template<> int Node< **class name** >::id_gen = 0;
```
- See [Usage](https://github.com/manujgrover71/Random_Tree_Generator/blob/main/README.md#usage) section for functions info.
- Compile the program
```shell
g++ -o <name-the-executable> <cpp-file-name>

# for example: g++ -o test test.cpp
```
- Run the program
  - For ubuntu
   ```shell
   ./<name-given-to-executable>
   
   # for example:
   # $ g++ -o test test.cpp
   # ./test
   ```
   - For windows
   ```shell
   .\<name-given-to-executable>
   
   # for example:
   # $ g++ -o demo test.cpp
   # .\demo
   ```
## Usage:

### - Tree Class:
> Custom class is denoted by *MyClass* in the following.

| Function Name / Declaration | Return Type | Syntax | Use |
| --- | --- | --- | --- |
| Default Constructor | void | Tree<MyClass> Obj; | Creates a new tree object with all contraints having a default value. (default value of max_out_degree = INF and max_depth = INF |
| Parameterized Constructor | void | Tree<MyClass> Obj(10, 20); | Creates a new tree object with parameterised constraints values |
| addNode() | ```bool``` | treeObj.addNode(MyClassObj) | Adds the argument object to the tree. Returns true if successfully added, false otherwise. |
| getEdges() | ```vector<pair<Node<MyClass> *, Node<MyClass> *>>``` | treeObj.getEdges() | Returns a list of edges of Node Object pointers. |

### Types of Constructor:
1. Default Constructor
```cpp
// Tree< **class name** > name;
Tree<int> a; // No limit on maxium out degree and maxium height

Tree<double> b;
Tree<MyClass> c;
```
2. Parameterized constructor
```cpp
// Tree< **class name** > name(max_out_degree, max_depth);

Tree<int> a(10, 5); // max_out degree = 10, max_depth = 5

Tree<double> b(10, 5);
Tree<MyClass> c(10, 5); // Any Random Class.
```

### Adding to Tree:

```cpp

// Note: Each node in the tree contains a unique id, which can be accessed through .getId() function.

Tree<int> obj;
obj.addNode(1); // returns true if 1 got added.
obj.addNode(10); // returns true if 10 got added.

Tree<MyClass> obj2;
MyClass tempObj; // any Random Class Obj.
obj2.addNode(tempObj); // return true if tempObj object of MyClass got added
```

### Get Edges.

```cpp
vector<pair<Node<MyClass> *, Node<MyClass> *>> edges = treeObj.getEdges(;
// or
auto edges = treeObj.getEdges();

// to iterate over the edges

for(int i = 0; i < edges.size(); i++) {
    Node<MyClass> *parent = edges[i].first;
    Node<MyClass> *child = edges[i].second;
}

// or you may use for each loop.
for(auto edge : edges) {
    Node<MyClass> *parent = edge.first;
    Node<MyClass> *child = edge.second;
}

// as these Nodes are pointers, use -> to access any function.
// for example: parent->getId(), child->getData()

```

- Node Class:

| Function Name / Declaration | Return Type | Syntax | Use |
| --- | --- | --- | --- |
| Parameterized constructor | void | Node<MyClass> node(data)| Creates a Node Object with data. |
| getData() | MyClass | nodeObj.getData() | Returns the data stored in the Node Object. |
| getId() | int | nodeObj.getId() | Returs the unique id that identifies the current node object. |
| getOutDegree() | int | nodeObj.getOutDegree() | Returns the current out degree of the given node object. |
| getDepth() | int | nodeObj.getDepth() | Returns the current Depth of given node object. |
| setDepth() | void | nodeObj.getDepth(depth) | Used to set the current depth of node object. |
| canAddChildren() | bool | nodeObj.canAddChildren() | Returns whether we can add a new child to current node. |
| addChild() | void | nodeObj.addChild(child) | Adds a new child to current Node |
| getChildren() | vector<Node<MyClass> *> | nodeObj.getChildren() | Returns a list of children of current node. |

## Demo:
  Here is the test file: [demo.cpp](https://github.com/manujgrover71/Random_Tree_Generator/blob/main/test.cpp)


Sample Structure of tree(denoted using id's):

1. Random tree with 12 nodes.<br><br>
![](https://github.com/manujgrover71/Random_Tree_Generator/blob/main/images/demo_image1.png)
![](https://github.com/manujgrover71/Random_Tree_Generator/blob/main/images/demo_image2.png)
2. Random tree with 12 nodes, max out degree: 3 and max depth: 4.<br><br>
![](https://github.com/manujgrover71/Random_Tree_Generator/blob/main/images/demo_image3(out3%2Cdepth4).png)
3. Random tree with 14 nodes, max out degree: 3, and max height: 3<br><br>
![](https://github.com/manujgrover71/Random_Tree_Generator/blob/main/images/demo_image4(out3%2Cmax3).png)
