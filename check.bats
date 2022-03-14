tests_folder=test_files
prog=motcache
no_args_output="Usage: ./motcache <nom_fichier>"
invalide_file_error="Erreur : Echec de l'ouverture du fichier."

# Normal usage

@test "test0 : Sans aucune entree, afficher Message erreur" {
    run ./$prog
    [ "$status" -eq 1 ]
    [ "${lines[0]}" = "$no_args_output" ]
}

@test "test1 : Fichier invalide ou erreur de lecture" {
    run ./$prog $tests_folder/echec_test
    [ "$status" -eq 1 ]
    [ "${lines[0]}" = "$invalide_file_error" ]
}

@test "test2 : MANDOLINE" {
    run ./$prog $tests_folder/text.txt
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "MANDOLINE" ]
}

@test "test3 : VENISE" {
    run ./$prog $tests_folder/venise.txt
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "VENISE" ]
}