// PQ contains the code for the proirity queue
// also contains node definition for tree

#ifndef PQ_H
#define PQ_H

// node of the priority queue and huffman tree
struct node {
    int key;
    char val;
    struct node *left, *right;
};

// malloc a new node
struct node *make_node(struct node *left, struct node *right, int k, int v);

// struct contains the nodes in heaped order and the length of the heap
// essentially a slice
// cap is the maximum capacity of the array nodes
// length is the current number in the array
struct heap {
    struct node **nodes;
    int len;
    int cap;
};

// turn an unordered array of node * into a min heap order in O(n) time
struct heap heapify(struct node **nodes, int len);

// remove and return the min element of the heap
struct node *pop_heap(struct heap *h);

// enqueue a node onto the heap. Does not grow the heap.
// Not growing is okay for huffman tree since 2 nodes are taken out for every 1 put in.
void push_heap(struct heap *h, struct node *n);

#endif /* PQ_H */
