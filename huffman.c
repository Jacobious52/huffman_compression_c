#include "huffman.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// SEG FAULT SEARCHING TOOL ;)
#define MARK fprintf(stderr, "%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);

int *make_freq_table(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "unable to open file %s\n", filename);
        return NULL;
    }

    // create empty map array where key is ascii value and value is frequency
    int *table = (int *)calloc(TABLE_SIZE, sizeof(int));

    char c;
    while ((c = fgetc(file)) != EOF) {
        if (c >= 0) {
            table[(int)c]++;
        }
    }
    table[TABLE_SIZE-1] = 1;

    return table;
}

void fill_table(struct node *root, char **table, char *seq, const char *a) {
    seq = (char *)realloc(seq, strlen(seq) + strlen(a) + 1);
    seq = strcat(seq, a);

    if (root == NULL) {
        return;
    }

    fill_table(root->left, table, strdup(seq), "0");
    fill_table(root->right, table, strdup(seq), "1");

    table[(int)root->val] = strdup(seq);

    free(seq);
}

char **huffman_encode_table(struct node *tree) {
    char **table = (char **)calloc(TABLE_SIZE, sizeof(char *));

    fill_table(tree, table, malloc(sizeof(char)), "");

    return table;
}

struct node *build_tree(struct heap *h) {
    while (h->len > 1) {
        struct node *l = pop_heap(h);
        struct node *r = pop_heap(h);
        struct node *root = make_node(l, r, l->key + r->key, 0);
        push_heap(h, root);
    }
    return pop_heap(h);
}

void free_tree(struct node *root) {
    if (root == NULL) return;

    // post order free
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

struct node *huffman_encode_tree(char *filename) {
    int *freq = make_freq_table(filename);

    // count number of non zero characters
    int i, count;
    for (i = 0, count = 0; i < TABLE_SIZE; ++i) {
        if (freq[i] > 0) count++;
    }

    // create an array of node * count large + 1 for EOF character
    struct node **nodes = (struct node **)malloc(count * sizeof(struct node *));
    for (i = 0, count = 0; i < TABLE_SIZE; ++i) {
        // only add chars that have a non zero freq to put in the heap
        if (freq[i] > 0) {
            nodes[count] = make_node(NULL, NULL, freq[i], (unsigned char)i);
            count++;
        }
    }

    // frequency table not needed anymore
    free(freq);

    struct heap h = heapify(nodes, count);
    struct node *t = build_tree(&h);

    // nodes array not needed anymore. nodes themself are in the tree and should be deleted through free_tree
    free(nodes);
    return t;
}
