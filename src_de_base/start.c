#include <cpu.h>
#include <inttypes.h>
#include "ecran.h"
#include "interruption.h"
#include <segment.h>
#include "processus.h"

// on peut s'entrainer a utiliser GDB avec ce code de base
// par exemple afficher les valeurs de x, n et res avec la commande display

// une fonction bien connue


void kernel_start(void)
{
    efface_ecran();
    //defilement();

    init();
    frequence();
    horloge();
    init_traitant_IT(32,traitant_IT_32);
    idle();
    //sti();
    //hlt();


    // quand on saura gerer l'ecran, on pourra afficher x
    // on ne doit jamais sortir de kernel_start
    while (1) {
        // cette fonction arrete le processeur
        hlt();
    }
}
