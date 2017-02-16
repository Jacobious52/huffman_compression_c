#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "pq.h"

// Last char is psudo eof
#define TABLE_SIZE 127

// create a huffman encoded tree from a file
struct node *huffman_encode_tree(char *filename);

// create an enoding table from a tree
// example:
// t[(int)'a'] = "01011"
char **huffman_encode_table(struct node *tree);

// free the tree from memory
void free_tree(struct node *root);

#endif /* HUFFMAN_H */
