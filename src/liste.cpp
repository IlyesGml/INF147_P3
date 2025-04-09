#include "..\inc\main.h"
#include "..\inc\liste.h"

// Initialisation de la liste vide
/**
 * @brief créer une liste avec le premier animal.
 *
 * @param animal Poisson ou requin à ajouter à la première position de la liste.
 *
 * @return t_noeud*
 */
t_noeud* creer_noeud(t_animal animal)
{
    t_noeud* nouveau_noeud = (t_noeud*)malloc(sizeof(t_noeud));
    if (nouveau_noeud == NULL)
    {
        printf("Erreur d'allocation de mémoire pour le noeud.\n");
        return NULL;
    }
    nouveau_noeud->animal = animal;
    nouveau_noeud->precedent = NULL;
    nouveau_noeud->suivant = NULL;
    return nouveau_noeud;
}
/**
 * @brief Ajouter un poisson ou requin à la tête de la liste.
 *
 * @param liste t_liste_requins ou t_liste_poissons sont la destination du nouveau poisson ou requin.
 * @param animal le poisson ou requin à ajouter à la liste dans t_liste.
 */
t_noeud* insererEnTete(t_liste** tete, t_animal animal)
{
    t_noeud* nouveau_noeud = creer_noeud(animal);
    if (nouveau_noeud == NULL)
    {
        printf("Erreur d'allocation de mémoire pour le noeud.\n");
        return NULL;
    }
    if (*tete == NULL)
    {
        *tete = nouveau_noeud;
#ifdef DEBUG
        printf("Liste vide, Tete: %p\n", tete);
#endif
        return nouveau_noeud;
    }
    else
    {
        nouveau_noeud->suivant = *tete;
        (*tete)->precedent = nouveau_noeud;
        *tete = nouveau_noeud;
    }
    return nouveau_noeud;
}

void supprimerEnTete(t_liste** liste)
{
    if (*liste == NULL)
    {
        printf("Erreur : la liste est vide.\n");
        return;
    }
    t_noeud* noeud_a_supprimer = *liste;
    if ((*liste)->suivant == NULL)
    {
        free(noeud_a_supprimer);
        *liste = NULL;
    }
    else
    {
        *liste = (*liste)->suivant;
        (*liste)->precedent = NULL;
        free(noeud_a_supprimer);
    }
}

void supprimerAnimal(t_noeud** tete, t_noeud* animal_to_kill)
{
    if (animal_to_kill == NULL || *tete == NULL)
    {
#ifdef DEBUG
        printf("Erreur : le noeud à supprimer est NULL.\n");
#endif
        return;
    }
    if ((*tete) == animal_to_kill)
    {
#ifdef DEBUG
        printf("Noeud à supprimer est le premier de la liste.\n");
#endif
        (*tete) = animal_to_kill->suivant;
        animal_to_kill->suivant->precedent = NULL;
        free(animal_to_kill);
        return;
    }
    if (animal_to_kill->suivant == NULL)
    {
#ifdef DEBUG
        printf("Noeud à supprimer est le dernier dans la liste.\n");
#endif
        t_noeud* pre_noeud = animal_to_kill->precedent;
        pre_noeud->suivant = NULL;
    }
    else
    {
        t_noeud* pre_noeud = animal_to_kill->precedent;
        t_noeud* next_noeud = animal_to_kill->suivant;
        pre_noeud->suivant = animal_to_kill->suivant;
        next_noeud->precedent = animal_to_kill->precedent;
    }


    free(animal_to_kill);
}

void libererListe(t_liste* liste)
{
    t_noeud* courant;
    while (liste != NULL)
    {
        courant = liste;
        liste = liste->suivant;
        free(courant);
    }
}

void afficherListe(t_liste* liste)
{
    t_noeud* courant = liste;
    for (int i = 0; courant != NULL; i++)
    {
        printf("Animal %d : Age = %d, Energie = %d, Position = (%d, %d)\n", i,
               courant->animal.age, courant->animal.energie_sante,
               courant->animal.posx, courant->animal.posy);
        courant = courant->suivant;
    }
    printf("\n");
}

t_liste* insererEnFin(t_liste** liste, t_animal animal)
{
    t_liste* nouveau_noeud = creer_noeud(animal);
    if (nouveau_noeud == NULL)
    {
        printf("Erreur d'allocation de mémoire pour le noeud.\n");
        return NULL;
    }

    // Cas où la liste est vide
    if (*liste == NULL)
    {
        *liste = nouveau_noeud;
        return nouveau_noeud;
    }

    // Parcours jusqu'au dernier élément
    t_liste* courant = *liste;
    while (courant->suivant != NULL)
    {
        courant = courant->suivant;
    }

    // Ajout du nouveau nœud à la fin
    courant->suivant = nouveau_noeud;
    nouveau_noeud->precedent = courant;

    return nouveau_noeud;
}


