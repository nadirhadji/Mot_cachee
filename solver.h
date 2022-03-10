/**
 * @file solver.h
 * @author Hadji Nadir - HADN08069703
 * @brief 
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 */

//Inculsion " " ou < >

//Declaration Macro et macro fonctions

//Declaration des types
enum Orientation {RIGHT , LEFT, UP, DOWN};

struct Position {
    enum Orientation o;
    int size;
    char *position;
};

//Declaration des fonctions publique avec leurs doctring

/**
 * @brief Count the number of char in a string
 * 
 * @param word Pointor to a char
 * @return int number of char before '\0'.
 */
int word_size(char *word);

/**
 * @brief Verify if an exact match of chars exists between the 
 * char sequence of word(before '\0') and the chars at the right
 * of the pointer position(included). 
 * 
 * @param row row number of the char to check
 * @param column column number if the char to check
 * @param position Pointer to a char in the grid
 * @param word Pointer to first char of a word
 * @param word_size Size of the word.
 * @return true if word exist right to position(included).
 * @return false if not.
 */
bool right_check(int row, int column, char *position, char *word, int word_size);

/**
 * @brief Verify if an exact match of chars exists between the 
 * char sequence of word(before '\0') and the chars at the left
 * of the pointer position(included). 
 * 
 * @param row row number of the char to check
 * @param column column number if the char to check
 * @param position Pointer to a char in the grid
 * @param word Pointer to first char of a word
 * @param word_size Size of the word.
 * @return true if word exist left to position(included).
 * @return false if not.
 */
bool left_check(int row, int column, char *position, char *word, int word_size);

/**
 * @brief Verify if an exact match of chars exists between the 
 * char sequence of word(before '\0') and the chars above the 
 * pointer position(included) in athe grid(12*12). 
 * 
 * @param row row number of the char to check
 * @param column column number if the char to check
 * @param position Pointer to a char in the grid
 * @param word Pointer to first char of a word
 * @param word_size Size of the word.
 * @return true if word exist above position(included).
 * @return false if not.
 */
bool above_check(int row, int column, char *position, char *word, int word_size);

/**
 * @brief Verify if an exact match of chars exists between the 
 * char sequence of word(before '\0') and the chars under the 
 * pointer position(included) in athe grid(12*12). 
 * 
 * @param row row number of the char to check
 * @param column column number if the char to check
 * @param position Pointer to a char in the grid
 * @param word Pointer to first char of a word
 * @param word_size Size of the word.
 * @return true if word exist under position(included).
 * @return false if not.
 */
bool under_check(int row, int column, char *position, char *word, int word_size);

/**
 * @brief Verify if the word matches up, down, right or left of
 * the poited char.
 * 
 * @param row row number of the char to check
 * @param column column number if the char to check
 * @param position Pointer to a char in the grid
 * @param word Pointer to first char of a word
 * @return Position structure {row,column,orientation} if found
 * NULL if not.
 */
Position check_word(int row, int column, char *position, char *word);

/**
 * @brief Add a Position object to the list in arguments
 * 
 * @param position the Position object to add
 * @param solutions array of the the found positions
 */
void add_found_position(Position position, Position solutions[]);

/**
 * @brief Find the position of the word in the grid and add it the 
 * solutions (If not null).
 * 
 *  Loop on the grid + call check word + 
 *  (eventually) call add_found_position
 * 
 * @param grid matrice of caracteres where to search words
 * @param solutions array of the found positions. 
 * @param word Pointer to first char of a word
 */
void find_word(char** grid, Position solutions[] ,char* word);

/**
 * @brief Find the position of every word in the grid.
 * Loop on words + Call check_word
 * 
 * @param words array of words in grid
 * @param grid matrice of caracteres where to search words
 * @return Position* array of the positions found.
 */
Position* find_words(char ** words, char** grid);

/**
 * @brief Replace all words in found on the grid previously
 * by 0. At the end only the chars of the mystery word will
 * remain in the grid. 
 * 
 * @param grid the grid to clean
 * @param positions positions of the found words previously 
 */
void clean_grid(char **grid, Position positions[]);

/**
 * @brief Orchester the internal behaviour of the Solver Module.
 * 
 * @param grid Matrice of char 
 * @param words array of words
 * @return char* Mystery word in the grid.
 */
char* solve(char **grid, char **words);

