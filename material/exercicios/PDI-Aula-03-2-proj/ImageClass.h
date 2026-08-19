// *****************************************************************************************
//  ImageClassNEW2.h
// *****************************************************************************************
#include <GL\gl.h>
#include <string>
using namespace std;

#define uchar unsigned char

class ImageClass
{

protected:
	int posX, posY;
	float zoomH, zoomV;
	unsigned char *data;
	unsigned int sizeX, sizeY;

public:

	double Tamanho;
	ImageClass(void);
	ImageClass(int sizeX, int sizeY);

	// arquivo
	bool Load(string);
    void LoadFrom(string diretorio, string nome);
	void Save(char *);
	void CopyTo(ImageClass *i);
	void Clear();
	void Delete(void);

	// desenho
	void Display(void);
	void DrawPixel(int x, int y, uchar r, uchar g, uchar b);
	void DrawLineH(int y, int x1, int x2, uchar r, uchar g, uchar b);
	void DrawLineV(int x, int y1, int y2, uchar r, uchar g, uchar b );
	void ReadPixel(GLint x, GLint y, uchar &r, uchar &g, uchar &b);

	double GetPointIntensity(int x, int y);
	int getSizeX() { return sizeX; };
	int getSizeY() { return sizeY; };
	float GetZoomH() { return zoomH; };
	float GetZoomV() { return zoomV; };
	void SetZoomH(float H) { zoomH = H; };
	void SetZoomV(float V) { zoomV = V; };

	unsigned char *GetImagePtr();
	void Realloc(int sizeX, int sizeY);
	void setPos(int X, int Y);
	void setSize(int X, int Y);

	void DrawBox(int x1,int y1,int x2,int y2,unsigned char r, unsigned char g, unsigned char b);
    void DrawLine(int x0,int y0,int x1, int y1,unsigned char r, unsigned char g, unsigned char b  );

    // Diogenes
    int size();
	unsigned char getPixel(GLint x, GLint y);
	void setPixel(GLint x, GLint y, unsigned char cor);
	void setPixel(GLint x, GLint y, unsigned char r, unsigned char g, unsigned char b);
    int getposX() { return posX; };
	int getposY() { return posY; };
	void Resize(int,int);
	bool Inside(int x, int y);

	unsigned char GetLuminancia(int x, int y);
	unsigned char GetMatiz(int x, int y);
	unsigned char GetSaturacao(int x, int y);
};
