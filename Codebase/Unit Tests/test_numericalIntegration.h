#pragma once
#include"../numericalIntegration.h"
#include<cassert>
#include"../pdf.h"
#include"../options.h"

class testing_numericalIntegration {
public:
	void testNumInt();
private:
	void testTrapezium();
};