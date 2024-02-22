#pragma once
#include"../Defunct/euroOption.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<vector>

class portfolio {
public:
	void managePortfolio();
private:
	void readFile();
	void promptUser();
	void output();
	std::vector<std::pair<std::unique_ptr<euroOption>, int>> m_positions;
	std::vector<std::pair<double, double>> m_optionData;
	double m_S;
	double m_vol;
	double m_r;
};