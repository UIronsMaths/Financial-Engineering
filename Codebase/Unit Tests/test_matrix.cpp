#include"test_matrix.h"

void testing_matrix::testMatrix() {
	testGetSet();
	testOperators();
	testLU();
	testThomas();
	testTranspose();
	testDet();
	testDiaDom();
	std::cout << "All testcases passed." << std::endl;
}
void testing_matrix::testGetSet() {

	//
	// Test Case 1: Correctness test.
	//
	matrix test1(3, 3);
	assert(test1.get(0, 0) == 0);
	test1.set(0, 0, 3);
	assert(test1.get(0, 0) == 3);
	matrix test2({ {1,0,0},{0,1,0},{0,0,1} });
	assert(test2.get(0, 0) == 1 && test2.get(2, 2) == 1 && test2.get(2, 1) == 0);
}
void testing_matrix::testOperators() {

	//
	// Test Case 1: Correctness test.
	//
	matrix m1({ { 1,0,0 }, { 0,2,0 }, { 0,0,3 } });
	matrix m2(3, 3);
	m2.set(0, 0, 4.0);
	m2.set(1, 1, 5.0);
	m2.set(2, 2, 6.0);

	matrix test = m1 + m2;
	std::vector<std::vector<double>> res = { {5, 0, 0}, {0, 7, 0},{0, 0, 9} };
	assert(test.m_data == res);

	test = m2 - m1;
	res = { {3, 0, 0}, {0, 3, 0},{0, 0, 3} };
	assert(test.m_data == res);
	
	test = m2 + 3;
	res = { {7, 3, 3}, {3, 8, 3},{3, 3, 9} };
	assert(test.m_data == res);
	
	test = m2 - 1;
	res = { {3, -1, -1}, {-1, 4, -1},{-1, -1, 5} };
	assert(test.m_data == res);
	
	test = m2 * 2;
	res = { {8, 0, 0}, {0, 10, 0},{0, 0, 12} };
	assert(test.m_data == res);
	
	test = m2 - m1;
	res = { {3, 0, 0}, {0, 3, 0},{0, 0, 3} };
	assert(test.m_data == res);

	test = m1;
	test += 1;
	res = { {2, 1, 1}, {1, 3, 1},{1, 1, 4} };
	assert(test.m_data == res);

	test = m1;
	test -= 1;
	res = { {0, -1, -1}, {-1, 1, -1},{-1, -1, 2} };
	assert(test.m_data == res);

	test = m1;
	test += m2;
	res = { {5, 0, 0}, {0, 7, 0},{0, 0, 9} };
	assert(test.m_data == res);

	test = m2;
	test -= m1;
	res = { {3, 0, 0}, {0, 3, 0},{0, 0, 3} };
	assert(test.m_data == res);

	test = m1;
	test *= 2;
	res = { {2, 0, 0}, {0, 4, 0},{0, 0, 6} };
	assert(test.m_data == res);

	test = m1 * m2;
	res = { {4, 0, 0}, {0, 10, 0},{0, 0, 18} };
	assert(test.m_data == res);

	assert(m1 != m2);
	test = m1;
	assert(m1 == test);
}
void testing_matrix::testLU() {

	//
	// Test Case 1: Correctness test.
	//
	int size = 3;
	matrix A(size, size); // Square matrix

	// Fill matrix A with values
	A.set(0, 0, 4);
	A.set(0, 1, 3);
	A.set(0, 2, 2);
	A.set(1, 0, 2);
	A.set(1, 1, 1);
	A.set(1, 2, 3);
	A.set(2, 0, 3);
	A.set(2, 1, 4);
	A.set(2, 2, 1);

	// Initialize matrices L and U
	matrix L(size, size);
	matrix U(size, size);

	// Perform LU decomposition
	A.LU_decomposition(L, U);
	std::vector<std::vector<double>> res1 = { {1,0,0},{0.5,1,0},{0.75,-3.5,1} };
	std::vector<std::vector<double>> res2 = { {4,3,2},{0,-0.5,2},{0,0,6.5} };
	assert(L.m_data == res1 && U.m_data == res2);
	matrix test = L * U;
	assert(test == A);
}
void testing_matrix::testThomas() {

	//
	// Test Case 1: Correctness test.
	//
	ThomasAlgorithm ta({ 0,0 }, { 1, 1, 1 }, { 0, 0 }, { 6, 8, 18 });
	std::vector<double> test = ta.solve();
	std::vector<double> res = { 6.0,8.0,18.0 };
	assert(test == res);
}
void testing_matrix::testTranspose() {

	//
	// Test case 1: Correctness test.
	//
	std::vector<std::vector<double>> test = { {1.0,2.0}, {3.0,4.0} };
	matrix A = test;
	A.transpose();
	std::vector<std::vector<double>> res = { {1.0,3.0}, {2.0,4.0} };
	assert(A == res);
}
void testing_matrix::testDet() {

	//
	// Test Case 1: Correctness test.
	//
	std::vector<std::vector<double>> test = { {1.0,2.0}, {3.0,4.0} };
	matrix A = test;
	assert(A.determinant() == -2);
}
void testing_matrix::testDiaDom() {

	//
	// Test Case 1: Correctness test.
	// Expected: True.
	//
	std::vector<std::vector<double>> m = { {3,1,1}, {2,6,3}, {9,0,-11} };
	matrix mat = m;
	assert(mat.diagDominant() == True);

	//
	// Test Case 2: Correctness test.
	// Expected: False.
	//
	m = { {3,-2,1}, {2,4,3}, {9,0,-11} };
	mat = m;
	assert(mat.diagDominant() == False);
}