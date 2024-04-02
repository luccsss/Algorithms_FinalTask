#pragma once
#include "iostream"

using namespace System::Drawing; // dibujar figuras geomentricas, darles color, etc.
using namespace std;

class CMovil {
protected:
	int x;
	int y;
	int dx;
	int dy;
	int velocidad;
	float ancho;
	float alto;
	int iteraX; // imagenes X
	int iteraY; // imagenes y;
	bool visible;
	float zoom;

	int iteraXMax;
	int iteraYMax;
public:
	CMovil(float zoom) {
		iteraX = 0;
		iteraY = 0;
		this->zoom = zoom;
	};
	~CMovil() {};
	// Polimorfismo
	virtual void dibujar(Graphics^ g)  // para colocar la imagenes (sprites o in) 
	{};
	virtual void mover(Graphics^ g) // para el movimiento de imagenes (sprites o in)
	{};
	// Colision
	bool determinarcolision(Rectangle recenemy) { return getRectangle().IntersectsWith(recenemy); } // colision
	Rectangle getRectangle() { return Rectangle(x, y, ancho * zoom, alto * zoom); } // presentar los valores para la colision
	Rectangle getPostRectangle() { return Rectangle(x + dx * velocidad, y + dy * velocidad, ancho, alto); }
	// Metodos set 
	void setx(int x) { this->x = x; }
	void sety(int y) { this->y = y; }
	void setdx(int dx) { this->dx = dx; }
	void setdy(int dy) { this->dy = dy; }
	void setalto(int alto) { this->alto = alto; }
	void setancho(int ancho) { this->ancho = ancho; }
	void setiterax(int iterax) { this->iteraX = iterax; }
	void setiteray(int iteray) { this->iteraY = iteray; }
	void setvisible(bool visible) { this->visible = visible; }
	void setZoom(int zoom) { this->zoom = zoom; }
	Rectangle setrectangles(int x, int y, int ancho, int alto) { return Rectangle(x, y, ancho, alto); };
	void setiteraY(int v) { iteraY = v; }
	// Metodos get
	int getx() { return x; };
	int gety() { return y; };
	int getdx() { return dx; };
	int getdy() { return dy; };
	int getalto() { return alto; };
	int getancho() { return ancho; };
	int getiterax() { return iteraX; };
	int getiteray() { return iteraY; };
	bool getvisible() { return visible; };
};