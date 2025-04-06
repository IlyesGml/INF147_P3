/**
 * @ Author: Ilyes Gharmoul
 * @ Create Time: 2025-02-18 19:04:25
 * @ Modified by: Your name
 * @ Modified time: 2025-04-06 19:11:48
 * @ Description: idk
 */

#ifndef MAIN_H
#define MAIN_H
/********************************  <   COMPILATEUR ET INCLUDE  >    ********************************/
#if !defined(VSCODE) && !defined(CLION) && !defined(VS_STUDIO)
#define VSCODE
#endif




#ifdef VSCODE
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#elif defined(CLION)
//insert your includes here >anthony


#elif defined(VS_STUDIO)
//insert your includes here >Sijam

#include <string.h>
#endif
#include "userinput.h"
#include "util.h"

#include "ocean.h"

#include "animal.h"
#include "liste.h"

#include "poisson.h"
#include "requin.h"



#include "utilitaire_affichage.h"
#include "winBGIm.h"

//int main();
int main_init(void);
/***********************  <   VERSION  >    ********************************/
#define DEBUG

#ifndef DEBUG
#define TP3
#endif
/****************************************************************************/
#ifdef DEBUG
/****************************  <   DEBUG  >    ************************************/
int main_debug(void); // fonction de test en mode débogage
#define TESTRANDOM
//#define TEST_INIT_POISSON // Test de la fonction d'initialisation des poissons
#define TEST_LISTE
#endif

#endif