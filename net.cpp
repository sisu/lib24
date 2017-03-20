#include <boost/asio.hpp>
#include <string>
#include <sstream>
using namespace std;

namespace net {
namespace {
boost::asio::ip::tcp::iostream net;
}

void connect(const string& addr, int port) {
	ostringstream oss;
	oss<<addr<<':'<<port;
	net.connect(oss.str());
}

void sendRaw(const string& data) {
	net<<data;
	net.flush();
}

string getLine() {
	string s;
	getline(net, s);
	return s;
}

} // namespace net
