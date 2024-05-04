#pragma once
#ifndef ASH_H
#define ASH_H


class Map;

//empieza en el pueblo paleta
class Ash
{
public:
	Ash();
	Ash(int inicioX, int inicioY); //constructor con cordenadas iniciales
	int getY() const;
	int getX() const;
	void setPosition(int x, int y);
	//void move(int direX, int direY);

private:
	int m_x;
	int m_y;
};

#endif

