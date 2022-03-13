/**
 * @file solver.c
 * @author Hadji Nadir - HADN08069703
 * @brief
 * @version 0.1
 * @date 2022-03-09
 *
 * @copyright Copyright (c) 2022
 */

// Inculsion " " ou < >
#ifndef SOLVER_H
#define SOLVER_H
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "solver.h"
#include "file_handler.h"

// Declaration Macro et macro fonctions auxiliaires

#define GRID_SIZE 12

// Declaration des types auxiliaires
typedef struct {
    char *word;
    int length;
} Word;

// Declaration et implementation des fonctions auxiliaures avec leurs doctring
void print_solution(Solution *solution)
{
    for (int i = 0; i < solution->count; i++)
    {
        Position *position = solution -> list[i];
        printf("row = %d ; column = %d ; ori = ",
               position -> point.row,
               position -> point.column);
        print_orientation(position -> orientation);
        printf(" ; size = %d \n", position -> size);
    }
}

void print_orientation(enum Orientation o) {
    if (o == RIGHT)
        printf("right");
    else if (o == LEFT)
        printf("left");
    else if (o == ABOVE)
        printf("above");
    else if (o == UNDER)
        printf("under");
    else
        printf("unknown");
}

/**
 * @brief Compare length of two string
 *
 * @param str1 pointer to string 1
 * @param str2 pointer to string 2
 * @return int 1 if str1 > str2 ; 0 if str1== str2 ; -1 if str1 < str2
 */
