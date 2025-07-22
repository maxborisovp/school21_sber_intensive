#include "list.h"

#include <stdio.h>
#include <stdlib.h>

#include "door_struct.h"

void add_door_test(struct node* root, struct door* door1, struct door* door2, struct door* door3,
                   struct door* door4);
void remove_door_test(struct node* root);

int main() {
    struct door door1;
    door1.id = 1;
    door1.status = 4;
    struct door door2;
    door2.id = 3;
    door2.status = 5;
    struct door door3;
    door3.id = 6;
    door3.status = 2;
    struct door door4;
    door4.id = 10;
    door4.status = 0;
    printf("Init list and add door1 id %d status %d\n", door1.id, door1.status);
    struct node* root = init(&door1);
    output(root);
    add_door_test(root, &door1, &door2, &door3, &door4);
    remove_door_test(root);

    return 0;
}

void add_door_test(struct node* root, struct door* door1, struct door* door2, struct door* door3,
                   struct door* door4) {
    printf("Test1 add door2 after root node id %d status %d\n", door2->id, door2->status);
    add_door(root, door2);
    output(root);
    struct node* found_door;
    if (root->door->id == 1 && root->pNext->door->id == 3)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");

    printf("Test2 add door3 after door with id=1(find_door(1,root)); new door id %d status %d\n", door3->id,
           door3->status);
    found_door = find_door(1, root);
    add_door(found_door, door3);
    output(root);
    if (root->door->id == 1 && root->pNext->door->id == 6 && root->pNext->pNext->door->id == 3)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");

    printf("Test3 add door4 after door with id=6; new door id %d status %d\n", door4->id, door4->status);
    found_door = find_door(6, root);
    add_door(found_door, door4);
    output(root);
    if (root->door->id == 1 && root->pNext->door->id == 6 && root->pNext->pNext->door->id == 10 &&
        root->pNext->pNext->pNext->door->id == 3)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");

    printf("Test4 add door1 after door with id=3; new door id %d status %d\n", door1->id, door1->status);
    found_door = find_door(3, root);
    add_door(found_door, door1);
    output(root);
    if (root->door->id == 1 && root->pNext->door->id == 6 && root->pNext->pNext->door->id == 10 &&
        root->pNext->pNext->pNext->door->id == 3 && root->pNext->pNext->pNext->pNext->door->id == 1)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");
}

void remove_door_test(struct node* root) {
    printf("\nTests remove door\n");
    printf("Test1 remove door with id 10\n");
    struct node* found_door = find_door(10, root);
    root = remove_door(found_door, root);
    output(root);
    if (root->door->id == 1 && root->pNext->door->id == 6 && root->pNext->pNext->door->id == 3 &&
        root->pNext->pNext->pNext->door->id == 1)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");

    printf("Test2 remove door with id 1\n");
    found_door = find_door(1, root);
    root = remove_door(found_door, root);
    output(root);
    if (root->door->id == 6 && root->pNext->door->id == 3 && root->pNext->pNext->door->id == 1)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");

    printf("Test3 remove door in center with id 3\n");
    found_door = find_door(3, root);
    root = remove_door(found_door, root);
    output(root);
    if (root->door->id == 6 && root->pNext->door->id == 1)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");

    printf("Test4 remove door with id 1\n");
    found_door = find_door(1, root);
    root = remove_door(found_door, root);
    output(root);
    if (root->door->id == 6)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");

    printf("Test5 remove last door with id 6\n");
    found_door = find_door(6, root);
    root = remove_door(found_door, root);
    output(root);
    if (root == NULL)
        printf("SUCCESS");
    else
        printf("FAIL");
    destroy(root);
}
