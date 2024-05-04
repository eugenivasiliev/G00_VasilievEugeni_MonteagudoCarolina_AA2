#include "PlayerView.h"
#include "Ash.h"
#include <iostream>

PlayerView::PlayerView(Map& map, Player& ash, Datos& datos) : m_map(map), m_ashX(0), m_ashY(0), m_viewWidth(0), m_viewHeight(0){
	m_ashX = ash.getX();
	m_ashY = ash.getY();
	m_viewWidth = datos.width / 2;
	m_viewHeight = datos.height / 2;
	for (int i = 0; i < m_viewHeight; ++i) {
		for (int j = 0; j < m_viewWidth; ++j) {
			m_view[i][j] = ' ';
		}
	}
}

void PlayerView::update(Datos& datos) {
	// Calcular el desplazamiento de la vista para mantener al jugador en el centro
	int startX = m_ashX -  m_viewWidth/ 2;
	int startY = m_ashY - m_viewHeight / 2;
	int endX = startX + m_viewWidth;
	int endY = startY + m_viewHeight;

	for (int i = 0; i < m_viewHeight; ++i) {
		for (int j = 0; j < m_viewWidth; ++j) {
			int mapX = startX + j;
			int mapY = startY + i;

			// Verificar si la posición está dentro de los límites del mapa
			if (InMapLimits(mapX, mapY)) {
				// Verificar si hay una pared en esta posición del mapa
				if (isWall(mapX, mapY)) {
					m_view[i][j] = 'X';
				}
				else {
					m_view[i][j] = m_map.getSymbol(mapX, mapY);
				}
			}
			else {
				m_view[i][j] = '-';
			}
		}
	}
}

void PlayerView::draw() const {
	//Dibujar vista del mapa con el jugador centrado
	for (int i = 0; i < m_viewWidth + 2; ++i) {
		std::cout << ".";
	}
	std::cout << std::endl;

	for (int i = 0; i < m_viewHeight; ++i) {
		std::cout << ".";
		for (int j = 0; j < m_viewWidth; ++j) {
			if (i == m_ashY && j == m_ashX) {
				std::cout << "A"; // Dibujar jugador
			}
			else {
				char symbolo = m_map.getSymbol(j, i);
				std::cout << symbolo; // Dibujar mapa
			}
			
		}
		std::cout << "." << std::endl;
	}
	//Dibujar el borde inferior del mapa
	for (int i = 0; i < m_viewWidth + 2; ++i) {
		std::cout << ".";
	}
}

void PlayerView::updatePositionPlayer(Player& ash) {
	m_ashX = ash.getX();
	m_ashY = ash.getY();
}


bool PlayerView::InMapLimits(int x, int y) const {
	return x >= 0 && x < m_map.getWidth() && y >= 0 && y < m_map.getHeight();
}

bool PlayerView::isWall(int x, int y) const {
	return m_map.getSymbol(x, y) == 'X';
}
