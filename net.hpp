#pragma once
#include <sstream>

namespace net {

using namespace std;

void connect(const string& addr, int port);
void sendRaw(const string& data);

string getLine();

inline istringstream getLineS() {
	return istringstream(getLine());
}

inline void addAll(ostream&) {}

template<class T, class...A>
inline void addAll(ostream& os, const T& t, const A&... args) {
	os << ' ' << t;
	addAll(os, args...);
}

template<class...A>
inline void send(const string& msg, const A&... data) {
	ostringstream oss;
	oss<<msg;
	addAll(oss,data...);
	oss<<'\n';
	sendRaw(oss.str());
}

} // namespace net
