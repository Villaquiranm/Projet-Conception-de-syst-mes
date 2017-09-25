#include "ecran.h"
#include <cpu.h>

uint16_t *ptr_mem(uint32_t lig, uint32_t col){
	return (uint16_t*) (0xB8000+2*(lig*80+col));
}
void ecrit_car(uint32_t lig,uint32_t col,char c){
	uint16_t* ptr;
	ptr=ptr_mem(lig,col);
	*ptr=(0xf00u)|c;
}
void efface_ecran (void){
	int lig,col;
	for (lig=0;lig<=24;lig++){
		for (col=0;col<=79;col++){
			ecrit_car(lig,col,' ');
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
void traite_car(char c){
	switch (c){
	case 8

	}

}
void gerer_lig_col(int option, uint32_t lig, uint32_t col){
	switch option{
	case 1
		/*case dans le quel le curseur doit etre dans la ligne suivante ex: ecrit un caractère
		 * */
	case 3
		/*Case dans le quel le curseur doit etre dans la cologne 0 de la ligne currente.
		 * */
	case 2
		/* Case dans le quel le curseur doit reculer
		 * */
	}
}
