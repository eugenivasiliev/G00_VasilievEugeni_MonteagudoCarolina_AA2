#include <iostream>
#include <Windows.h>
#include "ReadDoc.h"
#include "Map.h"
#include "Ash.h"
#include "Game.h"

std::pair<int, int> operator+ (const std::pair<int, int> &l, const std::pair<int, int> &r) {
	return std::make_pair(l.first + r.first, l.second + r.second);
}

void operator+= (std::pair<int, int> &l, const std::pair<int, int> &r) {
	l = l + r;
}

int main() {
	Game game;
	/*ReadDoc reader("config,txt");
	if (reader.readData()) {
		Datos datos = reader.getinfoData();

		Map map(datos); // Crear objeto de la clase Map
		map.draw(); //dibujar mapa

		Ash ash(12,17); // Inicializar a Ash en el centro del mapa

		PlayerView playerView(map, ash, datos);

		playerView.update(datos);
		playerView.updatePositionPlayer(ash);
		playerView.draw(); // Dibujar el mapa inicial con la posición de Ash

		//std::cout << std::endl;


		// Ejemplo de movimiento de Ash (hacia arriba)
		/*ash.setPosition(ash.getX(), ash.getY() - 1);
		map.update(ash);
		map.draw();*/

		// Ejemplo de movimiento de Ash (hacia la derecha)
		/*ash.setPosition(20, 17);
		playerView.updatePositionPlayer(ash);
		map.draw();
	}*/

	while (game.GameLoop());
	return 0;
}