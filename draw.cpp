#include "draw.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>

using namespace std;

namespace {

sf::RenderWindow window;
sf::Font font;

sf::Font& loadFont() {
//	bool ok = font.loadFromFile("/usr/share/fonts/TTF/Vera.ttf");
	bool ok = font.loadFromFile("/usr/share/fonts/TTF/DejaVuSans.ttf");
	assert(ok);
	return font;
}

} // namespace

sf::Font& Text::getFont() {
	static sf::Font& f = loadFont();
	return f;
}

Rect HasShapes::getBounds() const {
	Rect bounds;
	for(const auto& shape: shapes) {
		bounds.join(shape->bounds());
	}
	return bounds;
}

template<class S>
void Shape::drawObj(sf::RenderTarget& win, S& s) const {
	s.setFillColor(color_.toSF());
	s.setOutlineColor(outlineColor_.toSF());
	s.setOutlineThickness(outlineSize_);
	win.draw(s);
}

void Shape::draw(sf::RenderTarget& win) const {
	Drawable s = shape();
	if (s.shape) drawObj(win, *s.shape);
	if (s.text) {
#if SFML_VERSION_MAJOR<=2 && SFML_VERSION_MINOR<4
		auto& t = *s.text;
		t.setColor(color_.toSF());
		win.draw(t);
#else
		drawObj(win, *s.text);
#endif
	}

	if (!shapes.empty()) {
		sf::View old = win.getView();
		Rect outerBounds = bounds();
		outerBounds.scale(0.8);
		Rect innerBounds = getBounds();
		sf::View view(innerBounds.toSF());
		sf::FloatRect port = old.getTransform().transformRect(
				outerBounds.toSF());
//		cout<<"orig: "<<port.left<<' '<<port.top<<' '
//			<<port.width<<' '<<port.height<<'\n';
		port = sf::FloatRect(
				0.5f*(port.left + 1),
				0.5f*(1 - (port.top + port.height)),
				0.5f*port.width,
				0.5f*port.height);
//		cout<<"inner "<<innerBounds<<" outer "<<outerBounds<<'\n';
//		cout<<"transformed: "<<port.left<<' '<<port.top<<' '
//			<<port.width<<' '<<port.height<<'\n';
		view.setViewport(port);
		win.setView(view);
		for(const auto& a : shapes) {
			a->draw(win);
		}
		win.setView(old);
	}
}


Frame::~Frame() {
	if (!window.isOpen()) {
		window.create(sf::VideoMode(1024,768), "lib24");
//		window.create(sf::VideoMode(1000,1000), "lib24");
	}
	window.clear();

	Rect bounds = getBounds();
//	cout<<"bounds: "<<bounds<<'\n';
	sf::View view(bounds.toSF());
	window.setView(view);
	for(const auto& shape: shapes) {
		shape->draw(window);
	}

	window.display();
}
