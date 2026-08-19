#include "PDI.h"
#include <dirent.h>

string pasta = "../ImagensGL/"; // ao criar objeto

PDI::PDI()
{
    //ctor
    imgAtual = 0;
    algAtual = 0;
    carregaNomesImagens();
    imgLimite = arquivos.size();
}

PDI::~PDI()
{
    //dtor
}
//-------------------------------------------------------
// **********************************************************************
// void ConvertToGrayScale()
//
//
// **********************************************************************
void PDI::ConvertToGrayScale()
{
    // luminancia = (0.3*r + 0.59*g + 0.11*b);

    //Imagem->ReadPixel(GLint x, GLint y, unsigned char &r, unsigned char &g, unsigned char &b)
    // Obtém os valores R,G,B de um ponto X,Y da image

    //Imagem->DrawPixel(GLint x, GLint y, unsigned char r, unsigned char g, unsigned char b)
	// Exibe na coordenada X,Y um ponto com a cor R,G,B na imagem

	int x,y,i;

	for(x=0; x<Imagem->getSizeX(); x++) {
		for(y=0; y<Imagem->getSizeY(); y++)
        {
             i = Imagem->GetPointIntensity(x,y);
			 NovaImagem->DrawPixel(x, y, i,i,i);
		}
	}
}
// **********************************************************************
//  void CopiaImagem()
//
//
// **********************************************************************
void PDI::CopiaImagem()
{
 	int x,y;
 	unsigned char r,g,b;

	for(x=0; x<Imagem->getSizeX(); x++)
	{
		for(y=0; y<Imagem->getSizeY(); y++)
        {
            Imagem->ReadPixel(x, y, r, g, b);
            NovaImagem->DrawPixel(x, y, r,g,b);
		}
	}
}

void PDI::ConvertBlackAndWhite(int LIMIAR)
{
    int x,y;
    unsigned char r,g,b, i;

    for(x=0; x<Imagem->getSizeX(); x++) {
        for(y=0; y<Imagem->getSizeY(); y++)
        {
            Imagem->ReadPixel(x, y, r,g,b);
            i = (0.299*r + 0.587*g + 0.114*b);
            if (i < LIMIAR)
                NovaImagem->DrawPixel(x, y, 0,0,0);
	     else
                NovaImagem->DrawPixel(x, y, 255,255,255);
        }
    }
}

void PDI::GreenChannel()
{
    int x,y;
    unsigned char r,g,b;

    for(x=0; x<Imagem->getSizeX(); x++) {
        for(y=0; y<Imagem->getSizeY(); y++)
        {
            Imagem->ReadPixel(x, y, r,g,b);
            NovaImagem->DrawPixel(x, y, 0,g,0);
        }
    }
}

void PDI::ZoomOut(int fator)
{
    int x,y;
    unsigned char r,g,b;

    for(x=0; x<Imagem->getSizeX(); x+=fator) {
       for(y=0; y<Imagem->getSizeY(); y+=fator)
       {
          Imagem->ReadPixel(x, y, r,g,b);
          NovaImagem->DrawPixel(x/fator, y/fator, r,g,b);
       }
    }
}

void PDI::Thumbnail(int sizeX, int sizeY)
{
    int x,y;
    unsigned char r,g,b;
    int fatorX = Imagem->getSizeX() / sizeX;
    int fatorY = Imagem->getSizeY() / sizeY;

    for(x=0; x<sizeX; x++) {
       for(y=0; y<sizeY; y++)
       {
          Imagem->ReadPixel(x*fatorX, y*fatorY, r,g,b);
          NovaImagem->DrawPixel(x, y, r,g,b);
       }
    }
}


//-------------------------------------------------------
void PDI::Display()
{
    Imagem->Display();
    NovaImagem->Display();
}

void PDI::Init()
{
    // Cria um objeto imagem
	Imagem = new ImageClass();

	// carrega arquivo
	int r = Imagem->Load( pasta + arquivos[imgAtual] );

	if (!r)
    {
        printf("Imagem não encontrada. Verifique o nome do Arquivo.\n");
        printf("Pressione ENTRE para encerrar.");
        getchar();
		exit(1);
    }
	else printf ("Imagem carregada!\n");

	// Instacia o objeto que irá exibir a nova imagem
	// Caso precise alterar o tamanho da nova imagem, mude os parâmetros
	// da construtura, na chamada abaixo
	NovaImagem = new ImageClass(Imagem->getSizeX(), Imagem->getSizeY());

	// Posiciona a imagem nova ao lado da antiga
	NovaImagem->setPos(Imagem->getSizeX()+10, 0);
}

void PDI::Load()
{

}

void PDI::Reload()
{
    // Imagem 1
    Imagem->Delete();
    Imagem->Load(pasta + arquivos[imgAtual]);
    Imagem->setPos(10,25);

    // Imagem 2
    NovaImagem->Resize(Imagem->getSizeX(), Imagem->getSizeY());
	NovaImagem->setPos(Imagem->getSizeX()+25, 25);
}

void PDI::anteImagem()
{
    imgAtual--;
    if(imgAtual < 0)
        imgAtual = imgLimite-1;
}

void PDI::proxImagem()
{
    imgAtual++;
    if(imgAtual >= imgLimite)
        imgAtual = 0;
}

void PDI::carregaNomesImagens()
{
    DIR *dir;
    struct dirent *diread;

    if ((dir = opendir(pasta.c_str())) != NULL) {
        while ((diread = readdir(dir)) != NULL) {
            arquivos.push_back(diread->d_name);
            //printf("%-20s\n", diread->d_name);
        }
        closedir (dir);
    } else {
        perror ("opendir");
        return;
    }

    printf("\n\n");
    arquivos.erase(arquivos.begin(),arquivos.begin()+2);
    for (auto file : arquivos)
        cout << file << "\n";
    cout << endl;
    return;
}
