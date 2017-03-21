#include "check.hpp"

int main() {
	int x=1, y=2, z=3;
	CHECK_EQ(x,y)<<"lol "<<z;
}
