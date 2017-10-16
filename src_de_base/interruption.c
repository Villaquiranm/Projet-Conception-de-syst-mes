#include "ecran.h"
#include <string.h>
#include <cpu.h>
#include <segment.h>
uint32_t tick=0,segundos=0,minutos=0,horas=0;
void init_traitant_IT(int32_t num_IT, void (*traitant)(void)){
    uint32_t paroleh,paroleb;
    uint32_t* ptr;
    ptr=((uint32_t*) (0x1000))+(32*2);
    uint32_t pos=(uint32_t)(traitant);
    paroleh=(KERNEL_CS<<16)|(pos & 0x0000ffff);
    *ptr=paroleh;
    ptr++;
    paroleb=(pos & 0xffff0000)|0x8e00;
    *ptr=paroleb;
}
//Aqui va lo que se ejecutará luego de cada interrupción
void tic_PIT(void){
    outb(0x20,0x20);
    char str[2];
    tick++;
    if (tick==50){
    	segundos++;
    	tick=0;
    }
    if (segundos==60){
    	segundos=0;
	minutos++;
    }
    if (minutos==60){
    	minutos=0;
	horas++;
    }
    sprintf(str,"%2d:%2d:%2d",horas,minutos,segundos);
    montrer(str,8);
    
}
void horloge(void){
uint8_t masque=inb(0x21);
outb(masque&0xFE,0x21);

}
void frequence(void){
    outb(0x34,0x43);
uint16_t freq;
    freq=(((0x1234DD)/50)%256);
    outb((uint8_t) freq,0x40);
    freq=freq>>8;
    outb(((0x1234DD)/50)/256,0x40);
}
