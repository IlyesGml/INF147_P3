/**********************************************************************/
/* UTIL.CPP   Librairie de fonctions utilitaires.                     */
/**********************************************************************/

#include "main.h"

/**********************************************************************/
/* G�n�rer une valeur al�atoire enti�re.                              */
/**********************************************************************/

/* Fonction pour initialiser le g�n�rateur al�atoire. */
void init_alea(){
  srand(time(NULL));
}

/* Fonction al�atoire qui renvoie un entier inclu entre [min..max]. */
int  alea(int min, int max){
  return (int)((1.0 * rand()) / (RAND_MAX + 1) * (max-min+1)) + min;
}



