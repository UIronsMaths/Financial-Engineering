#pragma once
#include<cassert>
#include<iostream>
#include"../vanillaOptions.h"

class testing_options {
public:
	void testOptions();
private:
	void testVanilla();
	void testBarrier();
};