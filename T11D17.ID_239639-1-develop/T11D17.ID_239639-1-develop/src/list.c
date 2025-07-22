#include "list.h"

#include <stdio.h>
#include <stdlib.h>

#include "door_struct.h"

struct node* init(struct door* door) {
    struct node* new_elem = malloc(sizeof(struct node));
    new_elem->door = door;
    new_elem->pNext = NULL;
    return new_elem;
}

struct node* add_door(struct node* elem, struct door* door) {
    if (elem == NULL) {
        return NULL;
    }
    struct node* new_elem = malloc(sizeof(struct node));
    new_elem->door = door;
    new_elem->pNext = elem->pNext;
    elem->pNext = new_elem;
    return new_elem;
}

struct node* find_door(int door_id, struct node* root) {
    struct node* cur = root;
    while (cur != NULL && cur->door->id != door_id) {
        cur = cur->pNext;
    }
    return cur;
}

struct node* remove_door(struct node* elem, struct node* root) {
    struct node* cur = root;
    if (elem == root) {
        cur = root->pNext;
        free(root);
        root = cur;
    } else {
        while (cur->pNext != elem) {
            cur = cur->pNext;
        }
        cur->pNext = elem->pNext;
        free(elem);
    }
    return root;
}

void destroy(struct node* root) {
    while (root != NULL) {
        struct node* tmp = root->pNext;
        free(root);
        printf("OK");
        root = tmp;
    }
}

void output(struct node* root) {
    if (root == NULL)
        printf("list pust\n");
    else {
        struct node* cur = root;
        while (cur != NULL) {
            printf("%d %d\n", cur->door->id, cur->door->status);
            cur = cur->pNext;
        }
    }
}
