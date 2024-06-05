#pragma once

#include <string>

struct Data {
	int m_mapWidth, m_mapHeight, 
		m_palletTownStartPokemon, m_palletTownCondition, 
		m_forestStartPokemon, m_forestCondition, m_powerPikachu, 
		m_pokemonHealth, m_mewtwoHealth, m_minTime, m_maxTime;
};

class ReadDoc
{
public:
	ReadDoc(const std::string& fileName);
	bool readData(Data &data_);
	bool assertFormat(const char &divider);
	~ReadDoc();

private:
	std::string m_fileName;
};