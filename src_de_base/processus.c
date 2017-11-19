#include <cpu.h>
#include <inttypes.h>
#include "ecran.h"
#include "interruption.h"
#include <segment.h>
#include <string.h>
extern void ctx_sw(int32_t *ancient,int32_t *nouveau);
enum etat{ELU,PRETE,ENDORMI,MORT};
struct reg_type{
    int32_t ebx;
    uint32_t esp;
    int32_t ebp;
    int32_t esi;
    int32_t edi;
};
/*struct time_reveil{
  int32_t heure;
  int32_t minute;
  int32_t seconde;
};*/
struct processus {
    int32_t pid;
    char nom[15];
    enum etat etat; //0 élu ; 1 Activable
    struct reg_type zone;
    uint32_t pile[512];
    uint32_t s_reveil;
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
        int32_t time = get_time();
        for (int i=1;i<na_processes+1;i++){
          //printf("%s\n",t_Processus[i].nom);
          if (t_Processus[i].s_reveil<=time && t_Processus[i].etat!=MORT){

            t_Processus[i].etat=PRETE;
          }
        }
        uint32_t loop=0;
        avant= actif;
        do {
          if (actif==na_processes){
            actif=0;
          }else{
            actif++;
          }
          loop++;
        } while(t_Processus[actif].etat==ENDORMI || t_Processus[actif].etat==MORT);
            t_Processus[actif].etat=ELU;
            ctx_sw(&t_Processus[avant].zone.ebx,&t_Processus[actif].zone.ebx);
    }
void idle(void){
    for (;;){
      //printf("[%s] pid =%i\n", mon_nom(),mon_pid());
      sti();
      hlt();
      cli();
    }
}
void fin_processus(){
  t_Processus[actif].etat=MORT;
  printf("[%i] %s est mort maintenant\n",actif,mon_nom());
  ordonnance();
}
int32_t cree_processus(void (*code)(void), char *nom){
  if (na_processes==_PROCESS-1){
    return -1;
  }
  else{
    na_processes++;
    t_Processus[na_processes].pid=na_processes;
    sprintf(t_Processus[na_processes].nom,"%s",nom);
    t_Processus[na_processes].zone.esp=(uint32_t)(&t_Processus[na_processes].pile[510]);
    t_Processus[na_processes].pile[510]=(uint32_t)(code);
    t_Processus[na_processes].pile[511]=(uint32_t)(&fin_processus);
    t_Processus[na_processes].s_reveil=0;
    t_Processus[na_processes].etat=PRETE;
  return 0;
  }
}
void dors(uint32_t nb_seconds){
  t_Processus[actif].s_reveil+=nb_seconds;
  //t_Processus[actif].s_reveil%=60;
  t_Processus[actif].etat=ENDORMI;
  ordonnance();
}

void proc1(void){

    for(int i=0;i<5;i++){
      //t_Processus[actif].pile[511]=(uint32_t)(&fin_processus);
      printf("[temps = %u] processus %s pid = %i\n", get_time(),mon_nom(), mon_pid());
      dors(1);
    }
}
void proc2(void){
    for(int i=0;i<5;i++){
      printf("[temps = %u] processus %s pid = %i\n", get_time(),mon_nom(), mon_pid());
      dors(2);
    }
    //fin_processus();
}
void proc3(void){
    for(int i=0;i<5;i++){
      printf("[temps = %u] processus %s pid = %i\n", get_time(),mon_nom(), mon_pid());
      dors(3);
    }
    //fin_processus();
}

void init(){
    sprintf(t_Processus[na_processes].nom,"Idle");
    t_Processus[na_processes].pid=na_processes;
    t_Processus[na_processes].etat=ELU;
    t_Processus[na_processes].s_reveil=0;
    cree_processus(&proc1,"proc1");
    cree_processus(&proc2,"proc2");
    cree_processus(&proc3,"proc3");
    //cree_processus(&proc3,"proc3");
}
