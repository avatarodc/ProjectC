#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "fonctions.h"

void lire_utilisateurs(const char* nom_fichier, Utilisateur utilisateurs[], int* nb_utilisateurs) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        return;
    }

    *nb_utilisateurs = 0;
    while (fscanf(fichier, "%49s %49s", utilisateurs[*nb_utilisateurs].username, utilisateurs[*nb_utilisateurs].password) == 2) {
        (*nb_utilisateurs)++;
    }

    fclose(fichier);
}

// Fonction pour vérifier si la chaîne contient uniquement des espaces ou des tabulations
int contient_seulement_espaces(const char *chaine) {
    size_t longueur = strlen(chaine);
    for (size_t i = 0; i < longueur; i++) {
        if (!isspace(chaine[i])) {
            return 0; // La chaîne contient au moins un caractère qui n'est pas un espace ou une tabulation
        }
    }
    return 1; // La chaîne ne contient que des espaces ou des tabulations
}

void saisie_mot_de_passe(char *password, int max_length) {
    struct termios old, new;
    int i = 0;
    char ch;

    // Obtient les paramètres actuels de terminal
    if (tcgetattr(STDIN_FILENO, &old) != 0) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    // Copie les paramètres actuels
    new = old;

    // Désactive l'affichage de l'entrée
    new.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);

    // Applique les nouveaux paramètres au terminal
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &new) != 0) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }

    // Saisie du mot de passe
    while (i < max_length - 1) {
        ch = getchar();

        // Arrête la saisie si l'utilisateur appuie sur Entrée
        if (ch == '\n') {
            break;
        }

        // Stocke le caractère dans le mot de passe
        password[i++] = ch;
    }

    // Restaure les paramètres du terminal
    if (tcsetattr(STDIN_FILENO, TCSANOW, &old) != 0) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }

    // Ajoute le caractère de fin de chaîne
    password[i] = '\0';

    // Ajoute un saut de ligne après la saisie du mot de passe
    printf("\n");
}

int verifier_connexion_admin(const char* nom_fichier, Utilisateur utilisateur) {
    Utilisateur utilisateurs[100];
    int nb_utilisateurs = 0;
    lire_utilisateurs(nom_fichier, utilisateurs, &nb_utilisateurs);

    for (int i = 0; i < nb_utilisateurs; i++) {
        if (strcmp(utilisateur.username, utilisateurs[i].username) == 0 &&
            strcmp(utilisateur.password, utilisateurs[i].password) == 0) {
            return 1; // Connexion réussie
        }
    }

    return 0; // Connexion échouée
}

void connexion_admin(const char* nom_fichier) {
    Utilisateur admin;

    // Demander le nom d'utilisateur
    printf("Entrez votre nom d'utilisateur : ");
    scanf("%49s", admin.username);

    // Vérifier si le nom d'utilisateur est vide
    if (strlen(admin.username) == 0) {
        printf("Nom d'utilisateur vide. Connexion échouée.\n");
        return;
    }

    // Demander le mot de passe
    printf("Entrez votre mot de passe : ");
    saisie_mot_de_passe(admin.password, sizeof(admin.password));

    // Masquer le mot de passe
    printf("Vérification en cours...\n");

    if (verifier_connexion_admin(nom_fichier, admin)) {
        printf("Connexion réussie en tant qu'administrateur\n");
        // Ajoutez ici le code pour le menu de l'administrateur
    } else {
        printf("Connexion échouée, veuillez réessayer.\n");
    }
}


int verifier_connexion_apprenant(const char* nom_fichier, Utilisateur utilisateur) {
    Utilisateur utilisateurs[100];
    int nb_utilisateurs = 0;
    lire_utilisateurs(nom_fichier, utilisateurs, &nb_utilisateurs);

    for (int i = 0; i < nb_utilisateurs; i++) {
        if (strcmp(utilisateur.username, utilisateurs[i].username) == 0 &&
            strcmp(utilisateur.password, utilisateurs[i].password) == 0) {
            return 1; // Connexion réussie
        }
    }

    return 0; // Connexion échouée
}


// Fonction pour afficher le menu de l'administrateur
void afficher_menu_admin(const char* nom_fichier, Utilisateur user) {
    printf("Menu de l'administrateur\n");
    printf("1. GESTION DES ÉTUDIANTS\n");
    printf("2. GÉNÉRATION DE FICHIERS\n");
    printf("3. MARQUER LES PRÉSENCES\n");
    printf("4. ENVOYER UN MESSAGE\n");
    printf("5. DECONNEXION\n");
    printf("6. QUITTER\n");
    printf("Choisissez une option : ");
    int choix;
    scanf("%d", &choix);
    switch (choix) {
        case 1:
            printf("Gestion des étudiants\n");
            break;
        case 2:
            printf("Génération de fichiers\n");
            break;
        case 3:
            printf("Marquer les présences\n");
            break;
        case 4:
            printf("Envoyer un message\n");
            break;
        case 5:
            printf("DECONNEXION\n");
            break;
        case 6:
            printf("Quitter\n");
            break;
        default:}
}

void afficher_menu_apprenant(const char* nom_fichier, Utilisateur user) {
    printf("Menu de l'apprenant\n");
    printf("1. MARQUER MA PRÉSENCE\n");
    printf("2. NOMBRE DE MINUTES D’ABSENCE\n");
    printf("3. MES MESSAGES (0)\n");
    printf("4. DECONNEXION\n");
    printf("5. QUITTER\n");
    printf("Choisissez une option : ");
    int choix;
    scanf("%d", &choix);
    switch (choix) {
        case 1:
            printf("Marquer ma présence\n");
            break;
        case 2:
            printf("Nombre de minutes d'absence\n");
            break;
        case 3:
            printf("Mes messages\n");
            break;
        case 4:
            printf("DECONNEXION\n");
            break;
        case 5:
            printf("Quitter\n");
            break;
        default:
            break;
    }
}

void gerer_menu_admin(const char* nom_fichier, Utilisateur user) {
    if (verifier_connexion_admin(nom_fichier, user)) {
        afficher_menu_admin(nom_fichier, user);
    } else {
        printf("Connexion échouée, veuillez réessayer.\n");
    }
}

void gerer_menu_apprenant(const char* nom_fichier, Utilisateur user) {
    if (verifier_connexion_apprenant(nom_fichier, user)) {
        afficher_menu_apprenant(nom_fichier, user);
    } else {
        printf("Connexion échouée, veuillez réessayer.\n");
    }
}








