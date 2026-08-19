// **********************************************************************
//  BmpLib1.cpp
//  Produced by ...
//  Incremented by Diogenes Furlan
//
//  Le bitmaps 24 bits e 8 bits
//  Grava bitmaps 24 bits
// **********************************************************************

#include <cstdio>
#include <cstdlib>
#include "BmpLib2.h"

#define BMP_TYPE 19778      //0x4D42
#define BMP_OFFSET 54       //0x36
#define BMP_HEADERSIZE 40   //0x28

// estruturas

typedef struct
{
    unsigned short int fileid;
    unsigned long filesize;
    unsigned short int reserved1;
    unsigned short int reserved2;
    unsigned long imgoffset;
} bmpinfoheader ;

typedef struct
{
    unsigned long headersize;
    long imgwidth;
    long imgheight;
    unsigned short int numplanes;
    unsigned short int pixeldepth;
    unsigned long compression;
    unsigned long bitmapsize;
    long hresolution;
    long vresolution;
    unsigned long usedcolors;
    unsigned long significantcolors;
} imginfoheader;

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char unused;
} bmppalete ;

// variaveis

static unsigned char *red, *green, *blue;
static int width, height;

static imginfoheader imgheader;
static bmpinfoheader bmpheader;
static bmppalete palete[256];

