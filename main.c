#include <stdio.h>
#include <stdlib.h>
#include "Automata.h"

int main()
{
    Etat etatInit, *aut = NULL;
    char *path = "langage.txt";

    etatInit.numero = 0;
    etatInit.indice = -1;
    etatInit.final = 0;
    etatInit.b = 0;
    etatInit.lien = NULL;

    aut = &etatInit;

    // Génération d'une séquence aléatoire et l'ajouter au fichier
    genere_sequence(path);

    // Saisie de l'automate
    saisie_langage(path,aut);

    // Affichage de l'automate avant la minimisation
    printf("Affichage de l'automate avant la minimisation:\n");
    printf("______________________________________________\n");
    affiche_automate(aut);
    printf("\n");

    // Affectation des hateurs aux états de l'automate
    hauteurs_automate(aut);

    // la minimisation de l'automate
    minimisation(aut);

    // Affichage de l'automate apres la minimisation
    printf("Affichage de l'automate apres la minimisation:\n");
    printf("______________________________________________\n");
    affiche_automate(aut);

    // Tester l'appartenance d'une sequence donnée à l'automate minimisé
    tester(aut);

    return 0;
}
