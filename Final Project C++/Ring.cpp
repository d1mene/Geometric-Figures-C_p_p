#include "Ring.h"

const std::string RING_NAME = "RING";

const double PI = 3.141592;

const std::string INPUT_ERROR = "ERROR: invalid input for Ring";
const std::string RADIUS_ERROR = "ERROR: radiuses must be positive";
const std::string THIN_RING_ERROR = "ERROR: ring is too thin";
const std::string RADIUS_WARNING = "WARNING: the outer radius of ring should be passed first";
const std::string INVALID_SCALE = "ERROR: too small scale coefficient for ring";

Ring::Ring() : center_(Point(0, 0)), radius1_(2), radius2_(1) {};
Ring::Ring(Point center, double r1, double r2) : center_(center) {
	if (r1 < std::numeric_limits<double>::epsilon() || r2 < std::numeric_limits<double>::epsilon()) {
		throw RADIUS_ERROR;
	}
	if (std::abs(r1 - r2) < std::numeric_limits<double>::epsilon()) {
		throw THIN_RING_ERROR;
	}
	if (r1 > r2) {
		radius1_ = r1;
		radius2_ = r2;
	}
	else {
		std::cerr << RADIUS_WARNING << '\n';
		radius1_ = r2;
		radius2_ = r1;
	}
};

Ring::Ring(const Ring& otherRing) {
	radius1_ = otherRing.radius1_;
	radius2_ = otherRing.radius2_;
	center_ = otherRing.center_;
}

Ring::Ring(Ring&& otherRing) noexcept {
	radius1_ = otherRing.radius1_;
	radius2_ = otherRing.radius2_;
	center_ = otherRing.center_;

	otherRing.radius1_ = 0;
	otherRing.radius2_ = 0;
	otherRing.center_ = Point();
}


double Ring::getOuterRadius() const {
	return radius1_;
}
double Ring::getInnerRadius() const {
	return radius2_;
}

Point Ring::getCenter() const {
	return center_;
}

void Ring::setOuterRadius(double r1) {
	Ring tempRing(this->center_, r1, this->radius2_);
	this->swap(tempRing);
}
void Ring::setInnerRadius(double r2) {
	Ring tempRing(this->center_, this->radius1_, r2);
	this->swap(tempRing);
}

void Ring::setCenter(Point newCenter) {
	center_ = newCenter;
}

void Ring::swap(Ring& newRing) {
	std::swap(radius1_, newRing.radius1_);
	std::swap(radius2_, newRing.radius2_);
	std::swap(center_, newRing.center_);
}

double Ring::getArea() const {
	return PI * (radius1_ * radius1_ - radius2_ * radius2_);
}
	
FrameRectangle Ring::getFrameRectangle() const {
	return FrameRectangle(2 * radius1_, 2 * radius1_, center_);
}

void Ring::move(double k) {
	center_ += k;
}

void Ring::move(double k, double p) {
	center_.move(k, p);
}

void Ring::move(Point newCenter) {
	center_ = newCenter;
}

void Ring::scale(double k) {
	if (std::abs(k) < std::numeric_limits<double>::epsilon()) {
		throw INVALID_SCALE;
	}
	Ring scaledRing(center_, radius1_ * std::abs(k), radius2_ * std::abs(k));

	swap(scaledRing);
}

Ring* Ring::clone() const {
	return new Ring(*this);
}

std::string Ring::getName() const {
	return RING_NAME;
}

void Ring::print(std::ostream& out) const {
	out << *this;
}

Ring& Ring::operator=(const Ring& otherRing) {
	if (this != &otherRing) {
		Ring tempRing(otherRing);
		swap(tempRing);
	}
	return *this;
}
Ring& Ring::operator=(Ring&& otherRing) noexcept {
	if (this != &otherRing) {
		swap(otherRing);

		otherRing.radius1_ = otherRing.radius2_ = 0;
		otherRing.center_ = Point();
	}
	return *this;
}


std::istream& operator >> (std::istream& in, Ring& ring) {
	Point center;
	double r1 = 0.0, r2 = 0.0;

	if (!(in >> center >> r1 >> r2)) {
		throw INPUT_ERROR;
	}

	Ring tempRing(center, r1, r2);

	ring.swap(tempRing);

	return in;
}



std::ostream& operator << (std::ostream& out, const Ring& ring) {
	out << std::fixed << std::setprecision(1);

	FrameRectangle tempFrameRectangle = ring.getFrameRectangle();

	return (out << ring.getName() << " " << ring.getCenter() << "\nOuter radius: " << ring.getOuterRadius()
		<< "\nInner radius: " << ring.getInnerRadius() << '\n' << "Area: " << ring.getArea()
		<< '\n' << "Frame Points: " << tempFrameRectangle.getLowerLeftPoint() << " " << tempFrameRectangle.getHigherRightPoint() 
		<< '\n' << "Frame height: " << tempFrameRectangle.getHeight() << '\n' << "Frame width: " << tempFrameRectangle.getWidth() << '\n');
}