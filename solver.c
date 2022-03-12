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


//Declaration Macro et macro fonctions auxiliaires


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
    return strcmp(*pp1,*pp2);
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

//Declaration et implementation des fonctions publique sans leurs doctring

int word_size(char *word) {

}

bool right_check(int row, int column, char *position, char *word, int word_size) {

}

bool left_check(int row, int column, char *position, char *word, int word_size) {

}

bool above_check(int row, int column, char *position, char *word, int word_size) {

}

bool under_check(int row, int column, char *position, char *word, int word_size) {

}

Position check_word(int row, int column, char *position, char *word) {

}

void add_found_position(Position position, Position solutions[]) {

}

void find_word(char** grid, Position solutions[] ,char* word) {

}

Position** find_words_positions(char ** words, char** grid) {

}

void clean_grid(char **grid, Position positions[]) {

}

char* solve(char **grid, char **words) {

}

int main(int argc, char const *argv[])
{
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
    return 0;
}
