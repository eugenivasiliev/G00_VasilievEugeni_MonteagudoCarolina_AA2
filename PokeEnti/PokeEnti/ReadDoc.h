#pragma once
#ifndef READDOC_H
#define READDOC_H

#include "Datos.h"
#include <string>



class ReadDoc
{
public:
	ReadDoc(const std::string& fileName);
	bool readData();
	Datos getinfoData() const;

	~ReadDoc();

private:
	std::string m_fileName;
	int m_width;
	int m_height;
	int m_numPPaleta;
	int m_numPPDesblock;
	int m_numBosque;
	int m_numBDesblock;
};

#endif