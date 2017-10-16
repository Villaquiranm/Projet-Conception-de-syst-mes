void affiche_horloge(char *chaine);
extern void traitant_IT_32(void);
void init_traitant_IT(int32_t num_IT, void (*traitant_IT_32)(void));
void tic_PIT(void);
void horloge(void);
void frequence(void);

