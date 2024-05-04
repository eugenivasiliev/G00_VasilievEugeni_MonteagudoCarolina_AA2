#pragma once
#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include "Map.h"

class PlayerView
{
public:
	PlayerView(Map& map, Ash& ash, Datos& datos);
	void update(Datos& datos); //actualiza la vista del jugador
	void draw() const;
	void updatePositionPlayer(Ash& ash);

private:
	static const int VIEW_WIDTH = 50; // Ancho de la vista del jugador
	static const int VIEW_HEIGHT = 50; // Altura de la vista del jugador
	char m_view[VIEW_HEIGHT][VIEW_WIDTH]; // Vista del jugador
	Map& m_map;
	int m_ashX;
	int m_ashY;
	int m_viewWidth;
	int m_viewHeight;

	bool InMapLimits(int x, int y) const;
	bool isWall(int x, int y) const;
};

#endif