// **********************************************************************
//
//
// **********************************************************************
int get_BMP_size(char *name, unsigned int &sizeX, unsigned int &sizeY)
{
    FILE *fptr;

    if((fptr=fopen(name,"rb"))==NULL)
    {
        printf("\nFile not found.");
        return 1;
    }
    else
    {
        fread(&bmpheader.fileid,2,1,fptr);
        fread(&bmpheader.filesize,4,1,fptr);
        fread(&bmpheader.reserved1,2,1,fptr);
        fread(&bmpheader.reserved2,2,1,fptr);
        fread(&bmpheader.imgoffset,4,1,fptr);
        fread(&imgheader,sizeof(imgheader),1,fptr);

        if ((bmpheader.fileid != BMP_TYPE) ||
//           (bmpheader.imgoffset != 54) ||
                (imgheader.headersize != 40) )
//           (imgheader.numplanes != 1) ||
//           (imgheader.pixeldepth != 24) ||
//           (imgheader.compression != 0))
        {
            printf("\nError: Invalid bitmap image.");
            fclose(fptr);
            return 1;
        }
        else
        {
            sizeX = imgheader.imgwidth;
            sizeY = imgheader.imgheight;
            fclose(fptr);
            return 0;
        }
    }
}
// **********************************************************************
//
//
// **********************************************************************
bool BMP::load(const char* bmp, unsigned int &sizeX, unsigned int &sizeY)
{
    FILE *fptr;
    long x,y;
    unsigned int padbytes=0;

    if((fptr=fopen(bmp,"rb"))==NULL)
    {
        printf("\nFile not found.");
        return false;
    }
    else
    {
        fread(&bmpheader.fileid,2,1,fptr);   // 14 bytes
        fread(&bmpheader.filesize,4,1,fptr);
        fread(&bmpheader.reserved1,2,1,fptr);
        fread(&bmpheader.reserved2,2,1,fptr);
        fread(&bmpheader.imgoffset,4,1,fptr);
        fread(&imgheader,sizeof(imgheader),1,fptr);  // 40 bytes

        if (    (bmpheader.fileid != BMP_TYPE) ||
                //(bmpheader.imgoffset != 54) ||   //1078  0x436
                (imgheader.headersize != 40) ||
                (imgheader.numplanes != 1) ||
                //(imgheader.pixeldepth != 24) ||  //8
                (imgheader.compression != 0)
           )
        {
            printf("\nError: Invalid bitmap image.");
            return false;
        };


        red = (unsigned char *) malloc(imgheader.imgheight * imgheader.imgwidth);
        green = (unsigned char *) malloc(imgheader.imgheight * imgheader.imgwidth);
        blue = (unsigned char *) malloc(imgheader.imgheight * imgheader.imgwidth);

        if (red == NULL || green == NULL || blue == NULL)
        {
            printf("\nOut of memory.");
            return false;
        }

        if( imgheader.pixeldepth == 24 )
        {
            printf("24 bits. ");

            padbytes = (imgheader.imgwidth*3)%4;
            if(padbytes!=0)
                padbytes = 4-padbytes;

            for(x=imgheader.imgheight-1; x>-1; x--)
            {
                for(y=0; y<imgheader.imgwidth; y++)
                {
                    blue[(x*imgheader.imgwidth+y)] = getc(fptr);
                    green[(x*imgheader.imgwidth+y)] = getc(fptr);
                    red[(x*imgheader.imgwidth+y)] = getc(fptr);
                }
                for(y=0; y<(long)padbytes; y++)
                    getc(fptr);
            }
        }
        else if( imgheader.pixeldepth == 8 )
        {
            printf("8 bits. ");

            padbytes = (imgheader.imgwidth)%4;
            if(padbytes!=0)
                padbytes = 4-padbytes;

            // le palete
            int num_posicoes = (bmpheader.imgoffset - 54) / 4;
            for(int i=0; i<num_posicoes; i++)
            {
                fread(&palete[i].blue,1,1,fptr);
                fread(&palete[i].green,1,1,fptr);
                fread(&palete[i].red,1,1,fptr);
                fread(&palete[i].unused,1,1,fptr);
            }
            // atualiza dados
            unsigned char dado;
            for(x=imgheader.imgheight-1; x>-1; x--)
            {
                for(y=0; y<imgheader.imgwidth; y++)
                {
                    dado = getc(fptr);
                    blue[(x*imgheader.imgwidth+y)] = palete[dado].blue;
                    green[(x*imgheader.imgwidth+y)] = palete[dado].green;
                    red[(x*imgheader.imgwidth+y)] = palete[dado].red;
                }
                for(y=0; y<(long)padbytes; y++)
                    getc(fptr);
            }
        }
        else
        {
            printf("\nError: Size of bitmap image non tratable: %d bits.", imgheader.pixeldepth);
            fclose(fptr);
            return false;
        }
        sizeX = width = imgheader.imgwidth;
        sizeY = height = imgheader.imgheight;
        fclose(fptr);
    }
    return true;
}
// **********************************************************************
//
//
// **********************************************************************
void BMP::copy_to_ImageClass(unsigned char* data)
{
    long x,y, i;
    for(x=0; x<width; x++)
    {
        for(y=0; y<height; y++)
        {
            unsigned long addr;
            i = (y*width+ x);
            addr = (unsigned long)( (height-y-1) *(width)* 3 + x * 3 );
            data[addr++] = red[i];
            data[addr++] = green[i];
            data[addr] = blue[i];
        }
    }
}
// **********************************************************************
//
//
// **********************************************************************
void BMP::free_memory()
{
    free(red);
    free(green);
    free(blue);
    red = green = blue = NULL;
}
// **********************************************************************
//
//
// **********************************************************************
bool BMP::copy_from_ImageClass(unsigned char* data)
{
    long x,y, i;
    long tam = height*width;

    red = (unsigned char *) malloc(tam);
    green = (unsigned char *) malloc(tam);
    blue = (unsigned char *) malloc(tam);
    if (red == NULL || green == NULL || blue == NULL)
    {
        printf("\nOut of memory - CopyImageClassToBmp.");
        return false;
    }

    for(x=0; x<width; x++)
    {
        for(y=0; y<height; y++)
        {
            unsigned long addr;
            i = (y*width+ x);
            addr = (unsigned long)( (height-y-1) *(width)* 3 + x * 3 );
            red[i] = data[addr++];
            green[i] = data[addr++];
            blue[i] = data[addr];
        }
    }
    return true;
}
// **********************************************************************
//
//
// **********************************************************************
bool BMP::save(const char* bmp, unsigned char* data, unsigned int sizeX, unsigned int sizeY)
{
    FILE *fptr;
    long x,y;
    unsigned int padbytes=0;

    // copia os dados da ImageClass para o BMP
    width = sizeX;
    height = sizeY;
    if (!BMP::copy_from_ImageClass(data))
        return false; // erro
// ----

    bmpheader.fileid = BMP_TYPE;
    bmpheader.filesize = width * height + 54;
    bmpheader.reserved1 = 0;
    bmpheader.reserved2 = 0;
    bmpheader.imgoffset = 54;
    imgheader.headersize = 40;
    imgheader.imgwidth = width;
    imgheader.imgheight = height;
    imgheader.numplanes = 1;
    imgheader.pixeldepth = 24;
    imgheader.compression = 0;
    imgheader.bitmapsize = width * height;
    imgheader.hresolution = 0;
    imgheader.vresolution = 0;
    imgheader.usedcolors = 0;
    imgheader.significantcolors = 0;

    if((fptr=fopen(bmp,"wb"))==NULL)
    {
        printf("\nCould not write to file.");
        return false;
    }
    else
    {
        fwrite(&bmpheader.fileid,2,1,fptr);
        fwrite(&bmpheader.filesize,4,1,fptr);
        fwrite(&bmpheader.reserved1,2,1,fptr);
        fwrite(&bmpheader.reserved2,2,1,fptr);
        fwrite(&bmpheader.imgoffset,4,1,fptr);
        fwrite(&imgheader,sizeof(imgheader),1,fptr);


        padbytes = (imgheader.imgwidth*3)%4;
        if(padbytes!=0)
            padbytes = 4-padbytes;
        for(x=imgheader.imgheight-1; x>-1; x--)
        {
            for(y=0; y<imgheader.imgwidth; y++)
            {
                putc(blue[(x*imgheader.imgwidth+y)],fptr);
                putc(green[(x*imgheader.imgwidth+y)],fptr);
                putc(red[(x*imgheader.imgwidth+y)],fptr);
            }
            for(y=0; y< (long)padbytes; y++)
                putc(0,fptr);
        }
        fclose(fptr);
    }

    BMP::free_memory();
    return true;
}
// **********************************************************************
//
//
// **********************************************************************
//void copy_BMP_to_ImageClassOK(unsigned char* data)
//{
//   long count = 0;
//   long x,y, i;
//   for(x=0;x<height;x++)
//   {
//       for(y=0;y<width;y++)
//       {
//            unsigned long addr;
//            i = (x*width + y);
//            addr = (unsigned long)( (height-x-1) *(width)* 3 + y * 3 );
//            data[addr++] = red[i];
//            data[addr++] = green[i];
//            data[addr] = blue[i];
//       }
//    }
//}


