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
#include <stdio.h>
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

/**
 * @brief Get the number words object
 * 
 * @param file 
 * @return int 
 */
int get_number_words(FILE *file) {
    int number_words = 0;
    char buffer_empty_line = fgetc(file);
    long start_position = ftell(file);
    char buff[MATRICE_SIZE];
    while(fgets(buff,sizeof(buff),file) != NULL)
       number_words++;
    fseek(file,start_position,SEEK_SET);
    return number_words;
}

/**
 * @brief Create a dynamic string array object
 * 
 * @param nb 
 * @return char** 
 */
char** create_dynamic_string_array(int nb) {
    char **array;
    array = malloc(sizeof(char*) * nb );
    for ( int i = 0 ; i < nb ; i++) {
        array[i] = malloc( (MATRICE_SIZE+1) * sizeof(char) );
    }
    return array;
}

/**
 * @brief 
 * 
 * @param array 
 * @param nb_words 
 */
void delete_dynamic_string_array(char ** array, int nb_words) {
    for ( int i = 0 ; i < nb_words ; ++i)
        free(array[i]);
    free(array);
}

//Declaration et implementation des fonctions publique sans leurs doctring

FILE* open_file(const char *file_name) {
    FILE *file = fopen(file_name,"r");
    if ( file == NULL) {
        log_error_file_open();
        exit(1);
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

char** get_words(FILE *file, int nb_words) {
    char **array = create_dynamic_string_array(nb_words);
    for ( int i = 0 ; i < nb_words ; ++i) { 
        char word_buffer[MATRICE_SIZE];
        fgets(word_buffer, MATRICE_SIZE, file);
        int size = strlen(word_buffer) - 1;
        strncpy(array[i],word_buffer,size);
    }
    return array;
}

void print_matrice(Matrice m) {
    for ( int i = 0 ; i < MATRICE_SIZE ; ++i) {
        for ( int j = 0 ; j < MATRICE_SIZE ; j++) 
            printf(" %c ",m.matrice[i][j]);
        printf("\n");
    }
}

void print_words(char ** w, int nb_words) {
    for ( int i = 0 ; i < nb_words ; ++i) {
            printf("%s",w[i]);
        printf("\n");
    }
}