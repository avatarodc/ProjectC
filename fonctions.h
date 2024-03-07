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
void gerer_menu_apprenant(const char* nom_fichier, Utilisateur user);
void lister_classes(const char* nom_fichier);
void lister_etudiants_classe(const char* nom_fichier, const char* classe);
void marquer_presence_apprenant(const char* nom_fichier, int id);
void afficher_absences(const char* nom_fichier, int id_apprenant);
void marquer_absence(const char* nom_fichier, int id_apprenant, const char* date_heure);
void saisie_mot_de_passe(char *password, int max_length);
void connexion_admin(const char* nom_fichier);
void lister_classes(const char* nom_fichier);
void afficher_presences_classe(const char* nom_fichier, const char* classe) ;
void choisir_classe() ;
void afficher_liste_presences(const char* nom_fichier, const char* classe) ;
int est_dans_classe(int id, const char* classe);
int est_present(int id, const char* nom_fichier);
int contient_seulement_espaces(const char *chaine);
void afficher_etudiants_presence_classe(const char* nom_fichier, const char* classe) ;
void marquer_presence(const char* nom_fichier, int id_apprenant, const char* classe, int present);


#endif /* FONCTIONS_H */
