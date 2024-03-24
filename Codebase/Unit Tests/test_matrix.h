#pragma once
#include<cassert>
#include"../matrix.h"

class testing_matrix {
public:
	void testMatrix();
private:
	void testGetSet();
	void testOperators();
	void testLU();
	void testThomas();
	void testTranspose();
	void testDet();
	void testDiaDom();
};