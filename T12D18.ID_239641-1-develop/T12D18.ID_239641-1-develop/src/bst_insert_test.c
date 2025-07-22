#include <stdio.h>

#include "bst.h"

void bstree_insert_node_test(t_btree *root);

int main() {
    t_btree *root = bstree_create_node(5);
    bstree_insert_node_test(root);
    desroy_bstree(root);
    return 0;
}

void bstree_insert_node_test(t_btree *root) {
    int number = 6;
    printf("Test to insert right node after root, input item = %d\n", number);
    bstree_insert(root, number, compare_tree_items);
    printf("Output: root->right->item = %d\n", root->right->item);
    if (root->right->item == number)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");

    number = 2;
    printf("Test to insert left node after root, input item = %d\n", number);
    bstree_insert(root, number, compare_tree_items);
    printf("Output: root->left->item = %d\n", root->left->item);
    if (root->left->item == number)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");

    number = 3;
    printf("Test to insert input item = %d\nIt should be in left after root and next right node\n", number);
    bstree_insert(root, number, compare_tree_items);
    printf("Output: root->left->right->item = %d\n", root->left->right->item);
    if (root->left->right->item == number)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");
}
