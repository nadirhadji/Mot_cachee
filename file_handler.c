/**
 * @file file_handler.c
 * @author Hadji Nadir - HADN08069703
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 */

#ifndef FILE_HANDLER_H
#include "file_handler.h"
#endif

//Inculsion " " ou < >
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

//Declaration Macro et macro fonctions auxiliaires

#define log_error_file_open() \
    fprintf(stderr,"Erreur : Echec de l'ouverture du fichier. \n"); \

#define log_error_file_close() \
    fprintf(stderr,"Erreur : Echec de la fermeture du fichier. \n"); \


//Declaration des types auxiliaires

//Declaration et implementation des fonctions auxiliaures avec leurs doctring

void print_matrice(Matrice m) {
    for ( int i = 0 ; i < MATRICE_SIZE ; ++i) {
        for ( int j = 0 ; j < MATRICE_SIZE ; j++) 
            printf(" %c ",m.matrice[i][j]);
        printf("\n");
    }
}

//Declaration et implementation des fonctions publique sans leurs doctring

FILE* open_file(const char *file_name) {
    FILE *file = fopen(file_name,"r");
    if ( file == NULL) {
        log_error_file_open();
        return EXIT_FAILURE;
    }
    return file;
}

int close_file(FILE *file) {
    int val = fclose(file);
    if ( val != 0 )
        log_error_file_close();
    return val; 
}

Matrice get_matrice(FILE *file) {
    Matrice m;
    char newline_symbol_buffer;
    for ( int i = 0 ; i < MATRICE_SIZE ; ++i) {
        for ( int j = 0 ; j < MATRICE_SIZE ; ++j ) 
            m.matrice[i][j] = fgetc(file);
        newline_symbol_buffer = fgetc(file);
    }
    return m;
}

int get_number_words(FILE *file) {
    
    return 0;
}

Words get_words(FILE *file) {
    //TODO
    //return words;
}

int main(int argc, char const *argv[])
{
    const char *file_name = argv[1];
    FILE *file = open_file(file_name);
    Matrice m = get_matrice(file);
    print_matrice(m);
    return 0;
}


