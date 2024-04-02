#pragma once
#include "CMovil.h"
#include "CHero.h"
class CRayo :public CMovil {
private:

public:

	CRayo(Jugador* soldado) : CMovil(0.8) {
		Bitmap^ img = gcnew Bitmap("Imagenes//rayo.png");
		ancho = img->Width/5;
		alto = img->Height;
		x = soldado->getx() + (soldado->getancho() / 1);
		y = soldado->gety() + (soldado->getalto() / 4);
		dx = 10;
		iteraX = 0;
		iteraY = 0;
		visible = true;
		delete img;
	};
	~CRayo() {};
	void dibujar(Graphics^ g) {
		Bitmap^ img = gcnew Bitmap("Imagenes//rayo.png");
		Rectangle porcion = Rectangle(iteraX*ancho, iteraY * alto, ancho, alto);
		Rectangle zoomSection = Rectangle(x, y, ancho * zoom, alto * zoom);
		g->DrawImage(img, zoomSection, porcion, GraphicsUnit::Pixel);
		//g->DrawRectangle(gcnew Pen(Color::Brown, 3.0f), getRectangle());
		delete img;
	}
	void mover(Graphics^ g) {
		iteraX++;
		x += dx;
		if (iteraX >= 4) iteraX = 0;
	}
	bool pasoElLimite(Graphics^ g)
	{
		return (x + dx + ancho * zoom > g->VisibleClipBounds.Width);
	}
};