// requin.cpp
//
// // implementation des fonctions pour la gestion des requins dans l'ocean
//
#include "main.h"

int initialise_requin(t_liste_requin** tete_requin, t_ocean* ocean, int quantite) {
    // Verification des entrees
    if (quantite < 0) return 0;
    if (quantite == 0) return 1;  // Rien a faire
#ifdef DEBUG
    printf("Debut initialisation de %d requins...\n", quantite);
#endif
    t_animal requin;
    int requins_places = 0;

    for (int i = 0; i < quantite; i++)
    {
        // Initialisation des proprietes du requin
        requin.age = alea(0, MAX_AGE_REQUIN);
        requin.energie_sante = alea(1, ENERGIE_DIGESTION * 2);
        requin.jrs_gest = (requin.age >= NB_JRS_PUB_REQUIN) ? (alea(1, NB_JRS_GEST_REQUIN)) : 0;

        // Recherche d'une position vide
        int essais = 0;
        int position_trouvee = 0;

        while (essais < MAX_ESSAIS && !position_trouvee)
        {
            requin.posx = alea(0, LARGEUR - 1);
            requin.posy = alea(0, HAUTEUR - 1);

            if ((*ocean)[requin.posy][requin.posx].contenu == VIDE)
            {
                position_trouvee = 1;
            }
            essais++;
        }

        // Si pas de position vide trouvee
        if (!position_trouvee)
        {
            #ifdef DEBUG
            printf("Attention : seulement %d/%d requins places\n", requins_places, quantite);
            #endif
            return (requins_places > 0) ? 1 : 0;
        }

        // Placement du requin
        (*ocean)[requin.posy][requin.posx].contenu = REQUIN;
        t_liste_requin* nouveau = insererEnTete(tete_requin, requin);
        if (nouveau == NULL)
        {
            #ifdef DEBUG
            printf("Erreur memoire !\n");
            #endif
            return (requins_places > 0) ? 1 : 0;
        }

        (*ocean)[requin.posy][requin.posx].animal = nouveau;
        requins_places++;
    }
    #ifdef DEBUG
    printf("%d requins initialises avec succes\n", requins_places);
    #endif
    return 1;
}

int deplacer_requin_1_case(t_noeud* requin, t_ocean* ocean) {
    int posx_temp = requin->animal.posx;
    int posy_temp = requin->animal.posy;
    int nouvelle_posx, nouvelle_posy;

    // Choix aleatoire d'une case voisine
    if (!choix_aleatoire_case_voisine_libre(posx_temp, posy_temp, ocean, &nouvelle_posx, &nouvelle_posy))
    {
        return 0; // Echec
    }

    // Mise a jour de la grille
    if (!inserer_contenu_pointeur_case_grille(nouvelle_posx, nouvelle_posy, ocean, REQUIN, &(requin->animal)))
    {
        return 0; // Echec
    }

    // Mise a jour des coordonnees
    requin->animal.posx = nouvelle_posx;
    requin->animal.posy = nouvelle_posy;

    // Nettoyage ancienne position
    if (!effacer_contenu_case_grille(posx_temp, posy_temp, ocean))
    {
        // Si echec, annuler deplacement
        effacer_contenu_case_grille(nouvelle_posx, nouvelle_posy, ocean);
        requin->animal.posx = posx_temp;
        requin->animal.posy = posy_temp;
        return 0;
    }

    return 1; // Succes
}

int compter_requins(t_liste_requin* liste) {
    int nb_requin = 0;
    t_liste_requin* courant = liste;

    // Parcours de toute la liste
    while (courant != NULL)
    {
        nb_requin++;
        courant = courant->suivant;
    }

    return nb_requin;
}

int nouveau_requin(t_liste_requin** liste, t_animal* parent, t_ocean* ocean) {
    // Recherche d'une case voisine libre
    int new_x, new_y;
    if (choix_aleatoire_case_voisine_libre(parent->posx, parent->posy, ocean, &new_x, &new_y) == -1)
    {
        return 0; // Aucune case libre
    }

    // Creation du bebe-requin
    t_animal bebe = {
            .posx = new_x,
            .posy = new_y,
            .age = 0,
            .energie_sante = ENERGIE_DIGESTION, // energie specifique au requin
            .jrs_gest = 0
    };

    // Ajout du bebe a la liste des requins
    t_liste_requin* nouveau = insererEnTete(liste, bebe);
    if (!nouveau ||
        !inserer_contenu_pointeur_case_grille(new_x, new_y, ocean, REQUIN, &(nouveau->animal)))
    {
        if (nouveau) supprimerAnimal((t_noeud**)liste, (t_noeud*)nouveau);
        return 0;
    }

    // Mise a jour du parent apres reproduction
    reset_gestation(parent, -NB_JRS_GEST_REQUIN); // Reinitialisation de la gestation requin
    dec_energie(parent); // Le parent perd de l'energie apres reproduction

    return 1;
}

int deplacer_tout_les_requins (t_liste_requin** liste, t_ocean* ocean) {
    // Verification des parametres
    if (liste == NULL || ocean == NULL)
    {
        #ifdef DEBUG
        fprintf(stderr, "Parametres invalides\n");
        #endif
        return 0;
    }
    t_liste_requin* courant = *liste;
    // Parcours de toute la liste
    while (courant != NULL)
    {
        deplacer_requin_1_case(courant, ocean);
        courant = courant->suivant;
    }
    return 1;
}

int mort_requin(t_liste_requin** liste, t_ocean* ocean) {
    // Verification des parametres
    if (liste == NULL || *liste == NULL || ocean == NULL)
    {
        #ifdef DEBUG
        fprintf(stderr, "Parametres invalides\n");
        #endif
        return 0;
    }

    t_liste* courant = *liste;

    // Recuperation des coordonnees du requin
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
