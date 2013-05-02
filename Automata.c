#include "Automata.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int numE = 1;

/*
 * fonction qui insère une étiquette et son numero d'état destination dans une liste donnée en paramètre
 */
 void ins_etiq_dest(ListeEtiq **l, int etiq, int num){

    ListeEtiq *p, *it;

    p = (ListeEtiq*)malloc(sizeof(ListeEtiq));

    p->etiq = etiq;
    p->numEtatDest = num;
    p->suiv = NULL;

    if(*l == NULL){

        *l = p;

    } else {

        it = *l;

        if(etiq < it->etiq){

            p->suiv = it;
            *l = p;

        } else {

            while(it->suiv != NULL){

                if(etiq < it->suiv->etiq){

                    p->suiv = it->suiv;
                    it->suiv = p;
                    break;

                }

                it = it->suiv;

            }

            if(it->suiv == NULL){

                it->suiv = p;

            }

        }

    }

 }


/*
 * fonction qui insère un bloc dans la liste etat_predecesseur
 */
 void ins_et_pr(EtatPredecesseur *x, EtatPredecesseur **l){

    EtatPredecesseur *it;

    if(*l == NULL){

        *l = x;

    } else {

        for(it = *l; it->suiv != NULL; it = it->suiv);

        it->suiv = x;

    }

 }


/*
 * fonction qui affiche une liste de type etat_predecesseur
 */
 void affiche_et_pr(EtatPredecesseur *l){

    EtatPredecesseur *it = l;
    Etat *i;

    while(it != NULL){

        i = it->e;
        printf("\nEtat : (%d, %d)\n", i->indice, i->numero);
        i = it->pr;
        printf("Son predecesseur : (%d, %d)\n\n", i->indice, i->numero);
        it = it->suiv;

    }

 }


/*
 * fonction qui affiche les transitions
 */
 void affiche_transitions(Etat *aut){

    Etat *e = aut;
    Transition *t = NULL;

    if(e->b == 0){

        t = e->lien;

        while(t != NULL){

            printf("\n((%d, %d), %d, (%d, %d))", e->indice, e->numero, t->etiq, t->but->indice, t->but->numero);
            t = t->suiv;
            e->b = 1;

        }

        t = e->lien;

        while(t != NULL){

            if((t->but->lien != NULL) && (t->but->b == 0)){

                affiche_transitions(t->but);

            }

            t = t->suiv;

        }

    }

 }


/*
 * fonction qui affiche les états terminaux
 */
 void affiche_terminaux(Etat *aut){

    Etat *e = aut;
    Transition *t = e->lien;

    while(t != NULL){

        if((t->but->final == 1) && (t->but->b == 0)){

            printf("\n(%d, %d)", t->but->indice, t->but->numero);
            t->but->b = 1;

        }

        if(t->but->lien != NULL){

            affiche_terminaux(t->but);

        }

        t = t->suiv;

    }

 }



void initialisation_affichage(Etat *aut){

    Etat *e = aut;
    Transition *t = e->lien;

    e->b = 0;

    while(t != NULL){

        t->but->b = 0;

        if(t->but->lien != NULL){

            initialisation_affichage(t->but);

        }

        t = t->suiv;

    }

}


/*
 * fonction qui affiche les états d'un automate
 */
 void affiche_etats(Etat *aut){

    Etat *e = aut;
    Transition *t = e->lien;

    while(t != NULL){

        if(t->but->b == 0){

            printf("\n(%d, %d)", t->but->indice, t->but->numero);
            t->but->b = 1;

        }

        if(t->but->lien != NULL){

            affiche_etats(t->but);

        }

        t = t->suiv;

    }

 }


/*
 * fonction qui affiche l'automate
 */
 void affiche_automate(Etat *aut){

    printf("\nL'automate A = (Alphabet, Q, I, T, Transitions) :\n\n");

    printf("\nL'ensemble des etats Q :\n");
    printf("\nQ = {\n\n(%d, %d)", aut->indice, aut->numero);
    affiche_etats(aut);
    printf("\n\n}\n");
    initialisation_affichage(aut);

    printf("\nL'etat initial I : (%d, %d)\n", aut->indice, aut->numero);

    printf("\nL'ensemble des etats terminaux T : \n");
    printf("\nT = {\n");
    affiche_terminaux(aut);
    printf("\n\n}\n");
    initialisation_affichage(aut);

    printf("\nLes transitions : \n{\n");
    affiche_transitions(aut);
    printf("\n\n}\n\n");
    initialisation_affichage(aut);

 }


