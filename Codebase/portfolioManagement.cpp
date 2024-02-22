#include"portfolioManagement.h"

void portfolio::readFile() {
	std::ifstream fileStream;
	const std::string& filename = "portfolio.txt";
	std::ifstream& is = (fileStream.open(filename), fileStream);
	if (!is) {
		throw std::runtime_error("Error in porfolioManagement::readFile. Cannot open input stream.\n");
		return;
	}

	std::string type;
	int size;
	double strike;
	double expiry;
	int rowcount = 0;

	m_positions.clear();
	m_optionData.clear();
	while (fileStream >> type >> size >> strike >> expiry) {
		if (!fileStream) { break; }
		if (type == "C") {
			m_positions.push_back({ std::make_unique<euroCall>(strike, expiry), size });
		}
		else {
			m_positions.push_back({ std::make_unique<euroPut>(strike, expiry), size });
		}
		m_optionData.push_back({ strike, expiry });
		rowcount++;
	}
	fileStream.close();
	std::cout << rowcount << std::endl;
}

void portfolio::promptUser() {
	std::cout << "Please enter S0: ";
	std::cin >> m_S;
	std::cout << "Please enter volatility: ";
	std::cin >> m_vol;
	std::cout << "Please enter RF rate: ";
	std::cin >> m_r;
}

void portfolio::output() {
	std::cout << std::endl;
	// Table header
	std::cout << std::setw(10) << std::right << "Option"
		<< std::setw(15) << std::right << "Price"
		<< std::setw(15) << std::right << "Delta"
		<< std::setw(15) << std::right << "Gamma"
		<< std::setw(15) << std::right << "Theta" << std::endl;

	// Ruled line
	std::cout << std::setw(75) << std::setfill('=') << "=" << std::setfill(' ') << std::endl;


	// Table data
	int i = 1;
	double portPrice = 0;
	double portDelta = 0;
	double portGamma = 0;
	double portTheta = 0;
	for (auto& position : m_positions) {
		double price = position.first->priceByBSFormula(m_S, m_vol, m_r) * position.second;
		double delta = position.first->deltaByBSFormula(m_S, m_vol, m_r) * position.second;
		double gamma = position.first->gammaByBSFormula(m_S, m_vol, m_r) * position.second;
		double theta = position.first->thetaByBSFormula(m_S, m_vol, m_r) * position.second;
		portPrice += price;
		portDelta += delta;
		portGamma += gamma;
		portTheta += theta;
		std::cout << std::setw(10) << std::setprecision(2) << std::right << i
			<< std::setw(15) << std::fixed << std::setprecision(4) << std::right << price
			<< std::setw(15) << std::fixed << std::setprecision(4) << std::right << delta
			<< std::setw(15) << std::fixed << std::setprecision(4) << std::right << gamma
			<< std::setw(15) << std::fixed << std::setprecision(4) << std::right << theta << std::endl;
		i++;
	}

	// Ruled line
	std::cout << std::setw(75) << std::setfill('=') << "=" << std::setfill(' ') << std::endl;

	//Portfolio totals
	std::cout << std::setw(10) << std::right << "Total"
		<< std::setw(15) << std::fixed << std::setprecision(4) << std::right << portPrice
		<< std::setw(15) << std::fixed << std::setprecision(4) << std::right << portDelta
		<< std::setw(15) << std::fixed << std::setprecision(4) << std::right << portGamma
		<< std::setw(15) << std::fixed << std::setprecision(4) << std::right << portTheta << std::endl;
}

void portfolio::managePortfolio() {
	readFile();
	promptUser();
	output();
}