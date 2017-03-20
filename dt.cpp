#include "draw.hpp"
#include <cmath>

void draw() {
	Frame f;
//	f.circle(1,2).radius(1.5).color({"red"});
	auto& r = f.quad(0, 10, 0, 10);
	r.outlineColor({1,1,1});
	r.outlineSize(1);
	for(int i=0; i<10; ++i) {
		for(int j=0; j<10; ++j) {
			auto& s = f.circle(0.5*i+j,sqrt(3)/2*i).radius(0.5);
			s.color({0.2,0.0,0.2});
			s.outlineColor({1,1,0});
			s.outlineSize(0.01);
			if (i==1 && j==1) {
				auto& x = s.quad(0,1,0,1);
				x.color({1,0,1});
				auto& y = s.quad(2,3,0,1);
				y.color({1,1,0});
			} else if (i==2) {
				char c = 'A'+j;
				s.text(string(1+j%3,c)).color({1,1,1});
			}
		}
	}
//	auto& x = f.quad(0,5,0,5);
//	x.color({1,0,1});
}

int main() {
#if 0
	auto c = draw.circle(1,2);
	c->radius = 1.5;
	c->color = "red";
#else
#endif
	draw();

	sf::sleep(sf::seconds(1));
}
