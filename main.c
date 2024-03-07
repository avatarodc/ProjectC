#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include "fonctions.h"

int main() {
    char nom_fichier_utilisateurs[] = "connexion.txt";
    char nom_fichier_utilisateur[] = "apprenants.txt";
    char nom_fichier_absences[] = "absences.txt";
    int choix;
    Utilisateur user;

    int connexion_reussie = 0;

    initscr(); // Initialiser ncurses
    cbreak(); // Désactiver le mode de ligne tampon (la saisie est immédiatement disponible)
    noecho(); // Désactiver l'écho des caractères saisis

    do {
        printw("Entrez votre nom d'utilisateur : ");
        refresh();

        // Saisie du nom d'utilisateur
        echo(); // Activer l'écho des caractères saisis
        getnstr(user.username, sizeof(user.username)); // Permettre à l'utilisateur de saisir le nom d'utilisateur
        noecho(); // Désactiver l'écho des caractères saisis

        // Vérifier si le nom d'utilisateur contient des espaces
        if (contient_seulement_espaces(user.username)) {
            printw("\nLe nom d'utilisateur ne doit pas contenir d'espaces. Veuillez saisir à nouveau.\n");
            continue;
        }

        printw("\n");

        printw("Nom d'utilisateur : %s\n", user.username);

        printw("Entrez votre mot de passe : ");

        // Saisie du mot de passe
        int i = 0;
        char c;
        while (1) {
            c = getch(); // Lire un caractère sans l'afficher
            
            // Vérifier si c'est un caractère de contrôle (backspace ou espace)
            if (c == '\n' || c == '\r' || c == '\t' || c == ' ' || c == '\b') {
                if (i > 0 && (c == ' ' || c == '\b')) {
                    printw("\b \b"); // Effacer le caractère précédent
                    i--; // Décrémenter l'index pour effacer le caractère de la chaîne
                }
                if (c == '\n' || c == '\r') {
                    user.password[i] = '\0';
                    break;
                }
            } else {
                user.password[i++] = c;
                printw("*");
            }
        }

        // Vérifier si le mot de passe contient uniquement des espaces ou des tabulations
        if (contient_seulement_espaces(user.password)) {
            printw("\nMot de passe invalide.\n");
            continue;
        }

        if (verifier_connexion_admin(nom_fichier_utilisateurs, user)) {
            connexion_reussie = 1;
            endwin(); // Terminer ncurses

            printw("Connexion réussie en tant qu'administrateur\n");
            afficher_menu_admin(nom_fichier_absences, user);
            break;
        } else if (verifier_connexion_apprenant(nom_fichier_utilisateur, user)) {
            connexion_reussie = 1;
            endwin(); // Terminer ncurses
            afficher_menu_apprenant(nom_fichier_absences, user);
            break;
        } else {
            printw("\nLogin ou mot de passe incorrect. Voulez-vous réessayer ? (O/N) : ");
            refresh();
            char reessayer;
            reessayer = getch();
            if (reessayer != 'O' && reessayer != 'o') {
                break;
            }
        }
    } while (!connexion_reussie);

    if (!connexion_reussie) {
        printw("Connexion échouée. Au revoir.\n");
    }

    return 0;
}
