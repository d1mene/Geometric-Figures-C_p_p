#include "Triangle.h"

#include <cmath>
#include "Support.h"

const std::string TRIANGLE_NAME = "TRIANGLE";

const std::string INVALID_TRIANGLE = "ERROR: impossible to construct Triangle";
const std::string INVALID_SCALE = "ERROR: too small scale coefficient for triangle";


Triangle::Triangle() : a_(0, 0), b_(0, 1), c_(1, 0), center_(getTriangleCenter()), ab_(a_.getDistance(b_)), ac_(a_.getDistance(c_)),
bc_(b_.getDistance(c_)) {};

Triangle::Triangle(Point a, Point b, Point c) : a_(a), b_(b), c_(c), center_(getTriangleCenter()), ab_(a_.getDistance(b_)),
ac_(a_.getDistance(c_)), bc_(b_.getDistance(c_)) 
{
	if (!this->isTriangle()) {
		throw INVALID_TRIANGLE;
	}
};

Triangle::Triangle(const Triangle& triangle) {

	a_ = triangle.a_;
	b_ = triangle.b_;
	c_ = triangle.c_;
	center_ = triangle.center_;

	ab_ = triangle.ab_;
	bc_ = triangle.bc_;
	ac_ = triangle.ac_;

}

Triangle::Triangle(Triangle&& triangle) noexcept: a_(triangle.a_), b_(triangle.b_), c_(triangle.c_), 
					center_(triangle.center_), ab_(triangle.ab_),ac_(triangle.ac_), bc_(triangle.bc_) 
{
	triangle.a_ = Point();
	triangle.b_ = Point();
	triangle.c_ = Point();
	triangle.center_ = Point();

	triangle.ab_ = 0;
	triangle.bc_ = 0;
	triangle.ac_ = 0;
}


void Triangle::setA(Point a)
{
	a_ = a;
	if (!isTriangle()) {
		throw INVALID_TRIANGLE;
	}
}

void Triangle::setB(Point b)
{
	b_ = b;
	if (!isTriangle()) {
		throw INVALID_TRIANGLE;
	}
}

void Triangle::setC(Point c)
{
	c_ = c;
	if (!isTriangle()) {
		throw INVALID_TRIANGLE;
	}
}

Point Triangle::getA() const {
	return a_;
}

Point Triangle::getB() const {
	return b_;
}

Point Triangle::getC() const {
	return c_;
}
Point Triangle::getTriangleCenter() const {
	return Point((a_.getX() + b_.getX() + c_.getX()) / 3, (a_.getY() + b_.getY() + c_.getY()) / 3);
}

double Triangle::getAB() const {
	return ab_;
}

double Triangle::getBC() const {
	return bc_;
}

double Triangle::getAC() const {
	return ac_;
}

bool Triangle::isTriangle() const {
	return (ab_ < ac_ + bc_) && (ac_ < ab_ + bc_) && (bc_ < ab_ + ac_);
}

double Triangle::getPerimeter() const {
	return ab_ + bc_ + ac_;
}

void Triangle::swap(Triangle& triangle) noexcept {
	std::swap(a_, triangle.a_);
	std::swap(b_, triangle.b_);
	std::swap(c_, triangle.c_);
	std::swap(center_, triangle.center_);

	std::swap(ab_, triangle.ab_);
	std::swap(bc_, triangle.bc_);
	std::swap(ac_, triangle.ac_);
}

double Triangle::getArea() const {
	return std::sqrt(this->getPerimeter() / 2 * (this->getPerimeter() / 2 - this->getAB())
		* (this->getPerimeter() / 2 - this->getBC()) * (this->getPerimeter() / 2 - (*this).getAC()));
}