int reinit_liste_poisson(t_liste** liste, int n, t_ocean ocean)
{
    if (*liste != NULL)
    {
        libererListe(*liste);
        *liste = NULL;
    }

    // Initialisation du générateur aléatoire
    srand((unsigned int)time(NULL));


    int positions[HAUTEUR][LARGEUR] = {0};

    t_liste* dernier = NULL;

    for (int i = 0; i < n; i++)
    {
        int posx, posy;
        int essais = 0;

        do {
            posx = rand() % LARGEUR;
            posy = rand() % HAUTEUR;
            essais++;
            // On vérifie à la fois que la position n’a pas déjà été prise
            // et que la case dans l'océan est VIDE
        } while ((positions[posy][posx] || ocean[posy][posx].contenu != VIDE) && essais < MAX_ESSAIS);

        // Si on dépasse un nombre d'essais raisonnable, on arrête
        if (essais >= MAX_ESSAIS)
        {
            printf("Erreur : impossible de placer tous les poissons, trop peu de cases vides.\n");
            libererListe(*liste);
//*liste = NULL;
            return 0;
        }

        positions[posy][posx] = 1; // Marquer comme prise

        t_animal animal = {
                .age = rand() % (MAX_AGE_POISSON + 1),
                .jrs_gest = NB_JRS_GEST_POISSON,
                .energie_sante = ENERGIE_INIT_POISSON,
                .posx = posx,
                .posy = posy
        };

        t_liste* nouveau = creer_noeud(animal);
        if (nouveau == NULL)
        {
            libererListe(*liste);
            *liste = NULL;
            return 0;
        }

        // Placer le poisson dans l'océan
        ocean[posy][posx].contenu = POISSON;
        ocean[posy][posx].animal = nouveau;

        if (*liste == NULL)
        {
            *liste = nouveau;
            dernier = nouveau;
        }
        else
        {
            dernier->suivant = nouveau;
            nouveau->precedent = dernier;
            dernier = nouveau;
        }
    }

    return 1;
}


int reinit_liste_requin(t_liste** liste, int n, t_ocean ocean)
{
    if (*liste != NULL)
    {
        libererListe(*liste);
        *liste = NULL;
    }

    // Initialisation du générateur aléatoire
    srand((unsigned int)time(NULL));


    int positions[HAUTEUR][LARGEUR] = {0};

    t_liste* dernier = NULL;

    for (int i = 0; i < n; i++)
    {
        int posx, posy;
        int essais = 0;
        const int MAX_ESSAIS = 1000;

        do {
            posx = rand() % LARGEUR;
            posy = rand() % HAUTEUR;
            essais++;
            // On vérifie à la fois que la position n’a pas déjà été prise
            // et que la case dans l'océan est VIDE
        } while ((positions[posy][posx] || ocean[posy][posx].contenu != VIDE) && essais < MAX_ESSAIS);

        // Si on dépasse un nombre d'essais raisonnable, on arrête
        if (essais >= MAX_ESSAIS)
        {
            printf("Erreur : impossible de placer tous les poissons, trop peu de cases vides.\n");
            libererListe(*liste);
            *liste = NULL;
            return 0;
        }

        positions[posy][posx] = 1; // Marquer comme prise

        t_animal animal = {
                .age = rand() % (MAX_AGE_REQUIN + 1),
                .jrs_gest = (animal.age >= NB_JRS_PUB_REQUIN) ? (rand() % NB_JRS_GEST_REQUIN + 1) : 0,
                .energie_sante = (rand() % (ENERGIE_DIGESTION + ENERGIE_DIGESTION)) + 1,
                .posx = posx,
                .posy = posy
        };

        t_liste* nouveau = creer_noeud(animal);
        if (nouveau == NULL)
        {
            libererListe(*liste);
            *liste = NULL;
            return 0;
        }

        // Placer le poisson dans l'océan
        ocean[posy][posx].contenu = REQUIN;
        ocean[posy][posx].animal = nouveau;

        if (*liste == NULL)
        {
            *liste = nouveau;
            dernier = nouveau;
        }
        else
        {
            dernier->suivant = nouveau;
            nouveau->precedent = dernier;
            dernier = nouveau;
        }
    }

    return 1;
}
