// poisson.cpp
//
// // Implementation des fonctions pour la gestion des poissons dans l'ocean
//
#include "main.h"

int initialise_poisson(t_liste_poisson** tete_poisson, t_ocean* ocean, int quantite) {
    // Verification des entrees
    if ((quantite <= 0)||(quantite > MAX_POISSON)) return 0;
#ifdef DEBUG
    printf("Debut initialisation de %d poissons...\n", quantite);
#endif
    t_animal poisson;
    int poissons_places = 0;

    for (int i = 0; i < quantite; i++)
    {
        poisson.age = alea(0, MAX_AGE_POISSON);
        poisson.energie_sante = alea(1, ENERGIE_INIT_POISSON);
        poisson.jrs_gest = 0;
        int essais = 0;
        int position_trouvee = 0;

        while (essais < MAX_ESSAIS && !position_trouvee)
        {
            poisson.posx = alea(0, LARGEUR - 1);
            poisson.posy = alea(0, HAUTEUR - 1);
            if ((*ocean)[poisson.posy][poisson.posx].contenu == VIDE)
                position_trouvee = 1;
            essais++;
        }
        if (!position_trouvee)
        {
            #ifdef DEBUG
            printf("Attention : seulement %d/%d poissons places\n", poissons_places, quantite);
            #endif
            return (poissons_places > 0) ? 1 : 0;
        }
        // Placement du poisson
        (*ocean)[poisson.posy][poisson.posx].contenu = POISSON;
        t_liste_poisson* nouveau = insererEnTete(tete_poisson, poisson);
        if (nouveau == NULL)
        {
            #ifdef DEBUG
            printf("Erreur memoire !\n");
            #endif
            return (poissons_places > 0) ? 1 : 0;
        }
        (*ocean)[poisson.posy][poisson.posx].animal = nouveau;
        poissons_places++;
    }
    #ifdef DEBUG
    printf("%d poissons initialises avec succes\n", poissons_places);
    #endif
    return 1;
}

int deplacer_poisson_1_case(t_noeud* poisson, t_ocean* ocean) {
    int posx_temp = poisson->animal.posx;
    int posy_temp = poisson->animal.posy;
    int nouvelle_posx, nouvelle_posy;
    t_direction dir;
    int tentatives = 0;
    const int MAX_TENTATIVES = 8;
    do
    {
        // Choix aleatoire d'une case voisine
        dir = choix_aleatoire_case_voisine_libre(posx_temp, posy_temp, ocean, &nouvelle_posx, &nouvelle_posy);
        tentatives++;

        // Gestion du "wrap-around" horizontal
        if (nouvelle_posx < 0)
            nouvelle_posx = LARGEUR - 1;
        else if (nouvelle_posx >= LARGEUR)
            nouvelle_posx = 0;

        // Verifier si la case est valide et vide
        if (nouvelle_posy >= 0 && nouvelle_posy < HAUTEUR &&
            (*ocean)[nouvelle_posy][nouvelle_posx].contenu == VIDE)
        {
            break;
        }

        // Condition de sortie si trop de tentatives
        if (tentatives >= MAX_TENTATIVES)
        {
            return 0; // Echec
        }

    } while (1);

    // Mise a jour de la grille
    if (!inserer_contenu_pointeur_case_grille(nouvelle_posx, nouvelle_posy, ocean, POISSON, &(poisson->animal)))
    {
        return 0;
    }

    // Mise a jour des coordonnees
    poisson->animal.posx = nouvelle_posx;
    poisson->animal.posy = nouvelle_posy;

    // Nettoyage ancienne position
    if (!effacer_contenu_case_grille(posx_temp, posy_temp, ocean))
    {
        // Si d'echec, annuler deplacement
        effacer_contenu_case_grille(nouvelle_posx, nouvelle_posy, ocean);
        poisson->animal.posx = posx_temp;
        poisson->animal.posy = posy_temp;
        return 0;
    }

    return 1;
}

int deplacer_tout_les_poissons (t_liste_poisson** liste, t_ocean* ocean) {
    // Verification des parametres
    if (liste == NULL || ocean == NULL)
    {
        #ifdef DEBUG
        fprintf(stderr, "Parametres invalides\n");
        #endif
        return 0;
    }
    t_liste_poisson* courant = *liste;
    // Parcours de toute la liste
    while (courant != NULL)
    {
        if (deplacer_poisson_1_case(courant, ocean))
        courant = courant->suivant;
    }
    return 1;
}

int compter_poissons(t_liste_poisson* liste) {
    int nb_poisson = 0;
    t_liste_requin* courant = liste;

    // Parcours de toute la liste
    while (courant != NULL)
    {
        nb_poisson++;
        courant = courant->suivant;
    }

    return nb_poisson;
}

int nouveau_poisson(t_liste_poisson** liste, t_animal* parent, t_ocean* ocean) {
    // Verification capacite maximale
    if (compter_poissons(*liste) >= MAX_POISSON)
    {
        reset_gestation(parent, -NB_JRS_GEST_POISSON);
        return 0;
    }
    // Recherche case libre
    int new_x, new_y;
    if (choix_aleatoire_case_voisine_libre(parent->posx, parent->posy, ocean, &new_x, &new_y) == -1)
    {
        reset_gestation(parent, -NB_JRS_GEST_POISSON);
        return 0;
    }

    // Probabilite 33% de fausse couche
    if (alea(1, 3) == 1)
    {
        reset_gestation(parent, -NB_JRS_GEST_POISSON);
        return 0;
    }

    // Creation bebe
    t_animal bebe = {
            .posx = new_x,
            .posy = new_y,
            .age = 0,
            .energie_sante = ENERGIE_INIT_POISSON,
            .jrs_gest = 0
    };

    // Ajout a la liste
    t_liste_poisson* nouveau = insererEnTete(liste, bebe);
    if (!nouveau ||
        !inserer_contenu_pointeur_case_grille(new_x, new_y, ocean, POISSON, &(nouveau->animal)))
    {
        if (nouveau) supprimerAnimal((t_noeud**)liste, (t_noeud*)nouveau);
        return 0;
    }

    // Mise a jour parent
    reset_gestation(parent, -NB_JRS_GEST_POISSON);
    dec_energie(parent);

    return 1;
}

int mort_poisson(t_liste_poisson** liste, t_ocean* ocean) {
    // Verification des parametres
    if (liste == NULL || *liste == NULL || ocean == NULL)
    {
        #ifdef DEBUG
        fprintf(stderr, "Parametres invalides\n");
        #endif
        return 0;
    }

    t_liste* courant = *liste;

    // Recuperation des coordonnees du poisson
    int posx = courant->animal.posx;
    int posy = courant->animal.posy;

    // Verification des coordonnees
    if (posx < 0 || posx >= LARGEUR || posy < 0 || posy >= HAUTEUR)
    {
        #ifdef DEBUG
        fprintf(stderr, "Coordonnees invalides (%d,%d)\n", posx, posy);
        #endif
        return 0;
    }

    // Suppression de la tete
    *liste = courant->suivant;

    // Nettoyage de la case dans l'ocean
    (*ocean)[posy][posx].contenu = VIDE;
    (*ocean)[posy][posx].animal = NULL;

    // Liberation memoire
    free(courant);

    return 1;
}
