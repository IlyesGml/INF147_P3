//
// Created by afifa on 2025-04-04.
//

#ifndef INF147LAB3_OCEAN_H
#define INF147LAB3_OCEAN_H

#define HAUTEUR   60
#define LARGEUR  120

/* Type énuméré pour les 8 directions de déplacement */
typedef enum {IMPOSSIBLE=-1, HAUT, HAUT_DR, DROITE, BAS_DR, BAS, BAS_G, GAUCHE, HAUT_G} t_direction;

/* Type énuméré pour le contenu d'une case */
typedef enum {VIDE, POISSON, REQUIN} t_contenu;

/* Type structure pour le contenu d'une case de la grille */
typedef struct {
    t_contenu contenu; //Soit: VIDE, POISSON ou REQUIN
    void *animal; //Pointeur générique à un animal à cette case, sinon NULL
} t_case;

/* Type-tableau de la grille de l'océan (taille : 60 X 120) */
typedef t_case t_ocean[HAUTEUR][LARGEUR];

/*-----------------------------------------------------------------------
1--     Fonction vider_ocean
-----------------------------------------------------------------------

Description :
            Cette fonction initialise toutes les cases de l'océan à l'état VIDE
            avec un pointeur animal NULL. Elle parcourt l'intégralité de la grille
            en deux dimensions (HAUTEUR x LARGEUR) et réinitialise chaque case.

            Le processus suit ces étapes :
              1. Parcours de chaque ligne (de 0 à HAUTEUR-1)
              2. Pour chaque ligne, parcours de chaque colonne (de 0 à LARGEUR-1)
              3. Pour chaque case :
                  - Met le contenu à VIDE
                  - Met le pointeur animal à NULL

Paramètres d'entrée :
            - ocean : Pointeur vers la grille de l'océan à vider

Paramètres de sortie :
            Aucun retour. La grille est modifiée directement.

Remarques importantes :
            - Cette fonction doit être appelée avant toute initialisation de simulation
            - Elle garantit que toutes les cases sont dans un état connu avant utilisation

Exemple d'utilisation :
            t_ocean mon_ocean;
            vider_ocean(&mon_ocean);

            // Toutes les cases de mon_ocean sont maintenant VIDE avec animal=NULL
*/

void vider_ocean(t_ocean *ocean);

/*-----------------------------------------------------------------------
2--     Fonction obtenir_reference_case_grille
-----------------------------------------------------------------------

Description :
            Cette fonction retourne le pointeur animal stocké dans une case spécifique
            de la grille, après avoir vérifié que les coordonnées sont valides.

            Le processus suit ces étapes :
              1. Vérification que les coordonnées (posx, posy) sont dans les limites
              2. Retour du pointeur animal si les coordonnées sont valides
              3. Retour de NULL si les coordonnées sont invalides

Paramètres d'entrée :
            - posx : Position en x (colonne) dans la grille
            - posy : Position en y (ligne) dans la grille
            - ocean : Pointeur vers la grille de l'océan

Paramètres de sortie :
            - Retourne le pointeur animal si la case existe
            - Retourne NULL si les coordonnées sont invalides

Exemple de comportement :
            - Pour posx=10, posy=20 : retourne l'animal présent à ces coordonnées
            - Pour posx=-1, posy=0 : retourne NULL (hors limites)

Remarques importantes :
            - Ne vérifie pas si le pointeur animal est valide, seulement son existence

Exemple d'utilisation :
                t_animal* ref = (t_animal*)obtenir_reference_case_grille(10, 10, &ocean);

*/

void* obtenir_reference_case_grille(int posx, int posy, t_ocean *ocean);

