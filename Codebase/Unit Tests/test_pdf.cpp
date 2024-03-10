#include"test_pdf.h"

void testing_pdf::testPDF() const {
	testLogNorm();
	std::cout << "All testcases passed." << std::endl;
}

void testing_pdf::testLogNorm() const {
	pdf test1;
	assert(test1.lognormal(1, 0, 1) == 1 / sqrt(2 * test1.pi));
}