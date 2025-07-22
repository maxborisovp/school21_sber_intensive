#ifndef LIST_H
#define LIST_H

struct node {
    struct door* door;
    struct node* pNext;
};

struct node* init(struct door* door);
struct node* add_door(struct node* elem, struct door* door);
struct node* find_door(int door_id, struct node* root);
struct node* remove_door(struct node* elem, struct node* root);
void destroy(struct node* root);
void output(struct node* root);

#endif
