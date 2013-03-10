#include <stdio.h>

int ler_id(FILE *fp, int count, long long *id);
void ler_parametro_f(FILE *fp, int count, int dim, char *parametro);
int ler_user_ficheiro(FILE *fp, Perfil **ptr, int count, long long *id);
int carregar_bd(char *input, long long *id);
void guarda_user(FILE *fw, Perfil *p);
int guardar_bd(char *output, long long *id);
void limpa_hash(long long *id);
