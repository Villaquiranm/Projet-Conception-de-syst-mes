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
struct processus t_Processus[2];
void idle(void){
    for (int i=0;i<3;i++){
        printf("[idle] je tente de passer la main a proc1...\n");
        ctx_sw(&t_Processus[0].zone.ebx,&t_Processus[1].zone.ebx);
        printf("[idle] proc1 m'a redonne la main \n");
    }
    printf("[idle] je bloque le systeme\n");
    hlt();
}
void proc1(void){
    for(int a=0; a<3;a++){
        printf("[proc1] idle m'a donne la main \n");
        printf("[proc1] je tente de lui la redonner] \n");
        ctx_sw(&t_Processus[1].zone.ebx,&t_Processus[0].zone.ebx);
    }
     
       
}
void init(){
    sprintf(t_Processus[0].nom,"Idle");
    sprintf(t_Processus[1].nom,"proc1");
    t_Processus[0].pid=0;
    t_Processus[1].pid=1;
    t_Processus[0].etat=ELU;
    t_Processus[1].etat=PRETE;
    t_Processus[1].zone.esp=(uint32_t)(&t_Processus[1].pile[511]);
    t_Processus[1].pile[511]=(uint32_t)(&proc1);   
}
void ordonnance(){
  
    if (t_Processus[0].etat==ELU){
        t_Processus[0].etat=PRETE;
        t_Processus[1].etat=ELU;
        printf("[idle] je donne la main \n");
        ctx_sw(&t_Processus[0].zone.ebx,&t_Processus[1].zone.ebx);
    }
    else{
        t_Processus[1].etat=PRETE;
        t_Processus[0].etat=ELU;
        printf("[proc1] Je donne la main \n");
        ctx_sw(&t_Processus[1].zone.ebx,&t_Processus[0].zone.ebx);

    }   
}
char *mon_nom(void){
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
}
