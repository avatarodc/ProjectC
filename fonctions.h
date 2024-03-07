#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED


#define MAX_APPRENANTS 100
#define MAX_CLASSES 10
#define MAX_MATRICULE_LENGTH 20
#define MAX_DATE_LENGTH 20


typedef struct {
    char username[50];
    char password[50];
} Utilisateur;


typedef struct {
    char nom[50];
    char prenom[50];
    char matricule[MAX_MATRICULE_LENGTH];
    char classe[20];
} Apprenant;

// Structure pour représenter une liste de présence
typedef struct {
    char date[MAX_DATE_LENGTH];
    char classe[20];
    int nb_apprenants;
    char matricules_present[MAX_APPRENANTS][MAX_MATRICULE_LENGTH];
} ListePresence;




void lire_utilisateurs(const char* nom_fichier, Utilisateur utilisateurs[], int* nb_utilisateurs);
int verifier_connexion_admin(const char* nom_fichier, Utilisateur utilisateur);
int verifier_connexion_apprenant(const char* nom_fichier, Utilisateur utilisateur);
void afficher_menu_admin(const char* nom_fichier, Utilisateur user);
void afficher_menu_apprenant(const char* nom_fichier, Utilisateur user);
int contient_seulement_espaces(const char *chaine);
void gerer_menu_admin(const char* nom_fichier, Utilisateur user);
void gerer_menu_apprenant(const char* nom_fichier, Utilisateur user);


int charger_apprenants(Apprenant *apprenants, const char *nom_fichier);
void sauvegarder_apprenants(Apprenant *apprenants, int nb_apprenants, const char *nom_fichier);
void charger_presence(ListePresence *presence, const char *nom_fichier);
void sauvegarder_presence(ListePresence *presence, const char *nom_fichier);
void marquer_present(ListePresence *presence, Apprenant *apprenants, int nb_apprenants);
void afficher_presence(ListePresence presence);


#endif /* FONCTIONS_H */
