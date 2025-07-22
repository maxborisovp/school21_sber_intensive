#include "bst.h"

#include <stdio.h>
#include <stdlib.h>

t_btree* bstree_create_node(int item) {
    t_btree* root = malloc(sizeof(t_btree));
    root->item = item;
    root->left = NULL;
    root->right = NULL;
    return root;
}

void bstree_insert(t_btree* root, int item, int (*cmpf)(int, int)) {
    t_btree* cur = root;
    t_btree* new_node = malloc(sizeof(t_btree));
    new_node->item = item;
    new_node->left = NULL;
    new_node->right = NULL;

    int stop = 1;
    while (stop) {
        if (cmpf(cur->item, item)) {
            if (cur->left != NULL)
                cur = cur->left;
            else {
                cur->left = new_node;
                stop = 0;
            }
        } else {
            if (cur->right != NULL)
                cur = cur->right;
            else {
                cur->right = new_node;
                stop = 0;
            }
        }
    }
}

void bstree_apply_infix(t_btree* root, void (*applyf)(int)) {
    if (root != NULL) {
        bstree_apply_infix(root->left, applyf);
        applyf(root->item);
        bstree_apply_infix(root->right, applyf);
    }
}

void bstree_apply_prefix(t_btree* root, void (*applyf)(int)) {
    if (root != NULL) {
        applyf(root->item);
        bstree_apply_prefix(root->left, applyf);
        bstree_apply_prefix(root->right, applyf);
    }
}

void bstree_apply_postfix(t_btree* root, void (*applyf)(int)) {
    if (root != NULL) {
        bstree_apply_postfix(root->left, applyf);
        bstree_apply_postfix(root->right, applyf);
        applyf(root->item);
    }
}

void desroy_bstree(t_btree* root) {
    if (root != NULL) {
        desroy_bstree(root->left);
        desroy_bstree(root->right);
        free(root);
    }
}

int compare_tree_items(int item_old, int item_new) { return item_old > item_new; }

void print_tree_item(int item) { printf("%d ", item); }
