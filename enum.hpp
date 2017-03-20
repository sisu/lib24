#pragma once

#include <iostream>
#include <sstream>
#include <vector>

#define ENUM(type, ...) enum class type { __VA_ARGS__ }; \
	vector<string> type##_names_gen() { \
		istringstream ss(#__VA_ARGS__); string s; vector<string> v; \
		while(ss>>s) { \
			if(s.back()==',')s.erase(s.end()-1); \
			v.push_back(s); \
		} \
		return v; \
	} \
	vector<string> type ## _names = type##_names_gen(); \
	ostream& operator<<(ostream& o, const type& x) {return o<<type##_names[int(x)];} \
	istream& operator>>(istream& is, type& x) { \
		string s; is>>s; \
		for(size_t i=0; i<type##_names.size(); ++i) {\
			if (s == type##_names[i]) {x=type(i); return is;} \
		} \
		cerr << s << " is not " #type " ; valid: " #__VA_ARGS__ << endl; \
		abort(); \
	}
