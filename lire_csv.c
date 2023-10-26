char* find_vote_by_hash_in_csv(const char* hash, const char* filepath) {
    FILE* file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", filepath);
        return NULL;
    }

    char line[256]; // Ajustez la taille en fonction de votre fichier CSV

    // Lisez chaque ligne du fichier CSV
    while (fgets(line, sizeof(line), file)) {
        char* current_hash = getfield(line, 1); // Supposons que le hachage est dans la première colonne

        if (current_hash != NULL && strcmp(current_hash, hash) == 0) {
            // Hachage trouvé, retournez le vote (ou la colonne appropriée)
            char* vote = getfield(line, 2); // Supposons que le vote est dans la deuxième colonne

            if (vote != NULL) {
                fclose(file);
                return strdup(vote); // Assurez-vous de libérer la mémoire lorsque vous avez fini d'utiliser cette chaîne
            }
        }
    }

    fclose(file);

    // Si le hachage n'est pas trouvé, retournez NULL
    return NULL;
}
