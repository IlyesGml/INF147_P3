/*
 * Fichier: userinput.c
 * Auteur: Ilyes Gharmoul
 * Date: 2025-02-27
 * Description: Ce fichier contient des fonctions pour gérer les entrées utilisateur.
 * Version: 1.0
 * Touches fléchées et Échap
 * Fonction SaisieDirection() qui retourne une direction selon la touche pressée.
 *      Retourne 0 si aucune touche fléchée pressée.
 *      Retourne TOUCHE_ESC si la touche Échap est pressée.
 */

#include "main.h"

// Prototypes de fonctions
int SaisieDirection()
{
    int touche = _getch();
    if (touche == 27)
    { // Touche Échap
        return TOUCHE_ESC;
    }
    if (touche == 'y' || touche == 'Y')
    { // Touche Y
        return TOUCHE_Y;
    }
    if (touche == 'n' || touche == 'N')
    { // Touche N
        return TOUCHE_N;
    }
    if (touche == 0 || touche == 224)
    { // les touches fléchées ont deux parties
        switch (_getch())
        {
        case 72:
            return FLECHE_HAUT;
        case 80:
            return FLECHE_BAS;
        case 77:
            return FLECHE_DROITE;
        case 75:
            return FLECHE_GAUCHE;
        }
    }
    return 0; // Aucune touche fl�ch�e ou chiffre press�
}
int nombre_saisi()
{
    int nb = 0;
    char c;
    while (c != '\r')
    {
        c = _getch();
        if (c >= '0' && c <= '9')            
            nb = nb * 10 + (c - '0');          
    } 
    return nb;
}
