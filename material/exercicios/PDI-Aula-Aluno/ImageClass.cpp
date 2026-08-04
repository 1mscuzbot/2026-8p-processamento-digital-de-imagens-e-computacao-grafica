#include <stdio.h>
#include <stdlib.h>

#include <GL\gl.h>

#include "ImageClass.h"
#include "BmpLib2.h"

#define TAM_PIXEL 3

#define COLOR_WHITE 255

// **********************************************************************
string extensao(string arquivo)
{
    int tam = arquivo.length();
    int i;
    for(i=tam-1; arquivo[i]!='.'; i--);

    return arquivo.substr(i+1);
}
// **********************************************************************
//
//	Constructor
// **********************************************************************
ImageClass::ImageClass()
{
	data = NULL;
	setSize(0,0);

	posX = posY = 0;
	zoomH = zoomV = 1;

    // NOVO
    // Isto resolve o problema de ter a imagem com largura múltipla de 4
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}
// **********************************************************************
//
//	Constructor
// **********************************************************************
ImageClass::ImageClass(int sizeX, int sizeY)
{
    Realloc(sizeX,sizeY);

    posX = posY = 0;
	zoomH = zoomV = 1;

    // NOVO
    // Isto resolve o problema de ter a imagem com largura múltipla de 4
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}
// **********************************************************************
//
//
// **********************************************************************
void ImageClass::Realloc(int sizeX, int sizeY)
{
	unsigned int tam;

	Delete();

	setSize(sizeX, sizeY);

	tam = sizeof(unsigned char) * sizeX * sizeY * TAM_PIXEL;
	data = (unsigned char *) malloc (tam);
	memset(data,255,tam);
}
// **********************************************************************
//
//
// **********************************************************************
unsigned char *ImageClass::GetImagePtr()
{
	return data;
}
// **********************************************************************
//
//
// **********************************************************************
bool ImageClass::Load(string nome)
{
    string ext = (extensao(nome));

    if (ext == "bmp")
    {
        if (data)
            free(data); // é necessário desalocar a área da imagem

        if (BMP::load(nome.c_str(), sizeX, sizeY))
        {
            Realloc(sizeX, sizeY);
            BMP::copy_to_ImageClass(data);
            BMP::free_memory();
            return true;
        }
    }
    else
    {
        // futuros tipos de imagens
    }
    printf("\nErro: tipo de arquivo invalido");
    return false;
}
// **********************************************************************
//
//
// **********************************************************************
void ImageClass::Save(char *nome)
{
    if( BMP::save(nome, data, sizeX, sizeY) )
        printf("\nArquivo salvo com sucesso");
}
// **********************************************************************
//
//
// **********************************************************************
void ImageClass::Display()
{
	glPixelZoom(zoomH , zoomV);
	glRasterPos2f(posX, posY);
	glDrawPixels(sizeX, sizeY, GL_RGB, GL_UNSIGNED_BYTE, data);
//  glDrawPixels(sizeX, sizeY, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
}
// **********************************************************************
//
//
// **********************************************************************
void ImageClass::CopyTo(ImageClass *i)
{
    /// usar setSize antes
	unsigned int tam;
    tam = sizeof(unsigned char) * sizeX * sizeY * TAM_PIXEL;
	memcpy(i->data, data, tam);

//    i->sizeX = sizeX;
//    i->sizeY = sizeY;
}
// **********************************************************************
//
//
// **********************************************************************
void ImageClass::Clear()
{
	unsigned int tam;
	tam = sizeof(unsigned char) * getSizeX() * getSizeY() * TAM_PIXEL;
	memset(data, 255, tam);
}
// **********************************************************************
//
//
// **********************************************************************
void ImageClass::Delete()
{
	// Cleanup
	if (data)
	{
		free(data);
		data = NULL;
    }
}
// **********************************************************************
//
//
// **********************************************************************
void ImageClass::DrawPixel(GLint x, GLint y, unsigned char r, unsigned char g, unsigned char b)
{
	unsigned long addr;

	addr = (unsigned long)( y *(sizeX)* TAM_PIXEL + x * TAM_PIXEL );
	data[addr++] = r;
	data[addr++] = g;
	data[addr] = b;
}
// **********************************************************************
//
//
//
// **********************************************************************
void ImageClass::DrawLineH(int y, int x1, int x2,unsigned char r, unsigned char g, unsigned char b )
{
	int x;
	if (x1 <= x2)
		for (x = x1; x<=x2; x++)
		{
			DrawPixel(x,y,r,g,b);
		}
    else
		for (x = x2; x<=x1; x++)
		{
			DrawPixel(x,y,r,g,b);
		}

}
// **********************************************************************
//
//
//
// **********************************************************************
void ImageClass::DrawLineV(int x, int y1, int y2,unsigned char r, unsigned char g, unsigned char b )
{
	int y;
	for (y = y1; y<=y2; y++)
	{
		DrawPixel(x,y,r,g,b);
	}
}

// **********************************************************************
//
//
// **********************************************************************
void ImageClass::ReadPixel(GLint x, GLint y, unsigned char &r, unsigned char &g, unsigned char &b)
{
	unsigned long addr;

	addr = (unsigned long)( y *(sizeX)* TAM_PIXEL + x * TAM_PIXEL );
	r = data[addr++];
	g = data[addr++];
	b = data[addr];
}


