#pragma once

#include <cstdlib>
#include <iostream>
#include <sstream>

struct CheckFail {
	CheckFail(const char* file, int line) {
		oss<<file<<":"<<line<<": ERROR: ";
	}
	~CheckFail() {
		std::cerr<<oss.str()<<std::endl;
		abort();
	}

	template<class T>
	CheckFail& operator<<(const T& t) {
		oss<<t;
		return *this;
	}

	std::ostringstream oss;
};

#define CHECK_FAIL CheckFail(__FILE__, __LINE__)

#define CHECK_OP(a,b,op) while(!(a op b)) CHECK_FAIL\
	<<"Expected "<<#a<<" ("<<a<<") " \
	<<#op<<' '<<#b<<" ("<<b<<")\n"

#define CHECK_EQ(a,b) CHECK_OP(a,b,==)
#define CHECK_GT(a,b) CHECK_OP(a,b,>)
#define CHECK_LT(a,b) CHECK_OP(a,b,<)
#define CHECK_GE(a,b) CHECK_OP(a,b,>=)
#define CHECK_LE(a,b) CHECK_OP(a,b,<=)
#define CHECK(x) while(!(x)) CHECK_FAIL<<"Expected "<<#x;
