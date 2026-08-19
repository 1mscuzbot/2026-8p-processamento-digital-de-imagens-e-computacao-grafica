#ifndef UTIL_H
#define UTIL_H

#define MAX_ARQUIVOS 1000
#define TAM_NOME     260

extern char nomes[MAX_ARQUIVOS][TAM_NOME];
extern char pasta[];
extern int atualArq;

int CarregaNomes(char *pasta);
std::string Arquivo(int indice);

#endif