// **********************************************************************
//
//
//
// **********************************************************************
double ImageClass::GetPointIntensity(int x, int y)
{
	unsigned char r,g,b;
	double i;

	ReadPixel(x,y,r,g,b);
	i = (0.3 * r + 0.59 * g + 0.11 * b);
	return i;
}

// **************************************************************
//
// **************************************************************
void ImageClass::DrawBox(int x1,int y1,int x2,int y2,unsigned char r, unsigned char g, unsigned char b )
{
    DrawLineH(y1, x1, x2, r,g,b);
    DrawLineH(y2, x1, x2, r,g,b);
    DrawLineV(x1, y1, y2, r,g,b);
    DrawLineV(x2, y1, y2, r,g,b);
}

// **************************************************************
//
// **************************************************************
void ImageClass::DrawLine(int x0,int y0,int x1, int y1,unsigned char r, unsigned char g, unsigned char bb  )
{
        int dx = x1 - x0;
        int dy = y1 - y0;
        int x,y;
        float b, m;

        DrawPixel(x0, y0, r,g,bb);
        if (abs(dx) > abs(dy)) {          // slope < 1
            m = (float) dy / (float) dx;      // compute slope
            b = y0 - m*x0;
            dx = (dx < 0) ? -1 : 1;
            while (x0 != x1) {
                x0 += dx;
                y = (int)((m*x0 + b)+0.5);
                DrawPixel(x0, y, r,g,bb);
            }
        } else
        if (dy != 0) {                              // slope >= 1
            float m = (float) dx / (float) dy;      // compute slope
            float b = x0 - m*y0;
            dy = (dy < 0) ? -1 : 1;
            while (y0 != y1) {
                y0 += dy;
                x = (int) ((m*y0 + b)+0.5);
                DrawPixel(x, y0, r,g,bb);
            }
        }
}
// **********************************************************************
//
//
// **********************************************************************
void ImageClass::setPos(int X, int Y)
{
	this->posX = X;
	this->posY = Y;
}
// **********************************************************************
//
//
// **********************************************************************
void ImageClass::setSize(int X, int Y)
{
	this->sizeX = X;
	this->sizeY = Y;
}
// **********************************************************************
// Funcoes do Diogenes
// **********************************************************************
int ImageClass::size()
{
    return sizeX * sizeY;
}
// **********************************************************************
// **********************************************************************
unsigned char ImageClass::getPixel(GLint x, GLint y)
{
    if(x>=getSizeX() or x<0)
        return 0;
    if(y>=getSizeY() or y<0)
        return 0;

    unsigned char r, g, b;
    ReadPixel(x,y,r,g,b);
    return r;
}
// **********************************************************************
// **********************************************************************
void ImageClass::setPixel(GLint x, GLint y, unsigned char cor)
{
    setPixel(x,y,cor,cor,cor);
}
// **********************************************************************
// **********************************************************************
void ImageClass::setPixel(GLint x, GLint y, unsigned char r, unsigned char g, unsigned char b)
{
	unsigned long addr;

	addr = (unsigned long)( y *(sizeX)* TAM_PIXEL + x * TAM_PIXEL );
	data[addr++] = r;
	data[addr++] = g;
	data[addr] = b;
}
// **********************************************************************
// **********************************************************************
void ImageClass::LoadFrom(string diretorio, string nome)
{
    int r;
    r = Load( diretorio+nome );
    if (!r)
    {
        printf("Imagem %s não carregada. Verifique o nome do Arquivo ou seu conteudo.", nome.c_str());
        printf("\nPressione ENTRE para encerrar.");
        getchar();
        exit(1);
    }
    else
        printf ("Imagem %s carregada!\n", nome.c_str());
}
// **********************************************************************

// **********************************************************************

unsigned char ImageClass::GetLuminancia(int x, int y)
{
	unsigned char r,g,b;
	double Y;

	ReadPixel(x,y,r,g,b);
	Y = (0.299 * r + 0.587 * g + 0.114 * b);
	return (unsigned char)Y;
}

unsigned char ImageClass::GetMatiz(int x, int y)
{
	unsigned char r,g,b;
	double I;

	ReadPixel(x,y,r,g,b);
	I = (0.596 * (int)r - 0.275 * (int)g - 0.321 * (int)b);
	if(I<0) I+=256;
	return (unsigned char)I;
}

unsigned char ImageClass::GetSaturacao(int x, int y)
{
	unsigned char r,g,b;
	double Q;

	ReadPixel(x,y,r,g,b);
	Q = (0.212 * r - 0.523 * g + 0.311 * b);
	if(Q<0) Q+=256;
	return (unsigned char)Q;
}
/*
Pixel ImageClass::GetYIQ(int x, int y)
{
	unsigned char r,g,b;
	double i;

	ReadPixel(x,y,r,g,b);
	P.Y = (0.299 * r + 0.587 * g + 0.114 * b);
	P.I = (0.596 * r - 0.257 * g - 0.321 * b);
	P.Q = (0.212 * r - 0.523 * g + 0.311 * b);
	return P;
}

Pixel ImageClass::YIQtoRGB(Pixel Q)
{
	unsigned char r,g,b;
	Pixel P;

	P.R = (1*Y + 0.9563 * I + 0.6210 * Q);
	P.G = (1*Y - 0.2721 * I - 0.6474 * Q);
	P.B = (1*Y - 1.1070 * I + 1.7046 * Q);
	return P;
}
*/