/*-----------------------------------------------------------------------
3--     Fonction inserer_contenu_pointeur_case_grille
-----------------------------------------------------------------------

Description :
            Cette fonction insère un nouveau contenu et un pointeur animal dans une
            case spécifique de la grille, après avoir effectué plusieurs validations.

            Le processus suit ces étapes :
              1. Vérification que les coordonnées sont dans les limites
              2. Validation que le contenu est soit VIDE, POISSON ou REQUIN
              3. Vérification de la cohérence entre le contenu et le pointeur animal
              4. Modification de la case si toutes les validations passent

Paramètres d'entrée :
            - posx : Position en x (colonne) dans la grille
            - posy : Position en y (ligne) dans la grille
            - ocean : Pointeur vers la grille de l'océan
            - contenu : Nouveau contenu à insérer (VIDE, POISSON ou REQUIN)
            - animal : Pointeur vers l'animal à associer à cette case

Paramètres de sortie :
            - Retourne 1 si l'insertion a réussi
            - Retourne 0 si une validation a échoué

Exemple de comportement :
            - Pour contenu=POISSON et animal=ptr_valide : retourne 1 (succès)
            - Pour contenu=VIDE et animal=ptr_valide : retourne 0 (incohérence)

Remarques importantes :
            - La fonction garantit l'intégrité des données avant modification
            - Ne copie pas l'animal, seulement stocke le pointeur

Exemple d'utilisation :
           // Déclaration d'une variable océan
            t_ocean ocean;

            // Initialisation manuelle d'un requin
            t_case case_requin = {
                .contenu = REQUIN,    // Utilisation directe de l'enum
                .animal = NULL        // Pas d'allocation, on utilise NULL
            };

            // Insertion dans la grille
            if (inserer_contenu_pointeur_case_grille(15, 20, &ocean, case_requin.contenu, case_requin.animal)) {
                printf("Requin inséré à (15,20)\n");
            } else {
                printf("Échec d'insertion\n");
            }
*/

int inserer_contenu_pointeur_case_grille(int posx, int posy, t_ocean *ocean,
                                         t_contenu contenu, void *animal);

/*-----------------------------------------------------------------------
4--     Fonction effacer_contenu_case_grille
-----------------------------------------------------------------------

Description :
            Cette fonction réinitialise une case spécifique de la grille à l'état VIDE
            avec un pointeur animal NULL, après avoir vérifié que les coordonnées sont valides.

            Le processus suit ces étapes :
              1. Vérification que les coordonnées (posx, posy) sont dans les limites
              2. Réinitialisation du contenu à VIDE
              3. Mise à NULL du pointeur animal

Paramètres d'entrée :
            - posx : Position en x (colonne) dans la grille
            - posy : Position en y (ligne) dans la grille
            - ocean : Pointeur vers la grille de l'océan

Paramètres de sortie :
            - Retourne 1 si l'effacement a réussi
            - Retourne 0 si les coordonnées sont invalides

Remarques importantes :
            - Garantit que la case est dans un état connu après appel
            - Ne libère pas la mémoire de l'animal, seulement met le pointeur à NULL

Exemple d'utilisation :
            if (effacer_contenu_case_grille(10, 10, &ocean))
            {
                printf("Case (10,10) effacée\n");
            } else
            {
                printf("Coordonnées invalides\n");
            }
            // La case à (10,10) est maintenant VIDE avec animal=NULL
*/

int effacer_contenu_case_grille(int posx, int posy, t_ocean *ocean);

/*-----------------------------------------------------------------------
5--     Fonction nombre_case_voisine_libre
-----------------------------------------------------------------------

Description :
            Cette fonction compte le nombre de cases vides autour d'une position donnée
            en vérifiant les 8 cases adjacentes (haut, bas, gauche, droite et 4 diagonales).

            Le processus suit ces étapes :
              1. Vérification que les coordonnées centrales sont valides
              2. Pour chaque direction possible :
                  - Calcul des nouvelles coordonnées
                  - Vérification qu'elles sont dans les limites
                  - Incrémentation du compteur si la case est VIDE
              3. Retour du nombre total de cases vides trouvées

Paramètres d'entrée :
            - posx : Position centrale en x (colonne)
            - posy : Position centrale en y (ligne)
            - ocean : Pointeur vers la grille de l'océan

Paramètres de sortie :
            - Retourne le nombre de cases vides adjacentes (0 à 8)
            - Retourne -1 si les coordonnées centrales sont invalides

Exemple de comportement :
            - Pour une case entourée de 3 cases vides : retourne 3
            - Pour une case en bordure de grille : retourne moins de 8

Remarques importantes :
            - N'inclut pas la case centrale dans le décompte
            - Les cases hors limites ne sont pas considérées comme vides

Exemple d'utilisation :
            int cases_libres = nombre_case_voisine_libre(30, 30, &ocean);
            if (cases_libres >= 0)
            {
                printf("Nombre de cases voisines libres: %d\n", cases_libres);
            } else
            {
                printf("Position invalide\n");
            }
*/

