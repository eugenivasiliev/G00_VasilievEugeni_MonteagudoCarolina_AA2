#pragma once
#ifndef ASH_H
#define ASH_H
#include <Windows.h>

class Map;

//empieza en el pueblo paleta
class Player
{
public:
	Player();
	Player(int inicioX, int inicioY); //constructor con cordenadas iniciales
	int getX() const;
	int getY() const;
	void setPosition(int x, int y);
	void move(short direction);

private:
	int m_x;
	int m_y;
};

#endif

