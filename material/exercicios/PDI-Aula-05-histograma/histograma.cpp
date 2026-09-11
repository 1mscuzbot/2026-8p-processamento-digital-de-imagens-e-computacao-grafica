// **********************************************************************
// Aula 05 — Exercicios de Histograma
// Processamento Digital de Imagens
//
// Exercicio 1: Montar histograma
// Exercicio 2: Histograma normalizado
// Exercicio 3: Encontrar min e max
// Exercicio 4: Contrast stretching
// Exercicio 5: Equalizacao de histograma
// **********************************************************************

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "BmpLib2.h"

#define MAX_INTENSIDADE 256

// **********************************************************************
// Exercicio 1 — Histograma
// Conta quantos pixels existem para cada nivel de intensidade (0-255)
// **********************************************************************
void exercicio1_histograma(unsigned char* imagem, int largura, int altura,
                           int histograma[MAX_INTENSIDADE])
{
    memset(histograma, 0, sizeof(int) * MAX_INTENSIDADE);

    for (int i = 0; i < altura; i++)
        for (int j = 0; j < largura; j++)
        {
            int idx = (i * largura + j) * 3;
            // Converter RGB para intensidade (media dos 3 canais)
            int intensidade = (imagem[idx] + imagem[idx+1] + imagem[idx+2]) / 3;
            histograma[intensidade]++;
        }

    printf("=== Exercicio 1: Histograma ===\n");
    printf("Intensidade | Frequencia\n");
    for (int i = 0; i < MAX_INTENSIDADE; i++)
    {
        if (histograma[i] > 0)
            printf("    %3d     |   %6d\n", i, histograma[i]);
    }
    printf("\n");
}

// **********************************************************************
// Exercicio 2 — Histograma Normalizado
// Calcula a probabilidade relativa de cada intensidade
// **********************************************************************
void exercicio2_histograma_normalizado(int histograma[MAX_INTENSIDADE],
                                       int totalPixels,
                                       float HN[MAX_INTENSIDADE])
{
    for (int i = 0; i < MAX_INTENSIDADE; i++)
        HN[i] = (float)histograma[i] / totalPixels;

    printf("=== Exercicio 2: Histograma Normalizado ===\n");
    printf("Intensidade | Probabilidade\n");
    for (int i = 0; i < MAX_INTENSIDADE; i++)
    {
        if (HN[i] > 0.0f)
            printf("    %3d     |    %.6f\n", i, HN[i]);
    }
    printf("\n");
}

// **********************************************************************
// Exercicio 3 — Encontrar Minimo e Maximo
// Menor e maior intensidade presentes na imagem
// **********************************************************************
void exercicio3_min_max(int histograma[MAX_INTENSIDADE],
                        int &rmin, int &rmax)
{
    rmin = 255;
    rmax = 0;

    for (int i = 0; i < MAX_INTENSIDADE; i++)
    {
        if (histograma[i] > 0)
        {
            if (i < rmin) rmin = i;
            if (i > rmax) rmax = i;
        }
    }

    printf("=== Exercicio 3: Min e Max ===\n");
    printf("Minimo: %d\n", rmin);
    printf("Maximo: %d\n", rmax);
    printf("Faixa:  %d niveis\n\n", rmax - rmin + 1);
}

// **********************************************************************
// Exercicio 4 — Contrast Stretching
// Expande a faixa de intensidades para 0-255
// **********************************************************************
void exercicio4_contrast_stretching(unsigned char* imagem,
                                    unsigned char* saida,
                                    int largura, int altura,
                                    int rmin, int rmax)
{
    float fator = 255.0f / (rmax - rmin);

    for (int i = 0; i < altura; i++)
        for (int j = 0; j < largura; j++)
        {
            int idx = (i * largura + j) * 3;
            for (int c = 0; c < 3; c++)
            {
                int valor = imagem[idx + c];
                int novo = (int)((valor - rmin) * fator + 0.5f);
                // Clamp para [0, 255]
                if (novo < 0) novo = 0;
                if (novo > 255) novo = 255;
                saida[idx + c] = (unsigned char)novo;
            }
        }

    printf("=== Exercicio 4: Contrast Stretching ===\n");
    printf("Faixa original: [%d, %d]\n", rmin, rmax);
    printf("Faixa resultante: [0, 255]\n\n");
}