FrameRectangle Triangle::getFrameRectangle() const {

	double maxX = max(a_.getX(), b_.getX(), c_.getX());
	double minX = min(a_.getX(), b_.getX(), c_.getX());
	double maxY = max(a_.getY(), b_.getY(), c_.getY());
	double minY = min(a_.getY(), b_.getY(), c_.getY());

	double frameRectangleWidth = maxX - minX;
	double frameRectangleHeight = maxY - minY;

	Point frameRectangleCenter(minX + frameRectangleWidth / 2, minY + frameRectangleHeight / 2);
	return FrameRectangle(frameRectangleWidth, frameRectangleHeight, frameRectangleCenter);
}

void Triangle::move(double k) {
	a_.move(k);
	b_.move(k);
	c_.move(k);
	center_.move(k);
}

void Triangle::move(double k, double p) {
	a_.move(k, p);
	b_.move(k, p);
	c_.move(k, p);
	center_.move(k, p);
}

void Triangle::move(Point newCenter) {
	double shiftX = newCenter.getX() - center_.getX();
	double shiftY = newCenter.getY() - center_.getY();

	center_ = newCenter;
	a_.move(shiftX, shiftY);
	b_.move(shiftX, shiftY);
	c_.move(shiftX, shiftY);
}

void Triangle::scale(double k) {
	if (std::abs(k) < std::numeric_limits<double>::epsilon()) {
		throw INVALID_SCALE;
	}

	Point newAPoint(center_.getX() + k * (a_.getX() - center_.getX()), center_.getY() + k * (a_.getY() - center_.getY()));
	Point newBPoint(center_.getX() + k * (b_.getX() - center_.getX()), center_.getY() + k * (b_.getY() - center_.getY()));
	Point newCPoint(center_.getX() + k * (c_.getX() - center_.getX()), center_.getY() + k * (c_.getY() - center_.getY()));

	Triangle scaledTriangle(newAPoint, newBPoint, newCPoint);

	swap(scaledTriangle);
}

Triangle* Triangle::clone() const {
	return new Triangle(*this);
}

std::string Triangle::getName() const {
	return TRIANGLE_NAME;
}

void Triangle::print(std::ostream& out) const {
	out << *this;
}

bool Triangle::operator==(const Triangle& triangle) const {
	return a_ == triangle.a_ && b_ == triangle.b_ && c_ == triangle.c_;
}

bool Triangle::operator<(const Triangle& triangle) const {
	return this->getArea() < triangle.getArea();
}

void Triangle::operator += (double k) {
	a_ = a_ + k;
	b_ = b_ + k;
	c_ = c_ + k;
}

Triangle& Triangle::operator=(const Triangle& triangle) {
	if (this != &triangle) {
		Triangle tempTriangle(triangle);
		swap(tempTriangle);
	}
	return *this;
}

Triangle& Triangle::operator=(Triangle&& triangle) noexcept {
	if (this != &triangle) {
		swap(triangle);

		triangle.a_ = triangle.b_ = triangle.c_ = triangle.center_ = Point();
		triangle.ab_ = triangle.bc_ = triangle.ac_ = 0;
	}
	return *this;
}


std::istream& operator >> (std::istream& in, Triangle& triangle) {
	Point a, b, c;

	in >> a >> b >> c;

	Triangle temp(a, b, c);
	triangle.swap(temp);

	return in;
}

std::ostream& operator << (std::ostream& out, const Triangle& triangle) {
	out << std::fixed << std::setprecision(1);

	FrameRectangle tempFrameRectangle = triangle.getFrameRectangle();

	return (out << triangle.getName() << " " << triangle.getA() << " " << triangle.getB() << " " << triangle.getC()
		<< '\n'  << "Area: " << triangle.getArea() << '\n' << "Frame Points: " << tempFrameRectangle.getLowerLeftPoint() << " "
		<< tempFrameRectangle.getHigherRightPoint() << '\n' << "Frame height: " << tempFrameRectangle.getHeight()
		<< '\n' << "Frame width: " << tempFrameRectangle.getWidth() << '\n');
}