#include "Ash.h"

Ash::Ash() : m_x(0), m_y(0){}
Ash::Ash(int inicioX, int inicioY) : m_x(inicioX), m_y(inicioY){}

int Ash::getY() const {
	return m_y;
}

int Ash::getX() const {
	return m_x;
}

void Ash::setPosition(int x, int y) {
	m_x = x;
	m_y = y;
}
//void Ash::move(int direX, int direY) {
//
//}