#pragma once
#include <iostream>
#include <vector>
#include "CHero.h"
#include "CRayo.h"
#include "CEnemigo.h"
#include "Cvidas.h"

class CControladora
{
private:
	int windowWidth;
	int windowHeight;
	bool visible;
	CCorazon* objvida;
	int vidas;
	int puntos;
	Jugador* objHero1;
	vector<CRayo*> vectrayo;
	vector<CRayo*> vectaliado;
	vector<CEnemigo*>vecdragon;

public:
	~CControladora() {
		for (CRayo* rayo : vectrayo)
		{
			delete rayo;
		}
		vectrayo.clear();
	};

	CControladora(int windowWidth, int windowHeight) {
		//srand(time(NULL));
		visible = false;
		this->windowWidth = windowWidth;
		this->windowHeight = windowHeight;
		objHero1 = new Jugador();
		objvida = new CCorazon();
		vidas = 0;
		puntos = 0;
		for (int i = 0; i < 4; i++) { vecdragon.push_back(new CEnemigo()); }


	}; 
	void dibujarhero1(Graphics^ g) {
		objHero1->dibujar(g);
	}
	void agregarrayo() {
		vectrayo.push_back(new CRayo(objHero1));
	}
	void agregaraliado() {
		for (int i = 0; i < 4; i++)
		{
			vectaliado.push_back(new CRayo(objHero1));
		    vectaliado[i]->sety((20 + rand() % (480 - 20 + 1)));
		}
	}
	void animacionrayo(Graphics^ g) {
		for (int i = 0; i < vectrayo.size(); i++) {
			vectrayo[i]->mover(g);
			vectrayo[i]->dibujar(g);
			if (vectrayo[i]->pasoElLimite(g))
			{
				vectrayo[i]->setdx(0);
				vectrayo.erase(vectrayo.begin() + i);
			}
		}
	}
	void animacionaliado(Graphics^ g) {
		for (int i = 0; i < vectaliado.size(); i++) {
			vectaliado[i]->mover(g); 
			vectaliado[i]->mover(g);
			vectaliado[i]->dibujar(g);
			if (vectaliado[i]->pasoElLimite(g))
			{
				vectaliado[i]->setdx(0);
				vectaliado.erase(vectaliado.begin() + i);
			}
		}
	}
	void animacionDragon(Graphics^ g)
	{
		for (int i = 0; i < vecdragon.size(); i++)
		{

			vecdragon.at(i)->dibujar(g);
			vecdragon.at(i)->movervirus(g);
		}

		for (int i = 0; i < vecdragon.size(); i++)
		{
			if (vecdragon.at(i)->getx() + vecdragon.at(i)->getancho() < 0)
				vecdragon.at(i)->setvisible(false);
		}
	}
	void animacionvidas(Graphics^ g) {
		objvida->setvidas(vidas);
		objvida->dibujar(g);
		objvida->mover(g);
	}
	
	void moverhero1(Graphics^ g, char tecla) {
		objHero1->moverh1(g, tecla);
	}
	//Colisiones
	void colisiones_dragon_hero(Graphics^ g)
	{
		//crear si son menor a 3 los virus
		if (vecdragon.size() < 3)
			vecdragon.push_back(new CEnemigo());

		for (int i = 0; i < vecdragon.size(); i++) {
			if (vecdragon.at(i)->getRectangle().IntersectsWith(objHero1->getRectangle()))
			{
				vidas++;
				vecdragon.at(i)->setvisible(false);

			}
		}


	}
	void colisiones_rayo_dragon(Graphics^ g)
	{
		for (int i = 0; i < vectrayo.size(); i++) {
			for (int j = 0; j < vecdragon.size(); j++) {
				if (vectrayo.at(i)->determinarcolision(vecdragon.at(j)->getRectangle()))
				{
					vectrayo.at(i)->setvisible(false);
					vecdragon.at(j)->setvisible(false);
					puntos += 10;
				}
			}
		}
	}
	void colisiones_aliado_dragon(Graphics^ g)
	{
		for (int i = 0; i < vectaliado.size(); i++) {
			for (int j = 0; j < vecdragon.size(); j++) {
				if (vectaliado.at(i)->determinarcolision(vecdragon.at(j)->getRectangle()))
				{
					vectaliado.at(i)->setvisible(false);
					vecdragon.at(j)->setvisible(false);
					puntos += 10;
				}
			}
		}
	}
	void superpoder(int momento) {
		switch (momento)
		{
		case 1:
			for (int i = 0; i < vectaliado.size(); i++)
			{
				vectaliado.at(i)->setdx(35);
			}
			break;
		case 2:
			for (int i = 0; i < vectrayo.size(); i++)
			{
				vectrayo.at(i)->setdx(10);
			}
			break;
		}
	}

	void eliminar(Graphics^ g) {
		for (int i = 0; i < vectrayo.size(); i++)
			if (!vectrayo.at(i)->getvisible())
				vectrayo.erase(vectrayo.begin() + i);

		for (int i = 0; i < vectaliado.size(); i++)
			if (!vectaliado.at(i)->getvisible()) 
				vectaliado.erase(vectaliado.begin() + i); 

		for (int i = 0; i < vecdragon.size(); i++)
			if (!vecdragon.at(i)->getvisible())
				vecdragon.erase(vecdragon.begin() + i);

		for (int i = 0; i < vectaliado.size(); i++)
		{
			if (vectaliado.at(i)->gety() > g->VisibleClipBounds.Width)
				vectaliado.erase(vectaliado.begin() + i);
		}
		for (int i = 0; i < vectrayo.size(); i++)
		{
			if (vectrayo.at(i)->gety() > g->VisibleClipBounds.Width)
				vectrayo.erase(vectrayo.begin() + i);
		}
		for (int j = 0; j < vecdragon.size(); j++)
			if (!vecdragon.at(j)->getvisible())
				vecdragon.erase(vecdragon.begin() + j);
	}

	int getpuntos() { return puntos; }
	bool terminar()
	{
		if (vidas >=3) {
			return true;
		}
		return false;
	}
	bool ganar() {

		if (puntos>=100) {
			return true;
		}

		return false;
	}
	void setVisibleHero2(short tipo) {
		switch (tipo)
		{
		case 1:
			objHero1->setvisible(false);
			break;
		case 2:
			objHero1->setvisible(true);
			break;
		}
	}
};