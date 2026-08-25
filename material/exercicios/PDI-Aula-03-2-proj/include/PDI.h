#ifndef PDI_H
#define PDI_H

#ifdef _WIN32
#include "..\ImageClass.h"
#else
#include "../ImageClass.h"
#endif

#include <iostream>
#include <vector>
using namespace std;

class PDI
{
    public:
        PDI();
        virtual ~PDI();

        // auxiliares arquivos Imagens
        void carregaNomesImagens();
        void Load();
        void anteImagem();
        void proxImagem();

        // glut functions
        void Init();
        void Display();
        void Reload();

        // algoritmos
        void CopiaImagem();
        void ConvertToGrayScale();
        void ConvertBlackAndWhite(int);
        void GreenChannel();
        void ZoomOut(int fator);
        void Thumbnail(int sizeX, int sizeY);
    protected:

    public:
        int imgAtual;
        int imgLimite;
        int algAtual;
        vector<string> arquivos;

        ImageClass *Imagem, *NovaImagem;
};

#endif // PDI_H
