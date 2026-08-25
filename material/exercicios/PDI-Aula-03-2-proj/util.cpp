#include <stdio.h>
#include <string.h>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#endif

#include "util.h"

// Define as variaveis e aloca a memria (pode inicializar aqui)
char nomes[MAX_ARQUIVOS][TAM_NOME];
char pasta[] = "..\\ImagensGL";
int atualArq = 0;

int CarregaNomes(char *pasta)
{
    int quantidade = 0;

#ifdef _WIN32
    WIN32_FIND_DATA dados;
    HANDLE hBusca;

    printf("%s\n", pasta);
    hBusca = FindFirstFile(pasta, &dados);

    if (hBusca == INVALID_HANDLE_VALUE)
    {
        printf("Erro ao abrir a pasta.\n");
        return 1;
    }

    do
    {
        printf("%s\n", dados.cFileName);

        if (strcmp(dados.cFileName, ".") != 0 &&
            strcmp(dados.cFileName, "..") != 0)
        {
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
#else
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    char caminho[512];

    printf("%s\n", pasta);
    dir = opendir(pasta);

    if (dir == NULL)
    {
        printf("Erro ao abrir a pasta.\n");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(caminho, sizeof(caminho), "%s/%s", pasta, entry->d_name);

        if (stat(caminho, &st) == 0 && S_ISREG(st.st_mode))
        {
            if (quantidade < MAX_ARQUIVOS)
            {
                strcpy(nomes[quantidade], entry->d_name);
                printf("%s\n", nomes[quantidade]);
                quantidade++;
            }
        }
    }

    closedir(dir);
#endif

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
    strcpy(nome, pasta);
    strcat(nome, nomes[atualArq]);
    return nome;
}
