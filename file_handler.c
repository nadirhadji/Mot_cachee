/**
 * @file file_handler.c
 * @author Hadji Nadir - HADN08069703
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 */

#include "file_handler.h"

//************Macro fonctions***************

#define log_error_file_open() \
    fprintf(stderr,"Erreur : Echec de l'ouverture du fichier.\n"); \

#define log_error_file_close() \
    fprintf(stderr,"Erreur : Echec de la fermeture du fichier. \n"); \

//***********Private functions***************

/**
 * @brief Create a dynamic char matrice of size nb on Heap.
 * 
 * Note that the number of rows in the matrice is nb
 * And the number of cells at each row is GRID_SIZE.
 * 
 * In the context of the the hidden word game each word
 * to find in the grid had a maximum size of GRID_SIZE.
 * 
 * @param nb number of rows in the matrice
 * @return char** a pointer the string array
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
 * @brief Free the allocated memory of the matrice given in parameter
 * 
 * @param array Pointer to the memory adress of the matrice to free 
 * @param nb_rows Number of rows in the matrice to be freed
 */
void delete_dynamic_string_array(char ** array, int nb_rows) {
   for ( int i = 0 ; i < nb_rows ; ++i)
       free(array[i]);
   free(array);
}

/**
 * @brief Compare length of two string
 *
 * @param str1 pointer to string 1
 * @param str2 pointer to string 2
 * @return int 1 if str1 > str2 ; 0 if str1== str2 ; -1 if str1 < str2
 */
int compare_words_length(const void *str1, const void *str2) {
   char *const *pp1 = str1;
   char *const *pp2 = str2;
   int size_1 = strlen(*pp1);
   int size_2 = strlen(*pp2);
   if (size_2 > size_1)
       return 1;
   else if (size_2 == size_1)
       return 0;
   else
       return -1;
}

/**
 * @brief sort a list of string from smallest to largest.
 *
 * @param words pointer to string array
 * @param count number of string in string array
 */
void sort_words_by_length(char **words, int count) {
   qsort(words, count, sizeof(*words), compare_words_length);
}

/**
 * @brief Open the file in read mode and return it if he exist. Null otherwise.
 * 
 * @param file_name Name or path to the file to open.
 * @return FILE* poiter to the file or null if an error occued. 
 */
FILE* open_file(const char *file_name) {
   FILE *file = fopen(file_name,"r");
   if ( file == NULL) {
       log_error_file_open();
       exit(1);
   }
   return file;
}

/**
 * @brief Close the file given in parameter
 * 
 * @param file *FILE type object
 * @return int 0 if closed, -1 if not
 */
int close_file(FILE *file) {
    int val = fclose(file);
    if ( val != 0 )
        log_error_file_close();
    return val; 
}

/**
 * @brief get the number of words in file. 
 * 
 * The pointer position after read and count is replaced at 
 * initial position (first word, first char).
 * 
 * @param file FILE* where words are listed (1 by line)
 */
int get_number_words(FILE *file) {
    int number_words = 0;
    fgetc(file);
    long start_position = ftell(file);
    char buff[GRID_SIZE];
    while(fgets(buff,sizeof(buff),file) != NULL)
       number_words++;
    fseek(file,start_position,SEEK_SET);
    //printf("Words count is : %d\n",number_words);
    return number_words;
}

/**
 * @brief Get a list of type char[][] containing all the words
 * in the file.
 * 
 * @param file FILE* where words are listed (1 by line)
 * @return nb_words number of words in the file 
 */
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

/**
 * @brief Get the grid in the file field with char type 
 * at each cell
 * 
 * @param file FILE* where the grid of chars is. 
 * @return array of type char** allocated on heap.
 */
char** get_grid(FILE *file) {
    char **grid = create_dynamic_string_array(GRID_SIZE);
    for ( int i = 0 ; i < GRID_SIZE ; ++i) {
        for ( int j = 0 ; j < GRID_SIZE ; ++j ) 
            grid[i][j] = fgetc(file);
        fgetc(file);
    }
    //print_grid(grid);
    return grid;
}

//***********Public functions***************

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

void print_words(char ** words_list, int nb_words) {
    for ( int i = 0 ; i < nb_words ; ++i) {
            printf("%s",words_list[i]);
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

