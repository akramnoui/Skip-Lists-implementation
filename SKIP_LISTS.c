#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "skip_list.h"
#define SKIP_LIST_MAX_LEVEL 6




int main(int argc, char *argv[]) {
	srand(time(0));
	int nb , rep , rep2;
	skiplist * maListe;
	printf("\n----------------------------------------------------------------------------------------\n");
	printf("				TP SKIPLISTS\n");
	printf("binome : Noui Akram\n         Belguenbour Walid\n");
	printf("section B Groupe 06\n                                            ");
	printf("\n----------------------------------------------------------------------------------------------\n");

	// Initialisation de la skiplist :
	printf("creation d'une skiplist\n");
	printf("*********************************************************************\n");

	printf("Introduire le nombre d'elements de la skiplist: ");
	scanf("%d", &nb);
	maListe = creation_skiplist(nb);
	printf("\nAffichage de la skiplist:\n");
	afficher_liste(maListe);


	// Suppression d'une valeur:
	printf("\n test de suppresion d'un element\n  ");
	printf("\nEntrer la valeur a supprimer: ");
	scanf("%d", &rep);
	suppression_maillon(maListe,rep);

	printf("\nAffichage de la skiplist:\n");
		afficher_liste(maListe);



	// Insertion une valeur a une position:
	printf("\ntest de l'algorithme d'insertion\n");
	printf("Insertion de la Valeur = : ");
	scanf("%d", &rep2);
	insertion_skiplist(maListe,rep2);

	printf("\nAffichage de la skiplist:\n");
	afficher_liste(maListe);







	return 0;
}
