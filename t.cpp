#if 1
#include <iostream>
#include <sstream>
#include <vector>
//#include <boost/asio.hpp>
using namespace std;
//boost::asio::ip::tcp::iostream net;

enum class E {
	PELLE,
	HERMANNI
};
const string E_names[] = {"PELLE", "HERMANNI"};
ostream& operator<<(ostream& o, const E& e) {
	o<<E_names[(int)e];
	return o;
}
#endif

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

ENUM(T, HEDGE, FUND);

#if 0
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

void asd() {
	send("asd",1,5.0);
}
#endif

int main() {
	E e = E::PELLE;
	cout<<e<<'\n';

	T t = T::HEDGE;
	cout<<t<<'\n';
	cin>>t;
	cout<<"k "<<t<<'\n';
}
