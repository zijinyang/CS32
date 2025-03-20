# Heaps

Every item has a priority, highest priority is returned first

A *complete binary tree* is a binary tree that is completely filled at every level, except possibly the deepest level, which is filled from left to right.

A (max) heap is a complete binary tree in which the value at every node is greater than values of all the nodes in its subtrees

A min heap is a complete binary tree in which the value at every node is less than values of all the nodes in its subtrees

## Deletion

* remove root
* remove last item added and set as root (to maintain complete binary tree)
* reform the heap quality
  * "trickle" the new root down
* O(logN), better than binary search tree

## Insertion

* add element in proper place for complete binary tree
* "bubble" element up to proper place
  * compare with parents, and if bigger, swap
* O(logN) also better than binary search tree

## Array Representation

$parent(i) = \lfloor \frac{i-1}{2} \rfloor$
$children(j) = 2j+1, 2j+2$

## Heapsort

Sorting by putting elements in array, then taking out, as it comes out in order of priority

$O(N!) = O(NlogN)$

* turn array into heap
  * starting with leaf nodes, incrementally make the smaller sub-trees heaps
  * $O(N)$
* repeatedly remove items from the heap
  * take first item and swap with last (equivalent to deletion of first item)
  * size of heap goes down 1
  * repeat