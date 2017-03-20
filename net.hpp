#pragma once
#include <sstream>

void connect(const string& addr, int port);
void init(int argc, const char** argv);
void sendRaw(const string& data);
string getLine();

void addAll(ostream&) {}

template<class T, class...A>
void addAll(ostream& os, const T& t, const A&... args) {
	os << ' ' << t;
	addAll(os, args...);
}

template<class...A>
void send(const string& msg, const A&... data) {
	ostringstream oss;
	oss<<msg;
	addAll(oss,data...);
	oss<<'\n';
//	sendRaw(oss.str());
}
