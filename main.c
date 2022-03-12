/**
 * @file main.c
 * @author Hadji Nadir - HADN08069703
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>
#include "file_handler.h"
#include "solver.h"

int main(int argc, char const *argv[])
{
    const char *file_name = argv[1];
    //File init
    FILE *file;
    file = open_file(file_name);

    //Matrice init
    char** matrice = get_matrice(file);
    print_matrice(matrice);

    //Word array init
    int n = get_number_words(file);
    printf("Nombre de mots = %d\n",n);
    char** words = get_words(file,n);
    //sort_words_by_length(words,n);
    print_words(words,n);
    
    solve(matrice,words,n);
    //Close file
    delete_dynamic_string_array(words,n);
    close_file(file);

    return 0;
}

