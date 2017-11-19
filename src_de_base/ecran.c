#include "ecran.h"
#include <cpu.h>
#include <string.h>
uint32_t l=0,c=0;
uint16_t *ptr_mem (uint32_t lig, uint32_t col){
	return (uint16_t*)( 0xB8000+2*(lig*80+col));
}
void ecrit_car(uint32_t lig,uint32_t col,char c){
	uint16_t* ptr;
	ptr=ptr_mem(lig,col);
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
void traite_car(char ca){
	uint32_t pos;
		switch(ca){
		/*case 1:
			case dans le quel le curseur doit etre dans la cologne suivante ex: ecrit un caractère

			if (l==24 && c==79){

			}
			else{
				if (c<80){
					c=(c)+1;
				}
				else{
					c=0;
					l=(l)+1;
				}
				place_curseur(l,c);
			}
			break;*/
		case '\b':
			/* Case dans le quel le curseur doit reculer
			 * 		 *
	 		 * */
			if (c==0){
				c=79;
				l=l-1;
			}
			else{
				c=c-1;
			}
			place_curseur(l,c);
			break;
		case '\t':
			/*Tabulación*/
			pos=8*((c/8)+1);
			if (pos<80){
				c=pos;
			}
			else{
			c=79;
			}
			place_curseur(l,c);
			break;
		case '\n':
			if (l==24) {
				defilement();
				l=24;
				c=0;
			}
			else{
				c=0;
				l=l+1;
				place_curseur(l,c);
			}

			break;
		case '\f':
			/*Case dans le quelle on efface l'ecran et on doit metre le punteur dans la ligne 0 cologne*/
			l=0;
			c=0;
			efface_ecran();
			place_curseur(l,c);
			break;
		case '\r':
			/*Ligne actuelle, Cologne 0*/
			c=0;
			place_curseur(l,c);
			break;
		default:
			/*case dans le quel le curseur doit etre dans la cologne suivante ex: ecrit un caractère
			*/
			if (c==79 && l==24) {
				defilement();
			}

			if (c<79){
				c++;
			}
			else{
				c=0;
				l=(l)+1;
			}
			ecrit_car(l,c,ca);
			place_curseur(l,c+1);

			}


}
void defilement(void){
	memmove(ptr_mem(0,0),ptr_mem(1,0),(size_t)(24*80*2));
	place_curseur(24,1);
		for (uint32_t cole=0;cole<=79;cole++){
			uint16_t *ptr=ptr_mem(24,cole);
			*ptr=(0xf00u)|' ';
		}
		l=24;
		c=1;


}
void console_putbytes(char *chaine,int32_t taille){
	for (int i=0;i<taille;i++){
		traite_car(chaine[i]);
	}
}
void montrer(char *chaine,int32_t taille){
	for (int i=0;i<taille;i++){
		ecrit_car(0,71+i,chaine[i]);
	}
}
