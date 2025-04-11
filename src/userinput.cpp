/*
 * Fichier: userinput.c
 * Auteur: Ilyes Gharmoul
 * Date: 2025-02-27
 * Description: Ce fichier contient des fonctions pour geree les entrees utilisateur.
 * Version: 1.0
 * Touches flechees et ehap
 * Fonction SaisieDirection() qui retourne une direction selon la touche pressee.
 *      Retourne 0 si aucune touche flechees pressee.
 *      Retourne TOUCHE_ESC si la touche echap est pressee.
 */

#include "main.h"

// Prototypes de fonctions
int SaisieDirection()
{
    int touche = _getch();
    if (touche == 27)
    { // Touche echap
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
    { // les touches flechees ont deux parties
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

    return 0; // Aucune touche flechee ou chiffre presse
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
            printf("%c", c); // Affiche le chiffre saisi        
    } 
    return nb;
}