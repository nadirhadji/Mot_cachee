/**
 * @file main.c
 * @author Hadji Nadir - HADN08069703
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include "solver.h"

int main(int argc, char const *argv[]) {
    const char *file_name = argv[1];
    char *hidden_word = calloc(sizeof(char),GRID_SIZE);
    get_hidden_word(file_name,hidden_word);
    printf("%s\n",hidden_word);
    free(hidden_word);
    return 0;
}