// **********************************************************************
// Exercicio 5 — Equalizacao de Histograma
// Uniformiza a distribuicao de intensidades usando CDF
// **********************************************************************
void exercicio5_equalizacao(unsigned char* imagem,
                            unsigned char* saida,
                            int largura, int altura,
                            int histograma[MAX_INTENSIDADE])
{
    int N = largura * altura;

    // 1. Calcular CDF (Funcao de Distribuicao Acumulada)
    float CDF[MAX_INTENSIDADE];
    CDF[0] = histograma[0];
    for (int k = 1; k < MAX_INTENSIDADE; k++)
        CDF[k] = CDF[k-1] + histograma[k];

    // 2. Transformacao: saida[k] = round(CDF[k] * 255 / N)
    int transformacao[MAX_INTENSIDADE];
    for (int k = 0; k < MAX_INTENSIDADE; k++)
    {
        transformacao[k] = (int)round(CDF[k] * 255.0f / N);
        // Clamp
        if (transformacao[k] < 0) transformacao[k] = 0;
        if (transformacao[k] > 255) transformacao[k] = 255;
    }

    // 3. Aplicar transformacao na imagem
    for (int i = 0; i < altura; i++)
        for (int j = 0; j < largura; j++)
        {
            int idx = (i * largura + j) * 3;
            // Converter para cinza, aplicar transformacao, escrever de volta
            int cinza = (imagem[idx] + imagem[idx+1] + imagem[idx+2]) / 3;
            int novo = transformacao[cinza];
            saida[idx] = saida[idx+1] = saida[idx+2] = (unsigned char)novo;
        }

    printf("=== Exercicio 5: Equalizacao de Histograma ===\n");
    printf("Transformacao aplicada:\n");
    printf("r -> s\n");
    for (int k = 0; k < MAX_INTENSIDADE; k++)
    {
        if (histograma[k] > 0)
            printf("%3d -> %3d\n", k, transformacao[k]);
    }
    printf("\n");
}

// **********************************************************************
// main
// **********************************************************************
int main(int argc, char** argv)
{
    const char* arquivo_entrada = "ImagensGL/C1.bmp";
    const char* arquivo_csaida  = "saida_contrast_stretching.bmp";
    const char* arquivo_eqsaida = "saida_equalizacao.bmp";

    if (argc > 1)
        arquivo_entrada = argv[1];

    // Carregar imagem
    unsigned int sizeX, sizeY;
    printf("Carregando: %s\n", arquivo_entrada);

    if (!BMP::load(arquivo_entrada, sizeX, sizeY))
    {
        printf("Erro ao carregar imagem!\n");
        return 1;
    }

    unsigned int tam = sizeX * sizeY * 3;
    unsigned char* imagem = (unsigned char*)malloc(tam);
    BMP::copy_to_ImageClass(imagem);
    BMP::free_memory();

    printf("Imagem: %dx%d (%d pixels)\n\n", sizeX, sizeY, sizeX * sizeY);

    int totalPixels = sizeX * sizeY;
    int histograma[MAX_INTENSIDADE];
    float HN[MAX_INTENSIDADE];
    int rmin, rmax;

    // Exercicio 1: Histograma
    exercicio1_histograma(imagem, sizeX, sizeY, histograma);

    // Exercicio 2: Histograma normalizado
    exercicio2_histograma_normalizado(histograma, totalPixels, HN);

    // Exercicio 3: Min e Max
    exercicio3_min_max(histograma, rmin, rmax);

    // Exercicio 4: Contrast stretching
    unsigned char* saida_cs = (unsigned char*)malloc(tam);
    exercicio4_contrast_stretching(imagem, saida_cs, sizeX, sizeY, rmin, rmax);
    BMP::save(arquivo_csaida, saida_cs, sizeX, sizeY);
    printf("Salvo: %s\n\n", arquivo_csaida);
    free(saida_cs);

    // Exercicio 5: Equalizacao
    unsigned char* saida_eq = (unsigned char*)malloc(tam);
    exercicio5_equalizacao(imagem, saida_eq, sizeX, sizeY, histograma);
    BMP::save(arquivo_eqsaida, saida_eq, sizeX, sizeY);
    printf("Salvo: %s\n\n", arquivo_eqsaida);
    free(saida_eq);

    free(imagem);

    printf("Exercicios concluidos!\n");
    return 0;
}
