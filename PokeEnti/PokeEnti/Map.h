#pragma once
#ifndef MAP_H
#define MAP_H

#include "Datos.h"
#include "Ash.h"


class Map
{
public:
	static const int WIDTH = 100;
	static const int HEIGHT = 100;

	Map(const Datos& datos);// , Ash& ash); //constructor
	void draw(); //dibujar mapa
	void update();
	char getSymbol(int x, int y) const;
	int getWidth() const;
	int getHeight() const;
	/*int m_mapWidth;
	int m_mapHeight;*/

private:
	Datos m_datos;
	char m_map[HEIGHT][WIDTH];
};

#endif