#include <stdio.h>

#include "bst.h"

void bstree_traverse_test(t_btree *root);

int main() {
    t_btree *root = bstree_create_node(5);
    bstree_insert(root, 7, compare_tree_items);
    bstree_insert(root, 2, compare_tree_items);
    bstree_insert(root, 3, compare_tree_items);
    bstree_insert(root, 6, compare_tree_items);
    bstree_insert(root, 10, compare_tree_items);
    bstree_insert(root, 1, compare_tree_items);
    printf("Now tree view:\n        5\n    2       7\n  1   3   6   10\n\n");
    bstree_traverse_test(root);
    desroy_bstree(root);
    return 0;
}

void bstree_traverse_test(t_btree *root) {
    const char *expected_infix = "1 2 3 5 6 7 10";
    const char *expected_prefix = "5 2 1 3 7 6 10";
    const char *expected_postfix = "1 3 2 6 10 7 5";

    printf("Test to output infix mode, wait: %s\nOutput: ", expected_infix);
    bstree_apply_infix(root, print_tree_item);

    printf("\n\nTest to output prefix mode, wait: %s\nOutput: ", expected_prefix);
    bstree_apply_prefix(root, print_tree_item);

    printf("\n\nTest to output postfix mode, wait: %s\nOutput: ", expected_postfix);
    bstree_apply_postfix(root, print_tree_item);
}
