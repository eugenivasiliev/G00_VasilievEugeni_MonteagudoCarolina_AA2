#include "ReadDoc.h"
#include <iostream>
#include <fstream>
#include <sstream>

ReadDoc::ReadDoc(const std::string& fileName) : m_fileName(fileName) {}

bool ReadDoc::readData() {
	std::string fileName = "config.txt";
	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cout << "Error";
		return false;
	}


	char separadores;
	file >> m_width >> separadores >> m_height >> separadores; //1a linea del txt
	file >> m_numPPaleta >> separadores >> m_numPPDesblock >> separadores; //2a linea del txt
	file >> m_numBosque >> separadores >> m_numBDesblock >> separadores; //3a linea del txt

	file.close();
}

Datos ReadDoc::getinfoData() const {
	Datos dato;
	dato.width = m_width;
	dato.height = m_height;
	dato.numPPaleta = m_numPPaleta;
	dato.numPPDesblock = m_numPPDesblock;
	dato.numBosque = m_numBosque;
	dato.numBDesblock = m_numBDesblock;
	return dato;
}

ReadDoc::~ReadDoc() {}