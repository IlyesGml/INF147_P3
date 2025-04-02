#include "main.h"

// Initialisation de la liste vide
void init_liste(t_liste* l) {
    l->taille = 0;
}

// Insertion d'un �l�ment � une position donn�e
int inserer(t_liste* l, t_animal valeur, int position) {
    if (l->taille >= MAX || position < 0 || position > l->taille) {
        printf("Erreur : Position invalide ou liste pleine.\n");
        return 0;
    }

    // D�calage � droite des �l�ments pour ins�rer la nouvelle valeur
    for (int i = l->taille; i > position; i--) {
        l->animal[i] = l->animal[i - 1];
    }

    l->animal[position] = valeur;
    l->taille++;
    return 1;
}

// Suppression d'un �l�ment � une position donn�e
int supprimer(t_liste* l, int position) {
    if (position < 0 || position >= l->taille) {
        printf("Erreur : Position invalide.\n");
        return 0;
    }

    // D�calage � gauche des �l�ments pour combler le vide
    for (int i = position; i < l->taille - 1; i++) {
        l->animal[i] = l->animal[i + 1];
    }

    l->taille--;
    return 1;
}

// Obtention d'un �l�ment � une position donn�e
int obtenir(t_liste* l, int position, t_animal* valeur) {
    if (position < 0 || position >= l->taille) {
        printf("Erreur : Position invalide.\n");
        return 0;
    }
    *valeur = l->animal[position];
    return 1;
}

// D�calage � gauche � partir d'une position donn�e
void decalage_gauche(t_liste* l, int position) {
    if (position < 0 || position >= l->taille) {
        printf("Erreur : Position invalide.\n");
        return;
    }

    for (int i = position; i < l->taille - 1; i++) {
        l->animal[i] = l->animal[i + 1];
    }

    l->taille--;
}

// D�calage � droite � partir d'une position donn�e
void decalage_droite(t_liste* l, int position) {
    if (l->taille >= MAX || position < 0 || position > l->taille) {
        printf("Erreur : Position invalide ou liste pleine.\n");
        return;
    }

    for (int i = l->taille; i > position; i--) {
        l->animal[i] = l->animal[i - 1];
    }

    l->taille++;
}

// Affichage des �l�ments de la liste
void afficher_liste(const t_liste* l) {
    if (l->taille == 0) {
        printf("Liste vide.\n");
        return;
    }

    printf("Liste : ");
    for (int i = 0; i < l->taille; i++) {
        printf("%d ", l->animal[i]);
    }
    printf("\n");
}
