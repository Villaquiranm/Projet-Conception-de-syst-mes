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
    uint32_t lig=0;
    uint32_t col=0;
    ecrit_car(lig,col,'p');
    gerer_lig_col(1,&lig,&col);
    ecrit_car(lig,col,'u');
    gerer_lig_col(1,&lig,&col);
    ecrit_car(lig,col,'t');
    gerer_lig_col(1,&lig,&col);
    ecrit_car(lig,col,'a');
    gerer_lig_col(1,&lig,&col);
    ecrit_car(lig,col,'j');
    gerer_lig_col(1,&lig,&col);
    ecrit_car(lig,col,'o');
    gerer_lig_col(1,&lig,&col);
    ecrit_car(lig,col,'r');
    gerer_lig_col(1,&lig,&col);
    ecrit_car(lig,col,'j');
    gerer_lig_col(1,&lig,&col);
    ecrit_car(lig,col,'e');
    gerer_lig_col(1,&lig,&col);
    // on ne doit jamais sortir de kernel_start
    while (1) {
        // cette fonction arrete le processeur
        hlt();
    }
}

