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
            printf("LISTER ETUDIANTS\n");
            lister_etudiants_classe("apprenants.txt", "ClasseA");
            printf("\n");
            printf("listes des etutudiants de la classe B\n");
            lister_etudiants_classe("apprenants.txt", "ClasseB");
            printf("\n");
            printf("listes des etutudiants de la classe C\n");
            lister_etudiants_classe("apprenants.txt", "ClasseC");
            lister_classes("classes.txt");
            printf("AFFICHER PRESENCES\n");
            afficher_presences_classe("absences.txt", "ClasseA");
            printf("la liste de presences des etudiants\n");
            afficher_presences_classe("absences.txt", "ClasseB");
            printf("la liste de presences des etudiants\n");
            afficher_presences_classe("absences.txt", "ClasseC");
            printf("la liste de presences des etudiants\n");
            break;
        case 2:
            printf("Génération de fichiers\n");
            break;
        case 3:
            printf("Marquer les présences\n");
            
            int id_apprenant , classe ;
            printf("Marquer la presence de l'apprenant\n");
            printf("1 - REFDIJ\n");
            printf("2 - DEVWEB\n");
            printf("3 - DATA\n");
            printf("4 - LISTE DES PRESENCES\n");
            printf("CHOISIR UNE CLASSE\n");
            scanf("%d",&classe);
            switch(classe){
                case 1 :
                    printf("REFDIJ  teste \n");
                    lister_etudiants_classe("apprenants.txt", "ClasseA");
                    printf("\n");
                    // printf("Entrez l'identifiant de l'apprenant : \n");
                    //scanf("%d", &id_apprenant);
                    marquer_presence_apprenant("absences.txt", id_apprenant);
                    break;
                case 2 :
                    lister_etudiants_classe("apprenants.txt", "ClasseB");
                    printf("DEVWEB\n");
                    printf("Entrez l'identifiant de l'apprenant : ");
                    scanf("%d", &id_apprenant);
                    marquer_presence_apprenant("absences.txt", id_apprenant);
                    break;
                case 3 :
                   // lister_etudiants_classe("apprenants.txt", "ClasseC");
                    printf("DATA\n");
                    
                    printf("Entrez l'identifiant de l'apprenant : ");
                   // scanf("%d", &id_apprenant);
                    marquer_presence_apprenant("absences.txt", id_apprenant);
                    break;
                case 4 :
                int classe;
                    printf("LISTE DES PRESENCES\n");
                    printf("1 - REFDIJ\n");
                    printf("2 - DEVWEB\n");
                    printf("3 - DATA\n");
                    printf("CHOISIR UNE CLASSE\n");
                    scanf("%d",&classe);
                    switch(classe){
                        case 1 :
                            printf("REFDIJ\n");
                            afficher_etudiants_presence_classe("absences.txt", "ClasseA");
                            break;
                        case 2 :
                            printf("DEVWEB\n");
                            afficher_etudiants_presence_classe("absences.txt", "ClasseB");
                            break;
                        case 3 :
                            printf("DATA\n");
                            afficher_etudiants_presence_classe("absences.txt", "ClasseC");
                            break;
                        default :
                            printf("ERREUR\n");
                            break;
                    }
                    break;
                default :
                    printf("ERREUR\n");
                    break;
            }
            printf("Entrez l'identifiant de l'apprenant : ");
            scanf("%d", &id_apprenant);
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
        default:
            break;
    }
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



void lister_etudiants_classe(const char* nom_fichier, const char* classe) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        return;
    }

    Apprenant apprenant;
    while (fscanf(fichier, "%s %s %s %d %s %s %s %d %d", apprenant.etat, apprenant.prenom, apprenant.nom, &apprenant.id, apprenant.username, apprenant.password, apprenant.classe, &apprenant.nbr_absence, &apprenant.cumul_retard) == 9) {
        if (strcmp(apprenant.classe, classe) == 0) {
            printf("%s %s %s\n", apprenant.prenom, apprenant.nom , apprenant.classe);
        }
    }

    fclose(fichier);
}




// Fonction pour choisir une classe parmi celles disponibles
void choisir_classe() {
    printf("Classes disponibles :\n");
    lister_classes("classes.txt");

    char classe[50];
    printf("Entrez le nom de la classe : ");
    scanf("%49s", classe);

    // Ici, vous pouvez ajouter la logique pour afficher les apprenants de la classe choisie
    // et permettre à l'utilisateur de choisir l'apprenant par son identifiant pour le marquer comme présent
}



