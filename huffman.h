#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "pq.h"

// create a huffman encoded tree from a file, n will be set to the len of the tree
struct node *huffman_encode_tree(char *filename, int *n);

// create an enoding table from a tree
// example:
// t[(int)'a'] = "01011"
char **huffman_encode_table(struct node *tree, int n);

// free the tree from memory
void free_tree(struct node *root);

#endif /* HUFFMAN_H */
