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
    char buff[GRID_SIZE];
    while(fgets(buff,sizeof(buff),file) != NULL)
       number_words++;
    fseek(file,start_position,SEEK_SET);
    //printf("Words count is : %d\n",number_words);
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
    array = calloc(sizeof(char*),nb);
    for ( int i = 0 ; i < nb ; i++) {
        array[i] = calloc(sizeof(char),GRID_SIZE);
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

char** get_grid(FILE *file) {
    char **grid = create_dynamic_string_array(GRID_SIZE);
    char newline_symbol_buffer;
    for ( int i = 0 ; i < GRID_SIZE ; ++i) {
        for ( int j = 0 ; j < GRID_SIZE ; ++j ) 
            grid[i][j] = fgetc(file);
        newline_symbol_buffer = fgetc(file);
    }
    //print_grid(grid);
    return grid;
}

char** get_words(FILE *file, int nb_words) {
    char **array = create_dynamic_string_array(nb_words);
    for ( int i = 0 ; i < nb_words ; ++i) { 
        char word_buffer[GRID_SIZE];
        fgets(word_buffer, GRID_SIZE, file);
        int size = strlen(word_buffer) - 1;
        strncpy(array[i],word_buffer,size);
    }
    //print_words(array,nb_words);
    return array;
}

void print_grid(char **grid) {

    printf("\n\t*** grid ***\n\n   ");

    for ( int j = 0 ; j < GRID_SIZE ; ++j) 
        printf("%d  ",j);
    printf("\n");

    for ( int i = 0 ; i < GRID_SIZE ; ++i) {
        printf("%d  ",i);
        for ( int j = 0 ; j < GRID_SIZE ; j++) 
            printf("%c  ",grid[i][j]);
        printf("\n");
    }
}

void print_words(char ** w, int nb_words) {
    for ( int i = 0 ; i < nb_words ; ++i) {
            printf("%s",w[i]);
        printf("\n");
    }
}

Game new_game(char* file_name) {
    FILE *file;
    file = open_file(file_name);
    char** grid = get_grid(file);
    int words_count = get_number_words(file);
    char** words = get_words(file,words_count);
    close_file(file);
    sort_words_by_length(words,words_count);
    Game game = {grid,words,words_count};
    return game;
}

void delete_game(Game game) {
    //printf("Restituation of allocated memory\n");
    delete_dynamic_string_array(game.words,game.words_count);
    delete_dynamic_string_array(game.grid,GRID_SIZE);
}