void afficher_presences_classe(const char* nom_fichier, const char* classe) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        return;
    }

    Apprenant apprenant;
    while (fscanf(fichier, "%s %s %s %d %s %s %s %d %d", apprenant.etat, apprenant.prenom, apprenant.nom, &apprenant.id, apprenant.username, apprenant.password, apprenant.classe, &apprenant.nbr_absence, &apprenant.cumul_retard) == 9) {
        if (strcmp(apprenant.classe, classe) == 0) {
            printf("Présences de l'étudiant %s %s :\n", apprenant.prenom, apprenant.nom);
            afficher_absences("absences.txt", apprenant.id);
            printf("\n");
        }
    }

    fclose(fichier);
}

void afficher_etudiants_presence_classe(const char* nom_fichier, const char* classe) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        return;
    }

    printf("Liste des étudiants de la classe %s :\n", classe);

    Apprenant apprenant;
    while (fscanf(fichier, "%s %s %s %d %s %s %s %d %d", apprenant.etat, apprenant.prenom, apprenant.nom, &apprenant.id, apprenant.username, apprenant.password, apprenant.classe, &apprenant.nbr_absence, &apprenant.cumul_retard) == 9) {
        if (strcmp(apprenant.classe, classe) == 0) {
            // Afficher l'étudiant et son état de présence
            printf("%s %s : ", apprenant.prenom, apprenant.nom);
            if (strcmp(apprenant.etat, "present") == 0) {
                printf("Présent\n");
            } else {
                printf("Absent\n");
            }
        }
    }

    fclose(fichier);
}





void afficher_absences(const char* nom_fichier, int id_apprenant) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        return;
    }

    int id;
    char date[20];

    while (fscanf(fichier, "%d %s", &id, date) == 2) {
        if (id == id_apprenant) {
            printf("Absence de l'étudiant %d le %s\n", id, date);
        }
    }

    fclose(fichier);
}



void lister_classes(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        return;
    }

    char classe[50];
    printf("Liste des classes :\n");
    while (fscanf(fichier, "%s", classe) != EOF) {
        printf("%s\n", classe);
    }

    fclose(fichier);
}


void afficher_liste_presences(const char* nom_fichier, const char* classe) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        return;
    }

    printf("Liste des présences pour la classe %s :\n", classe);

    // Lecture des données de présence
    int id;
    char date[20];
    while (fscanf(fichier, "%d %s", &id, date) == 2) {
        // Vérification si l'étudiant correspondant à cet ID est dans la classe donnée
        if (est_dans_classe(id, classe)) {
            // Affichage du nom de l'étudiant
            char* etat = est_present(id, nom_fichier) ? "Présent" : "Absent";
            printf("ID: %d - Etat: %s\n", id, etat);
        }
    }

    fclose(fichier);
}

int est_dans_classe(int id, const char* classe) {
    FILE* fichier = fopen("apprenants.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier des apprenants.\n");
        return 0;
    }

    // Lecture des données de chaque apprenant
    Apprenant apprenant;
    while (fscanf(fichier, "%s %s %s %d %s %s %s %d %d", apprenant.etat, apprenant.prenom, apprenant.nom, &apprenant.id, apprenant.username, apprenant.password, apprenant.classe, &apprenant.nbr_absence, &apprenant.cumul_retard) == 9) {
        if (apprenant.id == id && strcmp(apprenant.classe, classe) == 0) {
            fclose(fichier);
            return 1; // L'étudiant est dans la classe donnée
        }
    }

    fclose(fichier);
    return 0; // L'étudiant n'est pas dans la classe donnée
}

int est_present(int id, const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier des présences.\n");
        return 0;
    }

    // Vérification de la présence de l'étudiant dans le fichier des présences
    int presence = 0;
    int presence_id;
    char date[20];
    while (fscanf(fichier, "%d %s", &presence_id, date) == 2) {
        if (presence_id == id) {
            presence = 1; // L'étudiant est présent
            break;
        }
    }

    fclose(fichier);
    return presence;
}

void marquer_presence_apprenant(const char* nom_fichier, int id) {
    FILE* fichier = fopen(nom_fichier, "a");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        return;
    }

    time_t temps;
    struct tm date_heure;
    char date_heure_format[20];
    time(&temps);
    date_heure = *localtime(&temps);
    strftime(date_heure_format, sizeof(date_heure_format), "%Y-%m-%d %H:%M:%S", &date_heure);

    fprintf(fichier, "%d %s\n", id, date_heure_format);
    
    fclose(fichier);
}