int nombre_case_voisine_libre(int posx, int posy, t_ocean *ocean);

/*-----------------------------------------------------------------------
6--     Fonction choix_aleatoire_case_voisine_libre
-----------------------------------------------------------------------

Description :
            Cette fonction sélectionne aléatoirement une case vide parmi les cases
            adjacentes à une position donnée, et retourne la direction choisie ainsi
            que les nouvelles coordonnées.

            Le processus suit ces étapes :
              1. Définition des déplacements possibles pour chaque direction
              2. Collecte des directions valides (case dans les limites et VIDE)
              3. Si aucune direction valide :
                  - Retourne les coordonnées d'origine et direction 0
              4. Si directions valides :
                  - Choix aléatoire d'une direction
                  - Calcul des nouvelles coordonnées
                  - Retour de la direction et des nouvelles coordonnées

Paramètres d'entrée :
            - posx : Position de départ en x (colonne)
            - posy : Position de départ en y (ligne)
            - ocean : Pointeur vers la grille de l'océan
            - newx : Pointeur pour stocker la nouvelle position x
            - newy : Pointeur pour stocker la nouvelle position y

Paramètres de sortie :
            - Retourne la direction choisie (enum t_direction)
            - Modifie newx et newy avec les nouvelles coordonnées

Exemple de comportement :
            - Pour une case avec 3 voisins vides : choisit aléatoirement parmi eux
            - Pour une case sans voisins vides : retourne les mêmes coordonnées

Remarques importantes :
            - Utilise la fonction alea() pour le choix aléatoire
            - Les directions sont définies dans l'énumération t_direction

            Exemple d'utilisation :
            int newx, newy;
            t_direction dir = choix_aleatoire_case_voisine_libre(25, 25, &ocean, &newx, &newy);

            if (dir != 0 || (newx != 25 && newy != 25))
            {
                printf("Déplacement vers %d,%d direction %d\n", newx, newy, dir);
            } else
            {
                printf("Aucune case voisine libre\n");
            }

*/

t_direction choix_aleatoire_case_voisine_libre(int posx, int posy, t_ocean *ocean, int *newx, int *newy);

/*-----------------------------------------------------------------------
7--     Fonction dessiner_ocean
-----------------------------------------------------------------------

Description :
            Cette fonction affiche graphiquement l'état actuel de l'océan en utilisant
            les fonctions d'affichage du module utilitaire_affichage.

            Le processus suit ces étapes :
              1. Initialisation des compteurs de poissons et requins
              2. Effacement de la zone d'affichage
              3. Pour chaque case de la grille :
                  - Détermination de la couleur en fonction du contenu
                  - Incrémentation des compteurs si nécessaire
                  - Affichage de la case avec la couleur appropriée
              4. Affichage des informations (temps, nombre de proies/prédateurs)
              5. Pause courte pour la visualisation

Paramètres d'entrée :
            - ocean : Pointeur vers la grille de l'océan à afficher
            - temps : Numéro du cycle actuel à afficher

Paramètres de sortie :
            - Retourne toujours 1 (succès)

Exemple de comportement :
            - Les cases POISSON sont affichées en bleu
            - Les cases REQUIN sont affichées en rouge
            - Les cases VIDE sont affichées en noir

Remarques importantes :
            - Utilise les fonctions du module utilitaire_affichage
            - La pause de 10ms permet une visualisation fluide
            - Les couleurs sont définies par les constantes BLUE, RED, BLACK

Exemple d'utilisation :
            for (int cycle = 0; cycle < 100; cycle++)
            {
                // Simulation du cycle...
                dessiner_ocean(&ocean, cycle);
                // Pause pour visualisation
            }
            // Affiche l'océan avec les poissons (bleu) et requins (rouge)

*/

int dessiner_ocean(t_ocean *ocean, int temps);

#endif //INF147LAB3_OCEAN_H