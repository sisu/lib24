#include "enum.hpp"
#include "net.hpp"

ENUM(E, PELLE, HERMANNI);

ENUM(T, HEDGE, FUND);

using namespace std;

void asd() {
	net::send("asd",1,5.0);
}

int main() {
	E e = E::PELLE;
	cout<<e<<'\n';

	T t = T::HEDGE;
	cout<<t<<'\n';
	cin>>t;
	cout<<"k "<<t<<'\n';
}
