/**
 * @file main.c
 * @brief
 * @date 2025-04-01
 * @version 1.0
 */

#include "main.h"

#ifdef DEBUG
int main_debug()
{
    return 0;
}
int main_init(void)
{
    srand(time(NULL));
    return 0;
}
#elif TP3
int main_init(void)
{
    srand(time(NULL));
    return 0;
}
#endif

int main()
{
    main_init();
#ifdef DEBUG
    printf("Debug version\n");
    return main_debug();
#elif defined TP3
    printf("TP3 version\n");
    return 0

#else
    printf("No configuration defined!\n");
    return 1; // Error code
#endif
}
