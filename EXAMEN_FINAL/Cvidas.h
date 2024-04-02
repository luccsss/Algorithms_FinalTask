#pragma once
#include "CMovil.h"
class CCorazon : public CMovil
{
private:
public:
	~CCorazon() {};
	CCorazon() : CMovil(0.5) {
		Bitmap^ img = gcnew Bitmap("Imagenes//vidas.png");
		ancho = img->Width;
		alto = img->Height / 4;
		visible = true;
		x = 1;
		y = 5;
		iteraX = 0;
		iteraY = 0;
		delete img;
	};
	void dibujar(Graphics^ g) {
		Bitmap^ img = gcnew Bitmap("Imagenes//vidas.png");
		Rectangle areaSpriteADibujar = Rectangle(iteraX * ancho, iteraY * alto, ancho, alto);
		g->DrawImage(img, getRectangle(), areaSpriteADibujar, GraphicsUnit::Pixel);
		delete img;
	}
	void mover(Graphics^ g) {
		iteraY++;
	}
	void setvidas(int itera_Y) {
		iteraY = itera_Y;

	}
	int getvidas() {
		return iteraY;
	}

};