int compare_words_length(const void *str1,
                         const void *str2) {
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

Position **new_array_of_positions(int count_words) {
    Position **positions;
    positions = calloc(sizeof(Position *), count_words);
    for (int i = 0; i < count_words; ++i)
        positions[i] = malloc(sizeof(Position));
    return positions;
}

void delete_array_of_positions(Position **positions, int count_words) {
    for (int i = 0; i < count_words; ++i)
        free(positions[i]);
    free(positions);
}

bool right_check(int row, int col, char **grid, Word word) {
    // printf("right check\n");
    if (col > (GRID_SIZE - word.length))
        return false;
    else {
        for (int i = 0; i < word.length; ++i, ++col)
        {
            // printf("current word letter : %c\n",word.word[i]);
            // printf("current grid letter : %c\n",grid[row][col]);
            if (word.word[i] != grid[row][col])
                return false;
        }
    }
    return true;
}

bool left_check(int row, int col, char **grid, Word word)
{
    // printf("left check\n");
    if ( (word.length - col) > 1 )
        return false;
    else {
        for (int i = 0; i < word.length; ++i, --col)
            if (word.word[i] != grid[row][col])
                return false;
    }
    return true;
}

bool above_check(int row, int col, char **grid, Word word)
{
    // printf("above check\n");
    if (row < (word.length - 1))
        return false;
    else {
        for (int i = 0; i < word.length; ++i, row--) {
            // printf("current word letter : %c\n",word.word[i]);
            // printf("current grid letter : %c\n",grid[first_row][col]);
            if (word.word[i] != grid[row][col])
                return false;
        }
    }
    return true;
}

bool under_check(int row, int col, char **grid, Word word)
{
    // printf("under check\n");
    if (row > (GRID_SIZE - word.length))
        return false;
    else {
        for (int i = 0; i < word.length; ++i, ++row) {
            if (word.word[i] != grid[row][col])
                return false;
        }
    }
    return true;
}

enum Orientation check_orientation(int row, int col, char **grid, Word word) {
    
    //printf("current word checked : %s \n", word.word);
    if (under_check(row, col, grid, word)) {
        //printf("OK : match found at under test\n");
        return UNDER;
    }
    else if (above_check(row, col, grid, word)) {
        //printf("OK : match found at  above test\n");
        return ABOVE;
    }
    else if (right_check(row, col, grid, word)) {
        //printf("OK : match found at right check\n");
        return RIGHT;
    }
    else if (left_check(row, col, grid, word))  {
        //printf("OK : match found at left test\n");
        return LEFT;
    }
    else{
        // printf("KO : no match found\n");
        return NO;
    }
}

void add_found_solution(Solution *solution, enum Orientation o, int size, int row, int col) {
    int index = solution -> count;
    Position *position_buffer = solution -> list[index];
    position_buffer -> orientation = o;
    position_buffer -> size = size;
    position_buffer -> point.column = col;
    position_buffer -> point.row = row;
    ++solution -> count;
}

Solution *check_words_at_cell(int row, int col, Game game, Solution *solution) {
    for (int i = 0; i < game.words_count; i++) {
        //printf("current word checked : %s \n",game.words->list[i]);
        int length = strlen(game.words[i]);
        Word word = { game.words[i], length };
        enum Orientation orientation = check_orientation(row, col, game.grid, word);
        if (orientation != NO) 
            add_found_solution(solution, orientation, word.length, row, col);
    }
    return solution;
}

void find_words_positions(Game game, Solution *solution) {
    sort_words_by_length(game.words, game.words_count);
    for (int row = 0; row < GRID_SIZE
; row++) {
        for (int col = 0; col < GRID_SIZE
    ; col++) {
            //printf("\n** row : %d , col : %d , current : %c **\n", row, col, game.grid[row][col]);
            //printf("*************************************\n\n");
            check_words_at_cell(row, col, game, solution);
        }
    }
}

void empty_cell(char **grid, int row, int col) {
    if (grid[row][col] != '0')
            grid[row][col] = '0';
}

void delete_right(char **grid , Position *position) {
    int row = position->point.row;
    int col = position->point.column;
    int end = (col + position->size);
    for (; col < end ;++col) 
        empty_cell(grid,row,col);
}

void delete_left(char **grid , Position *position) {
    int row = position->point.row;
    int col = position->point.column;
    int start = (col - position->size);
    for (; col > start ;--col) 
        empty_cell(grid,row,col);   
}

void delete_above(char **grid, Position *position) {
    int row = position->point.row;
    int col = position->point.column;
    int start = (row - position->size);
    for (; row > start; --row)
        empty_cell(grid,row,col);
}

void delete_under(char **grid, Position *position) {
    int row = position->point.row;
    int col = position->point.column;
    int end = (row + position->size);
    for (; row < end ; ++row )
        empty_cell(grid,row,col);
}

void delete_word(char **grid , Position *position) {
    switch (position->orientation) {
        case RIGHT: delete_right(grid,position); break;
        case LEFT: delete_left(grid,position); break;
        case UNDER: delete_under(grid,position); break;
        case ABOVE: delete_above(grid,position); break;
        default: break;
    }
}

void clean_grid(char **grid, Solution *solution)
{
    print_grid(grid);
    for ( int i = 0 ; i < solution->count ; i++ ) {
        Position *position = solution->list[i];
        printf("row : %d col : %d size = %d\n",position->point.row,position->point.column,position->size);
        delete_word(grid,position);
    }
}

void append_char_to_string(char *str, char carac) {
    int length = strlen(str);
    str[length] = carac;
}

void build_hidden_word(char **grid, char *hidden_word) {
    //printf("Start Building the hidden word\n");
    char char_buffer;
    for (int row = 0; row < GRID_SIZE
; ++row) {
        for (int col = 0; col < GRID_SIZE
    ; ++col) {
           if( grid[row][col] != '0' ) {
               append_char_to_string(hidden_word,grid[row][col]);
           }
        }
    }
    //printf("End of Building the hidden word\n");
}

Solution solve(Game game)
{
    Position **empty_positions_list = new_array_of_positions(game.words_count);
    Solution solution = { empty_positions_list,0 };
    find_words_positions(game, &solution);
    //print_solution(&solution);
    return solution;
}

void get_hidden_word(char *file_name,char *hidden_word )
{
    Game game = new_game(file_name);
    Solution solution = solve(game);
    printf("Le nombre de mots : %d\n",game.words_count);
    print_words(game.words,game.words_count);
    clean_grid(game.grid, &solution);
    build_hidden_word(game.grid, hidden_word);
    delete_array_of_positions(solution.list, solution.count);
    delete_game(game);
}

// Param1 : Liste des mots
// Param2 : La grid
// Param3 : List des positions vide
// Param4 : mot caché vide.
//
// trier les mots du plus long au plus court
//
// boucle pour chaque case case de grid
//       verifier liste des mots
//       si mot trouvé
//           supprimer mot de la liste
//           creer objet position
//           ajouter objet position dans liste des position
//       sinon
//            continuer
// fin boucle
//
// boucle pour chaque position de list position
//       remplir de 0 sur grid
// fin boucle pour
//
// Pour chaque case de grid ( gauche droite ( haut bas) )
//       si 0 suivant
//       sinon concatener lettre a mot caché
// fin boucle
//
// Vider les espace memoire alouée
//
// Afficher mot cachée
//
// FIN