/*
 * fonction qui insère un numero de port d'une sequence de trois ports
 */
 Etat *insere_numeroPort(unsigned int numPort, Etat *courant, boolean b){

    static unsigned short num = 0;
    Etat *e = courant;
    Transition *t = e->lien;

    while(t != NULL){

        if(t->etiq == numPort){

            if(b == 1){

                t->but->final = 1;

            }

            return t->but;

        }

        t = t->suiv;

    }

    Etat *nouveauE = (Etat*)malloc(sizeof(Etat));
    Transition *nouvelleT = (Transition*)malloc(sizeof(Transition));

    nouveauE->indice = -1;
    nouveauE->numero = ++num;
    nouveauE->final = (b == 1)?1:0;
    nouveauE->b = 0;
    nouveauE->lien = NULL;

    nouvelleT->etiq = numPort;
    nouvelleT->but = nouveauE;
    nouvelleT->suiv = NULL;

    if(e->lien == NULL){

        e->lien = nouvelleT;

    } else {

        for(t = e->lien; t->suiv != NULL; t = t->suiv);
        t->suiv = nouvelleT;

    }

    return nouveauE;

 }


/*
 * fonction qui insère une séquence dans un automate
 */
 void insere_sequence(Etat *aut, int *numPort){

    Etat *buffer = aut;

    buffer = insere_numeroPort(numPort[0], buffer, 0);
    buffer = insere_numeroPort(numPort[1], buffer, 0);
    buffer = insere_numeroPort(numPort[2], buffer, 1);

 }


/*
 * fonction qui saisie un langage à partir d'un fichier
 */
 void saisie_langage(char *path, Etat *aut){

    FILE *f = fopen(path, "r");
    int numPort[3] = {0};

    if(f != NULL){

        while(fscanf(f, "(%d,%d,%d)", &numPort[0], &numPort[1], &numPort[2]) == 3){

            insere_sequence(aut, numPort);
            fseek(f, 1, SEEK_CUR);

        }

        fclose(f);

    }

 }


/*
 * fonction qui génère une séquence de trois ports et l'ajoute au fichier
 */
 void genere_sequence(char *path){

   FILE *f = fopen(path, "a");
   int i, numPort[3] = {0};

   if(f != NULL){

        srand(time(NULL));

        for(i = 0; i < 3; i++){

            numPort[i] = rand() % (65536 - 1024) + 1024;

        }

        fprintf(f, "(%d,%d,%d)\n", numPort[0], numPort[1], numPort[2]);
        fclose(f);

   }

 }


 /*
  * fonction qui teste l'appartenance d'une sequence à un automate
  */
  boolean appartient(Etat *aut, int *numPort){

    Transition *t = aut->lien;
    int i;

    for(i = 0; i < 3; i++){

        for(; (t->etiq != numPort[i]) && (t->suiv != NULL); t = t->suiv);

        if(t->etiq == numPort[i]){

            if(i == 2){

                if(t->but->final == 1){

                    return 1;

                } else {

                    break;

                }

            }

            if(t->but->lien != NULL){

                t = t->but->lien;

            } else {

                break;

            }

        } else {

            break;

        }

    }

    return 0;

  }


/*
 * fonction qui renumérote les états d'un même niveau
 */
 void renumerote_etats(EtatPredecesseur *l, int hauteur){

    EtatPredecesseur *it = l;

    while(it != NULL){

        it->e->indice = hauteur;
        it->e->numero = numE++;
        it = it->suiv;

    }

 }


/*
 * fonction qui fusionne les états équivalents
 */
 void fusionner(EtatPredecesseur *ep){

    Etat *ce;
    EtatPredecesseur *cep;
    Transition *t;

    if(ep != NULL){

        cep = ep->suiv;

        while(cep != NULL){

            ce = cep->pr;
            t = ce->lien;

            while(t != NULL){

                if(t->etiq == cep->etiq){

                    t->but = ep->e;

                }

                t = t->suiv;

            }

            cep = cep->suiv;

        }

    }

    free(ep);

 }


