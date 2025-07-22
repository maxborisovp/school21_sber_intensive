#ifndef MODULES_H
#define MODULES_H

typedef struct {
    int module_id;
    char module_name[30];
    int number_of_memory_level_in_module;
    int number_of_cells_on_the_level_in_module;
    int deletion_flag;
} Module;

#endif
