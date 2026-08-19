#include <stdio.h>
#include <windows.h>
#include <string>

#include "util.h"

// Define as variáveis e aloca a memória (pode inicializar aqui)
char nomes[MAX_ARQUIVOS][TAM_NOME];
char pasta[] = "..\\ImagensGL";
int atualArq = 0;

int CarregaNomes(char *pasta)
{
    WIN32_FIND_DATA dados;
    HANDLE hBusca;

    char nomes[MAX_ARQUIVOS][TAM_NOME];
    int quantidade = 0;

    printf("%s\n", pasta);
    hBusca = FindFirstFile(pasta, &dados);

    if (hBusca == INVALID_HANDLE_VALUE)
    {
        printf("Erro ao abrir a pasta.\n");
        return 1;
    }

    do
    {
        printf("%s\n",dados.cFileName);

        /* Ignora "." e ".." */
        if (strcmp(dados.cFileName, ".") != 0 &&
            strcmp(dados.cFileName, "..") != 0)
        {
            /* Verifica se e' um arquivo */
            if (!(dados.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                if (quantidade < MAX_ARQUIVOS)
                {
                    strcpy(nomes[quantidade], dados.cFileName);
                    quantidade++;
                }
            }
        }

    } while (FindNextFile(hBusca, &dados));

    FindClose(hBusca);

    /* Mostra os arquivos encontrados */
    printf("Arquivos encontrados: %d\n\n", quantidade);

    for (int i = 0; i < quantidade; i++)
    {
        printf("%d - %s\n", i, nomes[i]);
    }

    return 0;
}

std::string Arquivo(int indice)
{
    char nome[TAM_NOME];
    strcpy(nome,pasta);
	strcat(nome,nomes[atualArq]);
    return nome;
}

