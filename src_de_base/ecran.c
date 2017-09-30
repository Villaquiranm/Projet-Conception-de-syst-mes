#include "ecran.h"
#include <cpu.h>
#include <string.h>

uint16_t *ptr_mem (uint32_t lig, uint32_t col){
	return (uint16_t*)( 0xB8000+2*(lig*80+col));
}
void ecrit_car(uint32_t *lig,uint32_t *col,char c){
	uint16_t* ptr;
	ptr=ptr_mem(*lig,*col);
	*ptr=(0xf00u)|c;
}

void efface_ecran (void){
	uint32_t lige,cole;
	uint16_t* ptr;

	for (lige=0;lige<=24;lige++){
		for (cole=0;cole<=79;cole++){	
			ptr=ptr_mem(lige,cole);
			*ptr=(0xf00u)|' ';
		}
	}
}
void place_curseur(uint32_t lig, uint32_t col){
	uint16_t pos;
	pos=col+lig*80;
	uint8_t basse=pos;
	uint8_t haute=(pos>>8);
	outb(0x0F,0x3D4);
	outb(basse,0x3D5);
	outb(0x0e,0x3D4);
	outb(haute,0x3D5);
}
void traite_car(char c,uint32_t *lig,uint32_t *col){
	uint32_t pos;
		switch(c){
		case 1:
			/*case dans le quel le curseur doit etre dans la cologne suivante ex: ecrit un caractère
			*/
			if (*col<80){
				*col=(*col)+1;
			}
			else{
				*col=0;
				*lig=(*lig)+1;
			}
			place_curseur(*lig,*col);
			break;
		case '\b':
			/* Case dans le quel le curseur doit reculer
			 * 		 * 
	 		 * */				
			if (*col==0){
				*col=79;
				*lig=*lig-1;
			}
			else{
				*col=*col-1;
			}
			place_curseur(*lig,*col);
			break;
		case '\t':									
			/*Tabulación*/
			pos=8*((*col/8)+1);
			if (pos<80){
				*col=pos;
			}
			else{
			*col=79;
			}
			place_curseur(*lig,*col);
			break;
		case '\n': 
			/*Case dans le quel le curseur doit etre dans la ligne suivante*/
			*col=0;
			*lig=*lig+1;
			place_curseur(*lig,*col);
			break;
		case '\f': 
			/*Case dans le quelle on efface l'ecran et on doit metre le punteur dans la ligne 0 cologne*/ 
			*lig=0;
			*col=0;
			efface_ecran();
			place_curseur(*lig,*col);
			break;
		case '\r': 
			/*Ligne actuelle, Cologne 0*/
			*col=0;
			place_curseur(*lig,*col);
			break;
		default:
			/*case dans le quel le curseur doit etre dans la cologne suivante ex: ecrit un caractère
			*/
			if (*col<80){
				*col=(*col)+1;
			}
			else{
				*col=0;
				*lig=(*lig)+1;
			}
			ecrit_car(lig,col,c);
			place_curseur(*lig,*col+1);
		}
}
void defilement(void){
	memmove(ptr_mem(0,0),ptr_mem(1,0),(size_t)(24*80));	
}
void console_putbytes(char *chaine, int32_t taille, uint32_t *lig,uint32_t *col){
	for (int i=0;i<taille;i++){
		traite_car(chaine[i],lig,col);
	}
}
