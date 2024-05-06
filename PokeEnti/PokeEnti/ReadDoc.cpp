#include "ReadDoc.h"
#include <iostream>
#include <fstream>
#define DIVIDER ';'

ReadDoc::ReadDoc(const std::string& fileName) : m_fileName(fileName) {}

bool ReadDoc::readData(Data &data_) {
	std::string fileName = "config.txt";
	std::ifstream file(fileName);

	if (!file.is_open()) {
		std::cout << "ERROR in opening config.txt" << std::endl;
		return false;
	}

	int mapWidth, mapHeight,
		palletTownStartPokemon, palletTownCondition,
		forestStartPokemon, forestCondition;

	char divider = DIVIDER;
	file >> mapWidth >> divider;
	if(!assertFormat(divider)) return false;
	file >> mapHeight >> divider;
	if(!assertFormat(divider)) return false;
	file >> palletTownStartPokemon >> divider;
	if (!assertFormat(divider)) return false;
	file >> palletTownCondition >> divider;
	if (!assertFormat(divider)) return false;
	file >> forestStartPokemon >> divider;
	if (!assertFormat(divider)) return false;
	file >> forestCondition;

	file.close();

	data_ = { mapWidth, mapHeight, 
		palletTownStartPokemon, palletTownCondition, 
		forestStartPokemon, forestCondition };

	return true;
}

bool ReadDoc::assertFormat(const char &divider) {
	if (divider != DIVIDER) {
		std::cout << "ERROR in config.txt format (wrong divider)" << std::endl;
		return false;
	}
	return true;
}

ReadDoc::~ReadDoc() {}