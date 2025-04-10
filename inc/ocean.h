#ifndef OCEAN_H
#define OCEAN_H
//
// Created by afifa on 2025-04-04.
//
#define HAUTEUR   60
#define LARGEUR  120
#define MAX_ESSAIS LARGEUR* HAUTEUR

/* Type énuméré pour les 8 directions de déplacement */
typedef enum {HAUT, HAUT_DR, DROITE, BAS_DR, BAS, BAS_G, GAUCHE, HAUT_G} t_direction;

/* Type énuméré pour le contenu d'une case */
typedef enum {VIDE, POISSON, REQUIN} t_contenu;

/* Type structure pour le contenu d'une case de la grille */
typedef struct {
    t_contenu contenu; //Soit: VIDE, POISSON ou REQUIN
    void *animal; //Pointeur générique à un animal à cette case, sinon NULL
} t_case;

/* Type-tableau de la grille de l'océan (taille : 60 X 120) */
typedef t_case t_ocean[HAUTEUR][LARGEUR];
/**
 * @brief Initializes all cells of the ocean grid to the state VIDE with a NULL animal pointer.
 * 
 * @param ocean Pointer to the ocean grid to be cleared.
 * 
 * This function iterates through the entire 2D grid (HAUTEUR x LARGEUR) and resets each cell.
 * It ensures that all cells are in a known state before any simulation begins.
 */
void vider_ocean(t_ocean *ocean);

/**
 * @brief Retrieves the animal pointer stored in a specific cell of the grid.
 * 
 * @param posx X-coordinate (column) in the grid.
 * @param posy Y-coordinate (row) in the grid.
 * @param ocean Pointer to the ocean grid.
 * @return void* Pointer to the animal in the specified cell, or NULL if the coordinates are invalid.
 * 
 * This function checks if the given coordinates are within bounds and returns the animal pointer
 * if the cell exists. If the coordinates are invalid, it returns NULL.
 */
void* obtenir_reference_case_grille(int posx, int posy, t_ocean *ocean);

/**
 * @brief Inserts a new content and an animal pointer into a specific cell of the grid.
 * 
 * @param posx X-coordinate (column) in the grid.
 * @param posy Y-coordinate (row) in the grid.
 * @param ocean Pointer to the ocean grid.
 * @param contenu New content to insert (VIDE, POISSON, or REQUIN).
 * @param animal Pointer to the animal to associate with this cell.
 * @return int 1 if the insertion is successful, 0 if a validation fails.
 * 
 * This function validates the coordinates, content, and pointer consistency before modifying the cell.
 * It ensures data integrity by checking that the content and pointer are coherent.
 */
int inserer_contenu_pointeur_case_grille(int posx, int posy, t_ocean *ocean,
                                         t_contenu contenu, void *animal);

/**
 * @brief Resets a specific cell of the grid to the state VIDE with a NULL animal pointer.
 * 
 * @param posx X-coordinate (column) in the grid.
 * @param posy Y-coordinate (row) in the grid.
 * @param ocean Pointer to the ocean grid.
 * @return int 1 if the reset is successful, 0 if the coordinates are invalid.
 * 
 * This function ensures that the specified cell is in a known state after being cleared.
 * It does not free the memory of the animal, only sets the pointer to NULL.
 */
int effacer_contenu_case_grille(int posx, int posy, t_ocean *ocean);

/**
 * @brief Counts the number of empty cells around a given position in the grid.
 * 
 * @param posx Central X-coordinate (column).
 * @param posy Central Y-coordinate (row).
 * @param ocean Pointer to the ocean grid.
 * @return int Number of empty neighboring cells (0 to 8), or -1 if the central coordinates are invalid.
 * 
 * This function checks the 8 adjacent cells (up, down, left, right, and diagonals) and counts how many
 * are in the state VIDE. It excludes cells outside the grid boundaries.
 */
int nombre_case_voisine_libre(int posx, int posy, t_ocean *ocean);

/**
 * @brief Selects a random empty neighboring cell and returns the direction and new coordinates.
 * 
 * @param posx Starting X-coordinate (column).
 * @param posy Starting Y-coordinate (row).
 * @param ocean Pointer to the ocean grid.
 * @param newx Pointer to store the new X-coordinate.
 * @param newy Pointer to store the new Y-coordinate.
 * @return t_direction Direction chosen (enum t_direction), or 0 if no valid direction exists.
 * 
 * This function identifies all valid empty neighboring cells, selects one randomly, and updates
 * the new coordinates. If no empty cells are found, it returns the original coordinates and direction 0.
 */
t_direction choix_aleatoire_case_voisine_libre(int posx, int posy, t_ocean *ocean, int *newx, int *newy);

/**
 * @brief Displays the current state of the ocean grid graphically.
 * 
 * @param ocean Pointer to the ocean grid to display.
 * @param temps Current simulation cycle number to display.
 * @return int Always returns 1 (success).
 * 
 * This function uses graphical utilities to render the ocean grid. It displays cells with different
 * colors based on their content (e.g., blue for POISSON, red for REQUIN, black for VIDE) and shows
 * the current simulation time and counts of predators and prey.
 */
int dessiner_ocean(t_ocean *ocean, int temps);
#endif