/**
 * @ Author: Ilyes Gharmoul
 * @ Create Time: 2025-02-18 19:04:25
 * @ Modified by: Your name
 * @ Modified time: 2025-03-13 16:38:34
 * @ Description: idk
 */

#ifndef MAIN_H
#define MAIN_H
/********************************  <   PARAMETRES  >    ********************************/
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>

#include "userinput.h"

int main();
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
#endif

#endif