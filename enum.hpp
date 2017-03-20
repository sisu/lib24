#pragma once

#include <iostream>
#include <sstream>
#include <vector>

#define ENUM(type, ...) enum class type { __VA_ARGS__ }; \
	std::vector<std::string> type##_names_gen() { \
		std::istringstream ss(#__VA_ARGS__); std::string s; std::vector<std::string> v; \
		while(ss>>s) { \
			if(s.back()==',')s.erase(s.end()-1); \
			v.push_back(s); \
		} \
		return v; \
	} \
	std::vector<std::string> type ## _names = type##_names_gen(); \
	std::ostream& operator<<(std::ostream& o, const type& x) {return o<<type##_names[int(x)];} \
	std::istream& operator>>(std::istream& is, type& x) { \
		std::string s; is>>s; \
		for(size_t i=0; i<type##_names.size(); ++i) {\
			if (s == type##_names[i]) {x=type(i); return is;} \
		} \
		std::cerr << s << " is not " #type " ; valid: " #__VA_ARGS__ << std::endl; \
		abort(); \
	}
