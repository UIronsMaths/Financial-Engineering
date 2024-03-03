#pragma once
#include<cassert>
#include<iostream>
#include"../options.h"

class testing_options {
public:
	void testOptions();
private:
	void testVanilla();
	void testBarrier();
};