#ifndef _AUTOMATE
#define _AUTOMATE

#define MAX(a, b) (a > b)?a:b


/* type booléen */
typedef unsigned char boolean;


/* type état */
typedef struct etat{

    int indice;
    int numero;
    int hauteur;
    boolean final;
    boolean b;
    struct transition *lien;

} Etat;


/* type transition */
typedef struct transition{

    int etiq;
    struct transition *suiv;
    Etat *but;

} Transition;


/* liste d'états prédecesseurs */
typedef struct etat_predecesseur{

    Etat *e;
    Etat *pr;
    int etiq;
    struct etat_predecesseur *suiv;

} EtatPredecesseur;


/* liste d'étiquettes */
typedef struct liste_etiq{

    int etiq;
    int numEtatDest;
    struct liste_etiq *suiv;

} ListeEtiq;


/* les prototypes des fonctions utilisées pour manipuler l'automate */
void ins_etiq_dest(ListeEtiq **l, int etiq, int num);
void ins_et_pr(EtatPredecesseur *x, EtatPredecesseur **l);
void affiche_et_pr(EtatPredecesseur *l);
void affiche_transitions(Etat *aut);
void affiche_terminaux(Etat *aut);
void initialisation_affichage(Etat *aut);
void affiche_etats(Etat *aut);
void affiche_automate(Etat *aut);
Etat* insere_numeroPort(unsigned int numPort, Etat *courant, boolean b);
void insere_sequence(Etat *aut, int *numPort);
void saisie_langage(char *path, Etat *aut);
void genere_sequence(char *path);
boolean appartient(Etat *aut, int *numPort);
void renumerote_etats(EtatPredecesseur *l, int hauteur);
void fusionner(EtatPredecesseur *ep);
int comparaison_futur(EtatPredecesseur *x1, EtatPredecesseur *x2);
void comparaison_equivalent(EtatPredecesseur *l, int hauteur);
void recherche_famille(Etat *courant, EtatPredecesseur **l_T, EtatPredecesseur **l_N, int i);
void minimisation(Etat *aut);
int calcul_hauteur(Etat *e);
void hauteurs_automate(Etat *aut);
void tester(Etat *aut);


#endif
