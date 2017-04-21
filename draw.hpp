#pragma once
#include <utility>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

using namespace std;

template<class T, class...A>
inline unique_ptr<T> MakeUnique(A&&... args) {
	return unique_ptr<T>(new T(args...));
}

struct Vec2 {
	double data[2];

	Vec2() {
		data[0]=data[1]=0;
	}
	Vec2(double x, double y) {
		data[0]=x;
		data[1]=y;
	}
	double operator[](int i)const{return data[i];}
};

struct Range {
	double from = 1e100;
	double to = -1e100;

	void set(double f, double t) {
		from = f;
		to = t;
	}
	void join(Range r) {
		from = min(from, r.from);
		to = max(to, r.to);
	}
	void scale(double x) {
		double mid = 0.5*(from+to);
		double s = x*0.5*size();
		from = mid-s;
		to = mid+s;
	}
	double size() const {
		return to - from;
	}
};
inline ostream& operator<<(ostream& o, const Range& r) {
	return o<<'['<<r.from<<','<<r.to<<']';
}

struct Rect {
	Range ranges[2];

	Rect() {}
	Rect(double x0, double x1, double y0, double y1) {
		ranges[0].set(x0,x1);
		ranges[1].set(y0,y1);
	}
	Rect(sf::FloatRect r) {
		ranges[0].set(r.left, r.left+r.width);
		ranges[1].set(r.top, r.top+r.height);
	}

	Range& operator[](int i) {return ranges[i];}
	const Range& operator[](int i) const {return ranges[i];}

	void join(const Rect& r) {
		for(int i=0; i<2; ++i) ranges[i].join(r.ranges[i]);
	}
	void scale(double x) {
		for(int i=0; i<2; ++i) ranges[i].scale(x);
	}

	sf::FloatRect toSF() const {
		return sf::FloatRect(ranges[0].from, ranges[1].from,
				ranges[0].size(), ranges[1].size());
	}
};
inline ostream& operator<<(ostream& o, const Rect& r) {
	return o<<'['<<r[0]<<','<<r[1]<<']';
}

struct Color {
	double r=0,g=0,b=0,a=0;

	Color() {}
	Color(double r,double g,double b,double a=1):r(r),g(g),b(b),a(a){}
#if 0
	Color(const string& s) {
	}
#endif
	Color& operator=(const string& s) {
		return *this;
	}

	sf::Color toSF() const {
		return sf::Color(255*r,255*g,255*b,255*a);
	}
};

struct Shape;
struct Circle;
struct Quad;
struct Text;

struct HasShapes {
	vector<unique_ptr<Shape>> shapes;

	template<class...A>
	Circle& circle(A&&... args) {
		return add<Circle>(args...);
	}
	template<class...A>
	Quad& quad(A&&... args) {
		return add<Quad>(args...);
	}
	template<class...A>
	Text& text(A&&... args) {
		return add<Text>(args...);
	}

	template<class T, class...A>
	T& add(A&&... args) {
		auto c = MakeUnique<T>(forward<A>(args)...);
		auto p = c.get();
		shapes.push_back(move(c));
		return *p;
	}

	Rect getBounds() const;
};

struct Drawable {
	Drawable(unique_ptr<sf::Shape> shape): shape(move(shape)) {}
	Drawable(unique_ptr<sf::Text> text): text(move(text)) {}

	unique_ptr<sf::Shape> shape;
	unique_ptr<sf::Text> text;
};

struct Shape: HasShapes {
	Color color_;
	Color outlineColor_;
	double outlineSize_ = 0;

	virtual Rect bounds() const = 0;

	void draw(sf::RenderTarget& win) const;

	Shape& color(const Color& c) {
		color_ = c;
		return *this;
	}
	Shape& outlineColor(const Color& c) {
		outlineColor_ = c;
		return *this;
	}
	Shape& outlineSize(double size) {
		outlineSize_ = size;
		return *this;
	}

protected:
	virtual Drawable shape() const = 0;

private:
	template<class S>
	void drawObj(sf::RenderTarget& win, S& shape) const;
};

struct Circle: public Shape {
	Vec2 center_;
	double radius_;

	explicit Circle(Vec2 c): center_(c), radius_(0) {}
	Circle(Vec2 c, double r): center_(c), radius_(r) {}
	Circle(double x, double y): center_(x,y), radius_(0) {}

	Rect bounds() const override {
		Rect r;
		for(int i=0; i<2; ++i) {
			r[i].from = center_[i] - radius_;
			r[i].to = center_[i] + radius_;
		}
		return r;
	}

	Circle& radius(double r) {
		radius_ = r;
		return *this;
	}

protected:
	Drawable shape() const override {
		auto c = MakeUnique<sf::CircleShape>(radius_);
		c->setPosition(center_[0] - radius_, center_[1] - radius_);
		return {move(c)};
	}
};

struct Quad: public Shape {
	Rect rect;

	Quad(double x0, double x1, double y0, double y1):
		rect(x0,x1,y0,y1) {}

	Rect bounds() const override {
		return rect;
	}

protected:
	Drawable shape() const override {
		auto s = MakeUnique<sf::RectangleShape>(
				sf::Vector2f(rect[0].size(), rect[1].size()));
		s->setPosition(rect[0].from, rect[1].from);
		return {move(s)};
	}
};

struct Text: public Shape {
	string text_;
	Vec2 pos_;

	Text(string text): text_(move(text)) {}

	Text& pos(double x, double y) {
		pos_ = Vec2(x,y);
		return *this;
	}
	Text& pos(Vec2 v) {
		pos_ = v;
		return *this;
	}

	static sf::Font& getFont();

	Rect bounds() const override {
		sf::Text text(text_, getFont());
		return text.getLocalBounds();
	}

protected:
	Drawable shape() const override {
		auto s = MakeUnique<sf::Text>(text_, getFont());
		s->setPosition(pos_[0], pos_[1]);
		return {move(s)};
	}
};

struct Frame: HasShapes {
	~Frame();
};

