TARGET=test

run:
	g++ -std=c++17 test.cpp -o ${TARGET} -lgtest -lgtest_main; ./${TARGET}

