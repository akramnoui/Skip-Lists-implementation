#ifndef H_SKIP_LIST_
#define H_SKIP_LIST_
#define NIVEAU_MAXIMAL 6


	typedef struct skipmaillon {
    int valeur;
    struct skipmaillon **suivant;
} skipmaillon;

typedef struct skiplist {
    int niveau;
    struct skipmaillon *tete;
} skiplist;

skiplist *skiplist_init(skiplist *list);
void afficher_liste(skiplist *list);
int insertion_skiplist(skiplist *list, int valeur);
int rand_level();
skiplist *creation_skiplist(int n);
void suppression_maillon(skiplist *list, int nvvaleur);
void Liberer_maillon(skipmaillon*x);
void aff_tete(skiplist *list , skipmaillon *p);
void allouer_suiv(skipmaillon **p , int size);
skipmaillon * recherche_element(skiplist *list, int nvvaleur);
int comp_niveau(skiplist *list , int niveau );











#endif
