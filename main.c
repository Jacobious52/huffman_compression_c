#include "huffman.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    if (argc < 2) {
        printf("not enough args\n");
        return 0;
    }

    struct node *tree = huffman_encode_tree(argv[1]);
    char **table = huffman_encode_table(tree);

    FILE *file = fopen(argv[1], "r");
    char c;
    while ((c = fgetc(file)) != EOF) {
        printf("%s", table[(int)c]);
    }
    printf("%s", table[TABLE_SIZE-1]);

    free_tree(tree);
    free(table);

    return 0;
}
