#ifndef BST_H
#define BST_H

typedef struct t_btree {
    int item;
    struct t_btree* left;
    struct t_btree* right;
} t_btree;

t_btree* bstree_create_node(int item);
void bstree_insert(t_btree* root, int item, int (*cmpf)(int, int));
void bstree_apply_infix(t_btree* root, void (*applyf)(int));
void bstree_apply_prefix(t_btree* root, void (*applyf)(int));
void bstree_apply_postfix(t_btree* root, void (*applyf)(int));
void desroy_bstree(t_btree* root);

int compare_tree_items(int item_old, int item_new);
void print_tree_item(int item);
#endif
