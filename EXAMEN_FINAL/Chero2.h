#pragma once
#include "CMovil.h"
#include "CHero.h"
class Jugador2 : public CMovil {
public:
	~Jugador2() {};
	Jugador2(int _x,int _y) : CMovil(3) {
		Bitmap^ img = gcnew Bitmap("Imagenes//hero2.png"); // llama la imagen
		ancho = img->Width / 3;
		alto = img->Height / 4;
		x = _x;
		y = _y;
		dx = dy = 5;
		visible = false;
		iteraX = 2;
		iteraY = 2;
	};
	// metodos 
	void dibujar(Graphics^ g) {
		if (visible)
		{
			Bitmap^ img = gcnew Bitmap("Imagenes//hero2.png"); // llama la imagen
			Rectangle areaSpriteADibujar = Rectangle(iteraX * ancho, iteraY * alto, ancho, alto);
			g->DrawImage(img, getRectangle(), areaSpriteADibujar, GraphicsUnit::Pixel);
		}
		else
		{

		}
	}
	void moverh2(Graphics^ g, char tecla) {
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
			if (y + dy + alto <= g->VisibleClipBounds.Height - 65) {
				iteraY = 0;
				iteraX++;
				y += dy;
			}break;
		case 'D':
			if (x + dy + ancho <= g->VisibleClipBounds.Width - 50) {
				iteraY = 2;
				iteraX++;
				x += dx;
			}break;
		case 'N':
			iteraX = 0;
			iteraY = 0;
			break;
		}
		if (iteraX >= 3) iteraX = 0; // bucle
	}
};