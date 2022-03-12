/**
 * @file solver.c
 * @author Hadji Nadir - HADN08069703
 * @brief 
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 */

//Inculsion " " ou < >
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "solver.h"

//Declaration Macro et macro fonctions auxiliaires

#define MATRICE_SIZE 12

//Declaration des types auxiliaires

//Declaration et implementation des fonctions auxiliaures avec leurs doctring

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
    if ( size_2 > size_1 ) return 1;
    else if ( size_2 == size_1) return 0;
    else return -1;
}

/**
 * @brief sort a list of string from smallest to largest.
 * 
 * @param words pointer to string array
 * @param count number of string in string array
 */
void sort_words_by_length(char **words, int count) {
    qsort(words,count,sizeof(*words), compare_words_length);
}

Position** create_array_of_positions(int count_words) {
    Position **positions;
    positions = calloc(sizeof(Position*),count_words);
    for ( int i = 0 ; i < count_words ; ++i)
        positions[i] = malloc(sizeof(Position));
    return positions;
}

void delete_array_of_positions(Position **positions, int count_words) {
    for ( int i = 0 ; i < count_words ; ++i)
        free(positions[i]);
    free(positions);
}

//Declaration et implementation des fonctions publique sans leurs doctring
bool right_check(int row, int col , char **grid, Word word) {
     printf("right verif\n");
    if (col > ( MATRICE_SIZE - word.length ) )
        return false;
    else {
        for (int i = 0 ; i < word.length ; ++i , ++col ) {
            printf("word : %c , grid : %c \n",word.word[i], grid[row][col]);
             if (word.word[i] != grid[row][col])
                return false;
        }
           
    }
    return true;
}

bool left_check(int row, int col , char **grid, Word word) {
     printf("left verif\n");
    if ( col < (MATRICE_SIZE - 1 - word.length) )
        return false;
    else {
        int first_char = col - word.length + 1;
        for ( int i = 0 ; i < word.length ; ++i , ++first_char)
            if(word.word[i] != grid[row][first_char])
                return false;
    }
    return true;
}

bool above_check(int row, int col , char **grid, Word word) {
     printf("above verif\n");
    if ( row < (MATRICE_SIZE - 1 - word.length ) ) 
        return false;
    else {
        int first_row = row - word.length + 1;;
        for ( int i = 0 ; i < word.length ; ++i )
            if (word.word[i] != grid[first_row][col])
                return false;
    }
    return true;
}

bool under_check(int row, int col ,char **grid, Word word) {
    printf("under verif\n");
    if ( row > (MATRICE_SIZE - word.length) )
        return false;
    else {
        int first_row = row;
        for ( int i = 0 ; i < word.length ; ++i, ++first_row)  {
            if(word.word[i] != grid[first_row][col])
                return false;
        }
    }
    return true;
}

void add_found_solution(Solution solution, enum Orientation o, int size, int row, int col) {
    int index = solution.count;
    solution.list[index]->orientation = o;
    solution.list[index]->size = size;
    solution.list[index]->point.column = col;
    solution.list[index]->point.row = row;

    solution.count += 1;
}

enum Orientation check_orientation(int row, int col, char **grid, Word word) {
    
    if ( under_check(row,col,grid,word) ) {
        printf("under test\n");
        return UNDER;
    }
        
    else if ( above_check(row,col,grid,word)) {
        printf("above test");
        return ABOVE;
    }
        
    else if ( right_check(row,col,grid,word) ) {
        printf("right check");
        return RIGHT;
    }
        
    else if ( left_check(row,col,grid,word) ) {
        printf("left test");
        return LEFT;  
    }
          
    return NO;
}

Solution check_words_at_cell(int row, int col, Game game, Solution solution) {
    for (int i = 0 ; i < game.words.count ; ++i) {
        int length = strlen(game.words.list[i]);
        Word word = {game.words.list[i],length};
        enum Orientation orientation = check_orientation(col,row,game.grid,word);
        if ( orientation != NO) {
            add_found_solution(solution,orientation,word.length,row,col);
        }
    }
    return solution;
}

void find_words_positions(Game game,Solution solution) {
    sort_words_by_length(game.words.list,game.words.count);
    for (int col = 0 ; col < MATRICE_SIZE ; col++ ) {
        for (int row = 0; row < MATRICE_SIZE ; row++ ) {
            printf("row : %d , col : %d\n",row,col);
            check_words_at_cell(col,row,game,solution);
            printf("**********************\n");
        }
    }
}

void clean_grid(char **grid, Position** positions) {

}

void solve(char **grid, char **words, int nb_words) {
    Words w = {words,nb_words};
    Game game = {grid,w};
    Position **empty_positions_list = create_array_of_positions(game.words.count);
    Solution solution = {empty_positions_list, 0};
    find_words_positions(game,solution);

    for ( int i = 0 ; i < solution.count ; i++) {
        printf("row = %d ; column = %d ; ori = %d \n", 
        solution.list[i]->point.row, 
        solution.list[i]->point.column,
        solution.list[i]->orientation);
    }
}

    //Param1 : Liste des mots
    //Param2 : La matrice
    //Param3 : List des positions vide
    //Param4 : mot caché vide.
    //
    //trier les mots du plus long au plus court
    //
    //boucle pour chaque case case de matrice
    //      verifier liste des mots
    //      si mot trouvé
    //          supprimer mot de la liste
    //          creer objet position
    //          ajouter objet position dans liste des position
    //      sinon
    //           continuer
    //fin boucle
    //
    //boucle pour chaque position de list position
    //      remplir de 0 sur matrice
    //fin boucle pour
    //
    //Pour chaque case de matrice ( gauche droite ( haut bas) )
    //      si 0 suivant
    //      sinon concatener lettre a mot caché
    //fin boucle
    //
    //Vider les espace memoire alouée
    //
    //Afficher mot cachée
    //
    //FIN
