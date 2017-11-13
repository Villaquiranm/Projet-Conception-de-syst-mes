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
uint32_t na_processes=0;

struct processus t_Processus[_PROCESS];
char *mon_nom(){
  return t_Processus[actif].nom;
}
uint32_t mon_pid(){
  return t_Processus[actif].pid;
}
void ordonnance(){
        printf("[%s] je donne la main pid=%i \n",mon_nom(),mon_pid());

        if (actif==na_processes){
          actif=0;
          avant=na_processes;
        }else{
          avant=actif;
          actif++;
        }
        t_Processus[avant].etat=PRETE;
        t_Processus[actif].etat=ELU;
        ctx_sw(&t_Processus[avant].zone.ebx,&t_Processus[actif].zone.ebx);

    }

void idle(void){
    sti();
    for (int i=0;i<3;i++){
      printf("[%s] pid = %i\n", mon_nom(), mon_pid());
      sti();
      hlt();
      cli();
    }
    printf("[idle] je bloque le systeme\n");
    hlt();
}
int32_t cree_processus(void (*code)(void), char *nom){
  if (na_processes==_PROCESS-1){
    return -1;
  }
  else{
    na_processes++;
    t_Processus[na_processes].pid=na_processes;
    sprintf(t_Processus[na_processes].nom,nom);
    t_Processus[na_processes].etat=PRETE;
    t_Processus[na_processes].zone.esp=(uint32_t)(&t_Processus[na_processes].pile[511]);
    t_Processus[na_processes].pile[511]=(uint32_t)(code);
  return 0;
  }
}
void proc1(void){
    for(int i=0;i<3;i++){
      printf("[%s] pid = %i\n", mon_nom(), mon_pid());
      sti();
      hlt();
      cli();
    }
}
void proc2(void){
    for(int i=0;i<3;i++){
      printf("[%s] pid = %i\n", mon_nom(), mon_pid());
      sti();
      hlt();
      cli();
    }
}
void proc3(void){
    for(int i=0;i<3;i++){
      printf("[%s] pid = %i\n", mon_nom(), mon_pid());
      sti();
      hlt();
      cli();
    }
}
void init(){
    sprintf(t_Processus[na_processes].nom,"Idle");
    t_Processus[na_processes].pid=na_processes;
    t_Processus[na_processes].etat=ELU;
    cree_processus(&proc1,"proc1");
    cree_processus(&proc2,"proc2");
    cree_processus(&proc3,"proc3");
    //cree_processus(&proc3,"proc3");


}
