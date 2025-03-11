# Trees

* A tree is a collection of nodes
* nodes are connected by edges
* paths are edges from one node to each other

* A tree is defined by a **root node**
  * there is a unique path from a root node to each child node
  * No cycles

* **leaf node** has no children
  * other nodes are **non-leaf** or **interior**
* **depth** of a node is how many steps it takes to reach that node from the root
* **height of the tree** is the depth of the deepest node

Example code for node:

```cpp
struct Node
{
    string name;
    vector<Node*> children;
}
```

## Algorithms

Given a tree, find the number of nodes

```cpp
int countNodes(const Node* p)
{
    if(p == nullptr)
        return 0;
    int total = 1; // starts at one to count itself
    for(int k = 0; k < p-> children.size(); k++)
        total += countNodes(p->children[k])
    return total;
}
```

Print out the tree hierarchy

```cpp
void printTree(const Node* p, int depth)
{
    if(p!= nullptr)
    {
        cout << string(2*depth, ' ');
        cout << p->name << endl;
        for(int k = 0; k < p-> children.size(); k++)
            printTree(p->children[k], depth + 1);
    }
}
```

* **pre-order** traversal of the tree
  * the node is processed before the subtrees

* count tree is **post-order** traversal
  * node is processed after the subtrees

## Binary Trees

A binary tree is empty, or a node with a left binary tree and a right binary tree

* distinguishes between a left child and right child

Every Tree can be represented as a binary tree

* All siblings are connected by right pointers
* All children are connected by left pointers
* pointers can be renamed oldestChild and nextYoungestSibling

A **binary search tree (BST)** is empty, or a node with a left binary tree and a right binary tree such that:

* the value at every node in the left subtree is <= the value at this node
* the value at every node in the right subtree is >= the value at this node

### Insertion and Deletion on Binary Trees

Advantage over binary search on vector -> easy and cheap insertion and deletion

**Insertion:**

* follow tree until nullptr, insert element there

**Deletion:**

Three cases

1. Leaf:
    Easy, simply delete the node and reset the pointers

2. Node with 1 branch:
    Store branch, delete node, then replace node with stored branch

3. Node with 2 branches:
    * Need to find child node to be "promoted", replacing deleted node
    * Either the largest child in the left branch or the smallest child in the right branch
    * Then, delete the node to be promoted, using the two algorithms above, and replace the original deleted node with the promoted node

With a reasonably balanced binary search tree, Insertion, deletion, and lookup are all $O(log N)$

When selecting the node to be promoted, if one side is selected a lot, the tree may become unbalanced

* usually alternating choices works
  * if there is periodicity in the data, could just select randomly

### Printing a BST

```cpp
void printTree(const Node* p)
{
    if(p != nullptr)
    {
        printTree(p->left);
        cout << p->name << endl;
        printTree(p->right);
    }
}
```

**Inorder Traversal:** process left before, right after

### 2-3 Tree

* Nodes can have 2-3 children
* Nodes with 3 children have 2 values
* Left child is less than both
* Middle child is in between both
* Right child is greater than both*

## Sets

* no duplicates, lookup by value

```cpp
#include <set>

set<int> s;
s.insert(10);
s.insert(30);
s.insert(10);
s.insert(5);
s.find(30);
for(set<int>::iterator p = s.begin(); p != end(); p++)
    cout << *p << endl; //writes 5 10 30
```

* set needs a less than operator
* compare with itself returns false
* considered duplicates if neither one is less than the other
