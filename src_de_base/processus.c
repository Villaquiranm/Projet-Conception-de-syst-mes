#include <cpu.h>
#include <inttypes.h>
#include "ecran.h"
#include "interruption.h"
#include <segment.h>
#include <string.h>
enum etat{ELU,PRETE};
struct reg_type{
    int32_t ebx;
    uint32_t esp;
    int32_t ebp;
    int32_t esi;
    int32_t edi;
};
struct processus {
    int32_t pid;
    char nom[15];
    enum etat etat; //0 élu ; 1 Activable
    struct reg_type zone;
    uint32_t pile[512];
};
void idle(void){
    printf("[idle] je tente de passer la main a proc1...");
//    ctx_sw(,);
}
void proc1(void){
    printf("[proc1] idle m'a donne la main \n");
    printf("[proc1] j'arrete le systeme]\n");
    hlt();  
       
}
void init(){
    struct processus t_Processus[2];
    sprintf(t_Processus[0].nom,"Idle");
    sprintf(t_Processus[1].nom,"proc1");
    t_Processus[0].pid=0;
    t_Processus[1].pid=1;
    t_Processus[0].etat=ELU;
    t_Processus[1].etat=PRETE;
    t_Processus[1].zone.esp=(uint32_t)(&t_Processus[1].pile[511]);
    t_Processus[1].pile[511]=(uint32_t)(&proc1);   
}

