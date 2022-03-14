/**
 * @file solver.c
 * @author Hadji Nadir - HADN08069703
 * @brief
 * @version 0.1
 * @date 2022-03-09
 *
 * @copyright Copyright (c) 2022
 */

#include "solver.h"

#define GRID_SIZE 12

typedef struct {
    char *word;
    int length;
} Word;

//***************Private functions********************

/**
 * @brief For debug purpose, print to stdout value of Orientation
 * 
 * @param o Orientation value to be printed
 */
void print_orientation(Orientation o) {
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
 * @brief For debug purpose, print to stdout ouf the state of a Solution.
 * 
 * @param solution Solution object to be printed.
 */
void print_solution(Solution *solution) {
   for (int i = 0; i < solution->count; i++) {
      Position *position = solution -> list[i];
      printf("row = %d ; column = %d ; ori = ",
      position -> point.row,
      position -> point.column);
      Orientation o = position -> orientation;
      print_orientation(o);
      printf(" ; size = %d \n", position -> size);
   }
}

/**
 * @brief Allocate memory on heap to store the found Position
 * 
 * @param count_words Number of cell to allocate.
 * @return Position** Pointer to the array of Position
 */
Position** new_array_of_positions(int count_words) {
   Position **positions;
   positions = calloc(sizeof(Position *), count_words);
   for (int i = 0; i < count_words; ++i)
       positions[i] = malloc(sizeof(Position));
   return positions;
}

/**
 * @brief Free the allocated memory of the position array given in parameter
 * 
 * @param array Pointer to the memory adress of the positions to free 
 * @param nb_rows Number of cells in the array to free
 */
void delete_array_of_positions(Position **positions, int count_words) {
   for (int i = 0; i < count_words; ++i)
      free(positions[i]);
   free(positions);
}

/**
 * @brief Verify if word exist at right of grid[row][col]
 * 
 * @param row index of the row to check (from 0)
 * @param col index of the column to check (from 0)
 * @param grid Matrice of type **char containing the game grid
 * @param word char* and int wich are the adress and the size of te word.
 * @return true if found
 * @return false if not found
 */
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

/**
 * @brief Verify if word exist at left of grid[row][col]
 * 
 * @param row index of the row to check (from 0)
 * @param col index of the column to check (from 0)
 * @param grid Matrice of type **char containing the game grid
 * @param word char* and int wich are the adress and the size of te word.
 * @return true if found
 * @return false if not found
 */
bool left_check(int row, int col, char **grid, Word word) {
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

/**
 * @brief Verify if word exist above grid[row][col]
 * 
 * @param row index of the row to check (from 0)
 * @param col index of the column to check (from 0)
 * @param grid Matrice of type **char containing the game grid
 * @param word char* and int wich are the adress and the size of te word.
 * @return true if found
 * @return false if not found
 */
bool above_check(int row, int col, char **grid, Word word) {
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

/**
 * @brief Verify if word exist under grid[row][col]
 * 
 * @param row index of the row to check (from 0)
 * @param col index of the column to check (from 0)
 * @param grid Matrice of type **char containing the game grid
 * @param word char* and int wich are the adress and the size of te word.
 * @return true if found
 * @return false if not found
 */
bool under_check(int row, int col, char **grid, Word word) {
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

/**
 * @brief Verify if word is present at all 4 directions.
 * RIGHT, LEFT, ABOVE, UNDER
 * 
 * @param row index of the row to check (from 0)
 * @param col index of the column to check (from 0)
 * @param grid Matrice of type **char containing the game grid
 * @param word char* and int wich are the adress and the size of te word.
 * @return Orientation orientation of word at cell(row,col) on grid
 * if found or NO if not 
 */
Orientation check_orientation(int row, int col, char **grid, Word word) {
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

/**
 * @brief Append a Position to Solution
 * 
 * @param solution Current Solution object
 * @param o Orientation of the found word (RIGHT, LEFT, ...)
 * @param size Length of the found word
 * @param row index of the row where word found (from 0)
 * @param col index of the column where word found (from 0)
 */
void add_found_solution(Solution *solution, Orientation o, int size, int row, int col) {
   int index = solution -> count;
   Position *position_buffer = solution -> list[index];
   position_buffer -> orientation = o;
   position_buffer -> size = size;
   position_buffer -> point.column = col;
   position_buffer -> point.row = row;
   ++solution -> count;
}

/**
 * @brief Verify if a any word is found for the list at a particular cell.
 * 
 * @param row index of the row ( from 0 )
 * @param col index of the colum ( from 0 )
 * @param game The game data
 * @param solution Current solution before the check
 * @return Solution* Solution with more position if found.
 */
Solution* check_words_at_cell(int row, int col, Game game, Solution *solution) {
   for (int i = 0; i < game.words_count; i++) {
      //printf("current word checked : %s \n",game.words->list[i]);
      int length = strlen(game.words[i]);
      Word word = { game.words[i], length };
      Orientation orientation = check_orientation(row, col, game.grid, word);
      if (orientation != NO) 
          add_found_solution(solution, orientation, word.length, row, col);
   }
   return solution;
}

/**
 * @brief Iterate on all the grids cell and find the positions 
 * of all words if present.
 * 
 * @param game Game data
 * @param solution Solution to be filled after function call.
 */
void find_words_positions(Game game, Solution *solution) {
   for (int row = 0; row < GRID_SIZE; row++) {
       for (int col = 0; col < GRID_SIZE ; col++) {
           //printf("\n** row : %d , col : %d , current : %c **\n", row, col, game.grid[row][col]);
           //printf("*************************************\n\n");
           check_words_at_cell(row, col, game, solution);
       }
   }
}

/**
 * @brief Replace a char at row and col by '0'
 * 
 * @param grid Matrice of type **char
 * @param row index of the row (starting from 0).
 * @param col index of the col (starting from 0).
 */
void empty_cell(char **grid, int row, int col) {
   if (grid[row][col] != '0')
      grid[row][col] = '0';
}

/**
 * @brief Delete word at right of position
 * 
 * @param grid Matrice of type **char
 * @param position informations about a word's position 
 */
void delete_right(char **grid , Position *position) {
   int row = position->point.row;
   int col = position->point.column;
   int end = (col + position->size);
   for (; col < end ;++col) 
      empty_cell(grid,row,col);
}

/**
 * @brief Delete word at left of position
 * 
 * @param grid Matrice of type **char
 * @param position informations about a word's position 
 */
void delete_left(char **grid , Position *position) {
   int row = position->point.row;
   int col = position->point.column;
   int start = (col - position->size);
   for (; col > start ;--col) 
      empty_cell(grid,row,col);   
}

/**
 * @brief Delete word above position
 * 
 * @param grid Matrice of type **char
 * @param position informations about a word's position 
 */
void delete_above(char **grid, Position *position) {
   int row = position->point.row;
   int col = position->point.column;
   int start = (row - position->size);
   for (; row > start; --row)
      empty_cell(grid,row,col);
}

/**
 * @brief Delete word under a position
 * 
 * @param grid Matrice of type **char
 * @param position informations about a word's position
 */
void delete_under(char **grid, Position *position) {
   int row = position->point.row;
   int col = position->point.column;
   int end = (row + position->size);
   for (; row < end ; ++row )
       empty_cell(grid,row,col);
}

/**
 * @brief Replace all the char of a word by '0' in the grid.
 * Delete according to the Position object that give precise
 * informations about a word's position.
 * 
 * @param grid Matrice of type **char
 * @param position informations about a word's position
 */
void delete_word(char **grid , Position *position) {
   switch (position->orientation) {
       case RIGHT: delete_right(grid,position); break;
       case LEFT: delete_left(grid,position); break;
       case UNDER: delete_under(grid,position); break;
       case ABOVE: delete_above(grid,position); break;
       default: break;
   }
}

/**
 * @brief Will replace all the found words of solution by '0'
 * on the grid.
 * 
 * @param grid Matrice of type **char
 * @param solution Pointer to all Position in Solution   
 */
void clean_grid(char **grid, Solution *solution) {
   for ( int i = 0 ; i < solution->count ; i++ ) {
       Position *position = solution->list[i];
       delete_word(grid,position);
   }
}

/**
 * @brief Append a char to a char*
 * 
 * @param str string to be modified
 * @param carac char to append to str
 */
void append_char_to_string(char *str, char carac) {
   int length = strlen(str);
   str[length] = carac;
}

/**
 * @brief Build the hidden word by iterating on a solved grid.
 * The iteration is done from left to right and from top to
 * bottom. Each time a char is not equal to '0', that char is
 * append to the hidden word.
 * 
 * @param grid Matrice of type **char already solved
 * @param hidden_word Builed hidden word
 */
void build_hidden_word(char **grid, char *hidden_word) {
   //printf("Start Building the hidden word\n");
   for (int row = 0; row < GRID_SIZE ; ++row) {
       for (int col = 0; col < GRID_SIZE ; ++col) {
          if( grid[row][col] != '0' ) {
              append_char_to_string(hidden_word,grid[row][col]);
          }
       }
   }
    //printf("End of Building the hidden word\n");
}

/**
 * @brief Instanciate empty array of object Position and fill it 
 * with the positions of all found words on game grid.
 * 
 * @param game The game object
 * @return Solution containing the position of all found words.
 */
Solution solve(Game game) {
   Position **empty_positions_list = new_array_of_positions(game.words_count);
   Solution solution = { empty_positions_list,0 };
   find_words_positions(game, &solution);
   //print_solution(&solution);
   return solution;
}

//**************Public functions******************
void get_hidden_word(char *file_name,char *hidden_word ) {
   Game game = new_game(file_name);
   Solution solution = solve(game);
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