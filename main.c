/**
 * @file main.c
 * @author Hadji Nadir - HADN08069703
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include "solver.h"

#define log_error_nb_args() \
    fprintf(stderr,"Erreur : Seulement 1 argument est permis. \n"); \
    return 1;

int main(int argc, char *argv[]) {
   if ( argc == 2) {
      char *file_name = argv[1];
      char *hidden_word = calloc(sizeof(char),GRID_SIZE);
      get_hidden_word(file_name,hidden_word);
      printf("%s\n",hidden_word);
      free(hidden_word);
      return 0;
   } else {
      log_error_nb_args();
   }
}