int comparaison_futur(EtatPredecesseur *x1, EtatPredecesseur *x2){

    ListeEtiq *l1 = NULL, *l2 = NULL;
    Transition *t = x1->e->lien;

    while(t != NULL){

        ins_etiq_dest(&l1, t->etiq, t->but->numero);
        t = t->suiv;

    }

    t = x2->e->lien;

    while(t != NULL){

        ins_etiq_dest(&l2, t->etiq, t->but->numero);
        t = t->suiv;

    }

    if((l1 == NULL) && (l2 != NULL)){

        return 0;

    }

    if((l1 != NULL) && (l2 == NULL)){

        return 0;

    }

    while((l1 != NULL) && (l2 != NULL)){

        if((l1->etiq == l2->etiq) && (l1->numEtatDest == l2->numEtatDest)){

            l1 = l1->suiv;
            l2 = l2->suiv;

        } else {

            return 0;

        }

    }

    if((l1 != NULL) || (l2 != NULL)){

        return 0;

    }

    return 1;

}


void comparaison_equivalent(EtatPredecesseur *l, int hauteur){

    EtatPredecesseur *cl1 = l, *cl2, *cl3, *x, *l1 = NULL;

    while(cl1 != NULL){

        cl2 = cl1->suiv;
        cl3 = cl1;

        while(cl2 != NULL){

            if(comparaison_futur(cl1, cl2) == 1){

                if(l1 == NULL){

                    x = (EtatPredecesseur*)malloc(sizeof(EtatPredecesseur));
                    x->e = cl1->e;
                    x->etiq = cl1->etiq;
                    x->pr = cl1->pr;
                    x->suiv = NULL;
                    ins_et_pr(x, &l1);

                }

                ins_et_pr(cl2, &l1);
                cl3->suiv = cl2->suiv;
                cl2->suiv = NULL;
                cl2 = cl3->suiv;

            } else {

                cl3 = cl2;
                cl2 = cl2->suiv;

            }

        }

        fusionner(l1);
        l1 = NULL;
        cl1 = cl1->suiv;

    }

    renumerote_etats(l, hauteur);

}


void recherche_famille(Etat *courant, EtatPredecesseur **l_T, EtatPredecesseur **l_N, int i){

    Etat *ep = courant, *ce = courant;
    Transition *t;
    EtatPredecesseur *x;

    if(ce->lien != NULL){

        t = ce->lien;

        while(t != NULL){

            ce = t->but;

            if(ce->hauteur == i){

                x = (EtatPredecesseur*)malloc(sizeof(EtatPredecesseur));
                x->suiv = NULL;
                x->e = ce;
                x->pr = ep;
                x->etiq = t->etiq;

                if(ce->final == 0){

                    ins_et_pr(x, l_N);

                } else {

                    ins_et_pr(x, l_T);

                }

            } else {

                recherche_famille(ce, l_T, l_N, i);

            }

            t = t->suiv;

        }

    }

}


void minimisation(Etat *aut){

    int i;
    EtatPredecesseur *l_T = NULL, *l_N = NULL;

    recherche_famille(aut, &l_T, &l_N, 0);
    l_T->e->indice = 0;
    l_T->e->numero = 1;
    fusionner(l_T);

    for(i = 0; i < aut->hauteur; i++){

        numE = 1;
        l_T = NULL;
        l_N = NULL;
        recherche_famille(aut, &l_T, &l_N, i);
        comparaison_equivalent(l_N, i);
        comparaison_equivalent(l_T, i);

    }

    aut->indice = aut->hauteur;
    aut->numero = 1;

}


int calcul_hauteur(Etat *e){

    int r, h = 0, max = 0;
    Transition *t;

    if(e->lien == NULL){

        return h;

    }

    t = e->lien;
    r = calcul_hauteur(t->but);

    max = MAX(r, max);

    while(t->suiv != NULL){

        t = t->suiv;
        r = calcul_hauteur(t->but);
        max = MAX(r, max);

    }

    return (1 + max);

}


void hauteurs_automate(Etat *aut){

    Etat *ce = aut;
    Transition *t;

    if(ce != NULL){

        ce->hauteur = calcul_hauteur(ce);
        t = ce->lien;

        while(t != NULL){

            ce = t->but;
            hauteurs_automate(ce);
            t = t->suiv;

        }

    }

}



void tester(Etat *aut){

    int i, numPort[3] = {0};

    for(i = 0; i < 3; i++){

        do {

            printf("\nEntrer le port numero %d (1024 <= num port < 65536): ", (i+1));
            scanf("%d", (numPort + i));

        } while((numPort[i] < 1024) || (numPort[i] >= 65536)) ;

    }

    if(appartient(aut, numPort)){

        printf("\nLa sequence existe\n");

    } else {

        printf("\nLa sequence n'existe pas\n");

    }

}


