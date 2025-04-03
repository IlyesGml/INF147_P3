#include "animal.h"
#include <stdlib.h>


/*
Reçoit un animal et ses valeurs initiales, va initialiser l'animal reçu.
*/
void init_animal(t_animal* animal, int px, int py, int age, int energie, int gest) {
	animal->posx = px;						// Initialiser la position en X
	animal->posy = py;						// Initialiser la position en Y
	animal->age = age;						// Initialiser l'age
	animal->energie_sante = energie;		// Initialiser l'energie
	animal->jrs_gest = gest;				// Initialiser le nombre de jours de gestation
}

/*
Reçoit un animal et retourne sa position via [*px, *py].
*/
void get_position(const t_animal* animal, int* px, int* py) {
	*px = animal->posx;						// Posx est copié dans px
	*py = animal->posy;						// Posy est copié dans py
}

/*
Reçoit un animal et une position et va inscrire cette position à l'animal.
*/
void set_position(t_animal* animal, int px, int py) {
	animal->posx = px;						// Position X de l'animal est inscrit
	animal->posy = py;						// Position Y de l'animal est inscrit
}

/*
Reçoit un animal et retourne 1 si le poisson a attient l'age de
puberté ET a terminé sa période de gestation (donc, il va procréer),
retourne 0 sinon.
*/
int  puberte_atteinte(const t_animal* animal, int puberte, int gestation) {
	if (animal->age >= puberte && animal->jrs_gest >= gestation) {				// Si les contrainte de sont valide faire ce boucle
		return 1;
	}
	else {
		return 0;
	}
}

/*
Reçoit un animal et va incrémenter son age ainsi que le nombre de jours
en gestation de +1 jour si il est assez vieux pour procréer.
*/
void inc_age(t_animal* animal, int puberte) {
	animal->age++;								// Incrémenter l'age de +1
	if (animal->age >= puberte) {				// Si l'animal est est l'age de puberté faire ce boucle
		animal->jrs_gest++;						// Incémenter jrs_gest de +1
	}
}

/*
Reçoit un animal et va réinitialiser les jours de gestation à "val".
*/
void reset_gestation(t_animal* animal, int val) {
	animal->jrs_gest = val;						// Mise à jours de jours de gestation à "val"
}

/*
Reçoit un animal et va incrémenter son niveau d'énergie de la valeur reçue.
*/
void ajout_energie(t_animal* animal, int energie) {
	animal->energie_sante += energie;			// Incrémenter niveau d'energi de "energie"
}

/*
Reçoit un animal et va décrémenter son niveau d'énergie de -1.
*/
void dec_energie(t_animal* animal) {
	animal->energie_sante--;
}

/*
Reçoit un animal et va retourner son niveau d'énergie.
*/
int  get_energie(t_animal* animal) {
	return animal->energie_sante;
}

/*
Retourne 1 si l'animal reçu vient de mourir de faim (plus d'énergie)
OU si il a atteint son âge maximal (age_max). On retourne 0 sinon.
 */
int  est_mort(const t_animal* animal, int age_max) {
	if (animal->energie_sante <= 0 || animal->age == age_max) {			// Boucle si conditioon est vrai
		return 1;
	}
	else
	{
		return 0;
	}
}
