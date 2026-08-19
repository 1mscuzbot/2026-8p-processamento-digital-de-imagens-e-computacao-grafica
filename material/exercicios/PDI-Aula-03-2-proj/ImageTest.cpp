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

#include "pdi.h"

int LIMIAR = 100;

PDI pdi;

void MenuFuncoes(int op);
// **********************************************************************
//  void init(void)
//		Inicializa os parâmetros globais de OpenGL
//      Cria os objetos que representam as imagens
//
// **********************************************************************
void init(void)
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Fundo de tela azul

    pdi.Init();
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
    pdi.Display();

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
        pdi.CopiaImagem();
        glutPostRedisplay(); // obrigatório para redesenhar a tela
        break;
    case '2':
        pdi.ConvertToGrayScale();
        glutPostRedisplay(); // obrigatório para redesenhar a tela
        break;
    case '3':
        pdi.ConvertBlackAndWhite(128);
        glutPostRedisplay(); // obrigatório para redesenhar a tela
        break;
    case '+':
        LIMIAR +=10;
        printf("\nLIMIAR = %d", LIMIAR);
        break;
    case '-':
        LIMIAR -=10;
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
    case GLUT_KEY_LEFT:
        pdi.anteImagem();
        pdi.Reload();
        MenuFuncoes(pdi.algAtual);
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        pdi.proxImagem();
        pdi.Reload();
        MenuFuncoes(pdi.algAtual);
        glutPostRedisplay();
        break;
    default:
        break;
    }
}
// **********************************************************************
//  MENU GLUT
//
//
// **********************************************************************
// Função callback chamada para gerenciar eventos do mouse
void CriaMenu();

void GerenciaMouse(int button, int state, int x, int y)
{
    if (button == GLUT_RIGHT_BUTTON)
        if (state == GLUT_DOWN)
            CriaMenu();
    glutPostRedisplay();
}

// Gerenciamento do menu principal

void MenuPrincipal(int op)
{
}

// Gerenciamento do menu com as opções das amostragem

void MenuFuncoes(int op)
{
    pdi.algAtual = op;
    switch(op)
    {
        case 0: pdi.CopiaImagem(); break;
        case 1: pdi.ConvertToGrayScale(); break;
        case 2: pdi.ConvertBlackAndWhite(128); break;
        case 3: pdi.GreenChannel(); break;
        case 4: pdi.ZoomOut(2); break;
        case 5: pdi.Thumbnail(100,100); break;
    }
    glutPostRedisplay();
}

// Criacao do Menu

void CriaMenu()
{
    int menu,submenu[3];

    submenu[0] = glutCreateMenu(MenuFuncoes);
    glutAddMenuEntry("Copia Imagem",0);
    glutAddMenuEntry("Escala de Cinza",1);
    glutAddMenuEntry("Branco e Preto",2);
    glutAddMenuEntry("Green Channel",3);

    submenu[1] = glutCreateMenu(MenuFuncoes);
    glutAddMenuEntry("Zoom out",4);
    glutAddMenuEntry("Thumbnail",5);

    menu = glutCreateMenu(MenuPrincipal);
    glutAddSubMenu("Quantização",submenu[0]);
    glutAddSubMenu("Amostragem",submenu[1]);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
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
    //glutFullScreen();

    glutDisplayFunc ( display );
    glutReshapeFunc ( reshape );
    glutKeyboardFunc ( keyboard );
    glutSpecialFunc ( arrow_keys );
    glutMouseFunc( GerenciaMouse );

    glutMainLoop ( );
    return 0;
}


