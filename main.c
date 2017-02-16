#include "huffman.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    if (argc < 2) {
        printf("not enough args\n");
        return 0;
    }

    int n;
    struct node *tree = huffman_encode_tree(argv[1], &n);
    free_tree(tree);

    return 0;
}
