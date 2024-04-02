#pragma once
#include "CMovil.h"
class Jugador : public CMovil {
private:
public:
	~Jugador() {};
	Jugador() : CMovil(1.5) {
		Bitmap ^ img = gcnew Bitmap("Imagenes//hero1.png"); // llama la imagen
		Bitmap ^ img2 = gcnew Bitmap("Imagenes//hero2.png"); // llama la imagen
		ancho = (float(img->Width) / 4); alto = (float(img->Height) / 4);
		x = 12;
		y = 500;
		dx = dy = 5;
		iteraX = 0;
		iteraY = 2;
		visible = true;
	};
	// metodos 
	void dibujar(Graphics^ g) {
		if (visible)
		{
			Bitmap^ img = gcnew Bitmap("Imagenes//hero1.png"); // llama la imagen
			Rectangle areaSpriteADibujar = Rectangle(iteraX * ancho, iteraY * alto, ancho, alto);
			g->DrawImage(img, getRectangle(), areaSpriteADibujar, GraphicsUnit::Pixel);
		}
		else
		{
			Bitmap^ img2 = gcnew Bitmap("Imagenes//hero2.png"); // llama la imagen
			Rectangle areaSpriteADibujar = Rectangle(iteraX * ancho, iteraY * alto, ancho, alto);
			g->DrawImage(img2, getRectangle(), areaSpriteADibujar, GraphicsUnit::Pixel);
		}
	}
	void moverh1(Graphics^ g, char tecla) {
		switch (tecla)
		{
		case 'W':
			if (y - dy >= 50) {
				iteraY = 3;
				iteraX++;
				y -= dy;
			} break;
		case 'A':
			if (x - dx >= 0) {
				iteraY = 1;
				iteraX++;
				x -= dx;
			}break;
		case 'S':
			if (y + dy + alto < g->VisibleClipBounds.Height-30) {
				iteraY = 0;
				iteraX++;
				y += dy;
			}break;
		case 'D':
			if (x + dy + ancho < g->VisibleClipBounds.Width ) {
				iteraY = 2;
				iteraX++;
				x += dx;
			}break;
		case 'N':
			iteraX = 0;
			iteraY = 2;
			break;
		}
		if (iteraX >= 4) iteraX = 0; // bucle
	}
};