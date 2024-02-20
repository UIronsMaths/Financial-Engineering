#include"test_pdf.h"

void testing_pdf::testPDF() {
	testLogNorm();
	std::cout << "All testcases passed." << std::endl;
}

void testing_pdf::testLogNorm() {
	pdf test1;
	test1.lognormal(1, 0, 1);
}