// **********************************************************************
// COMPUTAÇÃO GRÁFICA
//
// **********************************************************************
//
// ImageTest.cpp
//
// Programa de testes para manipulação de Imagens
//
//		Este programa deve ser compilador junto com a classe "ImageClass",
//		que está implementada no arquivo "ImageClass.cpp"
//
//		- para compilar no Visual C ou Visual Studio acrescente as seguintes
//        bibliotecas:
//					 opengl32.lib glu32.lib glut32.lib
//
//		- para compilar no DEVCPP ou CodeBlocks (ou no g++) acrescente as seguintes
//        bibliotecas:
//		      -lopengl32 -lglut32 -lglu32
//
//		- para alterar a imagem que é carregada pelo programa, olhe a
//		  rotina 'init' e altere a linha:
//							r = Image->Load("    ");
//
// **********************************************************************


#include <stdio.h>
#include <math.h>

#include <windows.h>

#include <GL\gl.h>
#include "glut.h"

#include "ImageClass.h"

ImageClass *Image, *NovaImagem;
int LIMIAR = 100;

// **********************************************************************
// void ConvertToGrayScale()
//
//
// **********************************************************************
void ConvertToGrayScale()
{
    // luminancia = (0.3*r + 0.59*g + 0.11*b);

    //Image->ReadPixel(GLint x, GLint y, unsigned char &r, unsigned char &g, unsigned char &b)
    // Obtém os valores R,G,B de um ponto X,Y da image

    //Image->DrawPixel(GLint x, GLint y, unsigned char r, unsigned char g, unsigned char b)
	// Exibe na coordenada X,Y um ponto com a cor R,G,B na imagem

	int x,y,i;

	for(x=0; x<Image->getSizeX(); x++) {
		for(y=0; y<Image->getSizeY(); y++)
        {
             i = Image->GetPointIntensity(x,y);
			 NovaImagem->DrawPixel(x, y, i,i,i);
		}
	}
}
// **********************************************************************
//  void CopiaImagem()
//
//
// **********************************************************************
void CopiaImagem()
{
 	int x,y;
 	unsigned char r,g,b;

	for(x=0; x<Image->getSizeX(); x++)
	{
		for(y=0; y<Image->getSizeY(); y++)
        {
            Image->ReadPixel(x, y, r, g, b);
            NovaImagem->DrawPixel(x, y, r,g,b);
		}
	}
}
// **********************************************************************
//  void init(void)
//		Inicializa os parâmetros globais de OpenGL
//      Cria os objetos que representam as imagens
//
// **********************************************************************
void init(void)
{
	int r;

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Fundo de tela azul

    // Cria um objeto imagem
	Image = new ImageClass();

	r = Image->Load("../ImagensGL/abbey.bmp");

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
	NovaImagem = new ImageClass(Image->getSizeX(), Image->getSizeY());

	// Posiciona a imagem nova ao lado da antiga
	NovaImagem->setPos(Image->getSizeX()+10, 0);

}
// **********************************************************************
//  void reshape( int w, int h )
//		trata o redimensionamento da janela OpenGL
//
// **********************************************************************
void reshape( int w, int h )
{
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);
	gluOrtho2D(0,w,0,h);

	// Set the clipping volume
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
// **********************************************************************
//  void display( void )
//      Esta rotina é chamada toda vez que a tela precisa ser
//      redesenhada e toda vez qua a rotina 'glutPostRedisplay' é chamada
//
// **********************************************************************
void display( void )
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	Image->Display();
	NovaImagem->Display();

	glutSwapBuffers();
}
// **********************************************************************
//  void keyboard ( unsigned char key, int x, int y )
//
//
// **********************************************************************
void keyboard ( unsigned char key, int x, int y )
{
	switch ( key )
	{
		case 27:        // Termina o programa qdo
			exit ( 0 );   // a tecla ESC for pressionada
			break;
		case '1':
				CopiaImagem();
				glutPostRedisplay(); // obrigatório para redesenhar a tela
 				break;
		case '2':
				ConvertToGrayScale();
				glutPostRedisplay(); // obrigatório para redesenhar a tela
 				break;
        case '+': LIMIAR +=10;
                printf("\nLIMIAR = %d", LIMIAR);
                break;
        case '-': LIMIAR -=10;
                printf("\nLIMIAR = %d", LIMIAR);
                break;
		default:
			break;
	}
}
// **********************************************************************
//  void arrow_keys ( int a_keys, int x, int y )
//
//
// **********************************************************************
void arrow_keys ( int a_keys, int x, int y )
{
	switch ( a_keys )
	{
		case GLUT_KEY_UP:       // When Up Arrow Is Pressed...
			glutFullScreen ( ); // Go Into Full Screen Mode
			break;
	    case GLUT_KEY_DOWN:     // When Down Arrow Is Pressed...
			glutInitWindowSize  ( 700, 500 );
			break;
		default:
			break;
	}
}
// **********************************************************************
//  void main ( int argc, char** argv )
//
//
// **********************************************************************
int main ( int argc, char** argv )
{
	glutInit            ( &argc, argv );
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
	glutInitWindowPosition (100,100);

	// Define o tamanho da janela gráfica do programa
	glutInitWindowSize  (800, 400);
	glutCreateWindow    ( "Image Loader" );

	init ();
	glutFullScreen();

	glutDisplayFunc ( display );
	glutReshapeFunc ( reshape );
	glutKeyboardFunc ( keyboard );
	glutSpecialFunc ( arrow_keys );

	glutMainLoop ( );
    return 0;
}


