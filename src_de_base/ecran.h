/* Este archivo hace las funciones*/
#include <inttypes.h>
#include <stdio.h>
uint16_t *ptr_mem(uint32_t lig, uint32_t col);
void ecrit_car(uint32_t *lig,uint32_t *col,char c);
/*Lo que falta */
void efface_ecran(void);
void place_curseur(uint32_t lig, uint32_t col);
void traite_car(char c,uint32_t *lig,uint32_t *col);
void defilement(void);
void console_putbytes(char *chaine, int32_t taille,uint32_t* lig,uint32_t* col);
