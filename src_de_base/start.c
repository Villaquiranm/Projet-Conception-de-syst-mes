#include <cpu.h>
#include <inttypes.h>
#include "ecran.h"
// on peut s'entrainer a utiliser GDB avec ce code de base
// par exemple afficher les valeurs de x, n et res avec la commande display

// une fonction bien connue
uint32_t fact(uint32_t n)
{
    uint32_t res;
    if (n <= 1) {
        res = 1;
    } else {
        res = fact(n - 1) * n;
    }
    return res;
}

void kernel_start(void)
{
    // quand on saura gerer l'ecran, on pourra afficher x
    ecrit_car(5,2,'g');
    efface_ecran();
    place_curseur(0,0);
    // on ne doit jamais sortir de kernel_start
    while (1) {
        // cette fonction arrete le processeur
        hlt();
    }
}

