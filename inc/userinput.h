/**
 * @file userinput.h
 * @brief Définition des types et des fonctions pour la saisie utilisateur
 * @author Ilyes Gharmoul
 * @version 1.0
 * @date 2025-02-18
 */
#ifndef USERINPUT_H
#define USERINPUT_H

// Déclarations des fonctions et des variables globales
int SaisieDirection();
int nombre_saisi();
typedef enum {
    NULLE_INPUT = -1,
    FLECHE_HAUT,
    FLECHE_GAUCHE,
    FLECHE_BAS,
    FLECHE_DROITE,
    TOUCHE_ESC,
    TOUCHE_Y,
    TOUCHE_N
} Une_Direction;

#endif // USERINPUT_H
