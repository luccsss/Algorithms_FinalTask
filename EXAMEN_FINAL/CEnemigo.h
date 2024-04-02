#pragma once
#include "CMovil.h"
class CEnemigo :public CMovil
{
private:
	int direccion;
public:
	~CEnemigo() {};
	CEnemigo() :CMovil(1)
	{
		direccion = 1;
		Bitmap^ img;
		img = gcnew Bitmap("Imagenes//enemigo.png");
		ancho = img->Width/4;
		alto = img->Height/4;
		iteraX = 0;
		iteraY = 1;
		iteraXMax = 2;
		delete img;
		dx = 3 + rand() % ((7 + 1) - 3);
		dy = 3 + rand() % ((7 + 1) - 3);
		velocidad = 3 + rand() % ((5 + 1) - 3);
		visible = true;
		x = 1080;
		y = (20 + rand() % (420 - 20 + 1));
	}
	void dibujar(Graphics^ g)
	{
		Bitmap^ img;
		img = gcnew Bitmap("Imagenes//enemigo.png");
		//parte del sprite que se va a dibujar
		Rectangle areaSpriteADibujar = Rectangle(iteraX * ancho, iteraY * alto, ancho, alto);
		//area del personaje en la pantalla
		//getRectangle() es un metodo de la clase Personaje
		g->DrawImage(img, getRectangle(), areaSpriteADibujar, GraphicsUnit::Pixel);
		//retangulo colisionador
		g->DrawRectangle(gcnew Pen(Color::BlueViolet, 3.0f), getRectangle());
		delete img;

	}
	void movervirus(Graphics^ g) {
		switch (direccion)
		{
		case 1:
			//horizontal
			dy = 0;
			x -= dx * velocidad;
			iteraY = 1;
			iteraX++;
			if (iteraX >= iteraXMax) iteraX = 0;
			if (x <= 12)
			{
				direccion = 2;
			}
			break;
		case 2:
			x += dx * velocidad;
			iteraY = 2;
			iteraX++;
			if (iteraX >= iteraXMax) iteraX = 0;
			if (x >= g->VisibleClipBounds.Width - ancho)
			{
				direccion = 1;
			}
			break;
		default:
			break;
		}
    }
};