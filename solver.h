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
 * @return true if word exist right to position(included).
 * @return false if not.
 */
bool right_check(int row, int column, char *position, char *word);

/**
 * @brief Verify if an exact match of chars exists between the 
 * char sequence of word(before '\0') and the chars at the left
 * of the pointer position(included). 
 * 
 * @param row row number of the char to check
 * @param column column number if the char to check
 * @param position Pointer to a char in the grid
 * @param word Pointer to first char of a word
 * @return true if word exist left to position(included).
 * @return false if not.
 */
bool left_check(int row, int column, char *position, char *word);

/**
 * @brief Verify if an exact match of chars exists between the 
 * char sequence of word(before '\0') and the chars above the 
 * pointer position(included) in athe grid(12*12). 
 * 
 * @param row row number of the char to check
 * @param column column number if the char to check
 * @param position Pointer to a char in the grid
 * @param word Pointer to first char of a word
 * @return true if word exist above position(included).
 * @return false if not.
 */
bool above_check(int row, int column, char *position, char *word);

/**
 * @brief Verify if an exact match of chars exists between the 
 * char sequence of word(before '\0') and the chars under the 
 * pointer position(included) in athe grid(12*12). 
 * 
 * @param row row number of the char to check
 * @param column column number if the char to check
 * @param position Pointer to a char in the grid
 * @param word Pointer to first char of a word
 * @return true if word exist under position(included).
 * @return false if not.
 */
bool under_check(int row, int column, char *position, char *word);