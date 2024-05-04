#include "Map.h"
#include <iostream>

Map::Map(const Datos& datos) : m_datos(datos){
	for (int i = 0; i < m_datos.height; ++i) {
		for (int j = 0; j < m_datos.width; ++j) {
			m_map[i][j] = ' ';
		}
	}
}


void Map::draw(){
	// Dibujar el mapa y el jugador
	for (int i = 0; i < m_datos.height; ++i) {
		for (int j = 0; j < m_datos.width; ++j) {
			bool isWall = false;
			if (i == m_datos.height / 2 || j == m_datos.width / 2) {
				isWall = true;
			}
			if (isWall) {
				m_map[i][j] = 'X';
			}
			else {
				m_map[i][j] = ' ';
			}
		}
	}
	//para ver como es el mapa
	/*for (int i = 0; i < m_datos.height; ++i) {
		for (int j = 0; j < m_datos.width; ++j) {
			std::cout << m_map[i][j];
		}
		std::cout << std::endl;
	}*/

}


void Map::update() {
	
}

char Map::getSymbol(int x, int y) const {
	return m_map[y][x];
}

int Map::getWidth() const {
	return m_datos.width;
}

int Map::getHeight() const {
	return m_datos.height;
}

