#pragma once

#include <cstdlib>
#include <iostream>
#include <sstream>

struct CheckFail {
	~CheckFail() {
		std::cerr<<"ERROR: "<<oss.str()<<std::endl;
		abort();
	}

	template<class T>
	CheckFail& operator<<(const T& t) {
		oss<<t;
		return *this;
	}

	std::ostringstream oss;
};

#define CHECK_OP(a,b,op) while(!(a op b)) CheckFail()\
	<<"Expected "<<#a<<" ("<<a<<") " \
	<<#op<<' '<<#b<<" ("<<b<<")\n"

#define CHECK_EQ(a,b) CHECK_OP(a,b,==)
#define CHECK_GT(a,b) CHECK_OP(a,b,>)
#define CHECK_LT(a,b) CHECK_OP(a,b,<)
#define CHECK_GE(a,b) CHECK_OP(a,b,>=)
#define CHECK_LE(a,b) CHECK_OP(a,b,<=)
#define CHECK(x) while(!(x)) CheckFail()<<"Expected "<<#x;
