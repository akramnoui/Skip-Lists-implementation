#include <stdio.h>
#include <stdlib.h>
#include "skip_list.h"
#define NIVEAU_MAXIMAL 6

// machine abstraite
  /*----------------------------------------------------------------------------------------------------------------------------------------*/

void allouer(skipmaillon **p)
{
    *p= (skipmaillon *) malloc(sizeof(skipmaillon));
}
void aff_val(skipmaillon *p,int v)
{
    p->valeur=v;
}
skipmaillon *suivant(skipmaillon *p , int i)
{
 return (p->suivant[i]);
}
void aff_adr(skipmaillon *p , int i , skipmaillon *q  )
{
  p -> suivant[i] = q ;

}
int Valeur(skipmaillon *P)
{
  return (P->valeur);
}
void allouer_suiv(skipmaillon **p , int size)
{
	(*p)->suivant = (skipmaillon **) malloc(sizeof(skipmaillon*) * (size));//allouer un tableau de pointeurs de taille size
}

  /*----------------------------------------------------------------------------------------------------------------------------------------*/

skiplist *skiplist_init(skiplist *list) {
    int i;
    // on va allouer la tete de la skiplist
    skipmaillon *premier;
    allouer(&premier);
    list->tete = premier;
    aff_val(premier,INT_MAX);
    allouer_suiv(&premier, NIVEAU_MAXIMAL + 1);//allouer un tableau de pointeurs
    for (i = 0; i <= NIVEAU_MAXIMAL; i++) {
    aff_adr( premier, i ,NULL); // tous les pointeurs vont pointer vers NIL
    }

    list->niveau = 1;


    return list;
}



  /*----------------------------------------------------------------------------------------------------------------------------------------*/


	 void afficher_liste(skiplist *list)
  {
    skipmaillon *x = list->tete;
    int i , cpt=1 , y ;
		for (i =1; i <= list->niveau ;i ++  )
		{

			x = suivant(list-> tete ,i );
      printf("niveau [%d] :  " , i);
    while (x != NULL)
	{
    printf("[ %d ]->", Valeur(x));
    x = suivant(x,i);
    }
    printf("NULL\n");

	    }

	}

    /*----------------------------------------------------------------------------------------------------------------------------------------*/



	int insertion_skiplist(skiplist *list, int nvvaleur ) {
    skipmaillon *T[NIVEAU_MAXIMAL +1]; // on utilise le tableau T pour sauvegarder les maillons qui precedent le maillon a inserer pour l'utiliser lors du chainage
    skipmaillon *x = list->tete;
    int i , niveau ;
    // operation de recherche
    for (i = list->niveau; i >= 1; i--) {
        while (suivant(x,i) != NULL && Valeur(suivant(x,i)) < nvvaleur)
        {
            x = suivant(x,i);
        }
        T[i] = x;
    }
    if (nvvaleur == Valeur(x)) {
        return 0;
    } else {
        niveau = rand_niveau(); // designe un niveau aleatoire au maillon
        if (niveau > list->niveau)
         {
           // si le niveau du maillon est superieur au niveau de la liste on modifie les cases du tableau T pour qu'il poointent vers la tete
            for (i = list->niveau + 1; i <= niveau; i++)
            {
                T[i] = list->tete;
            }
            list->niveau = niveau;
        }
        // allocation du maillon
        allouer(&x);
        aff_val(x, nvvaleur);
        allouer_suiv(&x , niveau + 1); // allocation du tableau de pointeurs
        // modification du chainage
        for (i = 1; i <= niveau; i++)
        {
            	aff_adr(x , i , suivant(T[i] , i) );
      				aff_adr(T[i] , i , x) ;
        }

    }
    return 0;
}
  /*----------------------------------------------------------------------------------------------------------------------------------------*/

 int rand_niveau()
  {
    int niveau = 1;
    while (rand() < RAND_MAX / 2 && niveau < NIVEAU_MAXIMAL)
        niveau++;
    return niveau;
	}
  /*----------------------------------------------------------------------------------------------------------------------------------------*/

  // fonction pour creer une skiplist de n elements
  skiplist *creation_skiplist(int n)
  	{
  		skipmaillon *T[NIVEAU_MAXIMAL+1];
  		skiplist *list;
  		skiplist_init(list);
  		skipmaillon *x = list-> tete;
  		int i , niveau , y ;
  		for (y = 1 ; y <= n ; y ++)
  		{
  			printf("entrez la valeur a inserer : " );
  			int nvvaleur;
  			scanf("%d" , &nvvaleur);
  		  insertion_skiplist(list,nvvaleur);
  	   }
       skipmaillon *z = list-> tete-> suivant[niveau];
       while (comp_niveau(list,list->niveau) == 1 )
       {
		   list ->niveau --;
      }
  	return list;

  }
    /*----------------------------------------------------------------------------------------------------------------------------------------*/


    void suppression_maillon(skiplist *list, int nvvaleur) {
      int i;
      skipmaillon * T[NIVEAU_MAXIMAL + 1];
      skipmaillon *x = list->tete;
      // operation de recherche
      for (i = list->niveau ; i >= 1 ; i--)
      {
          while ( suivant(x,i) != NULL && Valeur(suivant(x,i)) < nvvaleur)
          {
              x = suivant(x,i);
          }
          // remplissage du tableau qui va servir au chainage
          T[i] = x;
       }

      x = suivant(x,1);
      if (Valeur(x) == nvvaleur)
       {
         // mise a jour du chainage
          for (i = 1; i <= list->niveau; i++) {
              if (suivant(T[i],i) != x)
                  break;
              aff_adr(T[i] , i , suivant(x,i));
        }
          // liberation de l'espace
          Liberer_maillon(x);
          // verification s'il existe un niveau vide et suppression du niveau dans ce cas
          while (list->niveau > 1 && suivant(list->tete ,list->niveau) == NULL)
              list->niveau--;
      }else
       {

         printf("cette valeur n'existe pas");
        }

  }


    /*----------------------------------------------------------------------------------------------------------------------------------------*/

     void Liberer_maillon(skipmaillon*x) {
        if (x)
          {
            free(x->suivant);
            free(x);
          }
      }
        /*----------------------------------------------------------------------------------------------------------------------------------------*/


      skipmaillon *recherche_element(skiplist *list , int nvvaleur) {
      skipmaillon *x = list->tete;
      int i , cpt=0 ;
     for (i = list->niveau; i >= 1; i--) {
         while (suivant(x,i) -> valeur < nvvaleur)
         {
             x = suivant(x,i);
             cpt ++;
          }
          cpt ++;
     }
     if (Valeur(suivant(x,1)) == nvvaleur) {
       return x ;

     } else {
         printf("cette valeur n'existe pas\n");
         return NULL;
     }


   }
   // au cas ou on a deux niveaux similaires ( ce qui est inutile) on utilise cette fonction pour comparer les niveaux
   int comp_niveau(skiplist *list , int niveau )
   {
     int i , true=1 ;
     skipmaillon *x = list->tete->suivant[niveau] , *y = list ->tete ->suivant[niveau -1];
      while( x != NULL && y != NULL && true == 1)
      {
        if (Valeur(x) != Valeur(y))
        {
          true = 0;
        }
        x = suivant(x,niveau);
        y = suivant(y,niveau-1);
      }
      return true;
   }
