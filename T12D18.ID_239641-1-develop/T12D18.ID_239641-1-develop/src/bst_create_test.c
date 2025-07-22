#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

void bstree_create_node_test(int number);

int main() {
    bstree_create_node_test(5);
    bstree_create_node_test(-9);
    bstree_create_node_test(0);
    return 0;
}

void bstree_create_node_test(int number) {
    printf("Test to create root bs tree node, input item = %d\n", number);
    t_btree *root = bstree_create_node(number);
    printf("Output: root.item = %d\n", root->item);
    if (root->item == number)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");
    free(root);
}
