#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

typedef struct {
    char username[50];
    char password[50];
} Utilisateur;


typedef struct {
    char etat[10];
    char prenom[50];
    char nom[50];
    int id;
    char username[50];
    char password[50];
    char classe[50];
    int nbr_absence;
    int cumul_retard;
    char matricule[50]; // Nouveau champ pour le matricule de l'étudiant
} Apprenant;

typedef struct {
    int id_apprenant;
    char classe[50];
    char date_heure[20];
    int present; // 1 pour présent, 0 pour absent
} Absence;





void lire_utilisateurs(const char* nom_fichier, Utilisateur utilisateurs[], int* nb_utilisateurs);
int verifier_connexion_admin(const char* nom_fichier, Utilisateur utilisateur);
int verifier_connexion_apprenant(const char* nom_fichier, Utilisateur utilisateur);
void afficher_menu_admin(const char* nom_fichier, Utilisateur user);
void afficher_menu_apprenant(const char* nom_fichier, Utilisateur user);
void gerer_menu_admin(const char* nom_fichier, Utilisateur user);

int contient_seulement_espaces(const char *chaine);




#endif /* FONCTIONS_H */
