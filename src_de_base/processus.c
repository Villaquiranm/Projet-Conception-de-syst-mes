#include <cpu.h>
#include <inttypes.h>
#include "ecran.h"
#include "interruption.h"
#include <segment.h>
#include <string.h>
extern void ctx_sw(int32_t *ancient,int32_t *nouveau);
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
int32_t actif=0;
int32_t avant=1;
#define _PROCESS 4

struct processus t_Processus[_PROCESS];
char *mon_nom(){
  return t_Processus[actif].nom;
}
uint32_t mon_pid(){
  return t_Processus[actif].pid;
}
void ordonnance(){
        printf("[%s] je donne la main pid=%i \n",mon_nom(),mon_pid());
        t_Processus[actif].etat=PRETE;
        t_Processus[actif+1].etat=ELU;
        if (actif==_PROCESS-1){
          actif=0;
          avant=_PROCESS-1;
        }else{
          avant=actif;
          actif++;

        }
        ctx_sw(&t_Processus[avant].zone.ebx,&t_Processus[actif].zone.ebx);

    }

void idle(void){
    for (int i=0;i<3;i++){
        /*printf("[idle] je tente de passer la main a proc1...\n");
        ctx_sw(&t_Processus[0].zone.ebx,&t_Processus[1].zone.ebx);
        printf("[idle] proc1 m'a redonne la main \n");*/
        ordonnance();
    }
    printf("[idle] je bloque le systeme\n");
    hlt();
}
void proc1(void){
    for(int i=0;i<3;i++){
        ordonnance();
    }
}
void proc2(void){
    for(int i=0;i<3;i++){
        ordonnance();
    }
}
void proc3(void){
    for(int i=0;i<3;i++){
        ordonnance();
    }
}
void init(){
    sprintf(t_Processus[0].nom,"Idle");
    t_Processus[0].pid=0;
    for (size_t i = 1; i < _PROCESS; i++) {
      t_Processus[i].pid=i;
      sprintf(t_Processus[i].nom,"proc%i",i);
      t_Processus[i].etat=PRETE;
      t_Processus[i].zone.esp=(uint32_t)(&t_Processus[i].pile[511]);
    }
    t_Processus[0].etat=ELU;
    t_Processus[1].pile[511]=(uint32_t)(&proc1);
    t_Processus[2].pile[511]=(uint32_t)(&proc2);
    t_Processus[3].pile[511]=(uint32_t)(&proc3);
}

/*char *mon_nom(void){
    int i=0;
    while (t_Processus[i].etat==PRETE){
        i++;
    }
    return t_Processus[i].nom;
}
int mon_pid(void){
    int i=0;
    while (t_Processus[i].etat==PRETE){
        i++;
    }
    return t_Processus[i].pid;
}*/
