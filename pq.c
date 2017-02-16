#include "pq.h"

#include <stdio.h>
#include <stdlib.h>

struct node *make_node(struct node *left, struct node *right, int k, int v) {
    struct node *t = (struct node *)malloc(sizeof(struct node));
    t->key = k;
    t->val = v;
    t->left = left;
    t->right = right;
    return t;
}

void sift_down(struct heap h, int i, int n) {
    while (1) {
        // index of left child
        int l = 2*i + 1;
        if (l >= n || l < 0) break;

        int j = l;

        // index of right child
        int r = l + 1;
        if (r < n && !(h.nodes[l]->key < h.nodes[r]->key)) {
            j = r;
        }

        if (!(h.nodes[j]->key < h.nodes[i]->key)) break;

        // swap
        struct node *temp = h.nodes[i];
        h.nodes[i] = h.nodes[j];
        h.nodes[j] = temp;
        i = j;
    }
}

void sift_up(struct heap h, int i) {
    while (1) {
        // index of parent
        int j = (i - 1)/2;
        if (i == j || !(h.nodes[i]->key < h.nodes[j]->key)) break;

        // swap
        struct node *temp = h.nodes[i];
        h.nodes[i] = h.nodes[j];
        h.nodes[j] = temp;
        i = j;
    }
}

struct heap heapify(struct node **nodes, int len) {
    struct heap h = {nodes, len, len};

    int i;
    for (i = h.len/2 - 1; i >= 0; --i) {
        sift_down(h, i, h.len);
    }

    return h;
}

struct node *pop_heap(struct heap *h) {
    if (h->len < 1) {
        fprintf(stderr, "heap has no items left\n");
        return NULL;
    }

    // last element
    int n = h->len - 1;

    // swap first and last then sift top down
    struct node *temp = h->nodes[0];
    h->nodes[0] = h->nodes[n];
    h->nodes[n] = temp;

    sift_down(*h, 0, n);

    // shrink and remove last
    temp = h->nodes[n];
    h->nodes[n] = NULL;
    h->len = n;

    return temp;
}

void push_heap(struct heap *h, struct node *n) {
    if (h->len == h->cap) {
        fprintf(stderr, "heap has no more space left\n");
        return;
    }
    // increase size
    h->len++;
    // add to bottom and shift up
    h->nodes[h->len-1] = n;
    sift_up(*h, h->len-1);
}
