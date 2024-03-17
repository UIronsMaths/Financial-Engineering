#pragma once
#include<iostream>
#include<cassert>
#include"../priceByFDM.h"

class testing_fdmPrice {
public:
	void testFDMPrice();
private:
	void testVanilla();
	void testBarrier();
};